num(z, 0).
num(s(X), SY) :- num(X, Y), SY is Y+1.

soma(z, X, X).
soma(s(X), Y, s(Z)) :- soma(X, Y, Z).

mais1(A, B) :- soma(A, s(z), B).

le(z, _).
le(A, B) :- soma(A, _X, B).

lt(z, s(_)).
lt(A, B) :- soma(A, s(_X), B).

sub(A, B, X) :- soma(X, B, A).

mult(z, _, z).
mult(s(A), B, X) :-
    mult(A, B, Y),
    soma(B, Y, X).

dobro(X, Y) :- mult(X, s(s(z)), Y).

pot(_, z, s(z)).
pot(A, s(N), B) :-
    pot(A, N, Z),
    mult(A, Z, B).

quadrado(X, Y) :- pot(X, s(s(z)), Y).

div(A, B, Q, R) :-
    mult(B, Q, X),
    soma(X, R, A),
    lt(R, B).

divisivel(A, B) :-
    mult(B, _, A).

fact(z, s(z)).
fact(s(X), Y) :-
    fact(X, Y1),
    mult(s(X), Y1, Y).

factt(X, FX) :- factt(X, s(z), FX).
factt(z, FX, FX).
factt(s(X), FI, FO) :-
 mult(FI, s(X), SFI),
 factt(X, SFI, FO).

gt(A, B) :-
    soma(B, s(_X), A).

mdc(X, Y, A) :-
    div(X, A, QX, RX),
    RX == z,
    div(Y, A, QY, RY),
    RY == z.