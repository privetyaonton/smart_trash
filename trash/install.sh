#!/bin/sh
path_trash="$HOME/.SmartTrash"
path_list="$path_trash/.list_trash" 

if [ -d $HOME/.SmartTrash ] && [ -e $HOME/.list_trash ]
then
echo "Error: Smart Trash already installed"
exit
fi

if !([ -d $HOME/.SmartTrash ])
then
mkdir $path_trash
touch $path_list
elif !([ -e $HOME/.SmartTrash/.list_trash ])
then
touch $path_list
fi

if g++ main.cpp File.cpp Trash.cpp -o trash
then 
echo "Success: Compilation completed successfully"
else
echo "Error: Compilation failed"
echo "Error: Smart Trash can installation failed"
exit
fi
mv ./trash /usr/local/bin 

echo "Success: Smart Trash has been installed successfully"










