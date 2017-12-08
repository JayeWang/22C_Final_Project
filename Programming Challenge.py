def Factorial(n):
    if n <= 1:
        return 1
    else:
        return n * Factorial(n-1)
print Factorial(6)

def sign(num):
    if num == 0:
        return;
    print "No Parking"
    sign(num = num - 1)
sign(5)

def Array_Sum(list, size):
    if(size <= 0):
        return 0
    else:
        return Array_Sum(list, size - 1) + list[size - 1]
list = [1, 2, 3, 4, 5]
print Array_Sum(list, 5)

def Recursive_Multiplication(x, y):
    if x == 0:
        return 0
    else:
        return y + Recursive_Multiplication(x-1, y)
print Recursive_Multiplication(500,7)

def Recursive_Power(base, exp):
    if exp == 0:
        return 1
    else:
        return base * Recursive_Power(base, exp - 1)
print Recursive_Power(3, 100)

def Sum_of_Numbers(num):
    if num == 0:
        return 0
    else:
        return num + Sum_of_Numbers(num - 1)
print Sum_of_Numbers(200)

def String_Reverser(str):
    print str[::-1]
String_Reverser("123131232131312313111111")

def A(m, n):
    if m == 0:
        return n+1
    elif n == 0:
        return A(m-1, 1)
    else:
        return A(m-1, A(m, n-1))

print pow(2, pow(2, pow(2, pow(2, pow(2, 2))))) - 3
