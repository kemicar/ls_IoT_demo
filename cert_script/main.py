import binascii
filename = 'ls_prod.pem'
with open(filename, 'rb') as f:
    content = f.read()

print('// '+filename)
print('const char* test_root_ca = \ ')
outString = '"'
caCertLen = 0


x = len(content)

for i in range(0, x-1):
    first = (chr(content[i]))
 #   print(first,content[i])
    if content[i]==13:
        outString = outString + '\\n" \ '
    outString = outString+first
    if content[i]==10:
        outString = outString + '"'
    
outString = outString[:-2] #remove last comma and space

print(outString[:-1]+';')