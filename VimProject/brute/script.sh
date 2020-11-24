#/bin/bash

function compile() {
g++ -D_MY -Wall -Weffc++ -Wextra -Wfloat-conversion -Wconversion -Wshadow -Wno-unused-result -std=c++17 -O2 $1.cpp -o $1 && echo SUCCESS || echo FAIL
}

str=""
compile /home/alexandr/VimProject/source
compile /home/alexandr/VimProject/brute/testsource
compile /home/alexandr/VimProject/brute/generate
chmod -R 777 /home/alexandr/VimProject
cnt=0
while [ ${#str} = 0 ]
do
    sudo /home/alexandr/VimProject/brute/generate
    sudo cp /home/alexandr/VimProject/output.txt /home/alexandr/VimProject/input.txt
    sudo /home/alexandr/VimProject/brute/testsource
    sudo cp /home/alexandr/VimProject/output.txt /home/alexandr/VimProject/brute/output_test.txt
    sudo /home/alexandr/VimProject/source
    str="$(diff -q ~/VimProject/output.txt ~/VimProject/brute/output_test.txt)"
    echo "ok "$cnt
    cnt=$((cnt + 1))
done
diff -y ~/VimProject/output.txt ~/VimProject/brute/output_test.txt
echo

