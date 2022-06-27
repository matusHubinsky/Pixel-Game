#!/bin/bash

FIND="shared"
REPLACE="shared->"

path=/home/leviathan/Documents/VUT/git/PixelGame/code

# echo replace
for file in $(path)include/*.h
do
   	cat $(file) | echo $(FIND) > $(REPLACE)  
done

# awk replace
for file in $(path)/src/*.c
do
    cat $(file) | awk -v find="$FIND" replace="$REPLACE" 'gsub(find, replace)' 
done
