:- dynamic(c/2).
:- op(300, fx, conta).

resetc(C) :-
    retract(c(C, _)), !,
    assertz(c(C, 0)).
resetc(C) :-
    assertz(c(C, 0)).

inc(C) :-
    retract(c(C, V)),
    V1 is V+1,
    assertz(c(C, V1)).

dec(C) :-
    retract(c(C, V)),
    V1 is V-1,
    assertz(c(C, V1)).

get(C, V) :-
    c(C, V).

set(C, V) :-
    retract(c(C, _)),
    assertz(c(C, V)).

conta(G) :-
    functor(G, F, A),
    inc(F/A),
    G.

reset(G) :-
    functor(G, F, A),
    resetc(F/A).

quantos(G, N) :-
    functor(G, F, A),
    get(F/A, N).

fib(0, 1).
fib(1, 1).
fib(X, Y) :-
    X1 is X-1,
    X2 is X-2,
    conta fib(X1, Y1),
    conta fib(X2, Y2),
    Y is Y1 + Y2.