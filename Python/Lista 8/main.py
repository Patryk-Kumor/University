import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

import shelve
import datetime

rows = (1, "Jan", "Kowalski", "01.01.2017", "+48 12345678", "jan@kowal.pl")
class Database:
    def __init__(self):
        self.db = shelve.open("storage.db", 'c')    

    def show_contacts(self):
        W=[]
        for keys in self.db:
            One = []
            One += [int(keys)]
            One += list(self.db[keys])
            W += [tuple(One)]
        return W  

    def get(self, ID):
        W = self.db[str(ID)]
        return (W[1],W[0],W[3],W[4])

    def add_person(self, rest):
        i = 0
        for keys in self.db:
            i += 1
        self.db[str(str(i))] = rest
        
    def edit_person(self, ID, rest):
        if str(ID) in self.db:
            self.db[str(str(ID))] = rest
        
    def delete_person(self, ID):
        if str(ID) in self.db:
            print("found")
            del self.db[str(ID)]
            print ("deleted")

    def search_in_db(self, search):
        W=[]
        for keys in self.db:
            One = []
            One += [int(keys)]
            One += list(self.db[keys])
            if str(search) in str(One):
                W += [tuple(One)]
        return W 
  
      
def show(gtk_liststore, rows):
            gtk_liststore.clear()
            for x in rows:
                #print (x)
                gtk_liststore.append(x)    


class App:
    def __init__(self):
        self.database = Database()
        self.to_edit = False
        self.to_edit_ID = -1
        self.builder = Gtk.Builder()
        self.builder.add_from_file("style.glade")
        self.window = self.builder.get_object("Main")
        self.window.show_all()
        self.List_view = self.builder.get_object('List_view')
        self.liststore = self.builder.get_object('liststore')
        self.window2 = self.builder.get_object("Adder")
        self.builder.connect_signals(self)
        show(self.liststore,self.database.show_contacts())
        
    def add_person(self, new_window):
        self.builder.get_object('surname_entry').set_text('')
        self.builder.get_object('name_entry').set_text('')
        self.builder.get_object('phone_entry').set_text('')
        self.builder.get_object('email_entry').set_text('')
        new_window.show_all()
        
    def search_changed(self, searchentry):
        rows = self.database.search_in_db(searchentry.get_text())
        self.liststore.clear()
        for x in rows:
            self.liststore.append(x)   
        
    def edit_window(self, button):
        self.to_edit = True
        treeselection = self.List_view.get_selection()
        (model, tree_iter) = treeselection.get_selected()
        if tree_iter:
            contact_id = model.get_value(tree_iter, 0)
            self.to_edit_ID = contact_id
            surname, name, phone, email = self.database.get(str(contact_id))
            self.builder.get_object('surname_entry').set_text(surname)
            self.builder.get_object('name_entry').set_text(name)
            self.builder.get_object('phone_entry').set_text(phone)
            self.builder.get_object('email_entry').set_text(email)
            self.window2.show_all()
        show(self.liststore,self.database.show_contacts())

    def delete_person(self, button):
        treeselection = self.List_view.get_selection()
        (model, tree_iter) = treeselection.get_selected()
        if tree_iter:
            contact_id = model.get_value(tree_iter, 0)
            self.database.delete_person(str(contact_id))
        show(self.liststore,self.database.show_contacts())

    def submit(self, widget):
        if (not self.to_edit):
            surname = self.builder.get_object('surname_entry').get_text()
            name = self.builder.get_object('name_entry').get_text()
            phone = self.builder.get_object('phone_entry').get_text()
            email = self.builder.get_object('email_entry').get_text()
            date = str(datetime.datetime.now()).split(" ")[0]
            self.database.add_person( (name, surname, str(date), phone, email) )
            show(self.liststore,self.database.show_contacts())
            self.window2.hide()
        else:
            surname = self.builder.get_object('surname_entry').get_text()
            name = self.builder.get_object('name_entry').get_text()
            phone = self.builder.get_object('phone_entry').get_text()
            email = self.builder.get_object('email_entry').get_text()
            date = str(datetime.datetime.now()).split(" ")[0]
            self.database.edit_person( self.to_edit_ID, (name, surname, str(date), phone, email) )
            self.to_edit = False
            show(self.liststore,self.database.show_contacts())
            self.window2.hide()

    def hide_widget(self, widget):
        widget.hide()

    def main_quit(self, widget):
        Gtk.main_quit() 
        
app = App()
Gtk.main()
