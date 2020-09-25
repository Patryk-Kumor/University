function fib_rek(n)
{
  if (n == 0) { return 1; }
  if (n == 1) { return 1; }
  else 
  { 
    return fib_rek(n-2) + fib_rek(n-1);
  }
}

var fib_mem = (function() 
{
  var cache = [1, 1];
  return fib = function(n) 
  {
    if (n in cache)
    {
      return cache[n];
    }
    else 
    {
      var result = fib(n - 1) + fib(n - 2);
      cache[n] = result;
      return result;
    }
  };
})();

function fib(n)
{
  if (n > 0)
  {
    return memofac2(n - 2) + memofac2(n - 1);
  } else {
    return 1;
  }
}
function memoize(fn) 
{
  var cache = [1,1];
  return function (n) 
  {
    if (n in cache)
    {
      return cache[n]
    } 
    else 
    {
      var result = fn(n - 1) + fn(n - 2);
      cache[n] = result;
      return result;
    }
  }
}

function fib_iter(n)
{
  if (n == 0) { return 1; }
  if (n == 1) { return 1; }
  else
  {
    a = 1; b = 1;
    for (var i = 2; i<=n; i++)
    {
      c = a+b;
      a=b;
      b=c;
    }
    return c;
  }
}

function fib_rekord(n, time_rek, time_iter, time_mem, zgodny)
{
  this.n = n;
  this.rekurencyjne = time_rek;
  this.iterowane = time_iter;
  this.mem = time_mem;
  this.zgodnosc = zgodny;
}

function fib_table()
{
  var tab = [10,15,20,25,30,35,40];//,41,42]
  for (var i=0; i<tab.length; i++)
  {
    //Czas dla rekurencyjnej
    var t1 = Date.now();
    var a = fib_rek(tab[i]);
    var t2 =  Date.now();
    var t_1 = t2-t1
    //Czas dla iteracyjnej
    var t1 = Date.now();
    var b = fib_iter(tab[i]);
    var t2 =  Date.now();
    var t_2 = t2-t1
    //Czas dla mem
    var t1 = Date.now();
    var c =  fib_mem(tab[i]);
    var t2 =  Date.now();
    var t_3 = t2-t1
    //
    var memofac2 = memoize(fib);
    var d = memofac2(tab[i]);
    //Wyniki
    var rekord = new fib_rekord(tab[i], t_1/1000, t_2/1000, t_3/1000, ((a==b) && (a==c)));
    tab[i] = rekord;
  }
  console.table(tab);
}
fib_table();
