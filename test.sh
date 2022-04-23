#!/bin/bash
PROJ=pro
SRC=$PROJ.cpp
HDR=$PROJ.h
PROCESSES=1

# preklad cpp zdrojaku
mpic++ -o $PROJ $SRC $HDR

# spusteni
#mpirun -oversubscribe -np $PROCESSES ./$PROJ
mpirun -np $PROCESSES ./$PROJ

# uklid
rm -f $PROJ

