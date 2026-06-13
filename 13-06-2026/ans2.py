#!/usr/bin/python

from pwn import *
import sys

context.log_level = 'error'

totl_qus = 128
p = process('/challenge/run')
c_qus = 0
p.recvuntil(b'more sensitive):\n')
clach = []
for _ in range(40):
    clach.append(p.recvline().decode().strip())
print("started")
rm_char = str.maketrans('', '', '{,}?')

while c_qus < totl_qus:
    
    qus = p.recvline_startswith(b'Q').decode().split()
    
    c_qus = int(qus[1][:-1])
    print(c_qus)
    subject_clach = clach.index(qus[7])
    
    cat1_ix = qus.index('categories')
    an_ix = qus.index('an')
    
    c_subject_category = set(s.translate(rm_char) for s in qus[cat1_ix + 1: an_ix - 1])
    permission = qus[an_ix - 1]
    object_clach = clach.index(qus[qus.index('level' , -9) + 1])
    obj_cat_ix = qus.index('categories', -9)
    c_object_category = set(s.translate(rm_char) for s in qus[obj_cat_ix + 1:])
    
    if permission == 'read':
        is_clach = subject_clach <= object_clach
        is_object = c_object_category.issubset(c_subject_category)
    
    elif permission == 'write':
        is_clach = subject_clach >= object_clach
        is_object = c_subject_category.issubset(c_object_category)

    if is_clach and is_object:
        p.sendline(b"yes")
    else:
        p.sendline(b"no")
    
ans = p.recvline_startswith(b'pwn').decode()
print(ans)
