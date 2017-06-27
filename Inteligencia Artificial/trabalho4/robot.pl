troca(b, c).
troca(c, b).

% ---- ACÇÃO --------[PRE CONDIÇÕES]----[ADDLIST]------[DEL LIST]-------
accao(direita(A, B), [bracos(A, B)], [bracos(B, NA)], [bracos(A, B)]) :-
    member(A, [1,2,3,4]),
    member(B, [1,2,3,4]),
    A \= B,
    NA is B+1,
    member(NA, [1,2,3,4]).
accao(esquerda(A, B), [bracos(A, B)], [bracos(NB, A)], [bracos(A, B)]) :-
    member(A, [1,2,3,4]),
    member(B, [1,2,3,4]),
    A \= B,
    NB is A-1,
    member(NB, [1,2,3,4]).
accao(viracopos(A, B), [bracos(A, B), copo(A, AE), copo(B, BE)], [copo(A, NAE), copo(B, NBE)], [copo(A, AE), copo(B, BE)]) :-
    member(A, [1,2,3,4]),
    member(B, [1,2,3,4]),
    A \= B,
    troca(AE, NAE),
    troca(BE, NBE).
accao(trocacopos(A, B), [bracos(A, B), copo(A, AE), copo(B, BE)], [copo(A, BE), copo(B, AE)], [copo(A, AE), copo(B, BE)]) :-
    member(A, [1,2,3,4]),
    member(B, [1,2,3,4]),
    A \= B.

%estado_inicial([bracos(1, 2), copo(1, b), copo(2, c), copo(3, b), copo(4, b)]).
%estado_final([bracos(1, 2), copo(1, b), copo(2, b), copo(3, c), copo(4, b)]).
estado_inicial([bracos(1, 2), copo(1, b), copo(2, c), copo(3, b), copo(4, b)]).
estado_final([bracos(1, 2), copo(1, c), copo(2, c), copo(3, c), copo(4, b)]).