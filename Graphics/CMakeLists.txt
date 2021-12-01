# Just a recent number
cmake_minimum_required(VERSION 3.18)

# Use AVR GCC toolchain definition in your HOME/Arduino directory
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(ARDUINO_PATH $ENV{HOME}/Arduino)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    cmake_path(CONVERT "$ENV{HOMEDRIVE}$ENV{HOMEPATH}/Arduino" TO_CMAKE_PATH_LIST ARDUINO_PATH NORMALIZE)
endif()
set(CMAKE_TOOLCHAIN_FILE ${ARDUINO_PATH}/etc/toolchain-avr.cmake)

# we need the assembler this time
enable_language(ASM)

# Project name
project("graphicslibs")

# The deliverable
set(PRODUCT_NAME graphicslibs)

# Where to install
set(CMAKE_INSTALL_PREFIX ${ARDUINO_PATH})

# Target: the Arduino core library with all core source files to compile
# To get a list of .c and cpp files in Linux:
#       cd <project directory>
#       find src/cores/arduino -name \*.[cSs]\*
add_library(${PRODUCT_NAME} STATIC
        src/cores/arduino/wiring_pulse.S
	src/cores/arduino/abi.cpp
	src/cores/arduino/CDC.cpp
	src/cores/arduino/HardwareSerial0.cpp
	src/cores/arduino/HardwareSerial1.cpp
	src/cores/arduino/HardwareSerial2.cpp
	src/cores/arduino/HardwareSerial3.cpp
	src/cores/arduino/HardwareSerial.cpp
	src/cores/arduino/hooks.c
	src/cores/arduino/IPAddress.cpp
	src/cores/arduino/main.cpp
	src/cores/arduino/new.cpp
	src/cores/arduino/PluggableUSB.cpp
	src/cores/arduino/Print.cpp
	src/cores/arduino/Stream.cpp
	src/cores/arduino/Tone.cpp
	src/cores/arduino/USBCore.cpp
	src/cores/arduino/WInterrupts.c
	src/cores/arduino/wiring_analog.c
	src/cores/arduino/wiring.c
	src/cores/arduino/wiring_digital.c
	src/cores/arduino/wiring_pulse.c
	src/cores/arduino/wiring_shift.c
	src/cores/arduino/WMath.cpp
	src/cores/arduino/WString.cpp
	src/libraries/Wire/src/Wire.cpp
        src/libraries/Wire/src/utility/twi.c
        src/libraries/SPI/src/SPI.cpp
        src/IOBus/Adafruit_BusIO_Register.cpp
        src/IOBus/Adafruit_I2CDevice.cpp
        src/IOBus/Adafruit_SPIDevice.cpp
        src/display/Adafruit_GFX.cpp
        src/display/Adafruit_GrayOLED.cpp
        src/display/Adafruit_SPITFT.cpp
        src/display/glcdfont.c
	src/device/Adafruit_ILI9341.cpp
)

# Here the compiler finds include files (-I flags)
target_include_directories(${PRODUCT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cores/arduino
        ${CMAKE_CURRENT_SOURCE_DIR}/src/variants/standard
	${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/Wire/src
	${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/Wire/src/utility
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/SPI/src
	${CMAKE_CURRENT_SOURCE_DIR}/src/IOBus
	${CMAKE_CURRENT_SOURCE_DIR}/src/display
	${CMAKE_CURRENT_SOURCE_DIR}/src/device
)

# All .h files of Arduino core
# To get a list of .h files (in Linux):
#       cd <project directory>
#       find src/cores/arduino -name \*.h
# Also include the pins_arduino.h file
#       src/variants/standard/pins_arduino.h
set(INCLUDES
        src/variants/standard/pins_arduino.h
	src/cores/arduino/Arduino.h
	src/cores/arduino/binary.h
	src/cores/arduino/Client.h
	src/cores/arduino/HardwareSerial.h
	src/cores/arduino/HardwareSerial_private.h
	src/cores/arduino/IPAddress.h
	src/cores/arduino/new.h
	src/cores/arduino/PluggableUSB.h
	src/cores/arduino/Printable.h
	src/cores/arduino/Print.h
	src/cores/arduino/Server.h
	src/cores/arduino/Stream.h
	src/cores/arduino/Udp.h
	src/cores/arduino/USBAPI.h
	src/cores/arduino/USBCore.h
	src/cores/arduino/USBDesc.h
	src/cores/arduino/WCharacter.h
	src/cores/arduino/wiring_private.h
	src/cores/arduino/WString.h
	src/libraries/Wire/src/Wire.h
        src/libraries/Wire/src/utility/twi.h
        src/libraries/SPI/src/SPI.h
        src/IOBus/Adafruit_BusIO_Register.h
        src/IOBus/Adafruit_I2CDevice.h
        src/IOBus/Adafruit_SPIDevice.h
        src/IOBus/Adafruit_I2CRegister.h
        src/display/Adafruit_GFX.h
        src/display/Adafruit_GrayOLED.h
        src/display/Adafruit_SPITFT.h
        src/display/gfxfont.h
        src/display/Adafruit_SPITFT_Macros.h
        src/device/Adafruit_ILI9341.h
)

# Install the library here (INSTALL_PREFIX_PATH is prepended)
install(TARGETS ${PRODUCT_NAME} ARCHIVE DESTINATION lib)
install(FILES ${INCLUDES} DESTINATION include/arduino)
