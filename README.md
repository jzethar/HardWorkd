# Hard Wor(k)d
This is a simple tool designed to help with memorizing words. It assumes the user will type the word several times to reinforce memory. The interface is straightforward and easy to use.

## Interface
### Main page 
Main page contains the data of last session, score and database. 

![main page](docs/01.jpg)

There are 3 options:
- Start game
- Upload CSV
- Learn Words

### Start Game
On starting game there are flexible settings

![settings](docs/02.jpg)

and main game

![main game](docs/03.jpg)

After timer is done the new word will be shown.

### Upload page
On upload, words from .csv file will be uploaded to the database. 

![upload](docs/04.jpg)

### Learn Words
Finally, there is a possibility to learn some new words by typing memorization, it's not the most effective way, however, for someones it works.

![memorization](docs/05.jpg)

Simply, it gives 5 attempts to enter the word. 

## Stack
For running code you need:
- Qt6
- cmake 3.22+
- sqlite3 libraries

This project uses SQLite3 as its database. It's simple and the file can be moved anywhere or easily deleted or truncated.
In addition there is a python version with an attempt to create Spanish verb tester and it will be still WiP (and in my heart).
My condolences to all designers and anyone involved in design, but I honestly have no idea how to make things look good