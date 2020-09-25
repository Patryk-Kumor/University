function* fibYield() 
{
  var a = 1;
  var b = 1;
  while (true) 
  {  
    var c = a;
    a = b;
    b = c + a;
    yield c;
  }
}
function fib() 
{
  a = 1;
  b = 1;
  return {
    next : function() 
    {
      var c = a;
      a = b;
      b = a + c;
      return {
        value : c,
        done : false
      }
    }
  }
}

///////////////////////////////////////////////////////////

function* take(fun, top)
{
  var i = 0;
  var next = fun.next()
  while(i++ < top) 
  {
    yield next.value
    next = fun.next()
  }
}

// zwróć dokładnie 10 wartości z potencjalnie
// "nieskończonego" iteratora/generatora
for (let num of take( fibYield(), 10 ) ) 
{
  console.log(num);
}
for (let num of take( fib(), 10 ) ) 
{
  console.log(num);
}
  