# Simple Shell

A simple UNIX command line interpreter.

## Description

This is a simple shell program that replicates basic functionality of `/bin/sh`. It was developed as part of the Holberton School Simple Shell project.

## Team Members
- Norah Mohammed Alnujidi
- Rinad Fahad Alzuaybir

## Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode
```bash
$ ./hsh
($) /bin/ls
file1 file2
($) exit
$
```

### Non-Interactive Mode
```bash
$ echo "/bin/ls" | ./hsh
file1 file2
$
```

## Features

- Displays a prompt and waits for user input
- Executes commands with their full path
- Handles errors appropriately
- Supports EOF (Ctrl+D)

## Project Requirements

- All files compiled on Ubuntu 20.04 LTS
- Code follows Betty style
- No memory leaks
- Maximum 5 functions per file

## Repository

- **GitHub repository:** holbertonschool-simple_shell

## Authors

See AUTHORS file for list of contributors.
