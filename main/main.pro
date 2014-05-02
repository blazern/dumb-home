# Add more folders to ship with the application, here
folder_01.source = qmlsrc/code-if-wanna-live
folder_01.target = qmlsrc
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp
include(../common.pri)

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(cppsrc/qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qmlsrc/code-if-wanna-live/MapObjects.js \
    qmlsrc/code-if-wanna-live/MapObject.qml
