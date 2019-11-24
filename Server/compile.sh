#/bin/bash

cd ./Server/


echo -e "Object Remove!"
make clean

echo -e "\n"

echo -e "ThreadManager compile.sh"
sh -c ../ThreadManager/compile.sh

echo -e "Build!"
make all