#!/bin/zsh

echo "********************************************************************"
echo "*           Build the Arduino Package                              *"
echo "********************************************************************"

echo "List all connected boards:"
arduino-cli board list

echo "Compile project:"
# arduino-cli compile --fqbn arduino:avr:uno --library "/Users/holger/dev/Arduino/HexPod/lib" -v
arduino-cli compile --clean --fqbn arduino:avr:uno --library "/Users/holger/dev/Arduino/HexPod/lib" 
# /Library/Developer/CommandLineTools/usr/include/c++/v1/ c++ standard library

# Check the return code
if [[ $? -eq 0 ]]; then
    echo "Upload project:"
    arduino-cli upload -b arduino:avr:uno  -p /dev/cu.usbserial-1410
elif [[ $? -eq 1 ]]; then
    echo "-----------------------------"
    echo "Error: Compilation error"
    echo "-----------------------------"
else
    echo "-------------------------------------"
    echo "Command failed with return code: $?"
    echo "-------------------------------------"
fi
