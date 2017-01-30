
HEADERS += ./LotsOfLinesApp.h \
    ./VisualizationRendererWidget.h \
    ./LoadDataDialog.h
SOURCES += ./LoadDataDialog.cpp \
    ./LotsOfLinesApp.cpp \
    ./main.cpp \
    ./VisualizationRendererWidget.cpp
FORMS += ./LotsOfLinesApp.ui \
    ./LoadDataDialog.ui
RESOURCES += LotsOfLinesApp.qrc

INCLUDEPATH += ../../../DataModel/include
INCLUDEPATH += ../../../RenderingSystem/include
