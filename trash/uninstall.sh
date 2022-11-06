#!/bin/sh

if [ -d $HOME/.SmartTrash ]
then
rm -rf ~/.SmartTrash
echo "Success: Smart trash has been uninstall"
else
echo "Error: Smart trash can not in the system"
fi

