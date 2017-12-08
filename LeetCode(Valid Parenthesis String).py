class Solution(object):
    def plusOne(self, digits):
        num = self.getNumber(digits)
        num += 1
        lst = self.toDigit(num)
        return lst

    def getNumber(self, digits):
        base = 1
        total = 0
        for index in range(len(digits)-1, -1, -1):
            number = digits[index] * base
            total += number
            base *= 10
        return total
    def toDigit(self, num):
        lst = []
        while num > 0:
            lst.append(num%10)
            num /= 10
        return lst[::-1]






s = Solution()
print s.plusOne([1, 8, 1, 1, 1, 0, 0 ,0 ,0])
print s.plusOne([2])
