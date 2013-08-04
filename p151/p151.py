
import random

splits = { 16: [1,2,4,8],
           8 : [1,2,4],
           4 : [1,2],
           2 : [1],
           1 : [],
           }


def runweek():
    t = 0
    papers = [16]
    while papers:
        if len(papers) == 1:
            t += 1
        n = random.randrange(len(papers))
        papers[n:n+1] = splits[papers[n]]
    
    return t - 2

def runsimulation():
    n = 0.
    ones = 0
    while True:
        n += 1
        ones += runweek()
        if n % 1000 == 0:
            print(ones / n)

runsimulation()
