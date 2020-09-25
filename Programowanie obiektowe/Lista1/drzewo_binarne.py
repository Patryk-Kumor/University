def BST(str):
    return [str, None, None]  # węzeł, lewe poddrzewo, prawe poddrzewo 


def wstaw(element, drzewo): 
    if len(element) < len(drzewo[0]) and drzewo[1] is None:
        drzewo[1]=BST(element)
    elif len(element) > len(drzewo[0]) and drzewo[2] is None:
        drzewo[2]=BST(element)    
    else:
        if len(element) < len(drzewo[0]):
            wstaw(element,drzewo[1])
        elif len(element) > len(drzewo[0]):
            wstaw(element,drzewo[2])

def szukaj(element, drzewo):
    if element == drzewo[0]:
        return 'Znaleziono: ' + element

    elif len(element) < len(drzewo[0]):
        return szukaj(element, drzewo[1])
    
    elif len(element) > len(drzewo[0]):
        return szukaj(element, drzewo[2])



def rozmiar(drzewo):
    if drzewo == None:
        return 0
    
    return rozmiar(drzewo[1]) + 1 + rozmiar(drzewo[2])
