# Memory Info Kernel Module

This is a simple Linux kernel module that implements a character device to display memory information. It shows total, used, and free RAM in MB.
ex on cat /dev/ram: **TOTAL RAM: 8000MB, USED:5000MB, FREE:3000MB**

## Features

- Character device with `read` operation.
- Shows system memory stats: total RAM, used RAM, and free RAM.
- Logs initialization and unloading of the module to the kernel log.
- Buffer size: 128 bytes.
<img width="1770" height="300" alt="printmem" src="https://github.com/user-attachments/assets/3cc22303-f92f-4819-94da-43b175c12f66" />

## Usage

```bash
# Monitor kernel messages
sudo dmesg -W

# Insert the module
sudo insmod test.ko

# Check dmesg for the major number
dmesg | tail

# Create a device file (replace {major} with the number from dmesg)
sudo mknod /dev/ram c {major} 0

# Read memory info from the kernel buffer
cat /dev/ram
