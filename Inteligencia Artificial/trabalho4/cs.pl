/*
%estado inicial
h(at(home),s0).
h(sell(super,banana),s0).
h(sell(hws,drill),s0).
h(sell(super,milk),s0).
%consq  positivas
h(have(X),r(buy(X),S)):- h(sell(L,X),S), h(at(L),S).
h(at(Y),    r(go(X,Y),S))   :- h(at(X),S).
%inércia
h(have(X),r(_,S))   :- h(have(X),S).
h(at(X),r(A,S)) :- h(at(X),S),  A\= go(X,_).
*/

h(chao(a),s0).
h(chao(c),s0).
h(sobre(b,a),s0).
h( livre(b),s0).
h( livre(c),s0).
%consq
h(chao(A),r(move_chao(A),S)):- h(livre(A),S),   h(sobre(A,B),S).
h(livre(B),r(move_chao(A),S)):- h(livre(A),S),  h(sobre(A,B),S).
h(livre(A),r(move_chao(A),S)):- h(livre(A),S),  h(sobre(A,B),S).

h(sobre(A,B),r(move(A,B),S))    :- h(livre(A), S), h(livre(B),S), h(chao(A),S).
h(sobre(A,B),r(move(A,B),S))    :- h(livre(A), S), h(livre(B),S), h(sobre(A,C),S).
h(livre(A),r(move(A,B),S))  :- h(livre(A), S), h(livre(B),S), h(chao(A),S).
h(livre(A),r(move(A,B),S))  :- h(livre(A), S), h(livre(B),S), h(sobre(A,C),S).
h(livre(B),r(move(A,B),S))  :- h(livre(A), S), h(livre(B),S), h(sobre(A,C),S).
%inércia
h(sobre(A,B),r(Ac,S)):- h(sobre(A,B),S), Ac \= move_chao(A), h(livre(A),S), h(sobre(A,B),S).
h(sobre(A,C),r(Ac,S)):- h(sobre(A,C),S), Ac \= move(A,B), h(livre(A), S), h(livre(B),S), h(sobre(A,C),S).

h(livre(A), r(Ac, S)) :- h(livre(A), S), Ac \= move(B,A), h(livre(A), S).
h(chao(A), r(Ac, S)) :- h(chao(A), S), Ac \= move(A,B), h(chao(A), S).