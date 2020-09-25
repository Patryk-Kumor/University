var ile = 45;
var licznik = 0;
var toGo = false;
var toSTART = true;
var started = false;
var wait = false;


window.onload = function load()
{
    //USTAWIAMY POCZĄTKOWY ŚRODKOWY KWADRAT
    var nowy_kwadrat = document.createElement('div');
    nowy_kwadrat.classList.add("centerSquare");
    nowy_kwadrat.setAttribute("id", "centerSquare")
    nowy_kwadrat.addEventListener("mouseover", centerSquareMouse);
    nowy_kwadrat.addEventListener("mouseout", centerSquareMouseLeft);
    document.getElementById('box').appendChild(nowy_kwadrat);
}

// STOPER
function startTime() 
{
    if (!wait)
    {
        if (!started) {document.getElementById('timer').innerHTML = 0; started=true;}
        else {document.getElementById('timer').innerHTML = Number(document.getElementById('timer').innerHTML)+1;}
    }
    var t = setTimeout(startTime, 1000);
}


// FUNCKJE EVENTOWE NA KWADRATACH
function squareMouse()
{
    if (this.style.backgroundColor == "grey")
    {
        this.style.backgroundColor = "red";
        // KARA +5s
        document.getElementById('timer').innerHTML = Number(document.getElementById('timer').innerHTML) + 5;;
    }
    if ( (toGo) && (this.style.backgroundColor == "blue"))
    {
        toGo = false;
        if (this.style.backgroundColor == "blue")
        {
            this.style.backgroundColor = "grey";
            licznik++;
            document.getElementById('licznik').innerHTML = licznik;
        }
    }
}
function squareMouseLeft()
{
    if (this.style.backgroundColor == "red")
    {
        this.style.backgroundColor = "grey";
    }
}
// ŚRODKOWY KWADRAT
function centerSquareMouse()
{
    wait = true;
    if (!toGo)
    {
        toGo = true;
    }
    if (toSTART)
    {
        startTime();
        ustaw();
        toSTART=false;
    }
    if (licznik>=ile)
    {
        usun_wszystkie();
        ustaw();
        dodaj_wynik(document.getElementById('timer').innerHTML);
        document.getElementById('timer').innerHTML = 0;
        wait = true;
        licznik = 0;
    }
    this.style.backgroundColor = "yellow";
}
function centerSquareMouseLeft()
{
    wait = false;
    this.style.backgroundColor = "green";
}


// FUNKCJE
function ustaw()
{
    var arr0 = [0,1,2,3,5,6,7,8]
    var in_row = 5;
    for (var i=0; i<=7; i++)
    {
        var arr = [0,1,2,3,4,5,6,7,8]
        arr.sort(() => Math.random() - 0.5);
        // tylko wewnątrz jednego rzędu poziomego
        for (var j=0; j<in_row; j++)
        {
            var nowy_kwadrat = document.createElement('div');
            nowy_kwadrat.classList.add("square");
            nowy_kwadrat.setAttribute("id", "square")
            nowy_kwadrat.style.top = arr0[i]*100 + 'px';
            nowy_kwadrat.style.left = arr[j]*100 + 'px';
            nowy_kwadrat.style.backgroundColor = "blue"
            nowy_kwadrat.addEventListener("mouseover", squareMouse);
            nowy_kwadrat.addEventListener("mouseout", squareMouseLeft);
            document.getElementById('box').appendChild(nowy_kwadrat);
        }
    }
    var arr = [0,1,2,3,5,6,7,8]
    arr.sort(() => Math.random() - 0.5);
    // tylko wewnątrz jednego rzędu poziomego
    for (var j=0; j<in_row; j++)
    {
        var nowy_kwadrat = document.createElement('div');
        nowy_kwadrat.classList.add("square");
        nowy_kwadrat.setAttribute("id", "square")
        nowy_kwadrat.style.top = 4*100 + 'px';
        nowy_kwadrat.style.left = arr[j]*100 + 'px';
        nowy_kwadrat.style.backgroundColor = "blue"
        nowy_kwadrat.addEventListener("mouseover", squareMouse);
        nowy_kwadrat.addEventListener("mouseout", squareMouseLeft);
        document.getElementById('box').appendChild(nowy_kwadrat);
    }
}
function usun_wszystkie()
{
    var myNode = document.getElementById('box');
    var fc = myNode.firstChild;
    while( fc )
    {
        myNode.removeChild( fc );
        fc = myNode.firstChild;
    }
    // Dodaj środkowy
    var nowy_kwadrat = document.createElement('div');
    nowy_kwadrat.classList.add("centerSquare");
    nowy_kwadrat.setAttribute("id", "centerSquare")
    nowy_kwadrat.addEventListener("mouseover", centerSquareMouse);
    nowy_kwadrat.addEventListener("mouseout", centerSquareMouseLeft);
    document.getElementById('box').appendChild(nowy_kwadrat);
}


// DODATKOWE
function dodaj_wynik(wynik)
{
    var nowy_wynik = document.createElement('p')
    nowy_wynik.appendChild(document.createElement('br'));
    nowy_wynik.appendChild(document.createTextNode(wynik));
    document.getElementById('menu').appendChild(nowy_wynik);
}