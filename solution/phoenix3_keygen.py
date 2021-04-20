
print('Input Name:', end = ' ')
name = input()
ebx = 0xdeadc0de

for ch in name:
    edx = ord(ch)
    edx = (edx << 8) + edx 
    edx = (edx << 16) + edx
    ebx = ebx ^ edx
    ebx = ebx & 0xfefed0d0
    ebx = ebx | 0x000159a3
    eax = ebx & 0x0000ffff
    ebx = ebx >> 16
    ebx = ebx ^ eax

ebx = ebx & 0x0000ffff
sta = ebx

fibo = [10946, 17711, 28657, 46368, 75025]
res = ''

for eax in fibo:
    eax = eax ^ ebx
    eax = eax & 0x0000ffff
    sta = sta ^ eax
    eax = str(eax)
    while len(eax) < 5: 
        eax = '0' + eax 
    res += eax + '-'

print('Serial:', res[:-1])
