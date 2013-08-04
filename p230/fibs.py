from math import floor

def genfibs(n):
    a = 1
    b = 1
    for _ in range(n):
        yield a
        tmp = a
        a = b
        b += tmp


def F(n):
    return (127 + 19*n)*7**n


def fibceil(n):
    for f in genfibs(1000):
        if f > n:
            break
    return f


phi = 1.61803398875

def getdigit(n):
    return 2 + floor(n * phi) - floor((n+1) * phi)

A = '1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679'
B = '8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196'
#A='1415926535'
#B='8979323846'

def D(n):
    m = len(A)
    count = fibceil(n/m) * m - n
    if getdigit(1 + count // m) == 0:
        word = B
    else:
        word = A
    return int(word[-(count % m) - 1])

res = 0
for n in range(18):
    res += 10 ** n * D(F(n))
print(res)
