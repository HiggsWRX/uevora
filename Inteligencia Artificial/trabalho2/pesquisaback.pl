p:- estado_inicial(E0), back(E0,A), cpu_time(X), esc(A, X).

back(e([],A),A).
back(E,Sol):- sucessor(E,E1), restricoes(E1), forward_check(E1, E2), back(E2,Sol).

sucessor(e([v(N,D,V)|R],E),e(R,[v(N,D,V)|E])):- member(V,D).