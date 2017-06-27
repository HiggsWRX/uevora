limite(s0).
limite(r(_,s0)).
limite(r(_,r(_,s0))).
limite(r(_,r(_,r(_,s0)))).
limite(r(_,r(_,r(_,r(_,s0))))).

troca(b, c).
troca(c, b).

h(bracos(1,2),s0).
h(copo(1,b),s0).
h(copo(2,c),s0).
h(copo(3,b),s0).
h(copo(4,b),s0).

h(bracos(B,NA), r(direita(A,B),S)) :- limite(S), h(bracos(A,B),S), NA is B+1, member(NA, [1,2,3,4]).

h(bracos(NB,A), r(esquerda(A,B),S)) :- limite(S), h(bracos(A,B),S), NB is A-1, member(NB, [1,2,3,4]).

h(copo(A,NAE), r(viracopos(A,B),S)) :- limite(S), h(bracos(A,B),S), h(copo(A,AE),S), h(copo(B,_BE), S), troca(AE, NAE).
h(copo(B,NBE), r(viracopos(A,B),S)) :- limite(S), h(bracos(A,B),S), h(copo(A,_AE),S), h(copo(B,BE), S), troca(BE, NBE).

h(copo(A, BE), r(trocacopos(A,B),S)) :- limite(S), h(bracos(A,B),S), h(copo(A,_AE),S), h(copo(B,BE), S).
h(copo(B, AE), r(trocacopos(A,B),S)) :- limite(S), h(bracos(A,B),S), h(copo(A,AE),S), h(copo(B,_BE), S).

% inercia

h(bracos(A,B), r(Ac,S)) :- limite(S), h(bracos(A,B),S), (Ac \= direita(A,B); Ac \= esquerda(A,B)).
h(copo(A,B), r(Ac,S)) :- limite(S), h(copo(A,B),S), (Ac \= viracopos(A,B); Ac \= trocacopos(A,B)).

plano(S) :- h(copo(2,b),S), h(copo(3,c),S).