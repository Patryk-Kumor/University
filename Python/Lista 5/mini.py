#-*- coding: UTF-8 -*-

from html.parser import HTMLParser
import codecs
import re
import os
import urllib
import urllib.request

#-----------------------------------------------------------

class MyHTMLParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.Data = ""
    def handle_data(self, data):
        if (data not in list('!()-[]{};:\'"\,<>./?@#$%^&*_~')+["","\n","\t"," "]):
            self.Data = self.Data + " " + data + " "

#-----------------------------------------------------------

def zliczaj(html,cel):
    strona = MyHTMLParser()
    with open(html, encoding='utf-8') as data:
        strona.feed(data.read())

        txt = strona.Data
        strona.close()
    #print (txt)
    szukane = re.compile(cel, re.IGNORECASE)
    liczba_wystapien = len(re.findall(szukane, txt))
    return liczba_wystapien

#-----------------------------------------------------------

def wyszukiwarka_html(L, cel):
    dic = {}
    for strona in L:
        dic.update({strona:zliczaj(strona,cel)})
    L = sorted(dic.items(), key=lambda x:x[1])
    print(L)
    W=[]
    for i in L:
        if i[1] != 0:
            W.append(i[0])
    return {cel : W}
        
def wyszukiwarka_html_z_folderu(directory,cel):   #FOLDER ./HTML DOMYŚLNIE
    files = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]
    #print(files)
    dic = {}
    for strona in files:
       #if strona[-5:] == ".html":
        if strona.endswith(".html"):
            dic.update({strona:zliczaj(strona,cel)})
    L = sorted(dic.items(), key=lambda x:x[1])
    print(L)
    W=[]
    for i in L:
        if i[1] != 0:
            W.append(i[0])
    return {cel : W}

def make_html(some_url):
    return urllib.request.urlopen(some_url)

def wyszukiwarka_url(L, cel):
    for i in L:
        i = make_html(i)
    dic = {}
    for strona in L:
        if strona.endswith(".html"):
            dic.update({strona:zliczaj2(strona,cel)})
    L = sorted(dic.items(), key=lambda x:x[1])
    print(L)
    W=[]
    for i in L:
        if i[1] != 0:
            W.append(i[0])
    return {cel : W}

def zliczaj2(html,cel):
    strona = MyHTMLParser()
    strona.feed(html)

    txt = strona.Data
    strona.close()
    #print (txt)
    szukane = re.compile(cel, re.IGNORECASE)
    liczba_wystapien = len(re.findall(szukane, txt))
    return liczba_wystapien

#-----------------------------------------------------------

#f = codecs.open("1.html", 'r', 'utf-8')
#print (f.read(), '\n')

L = ["1.html", "2.html", "3.html", "4.html"]


X = wyszukiwarka_html(L, "python")
print(X, "\n")
Y = wyszukiwarka_html_z_folderu("./HTML","python")
print(Y, "\n")

#print(wyszukiwarka_url(["https://docs.python.org/3/howto/urllib2.html", "https://pl.wikibooks.org/wiki/Zanurkuj_w_Pythonie/S%C5%82owniki"], "Python"))



