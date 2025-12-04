cmake_minimum_required(VERSION 3.13)

set(project_name "MacroMasterKeyboard")

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

# Pull in FreeRTOS
set(FREERTOS_KERNEL_PATH "../firmware/FreeRTOS-Kernel")
include(FreeRTOS_Kernel_import.cmake)

project(example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

pico_sdk_init()

# add_executable(${project_name} ${SRC_FILES})
add_executable(${project_name}
        src/main.c
        src/blink.c
        src/usb_descriptors.c
        src/usb.c
        src/usb_keyboard_hid.c
        # src/deep_sleep.c
        # src/sd_driver.c
        src/ssd1306_driver.c
        src/ssd1306_gfx.c
        # src/display_app.c
        # src/animations.c
        # src/keyboard.c
        # src/pong_game.c
        )

target_compile_definitions(${project_name} PRIVATE
        mainCREATE_SIMPLE_BLINKY_DEMO_ONLY=1
        )

target_compile_options( ${project_name} PUBLIC
        ### Gnu/Clang C Options
        $<$<COMPILE_LANG_AND_ID:C,GNU>:-fdiagnostics-color=always>
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-fcolor-diagnostics>

        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wall>
        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wextra>
        $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Werror>
        $<$<COMPILE_LANG_AND_ID:C,Clang>:-Weverything>
        )

target_include_directories(${project_name} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/inc
        ${FREERTOS_DEMO_PATH}/Common/include
        )


target_link_libraries(${project_name}
        pico_stdlib
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap1
        hardware_spi
        hardware_i2c
        tinyusb_device
        tinyusb_board
        )

pico_add_extra_outputs(${project_name})

# Use USB uart
pico_enable_stdio_usb(${project_name} 1)
pico_enable_stdio_uart(${project_name} 1)
