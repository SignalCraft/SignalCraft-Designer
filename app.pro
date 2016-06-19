TEMPLATE = subdirs

SUBDIRS += compiler gui
gui.depends = compiler
