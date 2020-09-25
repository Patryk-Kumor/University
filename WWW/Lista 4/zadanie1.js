var div = document.createElement("div");
div.id = "menu";
var tekst = document.createTextNode("This is a div text");

// • Dodać element <div id="menu"></div>. W konsoli:
document.getElementById("content").appendChild(div);

// • Korzystając z CSS ustawić obramowanie menu w kolorze niebieskim.
//document.getElementById("menu").style.backgroundColor = 'blue';

// • Do div-a menu dodać 3 linki: Czerwony, Czarny, Brązowy. Po kliknięciu wybranego
// linka obramowanie menu powinno się zmienić na wybrany kolor.
function zmiana(x) 
{
    document.getElementById("menu").style.backgroundColor = x;
}; 
var czerwony = document.createElement('a');
czerwony.setAttribute('href','#');
czerwony.setAttribute('onclick',"zmiana('red')");
czerwony.innerHTML = "Czerwony ";
var czarny = document.createElement('a');
czarny.setAttribute('href','#');
czarny.setAttribute('onclick',"zmiana('black')");
czarny.innerHTML = "Czarny ";
var brazowy = document.createElement('a');
brazowy.setAttribute('href','#');
brazowy.setAttribute('onclick',"zmiana('brown')");
brazowy.innerHTML = "Brązowy ";

document.getElementById("menu").appendChild(czerwony);
document.getElementById("menu").appendChild(czarny);
document.getElementById("menu").appendChild(brazowy);