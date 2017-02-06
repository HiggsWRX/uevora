rainhas(N, R) :-
    length(R, N),
    fd_domain(R, 1, N),
    ok(R),
    fd_labeling(R).

ok([]).
ok([R|Rs]) :- ok(Rs, R, 1), ok(Rs).
ok([], _, _).
ok([Rj|Rs], Ri, I) :-
    I1 is I+1,
    ok(Rs, Ri, I1),
    Ri #\= Rj, Ri #\= Rj+I, Ri+I #\= Rj.

mkq(N, Q) :-
    length(Q, N),
    q(Q, N).
q([], _).
q([Q|Qs], N) :-
    q1(1, N, Q),
    q(Qs, N).
q1(Q, N, Q) :- Q =< N.
q1(I, N, Q) :- I < N, I1 is I+1, q1(I1, N, Q).

sendmore([S,E,N,D,M,O,R,Y]) :-
    fd_domain([S,E,N,D,M,O,R,Y], 0, 9),
    S #\= 0, M #\= 0,
    fd_all_different([S,E,N,D,M,O,R,Y]),
                 S*1000 + E*100 + N*10 + D
               + M*1000 + O*100 + R*10 + E
    #= M*10000 + O*1000 + N*100 + E*10 + Y,
    fd_labeling([S,E,N,D,M,O,R,Y]).

sendmost([S,E,N,D,M,O,T,Y]) :-
    fd_domain([S,E,N,D,M,O,T,Y], 0, 9),
    M #\= 0,
    fd_all_different([S,E,N,D,M,O,T,Y]),
              S*1000 + E*100 + N*10 + D +
              M*1000 + O*100 + S*10 + T #=
    M*10000 + O*1000 + N*100 + E*10 + Y,
    fd_maximize(fd_labeling([S,E,N,D,M,O,T,Y]), V).