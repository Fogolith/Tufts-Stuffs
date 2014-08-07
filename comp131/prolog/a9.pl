% Jake Austin (jausti01), Comp 131 Spring 2014, HW 9, 4/10/2014

% facts

man(george).
man(philip).
man(spencer).
man(charles).
man(mark).
man(andrew).
man(edward).
man(william).
man(harry).
man(peter).
man(james).
woman(mum).
woman(kydd).
woman(margaret).
woman(elizabeth).
woman(diana).
woman(anne).
woman(sarah).
woman(sophie).
woman(zara).
woman(beatrice).
woman(louise).
woman(eugenie).
parent(george, elizabeth).
parent(mum, elizabeth).
parent(george, margaret).
parent(mum, margaret).
spouse(george, mum).
spouse(mum, george).
parent(spencer, diana).
parent(kydd, diana).
spouse(kydd, spencer).
spouse(spencer, kydd).
parent(elizabeth, anne).
parent(elizabeth, charles).
parent(elizabeth, andrew).
parent(elizabeth, edward).
parent(philip, anne).
parent(philip, charles).
parent(philip, andrew).
parent(philip, edward).
spouse(philip, elizabeth).
spouse(elizabeth, philip).
parent(diana, william).
parent(diana, harry).
parent(charles, william).
parent(charles, harry).
spouse(charles, diana).
spouse(diana, charles).
parent(anne, peter). 
parent(anne, zara).
parent(mark, peter).
parent(mark, zara).
spouse(mark, anne).
spouse(anne, mark).
parent(andrew, beatrice).
parent(andrew, eugenie).
parent(sarah, beatrice).
parent(sarah, eugenie).
spouse(andrew, sarah).
spouse(sarah, andrew).
parent(edward, louise).
parent(edward, james).
parent(sophie, louise).
parent(sophie, james).
spouse(edward, sophie).
spouse(sophie, edward).

% clauses

grandchild(C, G) :- parent(X, C), parent(G, X).

greatgrandparent(G, C) :- parent(X, C), parent(Y, X), parent(G, Y).
greatgrandparent(G, C):- parent(X, C), spouse(S, X), parent(Y, S), parent(G, Y).
greatgrandparent(G, C):- parent(X, C), parent(Y, X), spouse(S, Y), parent(G, S).
greatgrandparent(G, C):- parent(X, C), parent(Y, X), parent(S, Y), spouse(G, S).


ancestor(A, B) :- parent(A, B).
ancestor(A, B) :- parent(X, B), ancestor(A, X).

brother(B, A) :- man(B), parent(X, B), parent(X, A), not(B=A).

sister(S, A) :- woman(S), parent(X, S), parent(X, A), not(S=A).

daughter(D, P) :- woman(D), parent(P, D).

son(S, P) :- man(S), parent(P, S).

firstcousin(C, A) :- aunt(X, A), parent(X, C). 

brotherinlaw(B, A) :- sister(S, A), spouse(B, S). 
brotherinlaw(B, A) :- spouse(X, A), brother(B, X).
brotherinlaw(B, A) :- spouse(X, A), sister(S, X), spouse(B, S).

sisterinlaw(S, A) :- brother(B, A), spouse(S, B).
sisterinlaw(S, A) :- spouse(X, A), sister(S, X).
sisterinlaw(S, A) :- spouse(X, A), brother(B, X), spouse(S, B).

aunt(A, N) :- parent(X, N), sister(A, X).
aunt(A, N) :- parent(X, N), sisterinlaw(A, X).

uncle(U, N) :- parent(X, N), brother(U, X).
uncle(U, N) :- parent(X, N), brotherinlaw(U, X).
