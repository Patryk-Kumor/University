program = []

for x in open('prog.pygo'):
  L = x.split()
  if L[0] == 'goto':
    program.append( ('goto', int(L[1])-1))
  elif L[0] == 'print':
    program.append( ('print', ' '.join(L[1:])))
  elif L[1] == '=':
    program.append( ('=', L[0], ' '.join(L[2:])))
  elif L[0] == 'if':
    program.append( ('if', ' '.join(L[1:-3]), int(L[-1])-1))    
  else:
    program.append( ('error',-1) )  
    
#for p in program:
#  print (p)    

PC = 0
E = {}

while PC < len(program):
  p = program[PC]
  if p[0] == 'goto':
    PC = p[1]
  elif p[0] == '=':
    E[p[1]] = eval(p[2], E)
    PC += 1
  elif p[0] == 'print':
    print( eval(p[1],E) )
    PC += 1
  elif p[0] == 'if':
    if eval(p[1], E) == True:
      PC = p[2]
    else:
      PC += 1
  else:
    print ('Nieznana instrukcja', p)    
