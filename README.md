# myshell

## The command interpreter reads the commands from stdin and executes them.
## Introduction
This program works like a real shell: it can read commands from stding and execute them.

## Installation and compilation
  ```bash
  $ git clone https://github.com/Rosovskyy/myshell
  $ cd myshel
  $ mkdir build
  $ cd build
  $ cmake -G"Unix Makefiles" ..
  $ make
  ```

## Realization
  We wrote a program, that works like a real interpreter. It has different built in functions, like: merrno, mpwd, mcd, mexit,   mecho, mexport. It can also run various external files.

## Running
  * merrno [-h|--help] - print the end code of the last program or command
  * mpwd [-h|--help] -  print the current path
  * mcd <path> [-h|--help] - move the <path>
  * mexit [end code] [-h|--help] - exit myshell
  * mecho [text|$<var_name>] [text|$<var_name>]  [text|$<var_name>] - print arguments or value of variable
  * mexport <var_name>[=VAL] - add global variable

## License and copyright
© Serhii Rosovskyi, Valerii Savoskin and Olexandr Vaitovych, students of the Ukrainian Catholic University


