# -------------------------------------------------
# Project created by QtCreator
# -------------------------------------------------
TARGET = UDM-600
TEMPLATE = app
SOURCES += \
    src/view_connect.cpp \
    src/main.cpp \
    src/view_calibration_machine.cpp \
    src/mainwindow.cpp \
    src/view_diagram.cpp \
    src_3rd_party/qextserialport/qextserialport.cpp \
    src_3rd_party/qextserialport/qextserialenumerator_unix.cpp \
    src_3rd_party/qextserialport/posix_qextserialport.cpp \
    src_project_independent/linear_converter_f.c \
    src_project_independent/calibration_structure.cpp \
    src/ctrl_tenso.cpp \
    src_project_independent/serial_frame3_parser.cpp \
    src_project_independent/data_storage.cpp \
    src_project_independent/view_calibration_structure.cpp \
    src_project_independent/view_config_serial_connect.cpp \
    src_project_independent/crc_16.c \
    src_project_independent/serial_frame3.c \
    src_project_independent/qwt_plot_diagram.cpp \
    src_project_independent/fir_filter.cpp
HEADERS += \ 
    src/view_calibration_machine.h \
    src/view_connect.h \
    src/tenso_sensor_structure.h \
    src/mainwindow.h \
    src/view_diagram.h \
    src_3rd_party/qextserialport/qextserialport_global.h \
    src_3rd_party/qextserialport/qextserialport.h \
    src_3rd_party/qextserialport/qextserialenumerator.h \
    src_project_independent/view_config_serial_connect.h \
    src_project_independent/view_calibration_structure.h \
    src_project_independent/linear_converter_f.h \
    src_project_independent/data_storage.h \
    src_project_independent/calibration_structure.h \
    src_project_independent/crc_16.h \
    src/ctrl_tenso.h \
    src_project_independent/serial_frame3_parser.h \
    src_project_independent/serial_frame3.h \
    src_project_independent/serial_frame3.h \
    src_project_independent/qwt_plot_diagram.h \
    src_project_independent/fir_filter.h
INCLUDEPATH += ext_h/qwt
INCLUDEPATH += src_project_independent
INCLUDEPATH += src_3rd_party/qextserialport
unix { 
    DEFINES += _TTY_POSIX_
    !contains(QMAKE_HOST.arch, x86_64) {
        DESTDIR = build_u32
        QMAKESPEC=linux-g++-32
        OBJECTS_DIR = build_u32/obj
        MOC_DIR = build_u32/moc
        LIBS += ext_lib/u32/libqwt.a
        message("linux x86 build")
    }
    else { 
        QMAKESPEC=linux-g++-64
        BUILDDIR = build_u64
        DESTDIR = build_u64
        OBJECTS_DIR = build_u64/obj
        MOC_DIR = build_u64/moc
        LIBS += ext_lib/u64/libqwt.a
        message("linux x86_64 build")
    }
    release:
}
win32 { 
    DESTDIR = build_w
    OBJECTS_DIR = build_w/obj
    MOC_DIR = build_w/moc
    DEFINES += _TTY_WIN_
    LIBS += ext_lib/w32/libqwt.a
}
