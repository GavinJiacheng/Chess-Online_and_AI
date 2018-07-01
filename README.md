# Smart_Chess
A Chess which is built by Qt and C++.
</br>It can paly online by creating games in server and the server will show all games to all clients.
</br>It can also play offline with two mode: 1, play with another human player; 2, play with AI.
</br>The AI uses the [MiniMax](https://www.wikiwand.com/en/Minimax) algorithm.
</br>Get some idea and information from [this tutorial](https://www.youtube.com/watch?v=9lqhMLFHj3A&list=PLMgDVIa0Pg8WrI9WmZR09xAbfXyfkqKWy)
and https://github.com/subeshb1/Chess
</br>AI's idea from https://github.com/lhartikk/simple-chess-ai
</br>You can download and play it from [HERE](https://github.com/Jiachenggavin/Smart_Chess/tree/release_files). (This is the old version. It cannot paly as Black vs AI and it cannot play online)

# How play online:
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/Online.gif)

</br>The server is complied by VS2017. The client(Game) is complied by Qt creator.
</br>It uses [cJSON](https://github.com/DaveGamble/cJSON) to serialize messages like move, create games, games list, etc.
</br>It's a TCP connection to make sure it can receive and send message successfully.

Here is another GIF how this game is played online:
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/Online2.gif)

# How this AI is:

![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/Lose.gif)

I am not even its opponent!!!

It was a simple version and looks very stupid:
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/smallfirst.gif)
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/smallend.gif)

This program can also play as PVP:

![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/PvP.gif)

Of course, it can do Promotion and Castling.
![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/promotion.gif)

![Alt text](https://github.com/Jiachenggavin/Smart_Chess/raw/master/Screenshots/NewCastling.gif)

# Bugs:
It still has many bugs in server. Sometimes it cannot send messages to clients.
</br>It has a bug in AI when the AI only has two possible turns left.

# Problems:
When the host is waiting for others to join, It needs some functions to give the host right to cancel the game. Or if no players is joining, the host cannot do anything else.
</br>It is easy but my time is not enough now.
</br>It will be done in the future.
