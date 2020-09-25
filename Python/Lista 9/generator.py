from math import sqrt
from itertools import islice
import time
import doctest

def is_prime(n):
    """
    Sprawdzanie pierwszości liczby n.
    Przykłady:
    >>> is_prime(-1)
    False
    >>> is_prime(1)
    False
    >>> is_prime(2)
    True
    """
    if n <= 1:
        return False
    if n % 2 == 0 and n > 2:
        return False
    for i in range(3, int(sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    return True


def pierwsze_skladana(n):
    """
    Zwracanie listy składanej wszystkich liczb pierwszych nie większych niż n.
    Przykłady:
    >>> pierwsze_skladana(0)
    []
    >>> pierwsze_skladana(1)
    []
    >>> pierwsze_skladana(72)
    [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71]
    >>> pierwsze_skladana(-100)
    Traceback (most recent call last):
    ...
    ValueError: math domain error
    >>> pierwsze_skladana("a")
    Traceback (most recent call last):
    ...
    TypeError: must be real number, not str
    >>> pierwsze_skladana(1.5)
    Traceback (most recent call last):
    ...
    TypeError: 'float' object cannot be interpreted as an integer
    """
    np = [j for i in range(2, int(sqrt(n)+1)) for j in range(i*2, n+1, i)]
    pierwsze = [i for i in range(2, n+1) if i not in np]
    return pierwsze


def pierwsze_funkcyjna(n):
    """
    Zwracanie listy funkcyjnej wszystkich liczb pierwszych nie większych niż n.
    Przykłady:
    >>> pierwsze_funkcyjna(0)
    []
    >>> pierwsze_funkcyjna(1)
    []
    >>> pierwsze_funkcyjna(2)
    []
    >>> pierwsze_funkcyjna(-100)
    []
    >>> pierwsze_funkcyjna("a")
    Traceback (most recent call last):
    ...
    TypeError: 'str' object cannot be interpreted as an integer
    >>> pierwsze_funkcyjna(1.5)
    Traceback (most recent call last):
    ...
    TypeError: 'float' object cannot be interpreted as an integer
    """

    return list(filter(lambda i: all(i % div for div in range(2, int(sqrt(i) + 1))), range(2, n)))


class Primes:
    def __init__(self):
        self.licznik = 1
        self.tab=[]   

    def __next__(self):
        self.licznik += 1
        if is_prime(self.licznik):
            return self.licznik

    def __iter__(self):
        return self


def pierwsze_iterowane(n):
    """
    Zwracanie listy funkcyjnej wszystkich liczb pierwszych nie większych niż n.
    Przykłady:
    >>> pierwsze_iterowane(-1)
    Traceback (most recent call last):
    ...
    ValueError: Indices for islice() must be None or an integer: 0 <= x <= sys.maxsize.
    >>> pierwsze_iterowane(0)
    Traceback (most recent call last):
    ...
    ValueError: Stop argument for islice() must be None or an integer: 0 <= x <= sys.maxsize.
    >>> pierwsze_iterowane(1)
    []
    >>> pierwsze_iterowane(2)
    [2]
    """
    L = []
    for prime in islice(Primes(), n - 1):
       if prime:
            L.append(prime)
    return L


doctest.testmod()



