# -*- coding: cp1250 -*-
import pygtk
pygtk.require('2.0')
import gtk
import os

pics = []


def on_destroy (widget):
    gtk.main_quit()
    return False

def chooser(widget, image):
    dialog = gtk.FileChooserDialog("Open..", None,gtk.FILE_CHOOSER_ACTION_OPEN,(gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN, gtk.RESPONSE_OK))
    dialog.set_default_response(gtk.RESPONSE_OK)

    filter = gtk.FileFilter()
    filter.set_name("Wszystkie pliki")
    filter.add_pattern("*")
    dialog.add_filter(filter)

    filter = gtk.FileFilter()
    filter.set_name("Pliki graficzne")
    filter.add_mime_type("image/png")
    filter.add_mime_type("image/jpeg")
    filter.add_mime_type("image/gif")
    filter.add_pattern("*.png")
    filter.add_pattern("*.jpg")
    filter.add_pattern("*.gif")
    filter.add_pattern("*.tif")
    filter.add_pattern("*.xpm")
    dialog.add_filter(filter)

    response = dialog.run()
    if response == gtk.RESPONSE_OK:
        print 'Wybrano: ', dialog.get_filename()
        pics = [gtk.gdk.pixbuf_new_from_file(dialog.get_filename())]
        image.set_from_pixbuf (pics[0])
        
    elif response == gtk.RESPONSE_CANCEL:
        print 'Nie wybrano pliku'
    dialog.destroy()


def create ():
    window = gtk.Window(gtk.WINDOW_TOPLEVEL)
    window.connect("destroy", on_destroy)

    pics.append (gtk.gdk.pixbuf_new_from_file("python.png"))

    image = gtk.Image()
    image.set_from_pixbuf(pics[0])

    button = gtk.Button ("Wybierz obrazek")
    button.connect("clicked", chooser, image)
 
    vbox = gtk.VBox()
    vbox.pack_start (image)
    vbox.pack_start (button)

    window.add(vbox)
    window.show_all()

create()
gtk.main()
