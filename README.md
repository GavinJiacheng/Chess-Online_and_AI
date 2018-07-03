# Smart_Chess
A Chess which is built by Qt and C++.
</br>It can be played online by creating games in the lobby, and the server will show all games in the lobby for all clients.
</br>It can also be played offline with two modes: 1: play with another human player; 2: play with a very SMART AI.
</br>The AI uses the [MiniMax](https://www.wikiwand.com/en/Minimax) algorithm.
</br>Get some idea and information from [this tutorial](https://www.youtube.com/watch?v=9lqhMLFHj3A&list=PLMgDVIa0Pg8WrI9WmZR09xAbfXyfkqKWy)
and https://github.com/subeshb1/Chess
</br>AI's idea from https://github.com/lhartikk/simple-chess-ai
</br>You can download and play it from [HERE](https://github.com/Jiachenggavin/Awesome_Chess-Cpp/tree/onlineEXE).

# How to play online:
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/Start.gif)

</br>VS2017 compiles the server. Qt creator compiles the client(Game).
</br>It uses winsock and windows.h to write the online part. So it cannot be run in Linux now. There will be a Linux version in the future.
</br>It uses [cJSON](https://github.com/DaveGamble/cJSON) to serialize messages like the move, create games, games list, etc.
</br>It's a TCP connection to make sure it can receive and send the message successfully.

Here is another GIF how this game is played online:
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/Online2.gif)

Here is an example of what happen when one side wins in one game:

![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/End.gif)

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
It still has many bugs in the server. Sometimes it cannot send messages to clients.
</br>It has a bug in AI when the AI only has two possible turns left.
