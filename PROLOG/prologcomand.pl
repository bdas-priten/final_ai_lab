% ---------- FACTS ----------

% gender
male(john).
male(paul).
male(robert).
male(james).
male(steve).

female(lisa).
female(mary).
female(susan).
female(anna).

% parent-child relationships
parent(john, paul).
parent(john, mary).
parent(paul, robert).
parent(paul, susan).
parent(mary, james).
parent(mary, anna).
parent(lisa, paul).
parent(lisa, mary).
parent(susan, steve).


% ---------- RULES ----------

% father and mother
father(X, Y) :- parent(X, Y), male(X).
mother(X, Y) :- parent(X, Y), female(X).

% sibling
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.

% brother and sister
brother(X, Y) :- sibling(X, Y), male(X).
sister(X, Y) :- sibling(X, Y), female(X).

% grandparent
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).

% grandfather and grandmother
grandfather(X, Y) :- grandparent(X, Y), male(X).
grandmother(X, Y) :- grandparent(X, Y), female(X).

% uncle and aunt
uncle(X, Y) :- brother(X, Z), parent(Z, Y).
aunt(X, Y) :- sister(X, Z), parent(Z, Y).

% cousin
cousin(X, Y) :- parent(P1, X), parent(P2, Y), sibling(P1, P2).

% child
child(X, Y) :- parent(Y, X).

% son and daughter
son(X, Y) :- child(X, Y), male(X).
daughter(X, Y) :- child(X, Y), female(X).



//  father(X, paul). //
// mother(X, mary). //
//
?- father(X, paul).
?- mother(X, mary).
?- sibling(X, susan).
?- brother(X, james).
?- sister(X, robert).
?- grandparent(X, steve).
?- grandfather(X, anna).
?- grandmother(X, paul).
?- uncle(X, james).
?- aunt(X, robert).
?- cousin(X, steve).
?- child(X, john).
?- son(X, paul).
?- daughter(X, mary).
//
