import pygtk
pygtk.require('2.0')
import gtk
import os



pics = []
clicks = 0
    
def on_destroy (widget):
    gtk.main_quit()
    return False

def button_clicked (widget, image):
    global clicks
    clicks += 1
    image.set_from_pixbuf (pics[clicks % len(pics)])

def create ():
    window = gtk.Window(gtk.WINDOW_TOPLEVEL)
    window.connect("destroy", on_destroy)

    directory = "./"
    files = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]
    for plik in files:
        if plik.endswith(".png") or plik.endswith(".jpg") or plik.endswith(".jpeg"):
           pics.append (gtk.gdk.pixbuf_new_from_file(plik))

    image = gtk.Image()
    image.set_from_pixbuf(pics[0])

    button1 = gtk.Button ("Nastepny obrazek")
    button2 = gtk.Button ("Poprzedni obrazek")
    button1.connect("clicked", button_clicked, image)
    button2.connect("clicked", button_clicked, image)
    
    vbox = gtk.VBox()
    vbox.pack_start (image)
    vbox.pack_start (button1)
    vbox.pack_start (button2)
    
    window.add(vbox)
    window.show_all()

if __name__ == "__main__":
    create()
    gtk.main()
