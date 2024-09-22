#!/bin/zsh

echo "********************************************************************"
echo "*           Monitor Arduino Serial Interface                       *"
echo "********************************************************************"

arduino-cli monitor -p /dev/cu.usbserial-1410
