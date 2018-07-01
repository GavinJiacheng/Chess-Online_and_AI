#-------------------------------------------------
#
# Project created by QtCreator 2018-06-07T18:32:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess_AI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    game.cpp \
    game.cpp \
    main.cpp \
    game.cpp \
    main.cpp \
    gameitems/gameboard.cpp \
    gameitems/boardbox.cpp \
    gameitems/piece.cpp \
    gameitems/king.cpp \
    gameitems/queen.cpp \
    gameitems/bishop.cpp \
    gameitems/rook.cpp \
    gameitems/pawn.cpp \
    gameitems/knight.cpp \
    gameitems/bishop.cpp \
    gameitems/boardbox.cpp \
    gameitems/gameboard.cpp \
    gameitems/king.cpp \
    gameitems/knight.cpp \
    gameitems/pawn.cpp \
    gameitems/piece.cpp \
    gameitems/queen.cpp \
    gameitems/rook.cpp \
    game.cpp \
    main.cpp \
    gameitems/bishop.cpp \
    gameitems/boardbox.cpp \
    gameitems/gameboard.cpp \
    gameitems/king.cpp \
    gameitems/knight.cpp \
    gameitems/pawn.cpp \
    gameitems/piece.cpp \
    gameitems/queen.cpp \
    gameitems/rook.cpp \
    game.cpp \
    main.cpp \
    button.cpp \
    gameitems/bishop.cpp \
    gameitems/boardbox.cpp \
    gameitems/gameboard.cpp \
    gameitems/king.cpp \
    gameitems/knight.cpp \
    gameitems/pawn.cpp \
    gameitems/piece.cpp \
    gameitems/queen.cpp \
    gameitems/rook.cpp \
    button.cpp \
    game.cpp \
    main.cpp \
    AI_files/possible_boxnpiece.cpp \
    AI_files/stupid_ai.cpp \
    AI_files/findallmovess.cpp \
    AI_files/findallmovess.cpp \
    AI_files/possible_boxnpiece.cpp \
    AI_files/stupid_ai.cpp \
    gameitems/bishop.cpp \
    gameitems/boardbox.cpp \
    gameitems/gameboard.cpp \
    gameitems/king.cpp \
    gameitems/knight.cpp \
    gameitems/pawn.cpp \
    gameitems/piece.cpp \
    gameitems/queen.cpp \
    gameitems/rook.cpp \
    button.cpp \
    game.cpp \
    main.cpp \
    onlineGame/chessroom.cpp \
    onlineGame/chatroom.cpp \
    AI_files/findallmovess.cpp \
    AI_files/possible_boxnpiece.cpp \
    AI_files/stupid_ai.cpp \
    gameitems/bishop.cpp \
    gameitems/boardbox.cpp \
    gameitems/gameboard.cpp \
    gameitems/king.cpp \
    gameitems/knight.cpp \
    gameitems/pawn.cpp \
    gameitems/piece.cpp \
    gameitems/queen.cpp \
    gameitems/rook.cpp \
    onlineGame/chatroom.cpp \
    onlineGame/chessroom.cpp \
    button.cpp \
    game.cpp \
    main.cpp \
    cJSON/cJSON.c \
    onlineGame/gamelobby.cpp

HEADERS += \
    game.h \
    game.h \
    game.h \
    gameitems/gameboard.h \
    gameitems/gameboard.h \
    gameitems/boardbox.h \
    gameitems/piece.h \
    gameitems/king.h \
    gameitems/queen.h \
    gameitems/bishop.h \
    gameitems/rook.h \
    gameitems/pawn.h \
    gameitems/knight.h \
    gameitems/bishop.h \
    gameitems/boardbox.h \
    gameitems/gameboard.h \
    gameitems/king.h \
    gameitems/knight.h \
    gameitems/pawn.h \
    gameitems/piece.h \
    gameitems/queen.h \
    gameitems/rook.h \
    game.h \
    gameitems/bishop.h \
    gameitems/boardbox.h \
    gameitems/gameboard.h \
    gameitems/king.h \
    gameitems/knight.h \
    gameitems/pawn.h \
    gameitems/piece.h \
    gameitems/queen.h \
    gameitems/rook.h \
    game.h \
    button.h \
    gameitems/bishop.h \
    gameitems/boardbox.h \
    gameitems/gameboard.h \
    gameitems/king.h \
    gameitems/knight.h \
    gameitems/pawn.h \
    gameitems/piece.h \
    gameitems/queen.h \
    gameitems/rook.h \
    button.h \
    game.h \
    AI_files/possible_boxnpiece.h \
    AI_files/stupid_ai.h \
    AI_files/findallmovess.h \
    AI_files/moves.h \
    AI_files/positioncalcuation.h \
    AI_files/findallmovess.h \
    AI_files/moves.h \
    AI_files/positioncalcuation.h \
    AI_files/possible_boxnpiece.h \
    AI_files/stupid_ai.h \
    gameitems/bishop.h \
    gameitems/boardbox.h \
    gameitems/gameboard.h \
    gameitems/king.h \
    gameitems/knight.h \
    gameitems/pawn.h \
    gameitems/piece.h \
    gameitems/queen.h \
    gameitems/rook.h \
    button.h \
    game.h \
    onlineGame/chessroom.h \
    onlineGame/chatroom.h \
    onlineGame/message.h \
    AI_files/findallmovess.h \
    AI_files/moves.h \
    AI_files/positioncalcuation.h \
    AI_files/possible_boxnpiece.h \
    AI_files/stupid_ai.h \
    cJSON/cJSON.h \
    gameitems/bishop.h \
    gameitems/boardbox.h \
    gameitems/gameboard.h \
    gameitems/king.h \
    gameitems/knight.h \
    gameitems/pawn.h \
    gameitems/piece.h \
    gameitems/queen.h \
    gameitems/rook.h \
    onlineGame/chatroom.h \
    onlineGame/chessroom.h \
    onlineGame/message.h \
    button.h \
    game.h \
    onlineGame/onlinemove.h \
    onlineGame/gamelobby.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    res.qrc
