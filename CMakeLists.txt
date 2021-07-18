
add_library(u8g2_port_hal u8g2_port_hal.c)
target_include_directories(u8g2_port_hal INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(u8g2_port_hal
        PRIVATE
        stm32cube::hal
        u8g2
        )
