# -*- coding: utf-8 -*-
from itertools import islice
import unittest
import types


class SimpleTestCase(unittest.TestCase):
    def setUp(self):
        self.plik = open("tekst.txt")
        self.generator = Wyrazy(self.plik)
        self.lista = wypisz(self.generator, 20845)
        self.licznik = licznik(self.lista)

    def tearDown(self):
        self.plik.close()

    def testA(self):
        for e in self.lista:
            assert type(e) == type("string")
            assert e not in list(' !()-[]{};:\'"\,<>./?@#$%^&*_~')
            assert e[-2:] != '-\n'
            assert e[-1:] != '\n'

    def testB(self):
        for e in self.licznik:
            assert type(e) == type(1)
            assert type(self.licznik[e]) == type(1)


class Wyrazy:
    def __init__(self, stream):
        self.stream = stream
        self.line = ''

    def __iter__(self):
        return self

    def __next__(self):
        if self.line == '':
            self.line = self.stream.readline()
        wyr, spacja, self.line = self.line.partition(' ')
        if wyr[-2:] == '-\n':
            wyr = wyr[:-2] + self.__next__()
        if (wyr[-1:] == '\n') or (wyr[-1:] == '\t') or (wyr[-1:] == '\r'):
            wyr = wyr[:-1]
        if wyr in list('!()-[]{};:\'"\,<>./?@#$%^&*_~'):
            return self.__next__()
        return wyr.strip('!()-[]{};:\'"\,<>./?@#$%^&*_~')


def wypisz(f, n):
    L = []
    for w in islice(f, n+1):
        if w:
            L.append(w)
    return L


def licznik(L):
    dic = {}
    for i in L:
        n = len(i)
        if n in dic:
            dic[n] += 1
        else:
            dic.update({n: 1})
    return dic

       
unittest.main()
