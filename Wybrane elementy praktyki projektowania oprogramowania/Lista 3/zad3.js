function forEach(array, f) 
{
  for (var i = 0; i < array.length; i++)
  {
    f(array[i])
  }
}

function map(array, f) 
{
  mapped = []
  for (var i = 0; i < array.length; i++)
  {
    mapped.push( f(array[i]) );
  }
  return mapped;
}

function filter(array, f) 
{
  filtered = []
  for (var i = 0; i < array.length; i++)
  {
    if (f(array[i]))
    { 
      filtered.push(array[i]);
    }
  }
  return filtered;
}

/////////////////////////////////////////////////

var a = [1,2,3,4];

forEach( a, _ => { console.log( _ ); } );
// [1,2,3,4]

console.log(filter( a, _ => _ < 3));
// [1,2]

console.log(map( a, _ => _ * 2 ));
// [2,4,6,8]

/////////////////////////////////////////////////

var a = [1,2,3,4,5,6,7,8,9,10];

console.log("\n");
function foo(e)
{
  return Math.pow(e,2)
}
console.log(map(a, foo));
console.log(a.map(foo));
// [1, 4, 9, 16, 25, 36, 49, 64, …]

function foo2(e)
{
  return (e % 2)==1;
}
console.log(filter(a, foo2));
console.log(a.filter(foo2));
// [1, 3, 5, 7, 9]