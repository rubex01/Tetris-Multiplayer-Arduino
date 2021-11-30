# Install script for directory: /home/martijn/Graphics

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/martijn/Arduino")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "avr-objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/martijn/Graphics/build/libgraphicslibs.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/arduino" TYPE FILE FILES
    "/home/martijn/Graphics/src/variants/standard/pins_arduino.h"
    "/home/martijn/Graphics/src/cores/arduino/Arduino.h"
    "/home/martijn/Graphics/src/cores/arduino/binary.h"
    "/home/martijn/Graphics/src/cores/arduino/Client.h"
    "/home/martijn/Graphics/src/cores/arduino/HardwareSerial.h"
    "/home/martijn/Graphics/src/cores/arduino/HardwareSerial_private.h"
    "/home/martijn/Graphics/src/cores/arduino/IPAddress.h"
    "/home/martijn/Graphics/src/cores/arduino/new.h"
    "/home/martijn/Graphics/src/cores/arduino/PluggableUSB.h"
    "/home/martijn/Graphics/src/cores/arduino/Printable.h"
    "/home/martijn/Graphics/src/cores/arduino/Print.h"
    "/home/martijn/Graphics/src/cores/arduino/Server.h"
    "/home/martijn/Graphics/src/cores/arduino/Stream.h"
    "/home/martijn/Graphics/src/cores/arduino/Udp.h"
    "/home/martijn/Graphics/src/cores/arduino/USBAPI.h"
    "/home/martijn/Graphics/src/cores/arduino/USBCore.h"
    "/home/martijn/Graphics/src/cores/arduino/USBDesc.h"
    "/home/martijn/Graphics/src/cores/arduino/WCharacter.h"
    "/home/martijn/Graphics/src/cores/arduino/wiring_private.h"
    "/home/martijn/Graphics/src/cores/arduino/WString.h"
    "/home/martijn/Graphics/src/libraries/Wire/src/Wire.h"
    "/home/martijn/Graphics/src/libraries/Wire/src/utility/twi.h"
    "/home/martijn/Graphics/src/libraries/SPI/src/SPI.h"
    "/home/martijn/Graphics/src/IOBus/Adafruit_BusIO_Register.h"
    "/home/martijn/Graphics/src/IOBus/Adafruit_I2CDevice.h"
    "/home/martijn/Graphics/src/IOBus/Adafruit_SPIDevice.h"
    "/home/martijn/Graphics/src/IOBus/Adafruit_I2CRegister.h"
    "/home/martijn/Graphics/src/display/Adafruit_GFX.h"
    "/home/martijn/Graphics/src/display/Adafruit_GrayOLED.h"
    "/home/martijn/Graphics/src/display/Adafruit_SPITFT.h"
    "/home/martijn/Graphics/src/display/gfxfont.h"
    "/home/martijn/Graphics/src/display/Adafruit_SPITFT_Macros.h"
    "/home/martijn/Graphics/src/device/Adafruit_ILI9341.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/martijn/Graphics/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
