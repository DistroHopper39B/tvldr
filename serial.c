/*
Serial COM1 output code for tvldr. 
*/
#include "types.h"
#define COM1 0x3F8 // <- the COM1 serial address, at least in VirtualBox

// outb definition for c wrapper (https://wiki.osdev.org/Inline_Assembly/Examples)
void outb(uint16_t port, uint8_t val)
{
    __asm__ __volatile__ ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

// inb defintion for c wrapper
uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__ ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}
/*
int init_serial() {
   char *str = "Hello, world!";
   int i;
   for (i = 0; str[i] != '\0'; i++) {
      outb(COM1, str[i]);
   }
   return 0;
}
*/

void PrintToSerial(const char *szBuffer) {
   int i;
   for (i = 0; szBuffer[i] != '\0'; i++) {
      outb(COM1, szBuffer[i]);
   }
}