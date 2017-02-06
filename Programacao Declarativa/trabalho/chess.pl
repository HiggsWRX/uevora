:- include(bd).
:- dynamic(grave/4).
:- dynamic(boardupdated/0).
:- dynamic(promote/1).
:- dynamic(getplay/4).
:- initialization(play).

% TODO: EN PASSANT

play :-
    gets(PlayString),
    \+ PlayString = [],
    saveplay(PlayString),
    handleplay,
    retract(boardupdated),
    play.
play :- printboard.

gets(String) :-
    get0(Char),
    gets([], Char, String), !.
gets(String, 10, String).                % 10 é o newline
gets(String, -1, String).                % -1 é o end-of-file
gets(I, Char, [Char|O]) :- get0(CC), gets(I, CC, O).

saveplay(PlayString) :-
    length(PlayString, L),
    (L is 4; L is 5, nth(5, PlayString, PP), number_codes(Z, [PP]), assertz(promote(Z))),
    nth(1, PlayString, OColCode), nth(2, PlayString, OLinCode),   % From column, From row
    nth(3, PlayString, DColCode), nth(4, PlayString, DLinCode),   % To column, To row
    number_codes(OCol, [OColCode]), number_codes(OLin, [OLinCode]),
    number_codes(DCol, [DColCode]), number_codes(DLin, [DLinCode]),
    assertz(getplay(OCol, OLin, DCol, DLin)).

handleplay :-
    getplay(OCol, OLin, DCol, DLin),
    checkinboard,
    checkteams, % can't capture same team
    turn(Color),
    pos(Piece, Color, OCol, OLin),
    validateplay(Piece, [OCol|OLin], [DCol|DLin]),
    updateboard,
    pos(rei, Color, ReiCol, ReiLin),
    \+ placeincheck(ReiCol, ReiLin),
    checkpromotion,
    toggle,
    retract(getplay(_, _, _, _)).
handleplay :-               % first handleplay fails, restore board and any changes
    boardupdated,
    restoreboard,
    fail.
handleplay :-
    promote(_),
    retract(promote(_)),
    fail.
handleplay :-
    retract(getplay(_, _, _, _)),
    fail.

checkinboard :-
    getplay(OCol, OLin, DCol, DLin),
    OCol > 0, OCol < 9, OLin > 0, OLin < 9,
    DCol > 0, DCol < 9, DLin > 0, DLin < 9.

checkteams :-
    getplay(_, _, DCol, DLin),
    \+ pos(_, _, DCol, DLin).
checkteams :-
    getplay(OCol, OLin, DCol, DLin),
    pos(_, Color1, OCol, OLin),
    pos(_, Color2, DCol, DLin),
    \+ Color1 == Color2.

validateplay(cavalo, [OCol|OLin], [DCol|DLin]) :-
    validateknight([OCol|OLin], [DCol|DLin]).
validateplay(torre, [OCol|OLin], [DCol|DLin]) :-
    validatetower([OCol|OLin], [DCol|DLin]),
    pos(Torre, Color, OCol, OLin),
    checkfirstmoved(Torre, Color, OCol, OLin).
validateplay(bispo, [OCol|OLin], [DCol|DLin]) :-
    validatebishop([OCol|OLin], [DCol|DLin]).
validateplay(peao, [OCol|OLin], [DCol|DLin]) :-
    pos(peao, Color, OCol, OLin),
    validatepawn(Color, [OCol|OLin], [DCol|DLin]).
validateplay(rainha, [OCol|OLin], [DCol|DLin]) :-
    (validatebishop([OCol|OLin], [DCol|DLin]); validatetower([OCol|OLin], [DCol|DLin])).
validateplay(rei, [OCol|OLin], [DCol|DLin]) :-
    validateking([OCol|OLin], [DCol|DLin]),
    pos(rei, Color, OCol, OLin),
    checkfirstmoved(rei, Color, OCol, OLin).

checkfirstmoved(Piece, Color, Col, Lin) :-
    nevermoved(Piece, Color, Col, Lin),
    retract(nevermoved(Piece, Color, Col, Lin)).
checkfirstmoved(_, _, _, _).

validateknight([OCol|OLin], [DCol|DLin]) :-
    (DCol is OCol-2; DCol is OCol+2),
    (DLin is OLin-1; DLin is OLin+1).
validateknight([OCol|OLin], [DCol|DLin]) :-
    (DCol is OCol-1; DCol is OCol+1),
    (DLin is OLin-2; DLin is OLin+2).

validatetower(Coord, Coord).  % Mesma coordenada, chegou ao destino com sucesso
validatetower([OCol|OLin], [DCol|DLin]) :-
    OCol == DCol,
    (DLin > OLin, Next is OLin+1; DLin < OLin, Next is OLin-1),
    (\+ pos(_, _, OCol, Next); Next == DLin), !,
    validatetower([OCol|Next], [DCol|DLin]).
validatetower([OCol|OLin], [DCol|DLin]) :-
    OLin == DLin,
    (DCol > OCol, Next is OCol+1; DCol < OCol, Next is OCol-1),
    (\+ pos(_, _, Next, OLin); Next == DCol), !,
    validatetower([Next|OLin], [DCol|DLin]).

validatebishop(Coord, Coord).
validatebishop([OCol|OLin], [DCol|DLin]) :-
    (OCol < DCol, NewCol is OCol+1; OCol > DCol, NewCol is OCol-1),
    (OLin < DLin, NewLin is OLin+1; OLin > DLin, NewLin is OLin-1),
    (\+ pos(_, _, NewCol, NewLin); [NewCol|NewLin] == [DCol|DLin]), !,
    validatebishop([NewCol|NewLin], [DCol|DLin]).

