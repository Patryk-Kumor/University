####################################################################
# Modul WdI
# Powinien dzialac zarowno dla Pythona 2.x jak i dla Pythona 3.x
####################################################################
import sys

version = 'python2.x'

try:
  x = raw_input
except:
  version = 'python3.x'
  raw_input = input


def printw(*args):
  strings = map(str, args)
  print (" ".join(strings))
 
def printf(format, *args):
  sys.stdout.write(format % args)
           
def scanf(s):
  values = []
  for f in s.split():
      prompt = "[" + f[1] + "]? "
      if f == "%s":
        values.append(raw_input(prompt))
      elif f == "%d":
        values.append(int(raw_input(prompt)))
      elif f == "%f":
        values.append(float(raw_input(prompt)))
  if len(values) == 1:
      return values[0]
  return values
 
class ArrayError: pass
 
class Array:
  def __init__(self, size1, size2 = 0):
      self.items = size1 * [0]
      self.size = size1
     
      if size2 != 0:
        for i in range(size1):
            self.items[i] = Array(size2)
 
  def __setitem__(self,i,x):
      if i < 0 or i >= len(self.items):
        raise ArrayError
      self.items[i] = x
     
  def __getitem__(self, i):
      if i < 0 or i >= len(self.items):
        raise ArrayError
      return self.items[i]  
  
  def __len__(self):
     return self.size   
     
  def __str__(self):
     return 'A[' + ', '.join(map(str, self.items)) + ']'    

      
class ListItem:
   def __init__(self,value):
      self.value = value
      self.next = None

class TreeItem:
   def __init__(self,value, left=None, right=None):
      self.value = value
      self.left = left
      self.right = right
            
