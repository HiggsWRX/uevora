:- dynamic(pos/4).
:- dynamic(turn/1).
:- dynamic(next/1).
:- dynamic(nevermoved/4).

%pos(PEÇA, COR, C, L)
pos(rainha, branco, 4, 1).
pos(rainha, preto, 4, 8).
pos(torre, branco, 1, 1).
pos(torre, branco, 8, 1).
pos(torre, preto, 1, 8).
pos(torre, preto, 8, 8).
pos(bispo, branco, 3, 1).
pos(bispo, branco, 6, 1).
pos(bispo, preto, 3, 8).
pos(bispo, preto, 6, 8).
pos(cavalo, branco, 2, 1).
pos(cavalo, branco, 7, 1).
pos(cavalo, preto, 2, 8).
pos(cavalo, preto, 7, 8).
pos(peao, branco, 1, 2).
pos(peao, branco, 2, 2).
pos(peao, branco, 3, 2).
pos(peao, branco, 4, 2).
pos(peao, branco, 5, 2).
pos(peao, branco, 6, 2).
pos(peao, branco, 7, 2).
pos(peao, branco, 8, 2).
pos(peao, preto, 1, 7).
pos(peao, preto, 2, 7).
pos(peao, preto, 3, 7).
pos(peao, preto, 4, 7).
pos(peao, preto, 5, 7).
pos(peao, preto, 6, 7).
pos(peao, preto, 7, 7).
pos(peao, preto, 8, 7).
pos(rei, branco, 5, 1).
pos(rei, preto, 5, 8).

pic(torre, branco, "\33\[94m♜\33\[39m").
pic(cavalo, branco, "\33\[94m♞\33\[39m").
pic(bispo, branco, "\33\[94m♝\33\[39m").
pic(rainha, branco, "\33\[94m♛\33\[39m").
pic(rei, branco, "\33\[94m♚\33\[39m").
pic(peao, branco, "\33\[94m♟\33\[39m").
pic(torre, preto, "\33\[30m♜\33\[39m").
pic(cavalo, preto, "\33\[30m♞\33\[39m").
pic(bispo, preto, "\33\[30m♝\33\[39m").
pic(rainha, preto, "\33\[30m♛\33\[39m").
pic(rei, preto, "\33\[30m♚\33\[39m").
pic(peao, preto, "\33\[30m♟\33\[39m").

turn(branco).      % input alternado entre jogada branca e preta
next(preto).

nevermoved(rei, branco, 5, 1).
nevermoved(rei, preto, 5, 8).
nevermoved(torre, branco, 1, 1).
nevermoved(torre, branco, 8, 1).
nevermoved(torre, preto, 1, 8).
nevermoved(torre, preto, 8, 8).

piece(1, rainha).
piece(2, torre).
piece(3, bispo).
piece(4, cavalo).