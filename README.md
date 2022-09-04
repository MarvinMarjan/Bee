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
To demonstrate some, I will use the "print" command.

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


**the documentation of commands will follow the following template:**

## (Command Name)

Description

Arguments<br>
Flags


## Commands

- [Exit](https://github.com/MarvinMarjan/Bee/edit/master/README.md#exit)
  
  
  
## Exit

End the program

this command has no arguments<br>
this command has no flags
