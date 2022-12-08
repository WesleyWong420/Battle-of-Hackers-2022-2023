flag = "APUBOH22{verybabyrev_b4ckw4rd5_i5_verybabyrev}"
flag_array = []

for char in flag:
	string = char.encode('utf-8')
	char_hex = string.hex()
	flag_array.append(char_hex)

print(flag_array[0:5])

i = 0

for item in flag_array:
	flag_array[i] = format((int(item, 16) ^ 42), 'x')
	i = i + 1

print(flag_array[0:5])

j = 0

for xor1 in flag_array[0:23]:
	flag_array[j] = format(((int(xor1, 16) << 3) >> 2), 'x')
	j = j + 1

print(flag_array[0:23])

k = 23

for xor2 in flag_array[23:46]:
	flag_array[k] = format((int(xor2, 16) ^ (int(xor2, 16) << 1)), 'x')
	k = k + 1

print(flag_array[23:46])