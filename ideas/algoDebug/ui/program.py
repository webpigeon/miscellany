from gi.repository import Gtk as gtk

builder = gtk.Builder()
builder.add_from_file("program.glade")

window = builder.get_object("window1")
window.show_all()

gtk.main()
