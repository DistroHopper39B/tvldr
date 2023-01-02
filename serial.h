#ifndef _SERIAL_H_
#define _SERIAL_H_
#include "types.h"
#define COM1 0x3F8 // <- the COM1 serial address, at least in VirtualBox

// outb definition for c wrapper (https://wiki.osdev.org/Inline_Assembly/Examples)
static void outb(uint16_t port, uint8_t val);
static uint8_t inb(uint16_t port);
#endif