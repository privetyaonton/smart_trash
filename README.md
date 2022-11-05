# Smart trash
## _Description_

When working with the terminal, I noticed the absence of any options for manipulating the trash can. Such as, for example, adding, emptying the trash can, restoring files or directories, and much more. And I decided to write a simple utility just for such opportunities.

But while writing the code, I noticed that getting information about files and directories that are in the built-in trash can is either difficult or impossible. Therefore, my utility is a separate hidden folder, which will store the information necessary for this, and most importantly, it will be hidden from the user.

## Features

- Temporarily deleting files or directories
- Restoring files or directories along the path they were deleted from
- Emptying the entire trash can, or completely deleting a specific file or directory
- Viewing the contents of the trash can

## Installation

First, clone this repository to yourself

```
git clone https://github.com/privetyaonton/smart_trash
```

Then go to the working folder of the project

```
cd smart_trash/trash
```

After that run the configuration script

```
sh install.sh
```

Wait until a message about the complete successful installation is displayed on the screen and you can work

## Unistallation

To remove the smart trash can, navigate to your project folder and type

```
sh uninstall.sh
```

## Tutorial

Now let's see how this utility works.

The command structure looks like this:

```
trash <command> <argument>
```

We pass any of the list of commands to the command, we pass the argument for the command to the argument, if it is needed

For example, to get all possible commands, type
```
trash help
```

Let's take a look at all the possible commands
### Remove

```
trash remove <name>
```

This command organizes the addition of a file or directory by name

### List

```
trash list
```

Prints the contents of the trash can and the sequence number of each

### Recove

```
trash recov <index>
```

Restoring a file or directory by their index, which will be visible when displaying the contents of the trash can

```
trash recovall
```

Restoring all files in the trash can

### Clear Trash

```
trash clr <index>

trash clrall
```

Commands identical to the restore command, only related to a complete removal from the system

### Help

```
trash help
```

Getting information about all the above commands



