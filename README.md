# TacticalWarfare

This is a work in progress.

A framework for making games. It is basically an application written in C++ with SFML.

The basic idea is that every user's application is self-contained.
The model it hat a set of clients will play together, by choosing one of themselves to be the server,
while the others connect to the server. Thus, every application will contain
1. Server - an object that will only run of the person in question is running the server
2. NetworkHandler - an object that connects to the server and handles sending and receiving information from it
3. MainMenu - an object detailing the layout of the game's main menu
4. Game - the game itself
