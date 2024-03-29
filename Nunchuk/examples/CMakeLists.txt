# Just a recent number
cmake_minimum_required(VERSION 3.18)

# Use AVR GCC toolchain definition in your HOME/Arduino directory
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(ARDUINO_PATH $ENV{HOME}/Arduino)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(ARDUINO_PATH "$ENV{HOMEDRIVE}$ENV{HOMEPATH}/Arduino")
endif()
set(CMAKE_TOOLCHAIN_FILE ${ARDUINO_PATH}/etc/toolchain-avr.cmake)

# Project name
project("Nunchuk")

# Product filename
set(PRODUCT_NAME readnunchuk)

# Create one target
# (Linux) `find src -name \*.c\*`
add_executable(${PRODUCT_NAME}
	src/nunchuk.cpp
)

# Add arduino core library
target_include_directories(${PRODUCT_NAME}
	PRIVATE "${ARDUINO_PATH}/include/arduino"
)
target_link_directories(${PRODUCT_NAME}
	PRIVATE "${ARDUINO_PATH}/lib"
)
target_link_libraries(${PRODUCT_NAME}
	nunchuk
	wire
	arduinocore
)

# Rename the output to .elf as we will create multiple files
set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

# Strip binary for upload
add_custom_target(strip ALL ${CMAKE_STRIP} ${PRODUCT_NAME}.elf DEPENDS ${PRODUCT_NAME})

# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL ${CMAKE_OBJCOPY} -R .eeprom -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS strip)

# Transform binary into hex file, this is the eeprom part (empty if you don't
# use eeprom static variables)
add_custom_target(eeprom ${CMAKE_OBJCOPY} -j .eeprom  --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.eep DEPENDS strip)

# Make assembly
add_custom_target(disasm ${CMAKE_OBJDUMP} -h --source --demangle --wide ${PRODUCT_NAME}.elf > ${PRODUCT_NAME}.lss DEPENDS ${PRODUCT_NAME})

# Upload the firmware with avrdude
add_custom_target(upload ${AVRDUDE} ${AVR_PORT} -c ${PROG_TYPE} -p ${MCU} -U flash:w:${PRODUCT_NAME}.hex DEPENDS hex)

# Upload the eeprom with avrdude
add_custom_target(upload_eeprom ${AVRDUDE} ${AVR_PORT}-c ${PROG_TYPE} -p ${MCU}  -U eeprom:w:${PRODUCT_NAME}.eep DEPENDS eeprom)

# Burn fuses
#add_custom_target(fuses ${AVRDUDE} ${AVR_PORT}-c ${PROG_TYPE} -p ${MCU}  -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m -U lock:w:${LOCK_BIT}:m )

# Clean extra files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PRODUCT_NAME}.hex;${PRODUCT_NAME}.eeprom;${PRODUCT_NAME}.lst;${PRODUCT_NAME}.lss")


