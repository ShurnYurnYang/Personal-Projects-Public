#!/bin/bash
clear
g++ -c main.cpp
g++ main.o -o proNav-app -lsfml-graphics -lsfml-window -lsfml-system
./proNav-app

# bash ./run.sh