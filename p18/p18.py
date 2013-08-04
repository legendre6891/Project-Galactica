#!/usr/bin/env python

with open('p18_nums.txt', 'r') as file:
    triangle = [ [ int(y) for y in x.split(' ') ] for x in file.read()[:-1].split('\n') ]

# top-down method
#for i, line in enumerate(triangle[1:]):
#    pl = triangle[i]
#    for j in range(i + 2):
#        if j == 0:
#            line[0] += pl[0]
#        elif j == i + 1:
#            line[j] += pl[i]
#        else:
#            line[j] += max(pl[j], pl[j - 1])
#print(max(triangle[-1]))

# bottom-up method
for i in range(len(triangle) - 1, 0, -1):
    nl = triangle[i]
    l = triangle[i - 1]
    for j in range(len(l)):
        l[j] += max(nl[j], nl[j + 1])
print(triangle[0][0])
