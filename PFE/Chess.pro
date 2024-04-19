QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess
TEMPLATE = app


SOURCES += main.cpp \
    client.cpp \
    clock.cpp \
    game.cpp \
    chessbox.cpp \
    chessboard.cpp \
    chesspiece.cpp \
    queen.cpp \
    pawn.cpp \
    bishop.cpp \
    knight.cpp \
    rook.cpp \
    king.cpp

HEADERS  += \
    client.h \
    clock.h \
    game.h \
    chessbox.h \
    chessboard.h \
    chesspiece.h \
    queen.h \
    pawn.h \
    bishop.h \
    knight.h \
    rook.h \
    king.h

FORMS    +=

RESOURCES += \
    resource.qrc
