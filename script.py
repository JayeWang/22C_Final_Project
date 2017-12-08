from math import *
import sys
import math
import random

def spam():
	print "Eggs!"
def square(n):
	return n ** 2
def power(base, exponent):
	return base ** exponent
def powerAndsquare(base, exponent):
	return square(power(base, exponent))
def cube(number):
	return number ** 3
def by_three(number):
	if(cube(number) % 3 == 0):
		return True
	else:
		return False
def biggest_number(*args):
	print max(*args)
	return max(*args)
def shut_down(s):
	if s == 'yes':
		return "Shutting down"
	elif s == 'no':
		return "Shutdown aborted"
	else:
		return "Sorry"
def distance_from_zero(n):
	if (type(n) == int) or (type(n) == float):
		return abs(n)
	else:
		return "Nope"


numbers = [5, 6, 7, 8]
letters = ['a', 'b', 'c', 'd', 'e']
letters.append('f')
print letters
print len(letters)

for number in numbers:
	print '{} '.format(number)
print numbers[0] + numbers[2]

spam()
print square(10)
print power(57, 3)
print powerAndsquare(57, 3)
print by_three(57)
print sqrt(24)
everything = dir(math)
print everything
print math.e
print math.factorial(17)
print type(biggest_number(10, 20, 4, 99, 89.99, 78, 34))
print shut_down("yes")
print sqrt(13689)
print distance_from_zero(10.0)
print distance_from_zero('no')

animals = 'catdogfrog'
ANIMALS = ['ant', 'bat', 'cat']
cat = animals[0:3]
dog = animals[3:6]
frog = animals[6:]
print cat
print dog
print frog

print ANIMALS.index("bat")
ANIMALS.insert(1, 'dog')
print ANIMALS


class Data(object):

    def __str__(self):
        return 'str'

    def __repr__(self):
        return 'repr'
print '{0!s} {0!r}'.format(Data())
print '{:_<100}'.format(str(math.factorial(50)))
print '{:_^100}'.format(str(math.factorial(50)))
print '{:_>100}'.format(str(math.factorial(50)))
print '{:.{prec}} = {:.{prec}f}'.format('Gibberish', 2.7182, prec=3)
print '{:.5}'.format('dictionary')
print '{:.10}'.format(str(math.factorial(1000)))

def is_even(x):
	if x % 2 == 0:
		return True
	else:
		return False

def is_int(x):
	if x == round(x):
		return True
	else:
		return False

def digit_sum(n):
	sum = 0
	while n > 0:
		sum += n % 10
		n = n / 10
	return sum

def factorial(n):
	product = 1
	while n >= 1:
		product *= n
		n = n - 1
	return product

def is_prime(x):
	if(x <= 1):
		return False
	for n in range(2, x-1):
		if x % n == 0:
			return False
	return True

def reverse(text):
	str = ""
	size = len(text)
	for index in range(size-1, -1, -1):
		str += text[index]
	return str

def anti_vowel(text):
	for character in text:
		if(is_vowel(character)):
			text = text.replace(character, '')
	return text
def is_vowel(character):
	vowel_string = "aeiouAEIOU"
	for c in vowel_string:
		if character == c :
			return True
	return False

print reverse("abcd")
print factorial(10)
print digit_sum(1234)
print anti_vowel("Hey You!")


score = {"a": 1, "c": 3, "b": 3, "e": 1, "d": 2, "g": 2,
         "f": 4, "i": 1, "h": 4, "k": 5, "j": 8, "m": 3,
         "l": 1, "o": 1, "n": 1, "q": 10, "p": 3, "s": 1,
         "r": 1, "u": 1, "t": 1, "w": 4, "v": 4, "y": 4,
         "x": 8, "z": 10}
def scrabble_score(word):
	sum = 0
	for character in word:
		sum += scores(character)
	return sum

def scores(character):
	for c in score :
		if character == c or character == c.upper():
			return score[c]
print scrabble_score("Helix")


def censor(text, word):
	size = len(word)
	str = list(text.split())
	sizeoftext = len(str)
	for i in range(0, sizeoftext):
		if str[i] == word:
			for index in range(0, size-1):
				str[i] = str[i].replace(str[i], '*'*size)
	text = " ".join(str)
	return text
print censor("this hack is wack hack", "hack")

def count(sequence, item):
	sum = 0
	for obj in sequence:
		if obj == item:
			sum = sum + 1
	return sum
print count([1, 2, 1, 1], 1)


def purify(numbers):
	size = len(numbers)
	even_numbers = []
	for index in range(0, size):
		if numbers[index] % 2 == 0:
			even_numbers.append(numbers[index])
	return even_numbers
print purify([4, 5, 5, 5, 4])


def product(integers):
	p = 1
	for integer in integers:
		p *= integer
	return p
print product([4, 5, 5])

