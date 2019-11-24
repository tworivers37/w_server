#!/bin/bash

cd ../ThreadManager

echo -e "ThreadManager remove!"
make clean

echo -e "\n"

echo -e "Build ThreadManager!"
make ThreadManager
