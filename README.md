# MiniOs

# Mini OS (Bootloader + Shell + File System)

A simple educational operating system built from scratch using x86 Assembly and C. This project demonstrates a custom bootloader, a shell written in C, and a virtual file system stored in a flat disk image. All components run in hosted mode (via .exe) or can be compiled into a bootable OS image.

## 📦 Features

* Bootloader in x86 Assembly (loads shell from disk)
* Freestanding shell in C (compiled for flat memory)
* Simulated FAT-like file system inside disk.img
* Supports file and directory commands:

  * `dir`, `cat`, `mkdir`, `delete`, `write`, `save`, `select`, `help`

## 📂 Directory Structure

```
project/
├── bootloader.asm         # Assembly bootloader code
├── shell.c / shell.o      # Freestanding shell code (bare-metal)
├── hosted_shell_main.c    # Shell version for hosted mode (Windows/Linux)
├── fs_impl.c              # File system logic
├── read_sector.c          # Reads sector from disk image
├── fs.h                   # Shared header for shell and fs
├── disk.img               # Virtual disk image (bootable and testable)
├── fs_writer_multi.py     # Script to populate file table + file data
├── disk_image_builder.py  # (Optional) Script to build a full disk image
├── shell_hosted.exe       # Hosted shell binary for testing
```

## 🛠️ Build Instructions (Hosted Mode)

1. Install GCC (MinGW for Windows or gcc on Linux).
2. Compile the shell:

   ```bash
   gcc hosted_shell_main.c fs_impl.c read_sector.c -o shell_hosted.exe
   ```
3. Run:

   ```bash
   ./shell_hosted.exe
   ```

## 🧪 Example Shell Usage

```
$ dir
f1.txt       [FILE]
f2.txt       [FILE]

$ cat f1.txt
This is file 1.

$ write notes.txt
Enter file content (end with ~ on a new line):
This is a test file.
~

$ mkdir backup
Directory created (in memory only)

$ delete f2.txt
File deleted (in memory only)

$ save
File table written to disk
```

## 💾 File System Format

* Sector 4: File table (30 entries max)
* Each FileEntry has:

  * name\[12]
  * type: 0 = file, 1 = dir
  * start\_sec
  * size\_sec
* File contents stored in sectors 6+

## 🧰 Tools Used

* NASM: Compile bootloader
* GCC: Compile shell & file system logic
* QEMU: For boot testing (if shell compiled as flat binary)
* Python: Scripts to write data to disk.img

## 🚀 Future Work

* Enable real mode execution via QEMU
* Add rename/move file support
* Enhance memory persistence for delete/mkdir
* GUI front-end for file system explorer

## 🙌 Credits

Built as a learning project for operating system fundamentals, file systems, and compiler design.

---

Feel free to fork, experiment, and modify!

MIT License
