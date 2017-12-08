class Solution(object):
    def calculate(self, s):
        total = 0
        i, signs = 0, [1, 1]
        while i < len(s):
            c = s[i]
            if c.isdigit():
                start = i
                while i < len(s) and s[i].isdigit():
                    i += 1
                total += signs.pop() * int(s[start:i])
                continue
            if c in '+-(':
                signs.append(signs[-1] * (-1 if c == '-' else 1))
            elif c == ')':
                signs.pop()
            i += 1
        return total

s = Solution()
print s.calculate('1+2-3+4-5+6')
