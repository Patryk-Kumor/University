def prefix(s,t):
    return s[0:len(s)]==t[0:len(s)]

def sumaDlugosciABC(L):
    return sum([(lambda x: len(L[x]))(x) for x in range(len(L))])

def c(A,B):
    return A+1 if A > B else A-1
