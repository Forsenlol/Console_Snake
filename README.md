# Console_Snake

### Compilation
g++ main.cpp game.cpp -o game

### Game control
#### Menu
e - Start game \
p - Pause \
r - Restart

#### Movement
w - Move up \
s - Move down \
d - Move right \
a - Move left

#### Common
t - Quit game

### Game play
To control the snake use control keys. When the snake picks up the fruit "f", it will increase by 1 in size, also the score will be increased. When a snake eats a bad fruit "b",  the snake will decrease by 1 in size, and the score will be decreased. If the score drops below 0 or if the snake eats itself, then the game is over.
