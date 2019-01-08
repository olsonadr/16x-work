#!/bin/bash

# Bash script that compiles the library with name of $1 found in the directory $2
#   and moves the .so file to everywhere it could be useful. The .cpp and .h files
#   of that name must be present in that $2 directory.

cd $2
g++ -fPIC $1.cpp -c
g++ -fPIC -shared $1.o -o lib$1.so
sudo cp lib$1.so /usr/lib/
sudo cp lib$1.so /lib
sudo cp lib$1.so /lib64
#g++ -I. -L. -l<lib_name> <program_using_lib_name>.cpp -o <program_using_lib_name>
