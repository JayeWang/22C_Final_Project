import operator
class Solution(object):
    def getSum(self, a, b):
        INT_MAX = 1 << 33
        result = a ^ b
        carry = a & b
        while carry != 0:
            carry_t = carry << 1
            carry = carry_t & result
            result = result ^ carry_t
        return result if result <= INT_MAX else ~result

sol = Solution()
print sol.getSum(-3, -5)
