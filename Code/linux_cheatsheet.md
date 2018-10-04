# Linux Cheat Sheet
All of the linux commands that we will need (and some extra) are included on this cheat sheet.

## Anatomy of a linux command
The following is **not** a valid linux command but is instead used to callout how most linux commands will look.
`sudo program/command options -flag`
* `sudo` is not always required but sometimes is. Only use if you know what you are doing!
* `program` or `command` indicates that the first word you type (after sudo) will either be opening up a specific program (try `nano`) or will execute a certain linux command.
* `options` will vary depending on the command of program you are using. If you want to open up the program nano and create a new file called `newFile.txt` you can do that in one command by typing `nano newFile.txt`. In this case `newFile.txt` is the option. Flags work in a very similar fashion.

## Use the manual!
One of the cool things about linux is that it comes with a great manual that will try and explain everything you can do! The problem is that sometimes it can be a bit overwhelming and poorly written. But for the most part it is great. If you want to know what a specific linux program does, or how to use a linux command correctly, simply type `man command`. For example, to see how to correctly use the linux command `mv`, type `man mv` and you will get the help file associated with that command displayed. Hit `q` to exit the manual.

## Useful linux commands
| Command | What it does |
|:-------:|:-------------|
|`pwd`    | prints the current working directory. Aka, what folder you are currently in |
|`ls`     | lists all the files and folders that are in the directory you are currently in |
|`mv`     | used to move files from one folder to another (can also move folders) |
|`cp`     | used to copy files (or folders) to another location |
|`cd`     | used to change directory, move into a different folder |
|`rm`     | used to remove a file or folder, careful, this can't be undone! |

## Useful linux programs
| Program | Brief Description |
|:-------:|:------------------|
|`nano`   | A simple, easy to use, and lightweight text editor. Use it to write your next school paper!|
|`apt`    | A program that allows you to install, remove, or update software |
|`cmartix`| You are the one Neo |
|`arduino`| A program that allows us to program the Arduino microcontroller|