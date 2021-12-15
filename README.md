# KBSMC Project
#### This repository contains a multiplayer game that communicates via infrared and uses a nunchuk as its input. 

### Important
* Please always run lint before pushing to a branch. We cant setup ci/cd jobs to check before merging automatically because school hasn't setup any runners.

### Requirements
* gcc-avr
* binutils-avr
* avr-libc
* avrdude
* make
* cmake
* python
* pip
* cpplint

### Running lint
1. Make sure you have python and pip installed (`sudo apt install python3`) & (`sudo apt install pip`)
2. Make sure you have pip installed (`pip install cpplint`)
3. To make sure cpplint is working you can run `cpplint --help` if it's not working you might need to reboot your system
4. Run `chmod +x ./cpplint.sh` to make the file executable
5. Run `cpplint.sh`

### Setup for developers
1. start
* Clone this repository
* Install python
* Install cpplint by running `pip install cpplint`
2. Installing Graphics library:
* Cd into the `./Graphics` dir
* Run `cmake -B build`
* Run `cmake --build build`
* Run `cmake --install build`
3. Installing Nunchuk library:
* Cd into the `./Nunchuk` dir
* Run `cmake -B build`
* Run `cmake --build build`
* Run `cmake --install build`
4. Setting right hz:
* Setup the right khz in the main (either 56 or 38)
5. Installing onto arduino
* Run `cmake -B build`
* Run `cmake --build build`
* Run `make -C build upload`
* You're done 🚀