validatepawn(branco, [OCol|OLin], [DCol|DLin]) :-
    (OLin == 2, DCol == OCol, (DLin is OLin+1; DLin is OLin+2); DCol == OCol, DLin is OLin+1).
validatepawn(branco, [OCol|OLin], [DCol|DLin]) :-
    pos(_, _, DCol, DLin),
    (DCol is OCol-1; DCol is OCol+1),
    DLin is OLin+1.
validatepawn(preto, [OCol|OLin], [DCol|DLin]) :-
    (OLin == 7, DCol == OCol, (DLin is OLin-1; DLin is OLin-2); DCol == OCol, DLin is OLin-1).
validatepawn(preto, [OCol|OLin], [DCol|DLin]) :-
    pos(_, _, DCol, DLin),
    (DCol is OCol-1; DCol is OCol+1),
    DLin is OLin-1.

validateking([5|1], [3|1]) :-      % caso especial castling
    validatecastling([5|1], [3|1]).
validateking([5|1], [7|1]) :-      % caso especial castling
    validatecastling([5|1], [7|1]).
validateking([5|8], [3|8]) :-      % caso especial castling
    validatecastling([5|8], [3|8]).
validateking([5|8], [7|8]) :-      % caso especial castling
    validatecastling([5|8], [7|8]).
validateking([OCol|OLin], [DCol|DLin]) :-
    [OCol|OLin] \= [DCol|DLin],
    (DCol is OCol-1; DCol is OCol+1; DCol == OCol),
    (DLin is OLin-1; DLin is OLin+1; DLin == OLin).

validatecastling([OCol|OLin], [DCol|DLin]) :-
    (DCol == 3, Y is 1, X is 4; Y is 8, X is 6),  % Y - See what tower is involved
    turn(CorTurno),                                    % X is midway point
    nevermoved(rei, CorTurno, OCol, OLin),
    nevermoved(torre, CorTurno, OLin, Y),
    validatetower([OLin|Y], [X|DLin]),
    \+ placeincheck(OCol, OLin),
    \+ placeincheck(X, OLin),
    \+ placeincheck(DCol, OLin),
    retract(pos(torre, CorTurno, OLin, Y)),
    assertz(pos(torre, CorTurno, X, OLin)).

updateboard :-
    getplay(OCol, OLin, DCol, DLin),
    pos(Piece, Color1, OCol, OLin),
    retract(pos(Piece, Color1, OCol, OLin)),
    ( pos(Captured, Color2, DCol, DLin), retract(pos(Captured, Color2, DCol, DLin)),
      assertz(grave(Captured, Color2, DCol, DLin)), assertz(pos(Piece, Color1, DCol, DLin))
    ; assertz(pos(Piece, Color1, DCol, DLin)) ),
    assertz(boardupdated).

restoreboard :-
    getplay(OCol, OLin, DCol, DLin),
    pos(Piece1, Color1, DCol, DLin),
    retract(pos(Piece1, Color1, DCol, DLin)),
    assertz(pos(Piece1, Color1, OCol, OLin)),
    grave(Piece2, Color2, DCol, DLin),
    retract(grave(Piece2, Color2, DCol, DLin)),
    assertz(pos(Piece2, Color2, DCol, DLin)).
restoreboard.

placeincheck(Col, Lin) :-
    next(OtherColor),    % color
    pos(Piece, OtherColor, PieceCol, PieceLin),
    \+ Piece == rei,    % kings cannot check
    validateplay(Piece, [PieceCol|PieceLin], [Col|Lin]).

checkpromotion :-
    promote(Code),
    piece(Code, Piece),
    getplay(_, _, DCol, DLin),
    turn(Color),
    retract(pos(peao, Color, DCol, DLin)),
    assertz(pos(Piece, Color, DCol, DLin)),
    toggle.     % por alguma razao o toggle nao funciona depois do
checkpromotion. % checkpromotion, temos de o fazer de novo aqui

toggle :-
    turn(Color),
    next(OtherColor),
    retract(turn(_)),
    retract(next(_)),
    assertz(turn(OtherColor)),
    assertz(next(Color)).

printboard :-
    for(I, -8, -1),
        abs(I, Ia),
        format("~n", _),
        write(Ia), format(" ", _),
        for(J, 1, 8),
            %printpeca(Ia, J),
            printc(J, Ia),
    fail.
printboard :-
    format("~n  ", _),
    for(I, 49, 56),
        format(" ~c ", [I]),
    fail.
printboard.

abs(X, Y) :-
    X > 0 -> Y is X; Y is -X.

printc(I, J) :-
    M is I mod 2,
    (   M is 0 ->
        N is J mod 2,
        (   N is 0 ->
            (   \+ pos(_, _, I, J) ->
                format("\33\[100m   \33\[49m", _)
            ;   pos(P, C, I, J), pic(P, C, T), format("\33\[100m ~s \33\[49m", [T])
            )
        ;   (   \+ pos(_, _, I, J) ->
                format("\33\[107m   \33\[49m", _)
            ;   pos(P, C, I, J), pic(P, C, T), format("\33\[107m ~s \33\[49m", [T])
            )
        )
    ;   N is J mod 2,
        (   N is 0 ->
            (   \+ pos(_, _, I, J) ->
                format("\33\[107m   \33\[49m", _)
            ;   pos(P, C, I, J), pic(P, C, T), format("\33\[107m ~s \33\[49m", [T])
            )
        ;   (   \+ pos(P, _, I, J) ->
                format("\33\[100m   \33\[49m", _)
            ;   pos(P, C, I, J), pic(P, C, T), format("\33\[100m ~s \33\[49m", [T])
            )
        )
    ).