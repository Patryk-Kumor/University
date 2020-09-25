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

console.log("Pierwsza opcja:")
var foo = 
{
  [Symbol.iterator]: fib
};
/*
for (var f of foo)
{
  console.log(f);
}
*/
for ( var f of foo )
{
  if (f > 100) {break;}
  console.log(f)
}

console.log("Druga opcja:")
var _it = fib();
/*
for ( var _result; _result = _it.next(), !_result.done; ) 
{
  console.log( _result.value );
}
*/
for ( var _result; _result = _it.next(), !_result.done; ) 
{
  if (_result.value >= 100) {break;}
  console.log( _result.value );
}

console.log("Trzecia opcja - nie działa, trzeba zainiciować symbol")
/*
for ( var i of fib() ) 
{
  console.log( i );
}
*/

////////////////////////////////////////////////////////////////////////
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

console.log("Pierwsza opcja:")
/*
for (var f of fibYield())
{
  console.log(f);
}
*/
for ( var f of fibYield() )
{
  if (f > 100) {break;}
  console.log(f)
}

console.log("Druga opcja:")
var _it = fibYield();
/*
for ( var _result; _result = _it.next(), !_result.done; ) 
{
  console.log( _result.value );
}
*/
for ( var _result; _result = _it.next(), !_result.done; ) 
{
  if (_result.value >= 100) {break;}
  console.log( _result.value );
}
