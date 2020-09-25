:- module(patryk_kumor, [solve/2]).
:- op(200, fx, ~).
:- op(500, xfy, v).


%=======================%
%----G��wny_predykat----%
%=======================%


solve(Clauses, Solution):-
  lista_zmiennych(Clauses,Variables),	%--Tworzymy_list�_zmiennych--%
  valuation(Variables,X),	%--Tworzymy_wszystkie_mo�liwe_warto�ciowania_dla_zmiennych--%
  is_set_true(Clauses,X),	%--Sprawdzamy_czy_dane_warto�ciowanie_jest_prawdziwe--%
  Solution=X.	%--Otrzymujemy_poprawne_warto�ciowania--%

  
%========================%
%--Predykaty_pomocnicze--%
%========================%


make_list(L,[L2]):- literal(L),neg(L,L2).	%--Tworzymy_list�_z_pojedynczej_klauzuli--%	
make_list(L v C,X):- make_list(L v C,X,[]).
make_list(C,A2,A):-
	literal(C),
	neg(C,C2),
	A2=[C2|A].
make_list(L v C,X,A):-
	neg(L,L2),
	Aa=[L2|A],
	make_list(C,X,Aa).

neg(L,L):- atom(L).	%--Wyrzucamy_ewentualn�_negacj�--%		
neg(~L,L2):- L2=L, atom(L).

literal(X) :- variable(X), !.	%--Sprawdzanie_czy_jest_litera�em--%
literal(~X) :- variable(X).
variable([]) :- !, fail.
variable(X) :- atom(X).

big_list([],[]).	%--Tworzymy_list�_list_ze_zmiennymi--%			
big_list([H|T],[H2|Y]):-
	make_list(H,H2),
	big_list(T,Y).

lista_zmiennych(C,X):-	%--Tworzymy_list�_niepowtarzaj�cych_si�_posortowanych_zmiennych--%
	big_list(C,Y),
	flatten(Y,Z),
	list_to_set(Z,V),
	sort(V,X).

%------------------------%

is_set_true([],_).	%--Sprawdzamy_czy_zbi�r_jest_spe�nialny_dla_danego_warto�ciowania--%
is_set_true([H|T],Valuation):-
	is_clause_true(H,Valuation),
	is_set_true(T,Valuation).
	
is_clause_true(L,Valuation):-	%--Sprawdzamy_czy_klauzula_jest_spe�nialna--%
	variable(L), member((L,t), Valuation),!.
is_clause_true(~L,Valuation):-
	variable(L), member((L,f), Valuation),!.
is_clause_true(L v C, Valuation):-
	is_clause_true(L, Valuation),!; is_clause_true(C, Valuation).

%------------------------%

valuation(Lista, S):-	%--Generujemy_wszystkie_mo�liwe_warto�ciowania--%
	reverse(Lista,L2),
	valuation(L2, [], S).
valuation([], Valuations, Valuations).
valuation([H|T], Valuations, A) :-
	add(H, H2),
	valuation(T, [H2|Valuations], A).

add(X, (X,f)).	%--Zamiana_zmiennej_na_jej_warto�ciowanie--% 
add(X, (X,t)).
