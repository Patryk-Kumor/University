#-*- coding: UTF-8 -*-

from html.parser import HTMLParser
import codecs
import re
import threading
import os
#-----------------------------------------------------------

class MyHTMLParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.Data = ""
    def handle_data(self, data):
        if (data not in list('!()-[]{};:\'"\,<>./?@#$%^&*_~')+["","\n","\t"," "]):
            self.Data = self.Data + " " + data + " "

def zliczaj(html,cel):
    global Wyniki
    strona = MyHTMLParser()
    with open(html, encoding='utf-8') as data:
        strona.feed(data.read())
        txt = strona.Data
        strona.close()
    szukane = re.compile(cel, re.IGNORECASE)
    liczba_wystapien = len(re.findall(szukane, txt))
    if liczba_wystapien != 0:
        Wyniki.update({html:liczba_wystapien})

def wyszukiwarka_html(L, cel):
    W = []
    global Wyniki
    for strona in L:
        wątek = threading.Thread(target=zliczaj, args=(strona,cel))
        wątek.start()
        W.append(wątek)
    for i in W:
        i.join()
    print(Wyniki)
    L = sorted(Wyniki.items(), key=lambda x:x[1])
    return {cel : L}

#-----------------------------------------------------------

class myThread (threading.Thread): 
    def __init__(self, d, s, target): 
        threading.Thread.__init__(self)
        self.dict = d
        self.s = s
        self.target = target

    def run(self):
        lock = threading.Lock()
        lock.acquire()
        x = zliczaj2(self.s, self.target)
        if x != 0:
            self.dict.update( {self.s : x} )
        lock.release()
        
def zliczaj2(html,cel):
    strona = MyHTMLParser()
    with open(html, encoding='utf-8') as data:
        strona.feed(data.read())
        txt = strona.Data
        strona.close()
    szukane = re.compile(cel, re.IGNORECASE)
    liczba_wystapien = len(re.findall(szukane, txt))
    return liczba_wystapien
        
def wyszukiwarka_html2(L, cel):
    d = {}
    T = []
    for s in L:
        thread = myThread (d, s, cel)
        thread.start()
        T.append(thread)
    for i in T:
        i.join()
    L = sorted(d.items(), key=lambda x:x[1])
    return {cel : L}
    print (d)

#-----------------------------------------------------------
    
L = ["1.html", "2.html", "3.html", "4.html"]
Wyniki = {}

X = wyszukiwarka_html(L, "python")
print(X, "\n")

Y = wyszukiwarka_html2(L, "python")
print(Y, "\n")

