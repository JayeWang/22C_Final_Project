bit = [[0, 0] for _ in range(32)]
print bit

def getBit(num):
    number = 0
    while(num > 0):
        num /= 2
        number += 1
    return number
def MAIN(num1, num2):
    var1 = getBit(num1)
    var2 = getBit(num2)
    x = num1
    if var2 - var1 >= 1:
        return 0
    else:
        for _ in range(num1 + 1, num2 + 1):
            x = x & _
        return x


class Solution(object):
    def getBit(self, num):
        number = 0
        while(num > 0):
            num /= 2
            number += 1
        return number
    def rangeBitwiseAnd(self, num1, num2):
        var1 = self.getBit(num1)
        var2 = self.getBit(num2)
        x = num1
        if var2 - var1 >= 1:
            return 0
        else:
            for _ in range(num1 + 1, num2 + 1):
                x = x & _
            return x
s = Solution()
print s.rangeBitwiseAnd(4, 8)

def LinearSearch(array, element):
    for num in array:
        if num == element:
            return True
    return False

def BinarySearch(array, element):
    def BinarySearch_Helper(array, element, start, end):
        if start == end:
            return start == element
        middle = (start + end) // 2
        if array[middle] == element:
            return True
        elif array[middle] > element:
            if low == middle:
                return False
            else:
                return BinarySearch(array, element, start, middle-1)
        else:
            return BinarySearch(array, element, middle+1, end)
    if len(array == 0):
        return False
    else:
        return BinarySearch_Helper(array, element, 0, len(array) - 1)

def BubbleSort(array):
    swap = False
    while not swap:
        swap = True
        for i in range(1, len(array)):
            if array[j-1] > array[j]:
                swap = True
                array[j-1], array[j] = array[j], array[j-1]

def SelectionSort(array):
    suffix = 0
    while suffix != len(array):
        for i in range(suffix + 1, len(array)):
            if array[i] < array[suffix]:
                array[i], array[suffix] = array[suffix], array[i]
        suffix += 1


def mergeSort(array):
    if len(array) < 2:
        return array
    else:
        middle = len(array) // 2
        left = mergeSort(array[:middle])
        right = mergeSort(array[middle:])
        return merge(left, right)
def merge(left, right):
    i, j = 0, 0
    result = []
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    while i < len(left):
        result.append(left[i])
        i += 1
    while j < len(right):
        result.append(right[j])
        j += 1
    return result

print mergeSort([9, 1, 7, 3, 4, 6, 78, 4, 35, 67, 0, 3])

# Python function to print permutations of a given list
def permutation(lst):

    # If lst is empty then there are no permutations
    if len(lst) == 0:
        return []

    # If there is only one element in lst then, only
    # one permuatation is possible
    if len(lst) == 1:
        return [lst]

    # Find the permutations for lst if there are
    # more than 1 characters

    l = [] # empty list that will store current permutation

    # Iterate the input(lst) and calculate the permutation
    for i in range(len(lst)):
       m = lst[i]

       # Extract lst[i] or m from the list.  remLst is
       # remaining list
       remLst = lst[:i] + lst[i+1:]

       # Generating all permutations where m is first
       # element
       for p in permutation(remLst):
               l.append([m] + p)
    return l



# Driver program to test above function
for _ in permutation([1,2,3,4,5]):
    print _

from itertools import combinations
class Solution(object):
    def combine(self, n, k):
        lst = []
        for _ in range(1, n+1):
            lst.append(_)
        comb = list(combinations(lst, k))
        return comb
s = Solution()
print s.combine(4, 2)

def makeCOM(lst, temp, num, n, k):
    if k == 0:
        lst.append(temp)
        return
    else:
        for i in range(num, n+1):
            temp.append(i)
            makeCOM(lst, temp, num+1, n, k-1)
def COM(n, k):
    temp = []
    lst = []
    makeCOM(lst, temp, 1, n, k)
    return lst
lst = COM(4,2)
print lst
