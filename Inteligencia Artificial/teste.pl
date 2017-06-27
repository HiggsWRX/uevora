estado_inicial(
     e([v(o(7),['+','-','*','/'],_),
        v(o(8),['+','-','*','/'],_),
        v(o(9),['+','-','*','/'],_),
        v(o(10),['+','-','*','/'],_),
        v(o(11),['+','-','*','/'],_),
        v(o(12),['+','-','*','/'],_),
        v(n(1),[1,2,3,4,5,6,7,8,9],_),
        v(n(2),[1,2,3,4,5,6,7,8,9],_),
        v(n(3),[1,2,3,4,5,6,7,8,9],_),
        v(o(1),['+','-','*','/'],_),
        v(o(2),['+','-','*','/'],_),
        v(n(4),[1,2,3,4,5,6,7,8,9],_),
        v(n(5),[1,2,3,4,5,6,7,8,9],_),
        v(n(6),[1,2,3,4,5,6,7,8,9],_),
        v(o(3),['+','-','*','/'],_),
        v(o(4),['+','-','*','/'],_),
        v(n(7),[1,2,3,4,5,6,7,8,9],_),
        v(n(8),[1,2,3,4,5,6,7,8,9],_),
        v(n(9),[1,2,3,4,5,6,7,8,9],_),
        v(o(5),['+','-','*','/'],_),
        v(o(6),['+','-','*','/'],_)],[])).

restricoes(e(_Ninst, Inst)) :-
    restr_todas_dif(Inst),
    member(v(n(1),_,Vn1),Inst),
    member(v(n(2),_,Vn2),Inst),
    member(v(n(3),_,Vn3),Inst),
    member(v(o(1),_,Vo1),Inst),
    member(v(o(2),_,Vo2),Inst), !,
    op(Vn1, Vo1, Vn2, Vo2, Vn3, 6),
    restr_seg_linha(Inst).
restricoes(e(_Ninst, Inst)) :-
    restr_todas_dif(Inst).

restr_seg_linha(Inst) :-
    restr_todas_dif(Inst),
    member(v(n(4),_,Vn4),Inst),
    member(v(n(5),_,Vn5),Inst),
    member(v(n(6),_,Vn6),Inst),
    member(v(o(3),_,Vo3),Inst),
    member(v(o(4),_,Vo4),Inst), !,
    op(Vn4, Vo3, Vn5, Vo4, Vn6, 15),
    restr_ter_linha(Inst).
restr_seg_linha(Inst) :-
    restr_todas_dif(Inst).

restr_ter_linha(Inst) :-
    restr_todas_dif(Inst),
    member(v(n(7),_,Vn7),Inst),
    member(v(n(8),_,Vn8),Inst),
    member(v(n(9),_,Vn9),Inst),
    member(v(o(5),_,Vo5),Inst),
    member(v(o(6),_,Vo6),Inst), !,
    op(Vn7, Vo5, Vn8, Vo6, Vn9, 24),
    restr_prim_coluna(Inst).
restr_ter_linha(Inst) :-
    restr_todas_dif(Inst).

restr_prim_coluna(Inst) :-
    restr_todas_dif(Inst),
    member(v(n(1),_,Vn1),Inst),
    member(v(n(4),_,Vn4),Inst),
    member(v(n(7),_,Vn7),Inst),
    member(v(o(7),_,Vo7),Inst),
    member(v(o(10),_,Vo10),Inst), !,
    op(Vn1, Vo7, Vn4, Vo10, Vn7, 12),
    restr_seg_coluna(Inst).
restr_prim_coluna(Inst) :-
    restr_todas_dif(Inst).

restr_seg_coluna(Inst) :-
    restr_todas_dif(Inst),
    member(v(n(2),_,Vn2),Inst),
    member(v(n(5),_,Vn5),Inst),
    member(v(n(8),_,Vn8),Inst),
    member(v(o(8),_,Vo8),Inst),
    member(v(o(11),_,Vo11),Inst), !,
    op(Vn2, Vo8, Vn5, Vo11, Vn8, 15),
    restr_ter_coluna(Inst).
