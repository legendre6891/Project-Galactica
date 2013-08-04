import operator

def is_perm(tup):
        return sorted(str(tup[0])) == sorted(str(tup[1]))

phisArr = []
with open('phis_small', 'r') as phis:
    for line in phis.readlines():
        phisArr += map(int, line.strip('\n ,').split(', '))
        
permphis = filter(is_perm, enumerate(phisArr[1:], start=2))
ratphis = map(lambda (x,y): (x,float(x)/y), permphis)

print(min(ratphis, key=operator.itemgetter(1)))

