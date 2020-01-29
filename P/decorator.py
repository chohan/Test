#!/usr/bin/python

import os,sys,time


registery = []

def register(func):
  print('registering %s' % func)
  registery.append(func)
  return func
@register
def df1():
  print("hi from df1")
df1()
@register
def df2():
  print("hi from df2")
df2()


def uppercase_decorator(function):
  def wrapper():
    #func = function()
    #make_uppercase = function().upper()
    #return make_uppercase
    return function().upper()
  return wrapper

def split_str(function):
  def wrapper():
    return function().split()
  return wrapper

@split_str
@uppercase_decorator
def say_hi():
  ''' split_str(uppercase_decorator(say_hi())) '''
  return "hello there"

a1 = say_hi()
print(a1)

def outer(func):
  msg = "this is decorator(outer/inner)"
  def inner():
    print(msg)
  return inner
@outer
def deco_func():
  print("deco_func print is never called")
deco_func()


def arbitrary_args(function):
  def wrapper(*args, **kwargs):
    print("positional args", args)
    print("keyword args", kwargs)
    function(*args, **kwargs)
  return wrapper

@arbitrary_args
def func_with_no_args():
  print("No arguments")

func_with_no_args()
#func_with_no_args(1,'a','b',40)
#func_with_no_args(key1='hi', key2='hello')

import types
class SelfDocumenting( object ):
    @classmethod
    def getMethods( aClass ):
        return [ (n,v.__doc__) for n,v in aClass.__dict__.items()
                 if type(v) == types.FunctionType ]
    def help( self ):
        """Part of the self-documenting framework"""
        print(self.getMethods())

class SomeClass( SelfDocumenting ):
    attr= "Some class Value"
    def __init__( self ):
        """Create a new Instance"""
        self.instVar= "some instance value"
    def __str__( self ):
        """Display an instance"""
        return "%s %s" % ( self.attr, self.instVar )
someClass = SelfDocumenting()
print(someClass.getMethods())

######################## closure ############################
def outer2(text):
  ''' closure function'''
  msg = text
  def inner():
    print(msg)
  return inner
my_closure = outer2("I am closure");my_closure()

def cls_multiply(m):
  def op(n):
    return m*n
  return op
cls_f1 = cls_multiply(10)
cls_f2 = cls_multiply(20)
print("closure:  %d" % cls_f1(4))
print("closure:  %d" % cls_f2(4))



############################## partial functions ########################
import functools
def multiply(x, y):
    return x * y
doubler = functools.partial(multiply, 2)
print(doubler(4))



