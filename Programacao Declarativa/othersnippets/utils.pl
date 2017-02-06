t(1, isto(nao, e(um), termo(simples))).
t(2, pois(pois(pois,claro), que(nao), se, percebe(o(que), significa(isto)))).

contem(ST, ST) :- atomic(ST).
contem(T, ST) :-
    compound(T),
    functor(T, _, A),
    contem(T, A, ST).
contem(T, A, ST) :-
    A > 1, A1 is A-1,
    contem(T, A1, ST).
contem(T, A, ST) :-
    arg(A, T, X),
    contem(X, ST).

univcontem(T, ST) :-
    T =.. L,
    univcontem_(L, ST).

univcontem_([H|_], H) :- atomic(H).
univcontem_([H|_], X) :-
    compound(H),
    univcontem(H, X).
univcontem_([_H|T], ST) :-
    univcontem_(T, ST).

avalia([], _, 0).
avalia([C|Cs], X, Y) :-
    avalia(Cs, X, YI),
    Y is X * YI + C.

derivada([_|P], D) :-
    derivada(P, 1, D).

derivada([], _, []).
derivada([C|Cs], N, [NC|NCs]) :-
    NC is N*C,
    N1 is N+1,
    derivada(Cs, N1, NCs).