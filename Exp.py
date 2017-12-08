class Solution(object):
    def findTheDifference(self, s, t):
        for c in s:
            if c in t:
                t = t.replace(c, '', 1)
        return t




sol = Solution()
print sol.findTheDifference("a", "aa")
