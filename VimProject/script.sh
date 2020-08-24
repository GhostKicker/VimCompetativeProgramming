#/bin/bash


str=""
while [ ${#str} = 0 ]
do
    sudo ~/VimProject/generate > ~/VimProject/input.txt
    sudo ~/VimProject/test > ~/VimProject/output1.txt
    sudo ~/VimProject/source > ~/VimProject/output.txt
    str="$(diff -q  ~/VimProject/output1.txt ~/VimProject/output.txt)"
    echo "ok"
done
cat ~/VimProject/input.txt
diff -y ~/VimProject/output.txt ~/VimProject/output1.txt

