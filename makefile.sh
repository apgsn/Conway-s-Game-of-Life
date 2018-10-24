#!/bin/bash

g++ Cell.cpp ConwaysField.cpp main.cpp -lsfml-graphics -lsfml-window -lsfml-system -std=c++11 -o "Conway's Game of Life"
./"Conway's Game of Life"
