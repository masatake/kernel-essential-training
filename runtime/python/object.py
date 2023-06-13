import os

n = 1024 * 1024 * 10
a = []

print ('pid = %d; press a key to start'%(os.getpid()))
input()

for i in range(n):
    o = object()
    a.append(o)

print ('allocation is done. I will enter spinning. Find me with top')
while True:
    pass

