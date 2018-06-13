# Hunt the Wumpus

A text based adventure originally invented by Gregory Yob. This version is a solution to a problem from the text _Programming Principles and Practice Using C++_ by Bjarne Stroustrup.

> _From Chapter 18 Ex 12:_
>
> Implement a version of the game "Hunt the Wumpus". The basic premise is that a rather smelly monster lives in a dark cave consisting of connected rooms. Your job is to slay the wumpus using bow and arrow. In addition to the wumpus, the cave has two hazards: bottomless pits and giant bats. If you enter a room with a bat, the bat picks you up and drops you into another room. If you enter a room with a bottomless pit, its the end of the game for you. If you enter the room with the Wumpus he eats you.

When initially confronted with this problem I did not possess the facilities to execute it satisfactorily. While I'm sure a minimal version was possible at the time, I grew frustrated when attempting to assemble the game components.

Game is currently playable though there are many opportunities to improve the project.
- Game class is too big and needs refactoring
- Game class lacks any testing, this will be achievable after above
- Message text is baked into the source code and needs to be stored separately
- Assignment_table has a logic bug that produces segfaults
- Naming of objects could be improved

On top of this list I would also like to explore how to properly utilize CMake to test my project as it currently compiles most of the source code twice.

Lastly, while refactoring I will keep an eye on what would be needed to be done to satisfy later exercises in the book:

> _From Chapter 19 Ex 14 & 15:_
>
> Provide a GUI interface and a bit of graphical output to the "Hunt the Wumpus" game. Take input from an input box and display a map of the part of the cave that is currently known to the player.
>
> Allow the user to mark the rooms based on knowledge and guesses, such as "maybe bats" and "bottomless pit".
