l=[]
while len(l) < 1024 * 1024:
    l.append(object())
print (len(l))
while True:
    pass

# top - 13:45:08 up 23 days, 13:04,  2 users,  load average: 2.77, 2.80, 2.66
# Tasks: 660 total,   4 running, 655 sleeping,   1 stopped,   0 zombie
# %Cpu(s):  1.7 us,  0.5 sy,  2.5 ni, 95.2 id,  0.0 wa,  0.1 hi,  0.0 si,  0.0 st
# MiB Mem : 257723.9 total, 194712.1 free,  23363.0 used,  39648.8 buff/cache
# MiB Swap:  40436.0 total,  40436.0 free,      0.0 used. 230857.9 avail Mem 

#     PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                              
# 2115876 yamato    25   5  254404  32780   4788 R  99.7   0.0   0:20.37 python                                               
# --------------------------------------^ about 32 byte?
