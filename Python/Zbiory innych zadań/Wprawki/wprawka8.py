def reszta(values, amount):
    if values == [] and amount == 0:
        return 1
    elif values == [] or amount < 0:    
        return 0
    else:
        A = reszta(values[1:], amount)
        B = reszta(values, amount - values[0])
        return A + B
    
