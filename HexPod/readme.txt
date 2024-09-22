Manual Arduino CLI:
- link: https://arduino.github.io/arduino-cli/1.0/


Arduino configuration:
- Initial configuration:
> arduino-cli config dump
{}

- Run this command to create configuration:
> arduino-cli config init
  Config file written to: /Users/holger/Library/Arduino15/arduino-cli.yaml
> arduino-cli config dump
  board_manager:
    additional_urls: []
> arduino-cli config set directories.user "/Users/holger/Library/Arduino15"
> arduino-cli config dump
board_manager:
    additional_urls: []
directories:
    user: /Users/holger/Library/Arduino15


List boards:
> arduino-cli board list      --> list all connected boards, their ports and FQBNs
> arduino-cli board listall   --> list all FQBNs

Compile:
> arduino-cli compile -b arduino:avr:uno HexPodCli.ino
  Note: -v can be appended for verbose output
> arduino-cli compile --upload --> for compilation and update
> arduino-cli compile --fqbn arduino:avr:uno --library "/Users/holger/dev/Arduino/HexPodCli/lib" -v

Upload to board:
> arduino-cli upload -b arduino:avr:uno  -p /dev/cu.usbserial-1410
> arduino-cli upload -v --> after attach has been executed

Attach sketch to board:
- create a yaml file that connects the sketch with the board, after this attach
  a simple arduino-cli compile command can be executed to compile the source code.
> arduino-cli board attach -p /dev/cu.usbserial-1410 -b arduino:avr:uno -v

Show installed cores:
> arduino-cli core list

Show boards connected to computer:
> arduino-cli board list 
- when a new board is found (and which has not yet been installed) then support for the
  new board can be installed via:
> arduino-cli core install arduino:samd -v   --> adjust the board name here


Update arduino cli:
> arduino-cli update

Search and install for required libraries:
> arduino-cli lib search "library_name"  --> adjust library name
> arduino-cli lib install "library_name"  --> adjust library name



