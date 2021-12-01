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
project("NunchukLib")

# The deliverable
set(PRODUCT_NAME nunchuk)

# Where to install
set(CMAKE_INSTALL_PREFIX ${ARDUINO_PATH})

# Target: the Nunchuk library with all core source files to compile
# To get a list of .c and cpp files in Linux:
#       cd <project directory>
#       find src/cores/arduino -name \*.[cSs]\*
add_library(${PRODUCT_NAME} STATIC
	src/Nunchuk.cpp
)

# Here the compiler finds include files (-I flags)
target_include_directories(${PRODUCT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${ARDUINO_PATH}/include/arduino
)

# All .h files of Nunchuk lib
# To get a list of .h files (in Linux):
#       cd <project directory>
#       find src -name \*.h
# Also include the pins_arduino.h file
#       src/variants/standard/pins_arduino.h
set(INCLUDES
	src/Nunchuk.h
)

# Install the library here (INSTALL_PREFIX_PATH is prepended)
install(TARGETS ${PRODUCT_NAME} ARCHIVE DESTINATION lib)
install(FILES ${INCLUDES} DESTINATION include/arduino)
