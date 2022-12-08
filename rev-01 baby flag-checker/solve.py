#!/usr/bin/env python3

cipher1 = "d6f4fed0cac43030a2b89eb0a6909690a6b09eb8ea903c"
cipher2 = "dbc3e722e8d2219fc5219fe4d1e8f5d8ddd8f5e8d1e4f9"

byte_array1 = bytearray.fromhex(cipher1)
byte_array2 = bytearray.fromhex(cipher2)

firstFlag = ""
secondFlag = ""

for byte in byte_array1:

    # Printable ASCII characters in Decimal
    for i in range(33, 127):
        if (((i ^ 42) << 1) == byte):
            firstFlag += chr(i)

for byte in byte_array2:

    # Printable ASCII characters in Decimal
    for i in range(33, 127):
        if (((i ^ 42) ^ ((i ^ 42) << 1)) == byte):
            secondFlag += chr(i)
 
print(firstFlag + secondFlag)