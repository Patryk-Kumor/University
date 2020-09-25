// tworzy tablicę n funkcji
// i-ta funkcja z tablicy ma zwrócić i

function createFs(n) 
{ 
  var fs = []; 
  for (var i=0; i<n; i++ ) 
  {
    (function(i) {fs[i] = function () // funkcja od razu się wykonuje i za każdym razem tworzy nowy kontekst
      {                               // (n różnych kontekstów vs jeden i ten sam)
        return i;
      };})(i)
  };
  return fs;
}

function oldcreateFs(n) 
{ 
  var fs = []; 
  for (var i=0; i<n; i++ ) 
  {
    fs[i] = function() // funkcja się nie wykonuje, jest obiekt kontekstu do którego trafia i
    {                  // ale wartość i się zmienia zanim funkcje zaczną się wykonywać
      return i;
    };
  };
  return fs;
}

var myfs = createFs(10);
console.log( myfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs[2]() ); // druga miała zwrócić 2
console.log( myfs[7]() );
// 10 10 10

console.log( "\n" );
var oldmyfs = oldcreateFs(10);
console.log( oldmyfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( oldmyfs[2]() ); // druga miała zwrócić 2
console.log( oldmyfs[7]() );
// 10 10 10







/*
function oldcreateFsBABEL(n) { 
  var fs = []; 
  var _loop = function _loop(i) { 
    fs[i] = function() 
    {                  
      return i;
    };
  };
  for (let i=0; i<n; i++ ) {
    _loop(i);
  };
  return fs;
}
console.log( "\n" );
var oldmyfsB = oldcreateFsBABEL(10);
console.log( oldmyfsB[0]() ); // zerowa funkcja miała zwrócić 0
console.log( oldmyfsB[2]() ); // druga miała zwrócić 2
console.log( oldmyfsB[7]() );
// 10 10 10
*/