restr_seg_coluna(Inst) :-
    restr_todas_dif(Inst).

restr_ter_coluna(Inst) :-
    restr_todas_dif(Inst),
    member(v(n(3),_,Vn3),Inst),
    member(v(n(6),_,Vn6),Inst),
    member(v(n(9),_,Vn9),Inst),
    member(v(o(9),_,Vo9),Inst),
    member(v(o(12),_,Vo12),Inst), !,
    op(Vn3, Vo9, Vn6, Vo12, Vn9, 18).
restr_ter_coluna(Inst) :-
    restr_todas_dif(Inst).

restr_todas_dif(L) :- restr_todas_dif(L, []).
restr_todas_dif([], L) :-
    fd_all_different(L).
restr_todas_dif([H|T], L) :-
    arg(1, H, n(_)),
    arg(3, H, V),
    restr_todas_dif(T, [V|L]).
restr_todas_dif([H|T], L) :-
    arg(1, H, o(_)),
    restr_todas_dif(T, L).

op(A, '+', B, '+', C, V) :-
    V is A + B + C.
op(A, '+', B, '-', C, V) :-
    V is A + B - C.
op(A, '+', B, '*', C, V) :-
    V is A + B * C.
op(A, '+', B, '/', C, V) :-
    V is A + B / C.
op(A, '-', B, '+', C, V) :-
    V is A - B + C.
op(A, '-', B, '-', C, V) :-
    V is A - B - C.
op(A, '-', B, '*', C, V) :-
    V is A - B * C.
op(A, '-', B, '/', C, V) :-
    V is A - B / C.
op(A, '*', B, '+', C, V) :-
    V is A * B + C.
op(A, '*', B, '-', C, V) :-
    V is A * B - C.
op(A, '*', B, '*', C, V) :-
    V is A * B * C.
op(A, '*', B, '/', C, V) :-
    V is A * B / C.
op(A, '/', B, '+', C, V) :-
    V is A / B + C.
op(A, '/', B, '-', C, V) :-
    V is A / B - C.
op(A, '/', B, '*', C, V) :-
    V is A / B * C.
op(A, '/', B, '/', C, V) :-
    V is A / B / C.

esc(L):-
    member(v(n(1),_,Vn1),L),
    member(v(n(2),_,Vn2),L),
    member(v(n(3),_,Vn3),L),
    member(v(n(4),_,Vn4),L),
    member(v(n(5),_,Vn5),L),
    member(v(n(6),_,Vn6),L),
    member(v(n(7),_,Vn7),L),
    member(v(n(8),_,Vn8),L),
    member(v(n(9),_,Vn9),L),
    member(v(o(1),_,Vo1),L),
    member(v(o(2),_,Vo2),L),
    member(v(o(3),_,Vo3),L),
    member(v(o(4),_,Vo4),L),
    member(v(o(5),_,Vo5),L),
    member(v(o(6),_,Vo6),L),
    member(v(o(7),_,Vo7),L),
    member(v(o(8),_,Vo8),L),
    member(v(o(9),_,Vo9),L),
    member(v(o(10),_,Vo10),L),
    member(v(o(11),_,Vo11),L),
    member(v(o(12),_,Vo12),L),
    format("~d ~a ~d ~a ~d ~n", [Vn1,Vo1,Vn2,Vo2,Vn3]),
    format("~a   ~a   ~a ~n", [Vo7,Vo8,Vo9]),
    format("~d ~a ~d ~a ~d ~n", [Vn4,Vo3,Vn5,Vo4,Vn6]),
    format("~a   ~a   ~a ~n", [Vo10,Vo11,Vo12]),
    format("~d ~a ~d ~a ~d ~n", [Vn7,Vo5,Vn8,Vo6,Vn9]).