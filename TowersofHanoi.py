def test(n):
	if n>0:
		test(n/2)
		print n%2,
test(17)

def test(x,y,s):
	if x != 0:
		if x % 2 == 1:
			s += y
		print s
		test(x/2, 2*y, s)

test(41, 20, 0)
