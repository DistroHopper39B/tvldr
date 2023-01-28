.PHONY: inject_kernel
# handy tools to remember under darwin tools
# otool -l mach_kernel 
# size -m mach_kernel
#
#
ARCH	= i386

CC  := i686-linux-gnu-gcc
LD  := i686-linux-gnu-ld
OBJCOPY := i686-linux-gnu-objcopy
LDFLAGS = -T mach-o.ld -melf_i386 --no-undefined -z notext --orphan-handling=warn -z nocopyreloc --gc-sections -pie

# start.o must be 1st in the link order (ld below)
OBJ2	= start.o vsprintf.o console.o utils.o elilo_code.o darwin_code.o linux_code.o boot_loader.o
OBJ = boot_loader.o linux_code.o darwin_code.o elilo_code.o utils.o console.o vsprintf.o start.o

mach_kernel: $(KERN_OBJ) $(OBJ)
	$(LD) $(LDFLAGS) -o mach_kernel.elf $(OBJ) \
	-static

%.o:	%.c
	$(CC) -c -static -nostdlib -fno-stack-protector -O0 -o $@ -c $<

%.o:	%.s
	$(CC) -c -static -nostdlib -DASSEMBLER -o $@ -c $<
macho:  mach_kernel.elf
	$(OBJCOPY) -O binary --strip-debug mach_kernel.elf mach_kernel

clean:
	rm -f *.o mach_kernel*
#         -sectcreate __TEXT __vmlinuz vmlinuz \
        -sectcreate __TEXT __initrd initrd.img
# -e must be accounted for.