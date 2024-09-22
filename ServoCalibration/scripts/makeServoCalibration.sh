#!/bin/zsh

echo "********************************************************************"
echo "*           Build the Arduino Package                              *"
echo "********************************************************************"

echo "List all connected boards:"
arduino-cli board list

echo "Compile project:"
# arduino-cli compile --fqbn arduino:avr:uno --library "/Users/holger/dev/Arduino/ServoCalibration/lib" -v
arduino-cli compile --clean --fqbn arduino:avr:uno --library "/Users/holger/dev/Arduino/ServoCalibration/lib" 

echo "Upload project:"
arduino-cli upload -b arduino:avr:uno  -p /dev/cu.usbserial-1410
