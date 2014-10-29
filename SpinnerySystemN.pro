#-------------------------------------------------
#
# Project created by QtCreator 2014-04-26T17:33:00
#
#-------------------------------------------------

QT       += core gui xml sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpinnerySystemN
TEMPLATE = app


SOURCES += main.cpp\
           ui/mainwindow.cpp \
    src/topeview/control/basenodemanager.cpp \
    src/topeview/control/parse.cpp \
    src/topeview/widget/edge.cpp \
    src/topeview/widget/graphwidget.cpp \
    src/topeview/widget/node.cpp \
    src/zmq/mycore/myabstractzmq.cpp \
    src/zmq/mycore/myclient.cpp \
    src/zmq/mycore/myserver.cpp \
    src/zmq/mymessage/message.cpp \
    src/zmq/mymessage/messageuitl.cpp \
    src/zmq/zmqhelper.cpp \
    src/serial/serial.cpp \
    ui/widget/mainwidget.cpp \
    ui/widget/topeviewwidget.cpp \
    ui/widget/systemwidget.cpp \
    ui/widget/logwidget.cpp \
    ui/rewidget/mymenulabel.cpp \
    src/database/sqlutil.cpp \
    src/database/dao/logdao.cpp \
    src/bean/syslog.cpp \
    ui/form/exitdialog.cpp \
    src/config/config.cpp \
    src/zmq/myapp/baseclient.cpp \
    src/tcpsocket/tcpclient.cpp \
    src/manager/basemanager.cpp \
    src/manager/tcpsocketmanager.cpp \
    src/manager/serialmanager.cpp \
    src/manager/zmqmanager.cpp \
    src/manager/sqlitemanager.cpp \
    ui/widget/consolewidget.cpp

HEADERS  +=  ui/mainwindow.h \
    src/topeview/control/basenodemanager.h \
    src/topeview/control/parse.h \
    src/topeview/widget/edge.h \
    src/topeview/widget/graphwidget.h \
    src/topeview/widget/node.h \
    src/zmq/mycore/myabstractzmq.h \
    src/zmq/mycore/myclient.h \
    src/zmq/mycore/myserver.h \
    src/zmq/mymessage/message.h \
    src/zmq/mymessage/messageuitl.h \
    src/zmq/common.h \
    src/zmq/zmq_utils.h \
    src/zmq/zmq.h \
    src/zmq/zmqhelper.h \
    src/serial/common.h \
    src/serial/serial.h \
    src/serial/SerialStream.h \
    src/serial/SerialStreamBuf.h \
    ui/widget/mainwidget.h \
    ui/widget/topeviewwidget.h \
    ui/widget/systemwidget.h \
    ui/widget/logwidget.h \
    ui/widget/common_widget.h \
    ui/rewidget/mymenulabel.h \
    src/database/sqlutil.h \
    src/database/dao/logdao.h \
    src/bean/syslog.h \
    ui/form/exitdialog.h \
    src/config/config.h \
    src/zmq/myapp/baseclient.h \
    src/tcpsocket/tcpclient.h \
    src/manager/basemanager.h \
    src/manager/tcpsocketmanager.h \
    src/manager/managers.h \
    src/manager/serialmanager.h \
    src/manager/zmqmanager.h \
    src/database/qtsql_common.h \
    src/manager/sqlitemanager.h \
    ui/widget/consolewidget.h

FORMS    += ui/mainwindow.ui \
    ui/widget/mainwidget.ui \
    ui/widget/topeviewwidget.ui \
    ui/widget/systemwidget.ui \
    ui/widget/logwidget.ui \
    ui/form/exitdialog.ui \
    ui/widget/consolewidget.ui


RESOURCES += \
    rs/main_rs.qrc





unix:!macx: LIBS += -L$$PWD/lib/ -lzmq

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

unix:!macx: PRE_TARGETDEPS += $$PWD/lib/libzmq.a


unix:!macx: LIBS += -L$$PWD/lib/ -lseria

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

unix:!macx: PRE_TARGETDEPS += $$PWD/lib/libseria.a
