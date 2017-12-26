cmake_minimum_required(VERSION 3.9)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME mycar)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SKETCH mycar.ino)




#### Uncomment below additional settings as needed.
# set(${CMAKE_PROJECT_NAME}_BOARD mega)
# set(${CMAKE_PROJECT_NAME}_PORT /dev/ttyACM0)
# set(mega.build.mcu atmega2560)
# set(mega.upload.protocol wiring)
# set(mega.upload.speed 115200)
set(CMAKE_CXX_STANDARD 11)

# include Ardunio headers for interception
include_directories(../arduino_clion_template/arduino/cores ../arduino_clion_template/arduino/tools)
include_directories(../arduino_clion_template/arduino/variants/mega)

# include Ardunio libraries
include_directories(../arduino_clion_template/arduino/libraries/Wire/src)
include_directories(../arduino_clion_template/arduino/libraries/SPI/src)
include_directories(../arduino_clion_template/arduino/libraries/SoftwareSerial/src)
include_directories(../arduino_clion_template/arduino/libraries/HID/src)
include_directories(../arduino_clion_template/arduino/libraries/EFPROM/src)

# include custom libraries
include_directories(../../libraries/PinChangeInterrupt/src)


# include custom libraries

add_executable(ArduinoTemplate  mycar.ino constant_define.h colliedSensor.h motor.h)
#generate_arduino_firmware(${CMAKE_PROJECT_NAME})