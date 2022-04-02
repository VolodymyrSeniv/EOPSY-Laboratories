#!/bin/bash


# Defining training functions


# help screen - Test1

# no options - Test2

# parameter collision - Test3

# uppercasing no-recursion - Test4

# uppercasing recursion - Test5

# lowercasing no-recursion - Test6

# lowercasing recursion - Test7

# empty directory - Test8

# not existing directory and file - Test9

# not file/directories arguments provided - Test10

# not file/directories arguments provided - Test11

#creating some directories to work with 
scriptCall=$1
Dir=$(pwd)
rm -rf Modify
mkdir Modify
mkdir Modify/Folder3
mkdir Modify/Folder4
mkdir Modify/Folder4/DontChangeFolder
mkdir Modify/Folder5
mkdir Modify/Folder5/ChangeMeFolder
mkdir Modify/Folder6
mkdir Modify/Folder6/DontChangeFolder
mkdir Modify/Folder7
mkdir Modify/Folder7/ChangeMeFolder
mkdir Modify/Folder8
read -n 1 -s -r -p "Press any key to continue "

Test1()
{
testNo=T1
echo
echo "$testNo: $scriptCall -h"
echo "Displaying a help message"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall -h
echo 
}


Test2()
{
testNo=T2
echo
echo "$testNo: $scriptCall"
echo "Raising an exception, because no options were selected"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall
echo 
}

Test3()
{
testNo=T3
echo
cd Modify/Folder3
touch Test3f
cd ..
cd ..
echo "$testNo: $scriptCall -u -l Modify/Folder3/test3f"
echo "Raising an exception, because of  parameter collision"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall -u -l Modify/Folder3/test3f
echo 
}

Test4()
{
testNo=T4
echo
cd Modify/Folder4
touch Test4f
cd DontChangeFolder
touch DontChangeFolderf
cd "$Dir"
echo "$testNo: $scriptCall -u Modify/Folder4/"
echo "Uppercasing files in Folder4 folder without recursion"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall -u Modify/Folder4/
echo 
}

Test5()
{
testNo=T5
echo
cd Modify/Folder5
touch Test5f
cd ChangeMeFolder
touch ChangeMeFolderf
cd "$Dir"
echo "$testNo: $scriptCall -u -r Modify/Folder5/"
echo "Script should uppercase files in Folder5 folder with recursion"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall -u -r Modify/Folder5/
echo 
}

Test6()
{
testNo=T6
echo
cd Modify/Folder6
touch Test6f
cd DontChangeMeFolder
touch DontChangeMeFolderf
cd "$Dir"
echo "$testNo: $scriptCall -l Modify/Folder6/"
echo "Lowercasing files in Folder6 folder without recursion"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall -l Modify/Folder6/
echo 
}

Test7()
{
testNo=T7
echo
cd Modify/Folder7
touch Test7f
cd ChangeMeFolder
touch ChangeMeFolderf
cd "$Dir"
echo "$testNo: $scriptCall -l -r Modify/Folder7"
echo "Lowercasing files in Folder7 folder with recursion"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall -l -r Modify/Folder7
echo 
}

Test8()
{
testNo=T8
echo
echo "$testNo: $scriptCall -l -r Modify/Folder8"
echo "No files - nothing to perform"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall -l -r Modify/Folder8
echo 
}

Test9()
{
testNo=T9
echo
echo "$testNo: $scriptCall -l -r  Modify/FRJNWVJWNR Modify/VREVEVEV/some.txt"
echo "Passed arguments don't exist, nothing to perform"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall -l -r Modify/FRJNWVJWNR/ Modify/VREVEVEV/some.txt
echo 
}

Test10()
{
testNo=T10
echo
echo "$testNo: $scriptCall -l -r"
echo "No files/directories to operate, nothing to perform"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall -l -r
echo 
}

Test11()
{
testNo=T11
echo
echo "$testNo: $scriptCall -l -r"
echo "Indicating invalid operation -[l|r] used together with -h"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
read -n 1 -s -r -p "Press any key to continue "
sh ./$scriptCall -l -h
echo 
}

#calling the tests
Test1

Test2

Test3

Test4

Test5

Test6

Test7

Test8

Test9

Test10

Test11

exit 0

