cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME DataLogger_Mephi_2026_1)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Core/App/app.c
    ${CMAKE_SOURCE_DIR}/Core/App/multi_button/button.c
    ${CMAKE_SOURCE_DIR}/Drivers/lwbtn/lwbtn.c

    # --- Драйвер ST7735 (LCD) ---
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/LCD/lcd.c
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/LCD/images.c
            
        # --- Библиотека DS18B20 ---
    ${CMAKE_SOURCE_DIR}/Drivers/ds18b20/ds18b20.c

    # --- Библиотека UGUI ---
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/ugui.c
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/ugui_button.c
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/ugui_checkbox.c
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/ugui_image.c
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/ugui_progress.c
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/ugui_textbox.c

    # --- Шрифты UGUI (автоматический сбор всех .c файлов из папки Fonts) ---
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/Fonts/font_10x16.c
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/Fonts/font_12x16.c
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/Fonts/font_16x26.c
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/Fonts/font_8x12.c
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/Fonts/arial_10X13_cyrillic.c
        # --- Путь к заголовкам DS18B20 ---
    ${CMAKE_SOURCE_DIR}/Drivers/ds18b20

)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/Core/Inc/app
    ${CMAKE_SOURCE_DIR}/Drivers
    ${CMAKE_SOURCE_DIR}/Drivers/lwbtn
    
    # --- Пути к заголовкам ST7735 и UGUI ---
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/LCD
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI
    ${CMAKE_SOURCE_DIR}/Drivers/st7735/UGUI/Fonts
)


# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
