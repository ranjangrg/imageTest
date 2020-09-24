#/usr/bin/bash

MAIN_EXEC_FILE="./main"

make clean;
make main;

if test -f "$MAIN_EXEC_FILE"; then
	#echo "$MAIN_EXEC_FILE exists"
	./main;
fi
