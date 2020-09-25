document.cookie.split(';').reduce((cookies, cookie) => {
  const [ name, value ] = cookie.split('=').map(c => c.trim());
  cookies[name] = value;
  return cookies;
}, {});

/*
function listCookies() {
    var theCookies = document.cookie.split(';');
    var aString = '';
    for (var i = 1 ; i <= theCookies.length; i++) {
        aString += i + ' ' + theCookies[i-1] + "\n";
    }
    return aString;
}
*/

/*
var x = document.cookie; 
window.alert(x);
*/

// ?"a"=1&name=janek