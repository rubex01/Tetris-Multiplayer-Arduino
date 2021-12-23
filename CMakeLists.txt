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
project("KBS")

# Product filename
set(PRODUCT_NAME KBS)

# Create one target
# (Linux) `find src -name \*.c\*`
add_executable(${PRODUCT_NAME}
        src/main.cpp
        src/Controller/Controller.cpp
        src/Display/Display.cpp
        src/Scenes/GameScene/GameScene.cpp
        src/Tetris/Block.cpp
        src/Tetris/Tetrominoes/OBlock.cpp
        src/Tetris/Tetrominoes/TBlock.cpp
        src/Tetris/Tetrominoes/IBlock.cpp
        src/Tetris/Tetrominoes/JBlock.cpp
        src/Tetris/Tetrominoes/LBlock.cpp
        src/Tetris/Tetrominoes/SBlock.cpp
        src/Tetris/Tetrominoes/ZBlock.cpp
        src/Tetris/BlockFactory.cpp
        src/Tetris/Score.cpp
        src/Communication/IRCommunication.cpp src/Communication/IRCommunication.h src/Communication/SendQueue.cpp src/Communication/SendQueue.h src/Communication/ReceivedData.cpp src/Communication/ReceivedData.h src/Communication/Frame.cpp src/Communication/Frame.h src/Scenes/Scene.cpp src/Scenes/Scene.h src/Scenes/StartScene/StartScene.cpp src/Scenes/StartScene/StartScene.h src/Scenes/LoseScene/LoseScene.cpp src/Scenes/LoseScene/LoseScene.h src/Scenes/WinScene/WinScene.cpp src/Scenes/WinScene/WinScene.h src/HighScore/HighScore.cpp src/HighScore/HighScore.h)



# Add arduino core library
target_include_directories(${PRODUCT_NAME}
        PRIVATE "${ARDUINO_PATH}/include/arduino"
        )
target_link_directories(${PRODUCT_NAME}
        PRIVATE "${ARDUINO_PATH}/lib"
        )
target_link_libraries(${PRODUCT_NAME}
        graphicslibs
        arduinocore
        nunchuk
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
