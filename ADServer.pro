TEMPLATE = subdirs

SUBDIRS = \
        ADServerLibrary/ADServer \
        ADServerLibrary/3rdParty/qhttp \
        ADServerDemo

ADServerLibrary/ADServer.depends = ADServerLibrary/3rdParty/qhttp
ADServerDemo.depends = ADServerLibrary/ADServer
