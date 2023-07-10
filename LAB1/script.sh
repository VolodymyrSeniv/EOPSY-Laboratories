#!/bin/bash

# Defining environment variables together with initial values

#I define the name of the script. Also using "basename" we can read the filename without extention from a directory or file path.# Defining name of the script
self=$(basename $0)


# Defining sed configuration-specific call method
sedCall=sed

# Display start-up message
echo "//////////////////////////"
echo "The script $lab1 is running"
echo "//////////////////////////"
echo

# Defining arguments
Lowerize=0  # lowercase -l argument
Upperize=0  # uppercase -u argument
Recursion=0  # recursive -r argument
Help=0  # help      -h argument

#defining patterns with regular expression
#s; - defines the string
#(.*) - means match any number of any characters so standing alone like thos means: Match everything, even if nothing is there.
#\U or \L - coresponds to the changes we want to make U-uppering, L-lowering  
#\1 - means, that everything found in the quotes automatically print as default 
regexUperize="s/\(.*\)/\U\1/"  # for UPPERCASE
regexLowerize="s/\(.*\)/\L\1/"  # for lowercase
chosenRegexR=""                # externally provided pattern

# Defining help function
ShowHelp()
{
echo "Instruction how to use"
echo "$lab1 -r -l or -u <dir/filenames...>"
echo "$lab1 -r <sed pattern> <dir/filenames...>"
echo "$lab1 -h"
echo "///////////////////////////////////////////"
echo "Notation:"
echo "-l, lowerizing directory and filenames"
echo "-u, upperizing directory and filenames"
echo "-r, recursive mode"
echo "-h, showing this help message"
echo
exit 0
}

# Defining arguments exception function
RaiseException()
{
echo "Can not perform operation: "$@""
echo "Type $lab1 -h to show help"
echo "//////////////////////////////////////////"
echo "Stop"
}


# Parsing option arguments
# lurh as an optstring
while getopts "lurh" argument; do
    case ${argument} in
        l)Lowerize=1;;
        u)Upperize=1;;
        r)Recursion=1;;
        h)Help=1;;
    esac
done

#using this command I shift to another command line argument(non option) 
shift "$((OPTIND-1))"

#Conditional statement to control the input to the script in terminal.
if [ ${Lowerize} -eq "1" ] || [ ${Upperize} -eq "1" ]; then
    if [ ${Help} -eq "1" ]; then
    RaiseException "Script cannot be run with -h and -[u|l] at the same time!"
    fi
fi

# Show help message if -h argument was set
if [ ${Help} = "1" ]; then
    ShowHelp
fi

# Raise argument exception if -l and -u are set at ones
if [ ${Lowerize} -eq "1" ] && [ ${Upperize} -eq "1" ]; then
    RaiseException "Lowerizing [-l] and uppercasing [-u] options cannot be performed at the same time!"
fi

# if anything was provided
if [ $# -lt 1 ]; then
	RaiseException "None of the options was selected or no arguments provided!"
fi


# According to mode, set pattern for sed tool. Connecting my arguments with the regular expression with the corresponding input in the command line
if [ ${Lowerize} -eq "1" ]; then
    chosenRegex=${regexLowerize}
elif [ ${Upperize} -eq "1" ]; then
    chosenRegex=${regexUperize}
else
    chosenRegex=$1  #if the no recongnisable pattern was set then the one from the command line is chosen
    shift 1    #moving to the next command line argument
fi

#///////////////////////////////////////////////////////////////////////////////////////
#find - is used to find files and directories, also it performs the subsequent operations on them.
#sed - used as a stream editor for serching, find replace, insert and delete files. 
#mv - a linux comand which has a property of renaming files and directories 
#grep - tool which is used to search for a string of characters in a specified file. It is searching with the help of regular expression.
#tac - tac command in Linux is used to concatenate and print files in reverse. This command will write each FILE to standard output, the last line first. When no file is specified then this command will read the standard input.
#-n - 
#-maxdepth - limits a search for a directory 
#New argument to store the file names to modify 
array="$@"
# check array length
if [ ${#array[@]} -eq "0" ]; then
    RaiseException "Nothing to rename"
fi
# Process next files/directories arguments
# Defining current file pointern
for arrayPtr in "${array[@]}"; do
    # set find command parameters together with 'tests' set to files only
    if [ ${Recursion} -eq "1" ]; then
       #recursive method

        findCall="find | grep \"${arrayPtr}\" | tac" 
    else
       #non-recursive
        findCall="find ${arrayPtr} -maxdepth 0 | tac"
    fi

    eval $findCall |while read -r filePtr; do


        # proccesing the current directory and file names
        currentDir=$(dirname "$filePtr")
        currentFile=$(basename "$filePtr")

       #performing a selected operation on the file name and making the new one
        newFile=$(echo -n ${currentFile} | $sedCall -e "$chosenRegex")

#changing the file name with the help of mv command
        mv -- "$filePtr" "$currentDir/$newFile"
    done

done

