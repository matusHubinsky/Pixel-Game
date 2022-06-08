#!/bin/bash

FIND="shared"
REPLACE="shared->"

path=/home/leviathan/Documents/VUT/git/PixelGame/code

for file in $(path)include/*.h
do
   	cat $(file) | awk -v find="$FIND" replace="$REPLACE" 'gsub(find, replace)'  
done


for file in $(path)/src/*.c
do
    cat $(file) | awk -v find="$FIND" replace="$REPLACE" 'gsub(find, replace)' 
done
