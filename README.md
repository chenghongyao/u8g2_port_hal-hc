# 说明

基于 STM32 HAL 库，为`u8g2`提供 IO 支持。

# 配置

下列端口都为可选项，按需设置

- 输出端口
  - U8G2_CS
  - U8G2_SCK
  - U8G2_MOSI
  - U8G2_DC
  - U8G2_RESET
  - U8G2_SCL
  - U8G2_SDA
- 输入端口
  - U8G2_SELECT
  - U8G2_NEXT
  - U8G2_PREV
  - U8G2_MENU

# CMake 引入

```CMake
add_subdirectory(stm32cube)
add_subdirectory(3rdparty/u8g2/csrc)
add_subdirectory(3rdparty/u8g2_port_hal)

add_executable(app.elf main.c)
target_link_libraries(app.elf
    PRIVATE
    stm32cube::core
    u8g2
    u8g2_port_hal)

```

# 使用

```C++
#include "u8g2.h"
#include "u8g2_port_hal.h"
void setup() {
    u8g2_Setup_ls013b7dh03_128x128_2(&u8g2,U8G2_R0,u8x8_byte_4wire_sw_spi,u8x8_gpio_and_delay_hal);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0); // wake up display
}
```
