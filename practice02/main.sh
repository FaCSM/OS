#!/bin/bash
g++ -c main1.cpp
g++ -o main1 main1.o -lpthread
rm main1.o
./main1
rm main1
g++ -c main2.cpp
g++ -o main2 main2.o -lpthread
rm main2.o
./main2
rm main2
g++ -c main3.cpp
g++ -o main3 main3.o -lpthread
rm main3.o
./main3
rm main3