# -*- coding: utf-8 -*-
from itertools import islice


class Wyrazy:
    
    def __init__(self, stream):
        self.stream = stream
        self.line = ''
        
    def __iter__(self):
        return self
    
    def __next__(self):
        if self.line == '':
            self.line = self.stream.readline()
        wyraz, spacja, self.line = self.line.partition(' ')
        if wyraz[-2:] == '-\n':
            wyraz = wyraz[:-2] + self.__next__()
        if (wyraz[-1:] == '\n') or (wyraz[-1:] == '\t') or (wyraz[-1:] == '\r'):
            wyraz = wyraz[:-1]
        if wyraz in list('!()-[]{};:\'"\,<>./?@#$%^&*_~'):
            return self.__next__()
        return wyraz.strip('!()-[]{};:\'"\,<>./?@#$%^&*_~')

def wypisz(f,n):    # to przerabia iterator na listę L
    L = []
    for w in islice(f,n+1):
       if w:
            L.append(w)
    return L

def licznik(L):
    dic={}
    for i in L:
        n = len(i)
        if n in dic:
            dic[n] += 1
        else:
            dic.update({n:1})
    return dic

text = open('tekst.txt')

L = wypisz(Wyrazy(text),100)

print(L)
print()
print(licznik(L))
