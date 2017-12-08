import math
def Factorial(n):
    if n < 0:
        return -1
    elif n == 0 or n == 1:
        return 1
    else:
        return n * Factorial(n-1)
print Factorial(100)

def summation(num):
    if num < 10:
        return num
    else:
        return num % 10 + summation(num/10)
print summation(99999999999999)

def Fibonacci(n):
    if n == 1 or n == 2:
        return 1
    else:
        return Fibonacci(n-1) + Fibonacci(n-2)

print Fibonacci(10)

def fun(num):
    if num > 0:
        fun(num/10)
        print num % 10,
    print '*',
fun(345)
