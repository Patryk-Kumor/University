function sum(...args) 
{
  var sum = 0;
  args.forEach( x => sum += x );
  return sum;
}
  
console.log(sum(1,2,3));
// 6
  
console.log(sum(1,2,3,4,5));
// 15
  