def f(x):
    return x * 2
def g(x):
    return x + 1

def compose(f, g):
    def h(x):
        return f(g(x))
    return h

def repeated(f,n):
    r = f
    for i in range(n - 1):
        r = compose(r, f)
    return r
    
        

