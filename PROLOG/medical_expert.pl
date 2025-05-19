% Declare dynamic predicates
:- dynamic yes/1, no/1.

% Entry point
check :-
    hypothesize(Disease),
    write('I believe you have '), write(Disease), nl,
    undo.

% Knowledge base
hypothesize(flu) :-
    checkSymptom(fever),
    checkSymptom(chills),
    checkSymptom(headache).

hypothesize(cold) :-
    checkSymptom(sneezing),
    checkSymptom(cough),
    checkSymptom(sore_throat).

hypothesize(malaria) :-
    checkSymptom(fever),
    checkSymptom(sweating),
    checkSymptom(vomiting).

hypothesize(unknown).  % default fallback

% Symptom checker
checkSymptom(S) :-
    (yes(S) -> true ;
     no(S) -> fail ;
     ask(S)).

% Ask user
ask(Symptom) :-
    format('Do you have ~w? (y/n): ', [Symptom]),
    read(Reply),
    nl,
    ((Reply == y ; Reply == yes) -> assertz(yes(Symptom)) ;
     assertz(no(Symptom)), fail).


// checkSymptom(malaria).//
// check. //
undo :- retract(yes(_)), fail.
undo :- retract(no(_)), fail.
undo.
