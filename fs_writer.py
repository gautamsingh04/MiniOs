# with open("disk.img", "wb") as f:
# f.write(b'\x00' * (512 * 9))  # 9 sectors = 4608 bytes
# nasm -f bin bootloader.asm -o bootloader.bin
# i686-elf-gcc -ffreestanding -c shell.c -o shell.o
# i686-elf-ld -Ttext 0x1000 shell.o -o shell.bin --oformat binary
# gcc hosted_shell_main.c fs_impl.c read_sector.c -o shell_main.exe
# gcc sector_viewer.c read_sector.c -o sector_viewer.exe
