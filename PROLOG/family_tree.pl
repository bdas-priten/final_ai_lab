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

% ---------- NEW RULES ----------

% ancestor: X is ancestor of Y if X is parent of Y or ancestor of a parent of Y
ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(X, Z), ancestor(Z, Y).

% descendant: X is descendant of Y if Y is ancestor of X
descendant(X, Y) :- ancestor(Y, X).

% related: X and Y are related if they share a common ancestor
related(X, Y) :-
    ancestor(Z, X),
    ancestor(Z, Y),
    X \= Y.

% only_child: X is an only child if X has a parent and no siblings
only_child(X) :-
    parent(P, X),
    \+ (parent(P, Y), X \= Y).

% spouse: X and Y are spouses if they have at least one common child (simplified assumption)
spouse(X, Y) :-
    parent(X, C),
    parent(Y, C),
    X \= Y.



Term	Description	Example
Fact	Basic true statement	male(john).
Predicate	Relation with name and arity	parent/2, father/2
Rule	Defines predicate in terms of others	father(X,Y) :- parent(X,Y), male(X).
Variable	Placeholder starting with uppercase	X, Y, Z
Conjunction	Logical AND (both must be true)	parent(Z,X), parent(Z,Y)
Inequality	Check not equal	X \= Y
Query	Question asked to Prolog	sibling(susan, X).

//

?- ancestor(john, steve).
?- descendant(steve, john).
?- related(robert, anna).
?- only_child(steve).
?- spouse(john, lisa).
//

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
