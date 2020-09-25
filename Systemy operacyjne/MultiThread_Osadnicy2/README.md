Projekt zaliczeniowy - Systemy operacyjne 2017/2018
Temat: Symulacja osadnictwa V2


*Problem synchronizacyjny -- rozwinięcie problemu producenta-konsumenta 
(zmiana cech zasobów, zmiana aktorów i logiki symulacji, konieczność argumentowania braku deadlocka)
"Osadę zamieszkuje populacja osadników, o ściśle zorganizowanej strukturze podziału obowiązków w osadzie.
Każdy z osadników posiada ważną względem reszty grupy rolę, która pozwala całej społeczności żyć
w pewnego rodzaju symbiozie."


Specyfikacja poszczególnych nowych elementów (lub rozszerzenie poprzednich) symulacji:
- Niektóre zasoby mogą się przeterminować
- Starzenie się osadników
- Dodanie aktorów/zasobów: drewna, drwali, budowlańców, domów (umożliwiającym sen/zakończenie pracy),
zbieraczy dodatkowego pożywienia o innym terminie przydatności do spożycia itp.
- Synchronizacja w cyklu dniowym
- Cykl zima/lato, wpływający na przydatność do spożycia produktów/szansę zdobycia zasobów
- Zapisywanie logów symulacji do pliku .txt


Objaśnienie argumentów:
./main 8 6 15 4 1 2 60 80 120 0 34 odpowiada kolejno ilości:
łowców, zbieraczy, kucharzy, drwali, budowlańców, dzieci, mięsa, roślin, pożywienia, drewna, domów.

Domyślny dobór argumentów, wraz z odpowiednią implementacją zasobów, daje im dużo większą szansę na przeżycie niż osadnictwo V1
