import numpy as np
import time, datetime
import random

def my_numpy():
    l = []
    for i in range(100):
        lsub=[]
        for j in range(100):
            lsub.append(0)
        l.extend([lsub])

    a=np.zeros((100, 100))
    tl1 = time.time()
    for i in range(100):
        for j in range(100):
            l[i][j] = l[i][j] + 5
    tl2 = time.time()
    tl = tl2 - tl1

    ta1 = time.time()
    ArrayOp = "a=a+10"
    ta2 = time.time()
    ta = ta2 - ta1
    print(ta, tl)

def test1():
    for i in range(20):
        #print(random.random())
        print(random.randrange(2,10))
    print(5//2, 5%2)

def test2():
    print("Hey John. How are you John".replace('John', 'john', 1))
    print("Hey John. How are you John".replace('John', 'john'))

def addToList(val, list=[]):
    list.append(val)
    return list

g = lambda x,y : x + y

def test3():
    """ this is called doc string"""
    list1 = addToList(1)
    list2 = addToList(123, [])
    list3 = addToList('a')
    print("list1 = %s" % list1)
    print("list2 = %s" % list2)
    print("list3 = %s" % list3)
    print(test3.__doc__)
    help(test3)
    str = "this is sample"
    print(str.split(' '))

    N = 3
    arr = np.array([1,2,3,4,5])
    print(arr.argsort()[-N:][::-1]) #????

    train_set = np.array([1,2,3])
    test_set  = np.array([[0,1,2],[1,2,3]])
    #print("train_set.append(test_set)", train_set.append(test_set)) # no arrtibute 'append'
    #print("np.concatenate([train_set, test_set])", np.concatenate([train_set, test_set]))
    print("np.vstack([train_set, test_set])", np.vstack([train_set, test_set]))
    #print("np.vstack([train_set, test_set])", np.hstack([train_set, test_set]))

    # reverse a string
    str = 'hello friend'
    ls = list(str)
    print(str);print(ls);ls.reverse();print(' '.join(ls))

    print("lambda", g(3,4))


def test4(*var):
    """ testing variable No of argments """
    for a in var:
        print(a),

import functools
def filter_map_reduce():
    lst = [x for x in range(10)]
    print("even list: ", list(filter(lambda x: x%2 == 0, lst)))
    print("odd list: ", list(filter(lambda x: x%2 != 0, lst)))
    print("map list: ", list(map(lambda x: x*2, lst)))
    print("sum: ", functools.reduce((lambda x, y: x + y), lst))

def py_functions():
    ''' any, all, len, min, max and sum '''
    print("py_functions: ", "any, all, len, min, max and sum")
    lst = [x for x in range(10)]
    print("any: %s" % bool(any(lst)))
    print("bin: %s" % bin(10))
    print("bytearray: %s" % bytearray(10))
    print(bytes(10))
    x = compile('print(55)', 'test', 'eval'); exec(x) 
    c1 = complex(1,2); print("complex: %s" % c1)
    print("quotient=%d, modulus=%d" % (5//2, 5%2)); print(divmod(5,2))
    print(list(enumerate(lst, 3)))
    print("int=%d, float=%f" % (10, 10))
    print("binary=%f, unicode=%d, scientific=%e" % (10, 10, 10))
    print("fix=%f, general=%g, octal=%o" % (10, 10, 10))
    print("hex=%x, number=%d, percentage=%d" % (10, 10, 10))
    print("globals: %s" % globals())
    print("locals: %s" % locals())
    print("hash: &=%s" % hash("Salah Chohan"))
    print("max %d" % max((x for x in range(10))))
    print("max %d" % max([x for x in range(10)]))
    print("max %d" % max(lst))
    print("min %d" % min(lst))
    print(memoryview(b"Hello"))
    print(dir(object()))
    print(range(10))    # xrange is not defined in python3
    print("reversed: %s" % list(reversed(lst)))
    print("slice: %s" % lst[slice(3)])
    lst = [9,1,8,3,7,4,6,5,8,9]
    print(sorted(lst))
    l1 = [1,2,3]
    l2 = ['a','b','c']
    l3 = ["hello", "hi", "wow"]
    print(list(zip(l1,l2,l3)))

from ctypes import cdll
def c_functions():
    lib = cdll.LoadLibrary('./libforPython.so')
    #lib = CDLL('./libforPython.so')
    print("calling C func: ", lib.add(4,5))
    print("calling C func: ", lib.subtract(7,4))

def fibonacci(num):     # acting as generator
    a, b = 0, 1
    for i in range(0, num):
        #print(a)
        yield a
        a, b = b, a+b

def fibonacci_caller():
    for item in fibonacci(12):
        print(item)

class Person(object):
    def __init__(self, name):
        self.name = name
    def identity(self):
        print("My name is %s" % self.name)

class SuperHero(Person):
    def __init__(self, name, hero_name):
        super(SuperHero, self).__init__(name)
        self.hero_name = hero_name
    def identity(self):
        super(SuperHero, self).identity()
        print("... and I am %s" % self.hero_name)

class ContextManager(object):
    def __init__(self):
        print("init method is called")

    def __enter__(self):
        print("enter method is called by context manager")

    def __exit__(self, exec_type, exec_value, exec_trackback):
        print("exit method is called by context manager")

with ContextManager() as manager:
    print('with statement block') 
       
cm = ContextManager()

def collections():
    lst = [4,3,6,2,7,5,2]   # ordered, changeable and indexed
    tpl = (4,3,6,2,7,5,2)   # ordered, unchangeable and indexed
    stt = {'cherry', "apple", 'orange'} # unordered, changeable, unindexed
    dct = {"model": "mustang", "brand": "Ford",  "year": 1974} # unordered, changeable, indexed
    print(lst);lst[3]=33;print(lst[3])
    print(tpl);print(tpl[3])
    print(stt);#print(stt[3]);#stt[3]=33;
    print(dct);dct[2]=1964;print(dct[2])
    print("duplicates removed: %s" % list(dict.fromkeys(lst)))

def my_datetime():
    dd = datetime.datetime.now()
    print(dd.strftime("%Y%m%d: %H%M%S:%f"))

###############################
class Singleton:
   __instance = None
   @staticmethod 
   def getInstance():
      """ Static access method. """
      if Singleton.__instance == None:
         Singleton()
      return Singleton.__instance
   def __init__(self):
      """ Virtually private constructor. """
      if Singleton.__instance != None:
         raise Exception("This class is a singleton!")
      else:
         Singleton.__instance = self
s = Singleton();print(s)
s = Singleton.getInstance();print(s)
s = Singleton.getInstance();print(s)


if __name__ == '__main__':
    #my_numpy()
    #test1()
    #test2()
    #test3()
    #test4(1);test4(1,2,3); test4('a', 'b', 'c')
    #filter_map_reduce()
    #py_functions()
    #c_functions()
    #fibonacci_caller()
    #collections()
    #my_datetime()
    

    salah = Person("Salah")
    salah.identity()
    wade = SuperHero("Wade Wilson", "Deadpool")
    wade.identity()
    print("Hello World"[::-1])  # reverse string


