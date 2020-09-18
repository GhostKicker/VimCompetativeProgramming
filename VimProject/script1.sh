#/bin/bash

while [ ~/VimProject/source > ~/VimProject/output.txt ]
do
    sudo ~/VimProject/generate > ~/VimProject/input.txt
    echo "ok"
done

