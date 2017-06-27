:-dynamic(nos_visitados/1).
:-dynamic(nos_em_memoria/1).

%Descricao do problema:

%estado_inicial(Estado)
%estado_final(Estado)

%representacao dos operadores
%op(Eact,OP,Eseg,Custo)

%representacao dos nos
%no(Estado,no_pai,OperadorCusto,Profundidade)

pesquisa(Problema,Alg):-
  consult(Problema),
  asserta(nos_visitados(0)),
  asserta(nos_em_memoria(0)),
  estado_inicial(S0),
  pesquisa(Alg,[no(S0,[],[],0,0)],Solucao),
  escreve_seq_solucao(Solucao),
  retract(nos_visitados(_)),
  retract(nos_em_memoria(_)),
  retractall(foram_visitados(_)).

pesquisa(it,Ln,Sol):- pesquisa_it(Ln,Sol,1).
pesquisa(largura,Ln,Sol):- pesquisa_largura(Ln,Sol).
pesquisa(profundidade,Ln,Sol):- pesquisa_profundidade(Ln,Sol).

pesquisa_it(Ln,Sol,P):- pesquisa_pLim(Ln,Sol,P).
pesquisa_it(Ln,Sol,P):- P1 is P+1,retractall(foram_visitados(_)), pesquisa_it(Ln,Sol,P1).

pesquisa_profundidade([no(E, Pai, Op, C, P)|_], no(E, Pai, Op, C, P)):-
  retract(nos_visitados(X)),
  Y is X+1, 
  assertz(nos_visitados(Y)),  
  estado_final(E).
pesquisa_profundidade([E|R], Sol):-
  expande(E, Lseg), 
  esc(E),
  insere_inicio(Lseg, R, Resto),
  length(Resto,Size),
  retract(nos_em_memoria(Nodes)),
  max(Size,Nodes,Max),
  assertz(nos_em_memoria(Max)),
  pesquisa_profundidade(Resto, Sol).  

%pesquisa_largura([],_):- !,fail.
pesquisa_largura([no(E,Pai,Op,C,P)|_],no(E,Pai,Op,C,P)):- 
  retract(nos_visitados(X)),
  Y is X + 1,
  asserta(nos_visitados(Y)),
  estado_final(E).
pesquisa_largura([E|R],Sol):- 
  expande(E,Lseg), 
  esc(E),
  insere_fim(Lseg,R,Resto),
  length(Resto,ListSize),
  retract(nos_em_memoria(X)),
  max(ListSize,X,Result),
  asserta(nos_em_memoria(Result)),
  pesquisa_largura(Resto,Sol).

expande(no(E,Pai,Op,C,P),L):- findall(no(En,no(E,Pai,Op,C,P),Opn,Cnn,P1),
                                    (op(E,Opn,En,Cn),P1 is P+1, Cnn is Cn+C),
                                    L).

expandePl(no(E,Pai,Op,C,P),[],Pl):- Pl =< P, ! .
expandePl(no(E,Pai,Op,C,P),L,_):- findall(no(En,no(E,Pai,Op,C,P),Opn,Cnn,P1),
                                    (op(E,Opn,En,Cn),P1 is P+1, Cnn is Cn+C),
                                    L).
insere_fim([],L,L).
insere_fim(L,[],L).
insere_fim(R,[A|S],[A|L]):- insere_fim(R,S,L).


insere_inicio([], L, L).
insere_inicio(L, [], L).
insere_inicio(R, T, L):- append(R,T,L).


pesquisa_pLim([no(E,Pai,Op,C,P)|_],no(E,Pai,Op,C,P),_):- 
  nos_visitados(X),
  Y is X+1, 
  retract(nos_visitados(X)), 
  assertz(nos_visitados(Y)),
  estado_final(E).

pesquisa_pLim([E|R],Sol,Pl):- expandePl(E,Lseg,Pl), esc(E),
                              insere_fim(R,Lseg,Resto),

                              length(Resto,X),
                              nos_em_memoria(Y),
                              max(X,Y,Z),
                              retract(nos_em_memoria(Y)),
                              assertz(nos_em_memoria(Z)),

                              pesquisa_pLim(Resto,Sol,Pl).


escreve_seq_solucao(no(E,Pai,Op,Custo,Prof)):- 
                                          write(custo(Custo)),nl,
                                          write(profundidade(Prof)),nl,
                                          escreve_seq_accoes(no(E,Pai,Op,_,_)),

                                          write('Nos visitados: '),
                                          nos_visitados(X),
                                          write(X),
                                          nl,
                                          write('Maximo de nos em memoria: '),
                                          nos_em_memoria(Y),
                                          write(Y).


escreve_seq_accoes([]).
escreve_seq_accoes(no(E,Pai,Op,_,_)):- 
  escreve_seq_accoes(Pai),
    write(e(Op,E)),nl.


esc(A):- write(A), nl.


% verificar o maximo 

max(X,X,X).
max(X,Y,Z):-
  X > Y,
  Z is X.
max(X,Y,Z):-
  Y > X,
  Z is Y.