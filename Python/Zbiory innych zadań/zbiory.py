#def powerset(iterable):
#    "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
#    s = list(iterable)
#    return chain.from_iterable(combinations(s, r) for r in range(len(s)+1))

def sumy(X):
        def zbior(K):
                if K:
                        reszta = zbior(K[1:])
                        return reszta + [[K[0]] + x for x in reszta]
                return [[]]
        L = set()
        for e in zbior(X):
                L.add(sum(e))     
        return (sorted(L))

def generuj(n, a, b):
	if n == 0:
		return [[]]
	else:
		return [[e] + rest for e in range(a,b+1) for rest in generuj(n-1, e, b)]
	
print (generuj(4,0,3))
print()
print(sumy([1,2,3,100]))
print()
#print(powerset([1,2,3]))
