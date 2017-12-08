class Solution(object):
    def isUgly(self, num):
        u = [1]
        i2, i3, i5 = 0, 0, 0
        while num > 1:
            u2, u3, u5 = 2 * u[i2], 3 * u[i3], 5 * u[i5]
            umin = min(u2, u3, u5)
            if umin == u2:
                i2 += 1
            if umin == u3:
                i3 += 1
            if umin == u5:
                i5 += 1
            u.append(umin)
            num -= 1
        return u[-1]
sol = Solution()
print sol.isUgly(1690)
