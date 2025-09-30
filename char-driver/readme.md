# Simple Char Device Kernel Module

This is a basic Linux kernel module that implements a simple character device. It allows reading from and writing to a fixed-size buffer in the kernel.

## Features

- Character device with `read` and `write` operations.
- Logs `open`, `read`, `write`, and `release` calls to the kernel log.
- Fixed buffer size: 64 bytes.
<img width="1928" height="1080" alt="print1" src="https://github.com/user-attachments/assets/0ab87d38-aa9d-4bb9-9356-f78ea74c29bb" />

## Usage

```bash
# Monitor new kernel messages
sudo dmesg -W

# Insert the module
sudo insmod test.ko

# Check dmesg for the major number
dmesg | tail

# Create a device file (replace {major} with the number from dmesg)
sudo mknod /dev/teste1 c {major} 0

# Write to the kernel buffer
./write

# Read from the kernel buffer
./read
    
