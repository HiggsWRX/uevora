limite(s0).
limite(r(_,s0)).
%limite(r(_,r(_,s0))).
%limite(r(_,r(_,r(_,s0)))).
%limite(r(_,r(_,r(_,r(_,s0))))).

h(chao(a),s0).
h(chao(c),s0).
h(sobre(b,a),s0).
h( livre(b),s0).
h( livre(c),s0).

%consq
%/* Exemplo para o problema: blocos a, b, c */

%accao(move_chao(A),[livre(A), sobre(A,B)], [chao(A), livre(B),livre(A)], [sobre(A,B)]):- member(A,[a,b,c]), member(B,[a,b,c]), A\= B.

%accao(move(A,B),[livre(A), livre(B),chao(A)], [sobre(A,B), livre(A)], [livre(B), chao(A)]):- member(A,[a,b,c]), member(B,[a,b,c]), A\= B.

%accao(move(A,B),[livre(A), livre(B),sobre(A,C)], [sobre(A,B), livre(A), livre(C)], [livre(B), sobre(A,C)]):- member(A,[a,b,c]), member(B,[a,b,c]), A\= B,member(C,[a,b,c]), A\=C, B\=C.

h(chao(A),r(move_chao(A),S)):- limite(S), h(livre(A),S), h(sobre(A,_B),S).
h(livre(A),r(move_chao(A),S)):- limite(S),h(livre(A),S), h(sobre(A,_B),S).
h(livre(B),r(move_chao(A),S)):-limite(S), h(livre(A),S), h(sobre(A,B),S).

h(sobre(A,B),r(move(A,B),S)) :- limite(S),h(livre(A), S), h(livre(B),S), h(chao(A),S).
h(sobre(A,B),r(move(A,B),S)) :-limite(S), h(livre(A), S), h(livre(B),S), h(sobre(A,_C),S).

h(livre(A),r(move(A,B),S)) :- limite(S),h(livre(A), S), h(livre(B),S), h(chao(A),S).

h(livre(A),r(move(A,B),S)) :- limite(S),h(livre(A), S), h(livre(B),S), h(sobre(A,_C),S).
h(livre(B),r(move(A,B),S)) :- limite(S),h(livre(A), S), h(livre(B),S), h(sobre(A,_C),S).

%in�rcia

h(sobre(A,B),r(Ac,S)):- limite(S), h(sobre(A,B),S),         
                        h(livre(A),S), (Ac\= move_chao(A); h(livre(C),S), Ac\=move(A,C)).

h(livre(A), r(Ac,S)):- limite(S),h(livre(A),S),
                       Ac \= move(_B,A).

h(chao(A),  r(Ac,S)):- limite(S),h(chao(A),S),
                      Ac \= move(A,_B).

plano(S):- h(sobre(b,c),S). %,h(chao(a),S), h(chao(c),S),  h(livre(b),S), h(livre(a),S).