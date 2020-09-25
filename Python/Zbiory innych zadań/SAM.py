import random

usuń={',','.',':',';',"!",'?','«','»','-','_','(',')','—'}
txt=open('pan_tadeusz.txt', encoding='utf8').read().split()
bez=[]

for element in txt:
    if element[-1] in usuń:
        bez.append(element[0:-1])
        bez.append(element[-1])
    else:
        bez.append(element)


#bez=wyrzuć_znaki(txt)

następnik=dict()

for i in range(len(bez)):
    if i==len(bez)-1:
        break
    else:
        if str(bez[i]) in następnik:
            następnik[str(bez[i])].append(bez[i+1])
        else:
            następnik[str(bez[i])]=[(bez[i+1])]
def symuluj(k):
    a=random.choice(bez)
    print(a)
    for i in range(k):
        b=random.choice(następnik[a])
        print(b)
        a=b
symuluj(20)    
