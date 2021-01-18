
#warning "Compiling my own driver for remote stripe. ThiS can break tons of stuff!"

#include <WiFiUdp.h>

enum class preset_ops : uint8_t
{
    NOOP              = 0,
    SETPIXEL          = 1,
    FADEOUT           = 2,
    FADEIN            = 3,
    BRIGHT            = 4,
    SETPIXEL_NOSHOW   = 5,
    SHOW              = 6,
    PRESET            = 7,
};

struct __attribute__((packed)) led_packet
{
    preset_ops special_ops;
    uint16_t pos;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

void send_wakeup_packet()
{
    if (TasmotaGlobal.global_state.network_down) return;

    const led_packet packet = {
      .special_ops = preset_ops::PRESET
    };

    char buff[sizeof(packet)];
    memcpy(&buff, (const void *) &packet, sizeof(packet));

    WiFiUDP UDP;
    UDP.beginPacket(IPAddress(192, 168, 32, 230), 1337);
    UDP.write(buff);
    UDP.endPacket();
}


#define XDRV_128			128

bool Xdrv128(uint8_t function) {
  bool result = false;

  switch (function) {
    case FUNC_WEB_ADD_HANDLER:
      send_wakeup_packet();
      break;
  }
  return result;
}