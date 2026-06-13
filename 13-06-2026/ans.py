from pwn import *
import re
p = process('/challenge/run')
totl_qus = 5
c_qus = 0
clach = {'UC' : 0, 'C' : 1, 'S' : 2, 'TS' : 3}
print("started")

while c_qus < totl_qus:
	
	qus = p.recvline_startswithb(b'Q').decode().split(" ")
	print(qus)
	c_qus = int(qus[1][:-1])
	subject_clach = clach[qus[7]]
	subject_category = qus[qus.index('categories') + 1: qus.index('an') - 1]
	c_subject_category = [re.sub(r'[{,}?]', '', s) for s in subject_category]
	permission = qus[qus.index('an') - 1]
	object_clach = clach[qus[qus.index('level' , -9) + 1]]
	object_category = qus[qus.index('categories', -9) + 1:]
	c_object_category = [re.sub(r'[{,}?]', '', s) for s in object_category]
	
	if permission == 'read':
		is_clach = subject_clach >= object_clach
		is_object = set(c_object_category).issubset(set(c_subject_category))
	
	elif permission == 'write':
		is_clach = subject_clach <= object_clach
		is_object = set(c_subject_category).issubset(set(c_object_category))

	if is_clach and is_object:
		print("answer is: Yes ")
		p.sendline(b"yes")
	else:
		print("answer is: No ")
		p.sendline(b"no")
	
print("Successfully ended")
ans = p.recvline_startswithb(b'pwn').decode()
print(ans)			