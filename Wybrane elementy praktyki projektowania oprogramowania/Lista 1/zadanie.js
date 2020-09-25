function zadanie2() 
{
    var tab = [];
    for (var i = 1; i <= 100000; i++)
    {
        //console.log("Nasza liczba to:",i);
        var x = i;
        var liczba = x % 10;
        var sum = 0
        while (x>0)
        {
            sum += liczba;
            if ((i % liczba) != 0) {break;}
            if (liczba == 0) {break;} //Zakładam że nie dzielimy przez zero
            x = (x-liczba)/10
            liczba = x % 10
        }
        if (x==0) 
        {
            if ((i % sum) == 0) { tab.push(i);}
        }     
    }
    return tab;
    //return tab.toString();
}

function zadanie3()
{
    var primes = [2]
    for (var i=3; i<=100000; i++)
    {
        for (j=0; j<=primes.length; j++)
        {
            if (i%primes[j] == 0) {break;}
            if (j == primes.length) {primes.push(i); break;}
        }
    }
    return 'Ilość primes: ' + primes.length
    //return primes;
}

function fib_rek(n)
{
    if (n == 0) { return 1; }
    if (n == 1) { return 1; }
    else 
    { 
        return fib_rek(n-2) + fib_rek(n-1);
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

function fib_rekord(n, time_rek, time_iter, zgodny)
{
    this.n = n;
    this.rekurencyjne = time_rek;
    this.iterowane = time_iter;
    this.zgodnosc = zgodny;
}

function fib_table()
{
    var tab = [10,15,20,25,30,35,40,41,42]
    for (var i=0; i<tab.length; i++)
    {
        //console.log("n =",i);
        //console.time("Czas dla rekurencyjnej");
        var t1 = Date.now();
        var a = fib_rek(tab[i]);
        var t2 =  Date.now();
        var t_1 = t2-t1
        //console.timeEnd("Czas dla rekurencyjnej");
        //console.time("Czas dla iteracyjnej");
        var t1 = Date.now();
        var b = fib_iter(tab[i]);
        var t2 =  Date.now();
        var t_2 = t2-t1
        //console.timeEnd("Czas dla iteracyjnej");
        var rekord = new fib_rekord(tab[i], t_1/1000, t_2/1000, a==b);
        tab[i] = rekord;
        //console.log("\n");
    }
    console.table(tab);
}

// TESTY
console.log('Koniec zadania 2:\n', zadanie2(), "\n");
console.log('Koniec zadania 3:\n', zadanie3(), "\n");
console.log('Koniec zadania 5:');
fib_table()
