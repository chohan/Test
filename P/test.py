#!/usr/bin/python

import os,sys,time

a1 = [["Amir", 27],["Ammar",25],["Sana",20]]
a2 = [["Amir", 127],["Ammar",125],["Sana",120]]

print("Bismillah")
N = 3
for i in range(N):
  if a1[i] == a1[i]:
    print("Name=%s, Age=%s, Id=%d" % (a1[i][0], a1[i][1], a2[i][1]))

#select t1.name, t1.id, t2.id from tab t1, tab t2 where t1.id=t2.id

# list comprehension
lc = [x*x for x in range(10)]
print("list comprehension: ", lc)

# generator
gen = (x*x for x in range(10))
print("generator", gen)
for i in gen:
  print(i)
for i in gen:
  print(i+1)

# yield
def squared(nums):
  for x in nums:
    yield(x*x)
sqs = squared([1,2,3,4])
print(sqs)
for i in range(4):
  print(next(sqs))

def list_generator():
  list_comprehension= [x*x for x in range(0, 10)]
  my_generator      = (x*x for x in range(0, 10))
  print(list_comprehension)  # output is a list
  print(my_generator)  # output is an object
  for i in (x*x for x in range(0, 10)): # iterate to prove it is a generator
    print(i)
  print("size of list comprehension=%d" % sys.getsizeof(list_comprehension))
  print("size of generator=%d" % sys.getsizeof(my_generator))


print(dir(os))
print(dir(os.path))
print(os.listdir())
print(os.stat('test.py'))
print(os.getenv("HOME"))
list_generator()