def remove_duplicates(elements):
	new_list = []
	for element in elements:
		if(not contains(new_list, element)):
			new_list.append(element)
	return new_list
def contains(old_list, number):
	for n in old_list:
		if(n == number):
			return True
	return False
print remove_duplicates([1, 1, 2, 2])

def median(elements):
	elements = sorted(elements)
	size = len(elements)
	if size % 2 == 0:
		return float(elements[size/2] + elements[size/2-1])/2
	else:
		return elements[(size-1)/2]
print median([4, 5, 5, 4])



grades = [100, 100, 90, 40, 80, 100, 85, 70, 90, 65, 90, 85, 50.5]
print "Grades:", grades

def print_grades(grades_input):
	for grade in grades_input:
		print grade
print_grades(grades)

def grades_sum(grades_input):
	sum = 0
	for grade in grades_input:
		sum += grade
	return sum
print grades_sum(grades)

def grades_average(grades_input):
	return grades_sum(grades_input) / float(len(grades_input))
print grades_average(grades)

def grades_variance(grades_input):
	average = grades_average(grades_input)
	variance = 0
	for grade in grades:
		variance += (average - grade) ** 2
	return variance / len(grades)
print grades_variance(grades)

def grades_std_deviation(variance):
	return variance ** 0.5
print grades_std_deviation(grades_variance(grades))


#items method does not appear in a specific order
my_dict = {
	"Name" : "Guido",
	"Age" : 56,
	"Gender" : "Male",
	"Height" : 60,
	"BDFL" : True
}

print my_dict.keys()
print my_dict.values()

for x in range(0, 1000):
	print x,
for key in my_dict:
	print key, my_dict[key]

evens_to_50 = [i for i in range(0, 51) if i% 2 == 0]
print evens_to_50

new_list = [x for x in range(1, 6)]
doubles = [element * 2 for element in new_list]
print new_list
print doubles

even_squares = [i ** 2 for i in range(1, 12) if i % 2 == 0]
print even_squares

cubes_by_four = [x ** 3 for x in range(1, 11) if (x ** 3) % 4 == 0]
print cubes_by_four

cubes_by_four_reverse = cubes_by_four[::-1]
print cubes_by_four_reverse

to_one_hundres = range(101)
backwards_by_tens = to_one_hundres[::-10]
print backwards_by_tens

to_21 = range(1, 22)
odds = to_21[::2]
middle_third = to_21[7:14]
print odds
print middle_third


languages = ["HTML", "JavaScript", "Python", "Ruby"]
print filter(lambda string: string == "Python", languages)

squares = [x ** 2 for x in range(1, 11)]
print filter(lambda num: num >= 30 and num <= 70, squares)

threes_and_fives = [x for x in range(1, 16) if x % 3 == 0 or x % 5 == 0]
print threes_and_fives

garbled = "!XeXgXaXsXsXeXmX XtXeXrXcXeXsX XeXhXtX XmXaX XI"
garbled_reverse = garbled[::-1]
print garbled_reverse
message = garbled_reverse[::1]


garbled = "IXXX aXXmX aXXXnXoXXXXXtXhXeXXXXrX sXXXXeXcXXXrXeXt mXXeXsXXXsXaXXXXXXgXeX!XX"
message = filter(lambda c : c != 'X', garbled)
print message

print bin(123)
print oct(1230000)

num  = 0b1100
mask = 0b0100
print bin(num & mask)

def check_bit4(input):
	mask = 0b1000
	desired = bin(input & mask)
	if desired > 0:
		return 'on'
	else:
		return 'off'
check_bit4(100)


def flip_bit(number, n):
	mask = 0b1 << n
	result = number ^ mask
	return result

class Animal(object):
	health = 'good'
	is_alive = True
	def __init__(self, name, age):
		self.name = name
		self.age = age
	def description(self):
		print self.name
		print self.age
hippo = Animal('Joffrey', 37)
sloth = Animal('Cersei', 45)
ocelot = Animal('Jon Snow', 55)
print hippo.health, sloth.health, ocelot.health



class ShoppingCart(object):
  """Creates shopping cart objects
  for users of our fine website."""
  items_in_cart = {}
  def __init__(self, customer_name):
    self.customer_name = customer_name

  def add_item(self, product, price):
    """Add product to the cart."""
    if not product in self.items_in_cart:
      self.items_in_cart[product] = price
      print product + " added."
    else:
      print product + " is already in the cart."

  def remove_item(self, product):
    """Remove product from the cart."""
    if product in self.items_in_cart:
      del self.items_in_cart[product]
      print product + " removed."
    else:
      print product + " is not in the cart."
newCart = ShoppingCart("Jakin")
newCart.add_item('LEMON', 55)
newCart.add_item('StrawBerry', 99)
newCart.add_item('LEMON', 55)


