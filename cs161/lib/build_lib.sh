#!/bin/bash

cd $2
g++ -fPIC $1.cpp -c
g++ -fPIC -shared $1.o -o lib$1.so
sudo cp lib$1.so /usr/lib/
#g++ -I. -L. -l<lib_name> <program_using_lib_name>.cpp -o <program_using_lib_name>
