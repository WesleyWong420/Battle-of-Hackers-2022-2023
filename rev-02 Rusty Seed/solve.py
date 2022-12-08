#!/usr/bin/env python3
from pwn import *
from math import sqrt

def approximateMiddleValue(num):

    curr = int(num)
    root = int(sqrt(curr)*100)

    return root*(10**4), (root+100)*(10**4)

def getNextRand(seed):

    mid = str(seed)[-12:-4] # Middle 8 charcters
    m_s = int(mid)**2

    return m_s, str(m_s)[:-12]  # New seed, leading characters

def bruteForce(rand1, rand2, rand3):

    count = 0
    next1 = next2 = next3 = next4 = "" 
    min_val, max_val = approximateMiddleValue(rand1)

    for i in range(min_val, max_val):
        seed = i**2

        if str(seed)[:-12] == rand1:
            seed, num = getNextRand(seed)

            if num == rand2:      
                for x in range(5):                     
                    seed, num = getNextRand(seed)  

                    if x == 0 and num != rand3: 
                        break   
                    elif x != 0: 
                        if count == 0:
                            next1 = num
                            count += 1
                        elif count == 1:
                            next2 = num
                            count += 1
                        elif count == 2:
                            next3 = num
                            count += 1
                        elif count == 3:
                            next4 = num
                            count += 1
                if x == 5: 
                    break

    return next1, next2, next3, next4
        
def exploit():

    elf = ELF('./rustyseed')

    #p = elf.process()
    p = remote('18.143.17.69', 9004)

    # Stage 1
    log.info(p.recvuntil(b'> '))
    p.sendline(b'1')

    log.info(p.recvuntil(b'Output: '))
    data = p.recvline()
    data = data.replace(b"\n", b"")
    print(data)

    log.info(p.recvuntil(b'> '))
    p.sendline(b'2')

    # Middle-square method
    log.info(p.recvuntil(b'> '))
    data = int(str(data)[-13:-5])**2
    p.sendline(str(data))
    print(data)

    log.info(p.recvuntil(b'> '))
    data = int(str(data)[-12:-4])**2
    p.sendline(str(data))
    print(data)

    # Stage 2
    log.info(p.recvuntil(b'> '))
    p.sendline(b'1')

    # Request for 3 succeeding number to perform Brute-forcing
    log.info(p.recvuntil(b'Output: '))
    data1 = p.recvline()
    data1 = data1.replace(b"\n", b"")
    data1 = data1.decode('UTF-8')
    print(data1)

    log.info(p.recvuntil(b'> '))
    p.sendline(b'1')

    log.info(p.recvuntil(b'Output: '))
    data2 = p.recvline()
    data2 = data2.replace(b"\n", b"")
    data2 = data2.decode('UTF-8')
    print(data2)

    log.info(p.recvuntil(b'> '))
    p.sendline(b'1')

    log.info(p.recvuntil(b'Output: '))
    data3 = p.recvline()
    data3 = data3.replace(b"\n", b"")
    data3 = data3.decode('UTF-8')
    print(data3)

    out1, out2, out3, out4 = bruteForce(data1, data2, data3)

    # Submit 4 guesses
    log.info(p.recvuntil(b'> '))
    p.sendline(b'2')

    log.info(p.recvuntil(b'> '))
    p.sendline(str(out1))
    print(out1)

    log.info(p.recvuntil(b'> '))
    p.sendline(str(out2))
    print(out2)

    log.info(p.recvuntil(b'> '))
    p.sendline(str(out3))
    print(out3)

    log.info(p.recvuntil(b'> '))
    p.sendline(str(out4))
    print(out4)

    log.info(p.recvuntil(b'}'))

def main():
    exploit()

if __name__ == "__main__":
    main()