class Shape(object):
	def __init__(self, number_of_sides):
		self.number_of_sides = number_of_sides

class Employee(object):
	def __init__(self, employee_name):
		self.employee_name = employee_name
	def calculate_wage(self, hours):
		self.hours = hours
		return hours * 20.00
class PartTimeEmployee(Employee):
	def calculate_wage(self, hours):
		self.hours = hours
		return hours * 12.00
	def full_time_wage(self, hours):
		return super(PartTimeEmployee, self).calculate_wage(hours)

Emily = Employee('Emily')
print Emily.calculate_wage(80)
Tom = PartTimeEmployee('Tom')
print Tom.calculate_wage(80)
print Tom.full_time_wage(80)
milton = PartTimeEmployee('milton')
print milton.full_time_wage(10)



class Triangle(object):
	number_of_sides = 3
	def __init__(self, angle1, angle2, angle3):
		self.angle1 = angle1
		self.angle2 = angle2
		self.angle3 = angle3
	def check_angles(self):
		if(self.angle1 + self.angle2 + self.angle3 == 180):
			return True
		else:
			return False
my_triangle = Triangle(30, 60, 90)
print my_triangle.number_of_sides
print my_triangle.check_angles()

class Equilateral(Triangle):
	angle = 60
	def __init__(self):
		super(Equilateral, self).__init__(self.angle, self.angle,
			 self.angle)
new_triangle = Equilateral()
print new_triangle.angle1




class Car(object):
	condition = "new"
	def __init__(self, model, color, mpg):
		self.model = model
		self.color = color
		self.mpg = mpg
	def display_car(self):
		print "This is a [%s] [%s] with [%s] MPG" %(self.model, self.color, str(self.mpg))
	def drive_car(self):
		self.condition = 'used'
class ElectricCar(Car):
	def __init__(self, model, color, mpg, battery_type):
		self.model = model
		self.color = color
		self.mpg = mpg
		self.battery_type = battery_type
	def drive_car(self):
		self.condition = 'like new'
car = Car("DeLorean", "silver", 88)
my_car = ElectricCar(car.model, car.color, car.mpg + 30, 'molten salt')
my_car.drive_car()
print my_car.condition


class Point3D(object):
	def __init__(self, x, y, z):
		self.x = x
		self.y = y
		self.z = z
	def __repr__(self):
		return "(%d, %d, %d)" % (self.x, self.y, self.z)
my_point = Point3D(1, 2, 3)
print my_point


my_list = [i ** 2 for i in range(1, 11)]
f = open('output.txt', 'w')
for item in my_list:
	f.write(str(item) + '\n')
f.close



def is_prime(x):
	if(x <= 1):
		return False
	for n in range(2, int(sqrt(x))):
		if x % n == 0:
			return False
	return True
print is_prime(2147483647)


def factorial(n):
	if n == 1:
		return 1
	else:
		return n * factorial(n-1)
print factorial(100)

def countChars(character, str, subscription):
	if subscription >= len(str):
		return 0
	elif str[subscription] == character:
		return 1 + countChars(character, str, subscription + 1)
	else:
		return countChars(character, str, subscription + 1)
print countChars('d', 'dddardwerscvsdawerqwer', 2)

def showMe(arg):
		if(arg > 10):
			return
		print arg
		showMe(arg = arg + 1)
showMe(0)

def GCD(x, y):
	if x % y == 0:
		return y
	else:
		return GCD(y, x%y)
print GCD(2147483647, 2147283646)

def Fibonacci(num):
	if num == 0:
		return 0
	elif num == 1:
		return 1
	else:
		return Fibonacci(num-1) + Fibonacci(num-2)

arr = []
for x in range(0, 2000):
	arr.append(0)
print arr
arr[1] = 1
for x in range(2, 2000):
	arr[x] = arr[x-1] + arr[x-2]
print arr[100]

arr.sort()

def BinarySearch(arr, start, end, element):
	mid = (start + end)/2
	if(start > end):
		return False
	elif arr[mid] == element:
		return mid
	elif element > arr[mid]:
		return BinarySearch(arr, mid + 1, end, element)
	elif element < arr[mid]:
		return BinarySearch(arr, start, mid-1, element)
print BinarySearch(arr, 0, len(arr) - 1, 354224848179261915075)

def Hanoi(discs, start, temporary, end):
	if discs <= 0:
		return
	else:
		Hanoi(discs-1, start, end, temporary)
		Hanoi.counter += 1
		Hanoi(discs-1, temporary, start, end)
Hanoi.counter = 0
def print_Hanoi(num):
	Hanoi(num, 3, 2, 1)
	print Hanoi.counter
print_Hanoi(10)

random_arr = []
for x in range(0, 100):
	random_arr.append(random.randint(1, 1000))
print random_arr
random_arr.sort()
print random_arr
