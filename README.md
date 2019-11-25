# Smart_Chess
A Chess game built by Qt and C++.
</br>The game can be played online by creating games in the lobby.The server will show all games in the lobby available for all clients.
</br>Playing offline is available with two modes: 1: Play against another human player; 2: Play against a very SMART AI.
</br>The AI uses the [MiniMax](https://www.wikiwand.com/en/Minimax) algorithm.
</br>Some idea and information from [this tutorial](https://www.youtube.com/watch?v=9lqhMLFHj3A&list=PLMgDVIa0Pg8WrI9WmZR09xAbfXyfkqKWy)
and https://github.com/subeshb1/Chess
</br>AI's idea from https://github.com/lhartikk/simple-chess-ai
</br>Click here to download and play [HERE](https://github.com/Jiachenggavin/Awesome_Chess-Cpp/tree/onlineEXE).

ALL code are in folder "Client" and "Server".

# How to play online:
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/Start.gif)

</br>VS2017 compiles the server. Qt creator compiles the client(Game).
</br>Winsock and windows.h are used to write the online part. Currently no Linux support is available. There will be a Linux version in the future.
</br>[cJSON](https://github.com/DaveGamble/cJSON) is used to serialize messages like the move, create games, games list, etc.
</br>A TCP connection is sent to make sure it can receive and send the message successfully.

Here is another GIF how this game is played online:
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/Online2.gif)

Here is an example of what happen when one side wins in one game:

![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/EndO.gif)

# How this AI is:

![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/Lose.gif)

I am not even its opponent!!!

The AI can play both of white side and black side:

![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/whiteAI.gif)


It was a simple version and looks very stupid:
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/smallfirst.gif)
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/smallend.gif)


This program can also play as PVP:

![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/PvP.gif)

Of course, it can do Promotion and Castling.
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/promotion.gif)

![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/NewCastling.gif)

# Bugs:
There are currently many server-side bugs. Sometimes the messages will not be sent to clients.
</br>There is a bug in AI when the AI only has two possible turns left.

Currently there a bugs in the code, I will be very appreciated if you can help me find the bugs!
In addition, if you have any ideas which can help improve this game, please let me know! 
