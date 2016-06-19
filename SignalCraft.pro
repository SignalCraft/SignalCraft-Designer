TEMPLATE = subdirs

SUBDIRS += app.pro test.pro
test.pro.depends = app.pro
