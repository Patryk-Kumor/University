function createGenerator(n,m) 
{
  var _state = n;
  return {
    next : function() 
    {
      return  {
        value : _state,
        done : _state++ >= m
      }
    }
  }
}
/*
function createGenerator() 
{
  var _state = 0;
  return {
    next : function() 
    {
      return  {
        value : _state,
        done : _state++ >= 10
      }
    }
  }
}
*/

console.log("\nRaz:")
var foo = 
{
  [Symbol.iterator] : createGenerator.bind(this,1,10)
};
for ( var f of foo )
{
  console.log(f);
} 

console.log("\nDwa:")
var foo1 = 
{
  [Symbol.iterator]: createGenerator.bind(this,10,20)
};
for (var f of foo1)
{
  console.log(f);
}

console.log("\nTrzy:")
var foo2 = 
{
  [Symbol.iterator]: createGenerator.bind(this,25,25)
};
for (var f of foo2)
{
  console.log(f);
}

//////////////////////////////////////////////////////
function isPrime(num) 
{
  for(var i = 2; i < num; i++)
  {
    if(num % i === 0) return false;
  }
  return num !== 1 && num !== 0;
}
function createGenerator2(n) 
{
  var _state = n;
  return {
    next : function() 
    {
      return  {
        value :  isPrime(_state),
        done : _state++ >= 5
      }
    }
  }
}
console.log("\nCztery:")
var foo2 = 
{
  [Symbol.iterator]: createGenerator2.bind(this,false)
};
for (var f of foo2)
{
  console.log(f);
}