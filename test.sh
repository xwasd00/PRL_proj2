#!/bin/bash
PROJ=pro
SRC=$PROJ.cpp
HDR=$PROJ.h
PROCESSES=1

if [ -z $1 ]; then
    echo "Parameter not given. Usage: $0 STRING"
    exit 1
fi
STRING=$1
SIZE=${#1}
let "PROCESSES = (2 * $SIZE) - 2"

# preklad cpp zdrojaku
mpic++ -o $PROJ $SRC $HDR

# spusteni
#mpirun -oversubscribe -np $PROCESSES ./$PROJ $STRING
mpirun -np $PROCESSES ./$PROJ $STRING

# uklid
rm -f $PROJ

