# Bee

Bee is my attempt to extend the power of the Windows
CMD by replicating it and adding new features
intended to help programmers like me in their
daily lives.

Bee is written in C++, due to the fact that 
it is the language I master and its power to make 
applications optimized and efficient.

Note that Bee was made specifically for Windows, 
so it probably won't work on other operating 
systems like Linux or MacOS.







# Documentation

## Basic syntax

Bee has some features to make it easier to use.
To demonstrate some, I will use the [Print](https://github.com/MarvinMarjan/Bee/edit/master/README.md#print) command.

Note: the "print" command by default concatenates all arguments into a single string


### Argument

Arguments are values that are passed to a command.
These arguments are separated by space (" ").


![image](https://user-images.githubusercontent.com/103616110/188334916-ab9d472c-0ae9-4921-97e5-970fd3c24b02.png)


In the above case, "hamburger" is the first argument, "pizza" is the second, and "potato" is the third.


### Flag

Flags are used to modify the way a command should work, they are similar to options

Syntax: - (flag_name)

To test this feature, we can disable the newline that the "print" command leaves at the end using the "-nl" flag:

Note that you can use more than one flag in a same command


![image](https://user-images.githubusercontent.com/103616110/188335152-270580a9-8201-49c1-957c-234c1e016a1a.png)
![image](https://user-images.githubusercontent.com/103616110/188335144-78213027-949d-4970-95be-a85d1b3bdf60.png)


### Quote

In Bee the arguments of a command are separated by a space (" ").

But there are some cases where the value passed has a space, 
and that space is not to be ignored.


![image](https://user-images.githubusercontent.com/103616110/188333221-41d63041-8c7a-48e0-bf4e-5236a876e65f.png)


in the above case, "print" is interpreting "hello, world" as two arguments instead of one, with the first argument being "hello," and the second being "world".
Then "print" concatenates the two arguments into a string and prints it to the screen

So, to get around this and make "print" interpret "hello," and "world" as an argument you can enclose the argument in quotes:


![image](https://user-images.githubusercontent.com/103616110/188333424-7c3d0ca6-e307-4814-9ad7-8a94efd5f212.png)


That way "print" will no longer separate "hello, world".


### Shortcuts

Sometimes you might want to write a long text or store a important value.
In these cases you can use a feature called "Shortcut", which works similarly to variables.

To create a Shortcut we can use the [Set](https://github.com/MarvinMarjan/Bee/edit/master/README.md#set) command.

The first argument is the shortcut name, and the second is the value to be stored.
Let's create a shortcut called "number" that stores the value "123":


![image](https://user-images.githubusercontent.com/103616110/188651510-58f8d755-7924-4e73-b663-542e971b6e9a.png)


Now we need to access the stored value. To access the value of a shortcut you need to use this syntax: `$name`


![image](https://user-images.githubusercontent.com/103616110/188652758-e9bb8826-ab17-4b91-ab19-b56fe380df19.png)


To list all shortcuts you can use the [List](https://github.com/MarvinMarjan/Bee/edit/master/README.md#list) command:


![image](https://user-images.githubusercontent.com/103616110/188653697-07612580-afae-4c01-9e8a-fb358218f6ec.png)


To delete a shortcut, use the [Del](https://github.com/MarvinMarjan/Bee/edit/master/README.md#del) command:


![image](https://user-images.githubusercontent.com/103616110/188653883-b77fb70b-51f4-42a6-bc4d-ebc82e31f04b.png)


To edit the value of a shorcut, use the [Set](https://github.com/MarvinMarjan/Bee/edit/master/README.md#set) command:


![image](https://user-images.githubusercontent.com/103616110/188654453-ba975853-7bf1-4c4d-ad65-7b5760bf0d26.png)


### Concatenation

Bee has support for concatenating two values into one using the sum character ("+")


![image](https://user-images.githubusercontent.com/103616110/188333622-b7157e18-cbf8-425f-ae3e-ca02ca034124.png)


### Colors !!

Bee allows the user to manipulate colors in "print" and other commands.

Supported colors are:

- RED
- GREEN
- YELLOW
- BLUE
- PURPLE
- CYAN
- WHITE
- GRAY
- WT_RED    (Light red)
- WT_GREEN  (Light Green)
- WT_YELLOW (Light yellow)
- WT_BLUE   (Light blue)
- WT_PURPLE (Light purple)
- WT_CYAN   (light cyan)

In addition to manipulating the colors, we can also manipulate the way they are displayed.

Supported display modes:
- NORMAL
- BOLD
- DARK
- ITALIC
- UNDERLINE
- TOGGLE_SLOW
- TOGGLE_RAPID
- INVERT
- CROSSED

The syntax for handling colors is: \ (color_name) ; (color_mode)

It is only necessary to add the ';' if you want to specify a display mode.

If you don't specify a display mode, "NORMAL" will be the default.


![image](https://user-images.githubusercontent.com/103616110/188334299-742164d3-fced-4009-a5ac-d6828c41ab08.png)
![image](https://user-images.githubusercontent.com/103616110/188334313-eaf4a2d6-d417-4576-8aac-3869e4a4591e.png)
![image](https://user-images.githubusercontent.com/103616110/188334440-bf041e42-b7f1-47b6-87c3-771c8b859d49.png)
![image](https://user-images.githubusercontent.com/103616110/188334442-48d065d3-0443-4ea7-8580-b392c93ed098.png)
![image](https://user-images.githubusercontent.com/103616110/188334443-ee175662-fc99-4003-b04c-216e37919356.png)


### Name variants

Some Bee commands are a little big, for example: diagnostic, make_file, remove_file, etc...

Writing these commands can take a while, so to solve this problem, you can use name variants.

Name variants are multiple names for the same command.

For this example i will use the "detail" command.


![image](https://user-images.githubusercontent.com/103616110/188334774-ec634e94-aedc-4b9e-b32f-ef8b2555a1b3.png)


Instead of writing "detail", we can opt for a smaller option: ".d":


![image](https://user-images.githubusercontent.com/103616110/188334819-b6e8409c-cc0b-465e-a6e5-b35fcd8110c8.png)


# Commands

## Command syntax

To facilitate the demonstration of the structure of a command, I will use a syntax that describes its parts:

- `[ text ]`: a argument
- `{ text (-text) }`: a flag
- `[ text ? ]` | `{ text (-text) ? }`: a optional argument/flag
- `[ text... ]`: indefinite number of arguments

## Command List

- [Exit](https://github.com/MarvinMarjan/Bee/edit/master/README.md#exit)
- [Setting](https://github.com/MarvinMarjan/Bee/edit/master/README.md#setting)
- [Detail](https://github.com/MarvinMarjan/Bee/edit/master/README.md#detail)
- [Help](https://github.com/MarvinMarjan/Bee/edit/master/README.md#help)
- [Clear](https://github.com/MarvinMarjan/Bee/edit/master/README.md#clear)
- [Color](https://github.com/MarvinMarjan/Bee/edit/master/README.md#color)
- [Color_Mode](https://github.com/MarvinMarjan/Bee/edit/master/README.md#color_mode)
- [Errs](https://github.com/MarvinMarjan/Bee/edit/master/README.md#errs)
- [Warns](https://github.com/MarvinMarjan/Bee/edit/master/README.md#warns)
- [Cd](https://github.com/MarvinMarjan/Bee/edit/master/README.md#cd)
- [Diag](https://github.com/MarvinMarjan/Bee/edit/master/README.md#diag)
- [Print](https://github.com/MarvinMarjan/Bee/edit/master/README.md#print)
- [Add](https://github.com/MarvinMarjan/Bee/edit/master/README.md#add)
- [Rmv](https://github.com/MarvinMarjan/Bee/edit/master/README.md#rmv)
- [Return](https://github.com/MarvinMarjan/Bee/edit/master/README.md#return)
- [Set](https://github.com/MarvinMarjan/Bee/edit/master/README.md#set)
- [Del](https://github.com/MarvinMarjan/Bee/edit/master/README.md#del)
- [List](https://github.com/MarvinMarjan/Bee/edit/master/README.md#list)
- [Mfile](https://github.com/MarvinMarjan/Bee/edit/master/README.md#mfile)
- [Rmfile](https://github.com/MarvinMarjan/Bee/edit/master/README.md#rmfile)
- [Mdir](https://github.com/MarvinMarjan/Bee/edit/master/README.md#mdir)
- [Rmdir](https://github.com/MarvinMarjan/Bee/edit/master/README.md#rmdir)
- [Rename](https://github.com/MarvinMarjan/Bee/edit/master/README.md#rename)
- [Sizeof](https://github.com/MarvinMarjan/Bee/edit/master/README.md#sizeof)
- [Lineof](https://github.com/MarvinMarjan/Bee/edit/master/README.md#lineof)
- [Read](https://github.com/MarvinMarjan/Bee/edit/master/README.md#read)
- [Write](https://github.com/MarvinMarjan/Bee/edit/master/README.md#write)
- [Run](https://github.com/MarvinMarjan/Bee/edit/master/README.md#run)
- [Stat](https://github.com/MarvinMarjan/Bee/edit/master/README.md#stat)
  
  
## Exit

End the program

Name variants:
- exit
- .x
- .exit
- quit
- .quit

Syntax:
`exit`

## Setting

Show/Edit system settings

Bee has some settings that can be modified by the user

Name variants:
- setting
- config
- .sett
- .conf
- \*

Syntax: `setting [ Setting_Name ? ] [ Setting_Value ? ]`

- If you want to see the settings: `setting`
- If you want to see a specific setting: `setting [ Setting_Name ]` -> `setting itellisense`
- If you want to modify a setting: `setting [ Setting_Name ] [ Setting_Value ]` -> `setting itellisense false`

## Detail

Show program details (Version, Name)

Name variants:
- detail
- .d
- .detail

Syntax: `detail`

## Help

Show a help message containing commands and their details (name variants, syntax, description)

Name variants:
- help
- .h
- .help

Syntax: help [ Command ? ] { command_name (-cn) ? }

- If you want to see whole help message: `help`
- If you want to see aa specific command: `help [ Command ]` -> `help print`
- If you want to see only command name: `help { command_name (-cn) }` -> `help -cn`

## Clear

Clear the console

Name variants:
- clear
- clean
- .cl

Syntax: `clear`

## Color

Show a list of colors

Name variants:
- color
- clr

Syntax: `color`

## Color_Mode

Show a list of color modes

Name variants:
- color_mode
- cmode

Syntax: `color_mode`

## Errs

Show a list of system errors

Name variants:
- errs
- errors
- err

Syntax: `errs`

## Warns

Show a list of system warnings

Name variants:
- warns
- warn

Syntax: `warns`

## Cd

Helps with directory navigation

Name variants:
- cd

Syntax: `cd [ Path ]`

## Diag

Display the details of the current directory

Note: By default "dirs" will not display the size of a directory

Name variants:
- diag
- diagnostic

Syntax: `diag { dirs_size (-ds) ? } { path_debug (-pd) ? }`

- If you want to show directory size: `diag { dirs_size (-ds) }` -> `diag -ds`
- If you want to debug diag: `diag { path_debug (-pd) }` -> `diag -pd`

## Print

Print a specific value in the console

Name variants:
- print

Syntax: `print [ Values... ? ]`

## Add

Add a new command

Name variants:
- add

Syntax: `add [ Cmd_Name ] [ Block ]`

## rmv

Remove a created command

Name variants:
- rmv
- remove

Syntax: `rmv [ Cmd_Name ]`

## Return

Defines a return value in a function (only works in created functions)

Name variants:
- return

Syntax: `return [ Value ]`

## Set

Create or edit a shortcut

Name variants:
- set

Syntax: `set [ Name ] [ Value ]`

## Del

Delete a shortcut

Name variants:
- del

Syntax: `del [ Name ]`

## List

List all Shortcuts/Functions

Name variants:
- list

Syntax: `list [ Name ? ]`

- If you want to see all shortcuts/functions: `list`
- If you want to see a specific shortcut/function: `list [ Name ]` -> `list target_name`

## Mfile

Create a file

Name variants:
- mfile
- make_file

Syntax: `mfile [ Path ]`

## Rmfile

Remove a file

Name variants:
- rmfile
- remove_file

Syntax: `rmfile [ Path ]`

## Mdir

Create a directory

Name variants:
- mdir
- make_dir

Syntax: `mdir [ Path ]`

## Rmdir

Remove a directory

Name variants:
- rmdir
- remove_dir

Syntax: `rmdir [ Path ]`

## Rename

Rename a file/directory

Name variants:
- rename

Syntax: `rename [ Path ] [ New_Name ]`

## Sizeof

Return the size of a file in bytes

Name variants:
- sizeof

Syntax: `siszeof [ Path ]`

## Lineof

Return the total lines of a file

Name variants:
- lineof

Syntax: `lineof [ Path ]`

## Read

Return the content of a file

Name variants:
- read
- read_file

Syntax: `read [ Path ]`

## Write

Write content in a file

Name variants:
- write
- write_file

Syntax: `write [ Path ] [ Content ] { clear_file (-cf) ? } { disable_newline (-nl) ? }`

- If you want to clear the file before writing: `write [ Path ] [ Content ] { clear_file (-cf) }` -> `write C:/some_dir/some_file.txt "hello, world" -cf`
- If you want to disable the new line after writing: `write [ Path ] [ Content ] { disable_newline (-nl) }` -> `write C:/some_dir/some_file.txt "hello, world" -nl`


## Run

Run a OS command

Name variants:
- run

Syntax: `run [ Command ]`

## Stat

Show OS status

Name variants:
- stat
- stats
- status
- .s

Syntax: `stat { update (-up) ? }`

- If you want to update every second: `stat { update (-up) }` -> `stat -up`
