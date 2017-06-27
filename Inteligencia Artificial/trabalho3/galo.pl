:-dynamic(quem_ganhou/1).


estado_inicial( ([(p(1,1),_), (p(1,2),_), (p(1,3),_ ),
                (p(2,1),_), (p(2,2),_), (p(2,3),_),
                (p(3,1),_), (p(3,2),_), (p(3,3),_)], o) ).

terminal((EstadoAct,_)):-
    verifica_victoria(EstadoAct);
    empate(EstadoAct).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 1 -victoria o
%% -1 - derrota
%% 0 -empate

valor((EstadoAct, _), 1, P):-
    verifica_victoria(EstadoAct),
    quem_ganhou(o),!.

valor((EstadoAct, _), -1, P):-
    verifica_victoria(EstadoAct),
    quem_ganhou(x),!.

valor((EstadoAct, _), 0, P):- 
    empate(EstadoAct),!.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

verifica_victoria(EstadoAct):-
    (victoria_linhas(EstadoAct);
        victoria_colunas(EstadoAct);
        victoria_diagonais(EstadoAct)).

victoria_linhas(EstadoAct):-
    (victoria_linha(EstadoAct,1);
        victoria_linha(EstadoAct,2);
        victoria_linha(EstadoAct,3)).

victoria_colunas(EstadoAct):-
    (victoria_coluna(EstadoAct,1);
        victoria_coluna(EstadoAct,2);
        victoria_coluna(EstadoAct,3)).

victoria_coluna(EstadoAct,Y):-
    findall(V, (member((p(_,Y),V),EstadoAct), atom(V)),L),
    verifica_victoria(L).

victoria_linha(EstadoAct,X):-
    findall(V, (member((p(X,_),V),EstadoAct), atom(V)),L),
    verifica_victoria(L).


%     victoria_diagonais(EstadoAct):-
    %    write (' cenas ').

%%%%%falta fazer victoria_diagonais



%%%%%%% OP %%%%%

op1((EstadoAct,V),jogar11,(EstadoS,V1)):-
    ((V = o -> V1 = x); V1 = o),
    substitui((1,1),EstadoAct,V1,EstadoS).

op1((EstadoAct,V),jogar12,(EstadoS,V1)):-
    ((V = o -> V1 = x); V1 = o),
    substitui((1,2),EstadoAct,V1,EstadoS).

op1((EstadoAct,V),jogar13,(EstadoS,V1)):-
    ((V = o -> V1 = x); V1 = o),
    substitui((1,3),EstadoAct,V1,EstadoS).

op1((EstadoAct,V),jogar21,(EstadoS,V1)):-
    ((V = o -> V1 = x); V1 = o),
    substitui((2,1),EstadoAct,V1,EstadoS).

op1((EstadoAct,V),jogar22,(EstadoS,V1)):-
    ((V = o -> V1 = x); V1 = o),
    substitui((2,2),EstadoAct,V1,EstadoS).

op1((EstadoAct,V),jogar23,(EstadoS,V1)):-
    ((V = o -> V1 = x); V1 = o),
    substitui((2,3),EstadoAct,V1,EstadoS).

op1((EstadoAct,V),jogar31,(EstadoS,V1)):-
    ((V = o -> V1 = x); V1 = o),
    substitui((3,1),EstadoAct,V1,EstadoS).

op1((EstadoAct,V),jogar32,(EstadoS,V1)):-
    ((V = o -> V1 = x); V1 = o),
    substitui((3,2),EstadoAct,V1,EstadoS).

op1((EstadoAct,V),jogar33,(EstadoS,V1)):-
    ((V = o -> V1 = x); V1 = o),
    substitui((3,3),EstadoAct,V1,EstadoS).

substitui((X,Y), EstadoAct, SimboloAct, EstadoFinal):-
    member((p(X,Y), V), EstadoAct),
    \+ atom(V), 
    V = SimboloAct,
    EstadoFinal = EstadoAct.