/*
Serial COM1 output code for tvldr. 
*/
#include "serial.h"

extern int printk(const char *szFormat, ...);

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

// Init serial
int init_serial() {
   char *str = "Hello, world!";
   int i;
   for (i = 0; str[i] != '\0'; i++) {
      outb(COM1, str[i]);
   }
   return 0;
}