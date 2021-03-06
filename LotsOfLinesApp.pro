# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = LotsOfLinesApp

# Output dirs
Debug {
    DESTDIR = $$PWD/bin/debug
    MOC_DIR += ./source/GeneratedFiles/debug
    OBJECTS_DIR += "$$PWD/obj/debug"
}
Release {
    DESTDIR = $$PWD/bin/release
    MOC_DIR += ./source/GeneratedFiles/release
    OBJECTS_DIR += "$$PWD/obj/release"
}

QT += core opengl widgets gui
DEFINES += QT_DLL QT_WIDGETS_LIB QT_OPENGL_LIB GLEW_STATIC
INCLUDEPATH += ./source/GeneratedFiles \
    . \
    ./source/GeneratedFiles/Debug

# Library dependencies
LIBS += -L"$$PWD/3rd-party/glew/lib/Release/Win32/" \
    -lopengl32 \
    -lglew32s \
    -lglu32

DEPENDPATH += .
UI_DIR += "$$PWD/source/GeneratedFiles"
RCC_DIR += "$$PWD/source/GeneratedFiles"
include(LotsOfLinesApp.pri)

