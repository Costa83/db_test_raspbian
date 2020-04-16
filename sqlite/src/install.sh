#!/bin/bash

rm -rf ../bin/*
make clean
make all
cp sttTest* ../bin/
make clean
