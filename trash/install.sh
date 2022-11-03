#!/bin/zsh
path_trash="$HOME/.SmartTrash"
path_list="$path_trash/.list_trash" 

if [ -d $HOME/.SmartTrash ] && [ -e $HOME/.list_trash ]
then
echo "/////////Smart Trash already installed//////////"
exit
fi

if !([ -d $HOME/.SmartTrash ])
then
mkdir $path_trash
fi

if !([ -e $HOME/.SmartTrash/.list_trash ])
then
touch $path_list
fi

if g++ main.cpp File.cpp Trash.cpp -o trash
then 
echo "Compilation completed successfully"
echo ".................................."
else
echo "Compilation failed"
echo "Smart Trash can installation failed"
exit
fi
mv ./trash /usr/local/bin 

echo "/////Smart Trash has been installed successfully//////"










