from math import floor


def legendre(n, p):
    pow = 0
    k = 1
    while True:
        val = floor(n / p**k)
        if val == 0:
            return pow
        pow += val
        k += 1

MOD = 1000000009
N = 100000000


if __name__ == '__main__':
    primes = []
    ans = 1
    with open('primes', 'r') as primes_file:
        for line in primes_file.readlines():
            p = int(line)
            leg = legendre(N, p)
            ans *= 1 + (p, 2*leg, MOD)
            if ans > MOD:
                ans %= MOD
                print(p)
    print(ans)
