
HEADERS += source/LotsOfLinesApp.h \
    source/VisualizationRendererWidget.h \
    source/LoadDataDialog.h \
    source/DataTableModel.h \
    source/LoadingWorker.h \
    source/OptionEditorWidget.h \
    source/PreferencesDialog.h \
    source/DataModel/CSVFileLoader.hpp \
    source/DataModel/DataFileLoader.hpp \
    source/DataModel/DataModel.hpp \
    source/DataModel/DataSet.hpp \
    source/DataModel/IDataLoader.hpp \
    source/DataModel/ProgressMessage.hpp \
    $$PWD/source/RenderingSystem/CollocatedPairedCoordinatesVisualizationMethod.hpp \
    $$PWD/source/RenderingSystem/IRenderer.hpp \
    $$PWD/source/RenderingSystem/IShader.hpp \
    $$PWD/source/RenderingSystem/IVertexBufferObject.hpp \
    $$PWD/source/RenderingSystem/IVisualizationMethod.hpp \
    $$PWD/source/RenderingSystem/OpenGLRenderer.hpp \
    $$PWD/source/RenderingSystem/OpenGLShader.hpp \
    $$PWD/source/RenderingSystem/OpenGLVertexBufferObject.hpp \
    $$PWD/source/RenderingSystem/ParallelCoordinatesVisualizationMethod.hpp \
    $$PWD/source/RenderingSystem/RadialPairedCoordinatesVisualizationMethod.hpp \
    $$PWD/source/RenderingSystem/RenderingSystem.hpp \
    $$PWD/source/RenderingSystem/Shaders.hpp \
    $$PWD/source/RenderingSystem/ShiftedPairedCoordinatesVisualizationMethod.hpp \
    $$PWD/source/RenderingSystem/VisualizationOptions.hpp
SOURCES += source/LoadDataDialog.cpp \
    source/LotsOfLinesApp.cpp \
    source/main.cpp \
    source/VisualizationRendererWidget.cpp \
    source/DataTableModel.cpp \
    source/LoadingWorker.cpp \
    source/OptionEditorWidget.cpp \
    source/PreferencesDialog.cpp \
    source/DataModel/CSVFileLoader.cpp \
    source/DataModel/DataFileLoader.cpp \
    source/DataModel/DataModel.cpp \
    source/DataModel/DataSet.cpp \
    $$PWD/source/RenderingSystem/CollocatedPairedCoordinatesVisualizationMethod.cpp \
    $$PWD/source/RenderingSystem/OpenGLRenderer.cpp \
    $$PWD/source/RenderingSystem/OpenGLShader.cpp \
    $$PWD/source/RenderingSystem/OpenGLVertexBufferObject.cpp \
    $$PWD/source/RenderingSystem/ParallelCoordinatesVisualizationMethod.cpp \
    $$PWD/source/RenderingSystem/RadialPairedCoordinatesVisualizationMethod.cpp \
    $$PWD/source/RenderingSystem/RenderingSystem.cpp \
    $$PWD/source/RenderingSystem/Shaders.cpp \
    $$PWD/source/RenderingSystem/ShiftedPairedCoordinatesVisualizationMethod.cpp \
    $$PWD/source/RenderingSystem/VisualizationOptions.cpp
FORMS += source/LotsOfLinesApp.ui \
    source/LoadDataDialog.ui \
    source/PreferencesDialog.ui
RESOURCES += source/LotsOfLinesApp.qrc \
    source/LotsOfLinesApp.qrc

INCLUDEPATH += ./source
INCLUDEPATH += ./3rd-party/glm
INCLUDEPATH += ./3rd-party/glew/include
