DROP TABLE IF EXISTS cliente CASCADE;
DROP TABLE IF EXISTS pagamento CASCADE;
DROP TABLE IF EXISTS historial CASCADE;
DROP TABLE IF EXISTS filme CASCADE;
DROP TABLE IF EXISTS etiqFilme CASCADE;
DROP TABLE IF EXISTS actor CASCADE;
DROP TABLE IF EXISTS director CASCADE;
DROP TABLE IF EXISTS filmeDirectores CASCADE;
DROP TABLE IF EXISTS filmeActores CASCADE;
DROP TABLE IF EXISTS premioFilme CASCADE;
DROP TABLE IF EXISTS premioActor CASCADE;
DROP TABLE IF EXISTS premioDirector CASCADE;

CREATE TABLE cliente (
	Login		VARCHAR(15) PRIMARY KEY,
	Password	VARCHAR(15),
	FirstName	VARCHAR(15),
	LastName	VARCHAR(15),
	DtAdesao	DATE,
	CCredito	CHAR(9),
	Porta		INTEGER,
	Rua		    VARCHAR(15),
	Cidade		VARCHAR(15)
);

CREATE TABLE pagamento (
	Pagamento 	INTEGER,
	DtPagamento DATE,
	Login		VARCHAR(15),
	PRIMARY KEY(Pagamento, Login),
	FOREIGN KEY(Login) REFERENCES cliente
);

CREATE TABLE filme (
	IdFilme		VARCHAR(6) PRIMARY KEY,
	TitOri		VARCHAR(50),
	TitIng		VARCHAR(50),
	TitPt		VARCHAR(50),
	Lingua		VARCHAR(15),
	DtEstreia	DATE,
	Resumo	    VARCHAR(500),
	LocalFilme	VARCHAR(15),
	Url		    VARCHAR(100),
	Path		VARCHAR(100)
);

CREATE TABLE historial (
	Login		VARCHAR(15),
	IdFilme		VARCHAR(6),
	DtVisto		DATE,
	PRIMARY KEY(Login, IdFilme),
	FOREIGN KEY (Login) REFERENCES cliente,
	FOREIGN KEY (IdFilme) REFERENCES filme
);

CREATE TABLE etiqFilme (
	IdFilme		VARCHAR(6),
	Genero	    VARCHAR(15),
	PRIMARY KEY(IdFilme, Genero),
	FOREIGN KEY(IdFilme) REFERENCES filme
);

CREATE TABLE Director (
	IdDirector	    VARCHAR(6) PRIMARY KEY,
	FirstName	    VARCHAR(15),
	LastName	    VARCHAR(15),
	DataNasc	    DATE,
	Nacionalidade   VARCHAR(15)
);

CREATE TABLE Actor (
	IdActor		    VARCHAR(6) PRIMARY KEY,
	FirstName	    VARCHAR(15),
	LastName	    VARCHAR(15),
	DataNasc	    DATE,
	Nacionalidade   VARCHAR(15)
);

CREATE TABLE filmeActores (
	IdFilme		VARCHAR(6),
	IdActor		VARCHAR(6),
	PRIMARY KEY(IdFilme, IdActor),
	FOREIGN KEY(IdFilme) REFERENCES filme,
	FOREIGN KEY(IdActor) REFERENCES actor
);

CREATE TABLE filmeDirectores (
	IdFilme		VARCHAR(6),
	IdDirector	VARCHAR(6),
	PRIMARY KEY(IdFilme, IdDirector),
	FOREIGN KEY(IdFilme) REFERENCES filme,
	FOREIGN KEY(IdDirector) REFERENCES director
);


CREATE TABLE premioFilme (
	IdFilme		VARCHAR(6),
	Premio		VARCHAR(50),
	PRIMARY KEY(IdFilme, Premio),
	FOREIGN KEY(IdFilme) REFERENCES filme
);

CREATE TABLE premioActor (
    IdFilme		VARCHAR(6),
	IdActor		VARCHAR(6),
	Premio		VARCHAR(50),
	PRIMARY KEY(IdFilme, IdActor, Premio),
	FOREIGN KEY(IdFilme) REFERENCES filme,
	FOREIGN KEY(IdActor) REFERENCES actor
);

CREATE TABLE premioDirector (
    IdFilme		VARCHAR(6),
    IdDirector	VARCHAR(6),
	Premio		VARCHAR(50),
	PRIMARY KEY(IdFilme, IdDirector, Premio),
	FOREIGN KEY(IdFilme) REFERENCES filme,
	FOREIGN KEY(IdDirector) REFERENCES director
);

INSERT INTO cliente VALUES('hiago93', 'aVrpJFts15', 'hiago', 'oliveira', '2015-06-01', '123456789', '1', 'Republica', 'Evora');
INSERT INTO cliente VALUES('luis69', 'omSPfDpOs14', 'luis', 'sousa', '2015-08-15', '987654321', '3', 'Lagoa', 'Evora');

INSERT INTO pagamento VALUES(1, '2015-06-01', 'hiago93');
INSERT INTO pagamento VALUES(2, '2015-07-01', 'hiago93');
INSERT INTO pagamento VALUES(3, '2015-08-01', 'hiago93');
INSERT INTO pagamento VALUES(4, '2015-09-01', 'hiago93');
INSERT INTO pagamento VALUES(1, '2015-08-15', 'luis69');
INSERT INTO pagamento VALUES(2, '2015-09-15', 'luis69');
INSERT INTO pagamento VALUES(3, '2015-10-15', 'luis69');
INSERT INTO pagamento VALUES(4, '2015-11-15', 'luis69');
INSERT INTO pagamento VALUES(5, '2015-12-15', 'luis69');

INSERT INTO filme VALUES('F1', 'Fight Club', 'Fight Club', 'Clube da Luta', 'Inglês', '1999-10-29', 'An insomniac office worker, looking for a way to change his life, crosses paths with a devil-may-care soap maker, forming an underground fight club that evolves into something much, much more…', 'California', 'http://www.imdb.com/title/tt0137523/', '/home/films/90s/fight_club.mxf');
INSERT INTO filme VALUES('F2', 'The Matrix', 'The Matrix', 'Matrix', 'Inglês', '1999-06-11', 'A computer hacker learns from mysterious rebels about the true nature of his reality and his role in the war against its controllers.', 'Various', 'http://www.imdb.com/title/tt0133093/', '/home/films/90s/the_matrix.mxf');
INSERT INTO filme VALUES('F3', 'The Maze Runner', 'The Maze Runner', 'Maze Runner - Correr ou Morrer', 'Inglês', '2014-10-10', 'Thomas is deposited in a community of boys after his memory is erased, soon learning they are all trapped in a maze that will require him to join forces with fellow runners for a shot at escape.', 'Louisiana', 'http://www.imdb.com/title/tt1790864/', '/home/films/10s/the_maze_runner.mxf');
INSERT INTO filme VALUES('F4', 'The Da Vinci Code', 'The Da Vinci Code', 'O Código Da Vinci', 'Inglês', '2006-05-19', 'A murder inside the Louvre and clues in Da Vinci paintings lead to the discovery of a religious mystery protected by a secret society for two thousand years -- which could shake the foundations of Christianity.', 'França', 'http://www.imdb.com/title/tt0382625/', '/home/films/00s7the_da_vinci_code.mxf');
INSERT INTO filme VALUES('F5', 'Into the Woods', 'Into the Woods', 'Caminhos da Floresta', 'Inglês', '2014-12-08', 'A witch tasks a childless baker and his wife with procuring magical items from classic fairy tales to reverse the curse put on their family tree.', 'Inglaterra', 'http://www.imdb.com/title/tt2180411/', '/home/films/10s/into_the_woods.mxf');
INSERT INTO filme VALUES('F6', 'The Matrix Reloaded', 'The Matrix Reloaded', 'Matrix Reloaded', 'Inglês', '2003-05-21', 'Neo and the rebel leaders estimate that they have 72 hours until 250,000 probes discover Zion and destroy it and its inhabitants. During this, Neo must decide how he can save Trinity from a dark fate in his dreams.', 'Various', 'http://www.imdb.com/title/tt0234215/', '/home/films/00s/the_matrix_reloaded.mxf');
INSERT INTO filme VALUES('F7', 'The Matrix Revolutions', 'The Matrix Revolutions', 'Matrix Revolutions', 'Inglês', '2003-11-05', 'The human city of Zion defends itself against the massive invasion of the machines as Neo fights to end the war at another front while also opposing the rogue Agent Smith.', 'Various', 'http://www.imdb.com/title/tt0242653/', '/home/films/00s/the_matrix_revolutions.mxf');
INSERT INTO filme VALUES('F8', '8 Mile', '8 Mile', '8 Mile', 'Inglês', '2003-01-17', 'A young rapper, struggling with every aspect of his life, wants to make it big but his friends and foes make this odyssey of rap, harder than it may seem.', 'Michigan', 'http://www.imdb.com/title/tt0298203/', '/home/films/00s/8_mile.mxf');
INSERT INTO filme VALUES('F9', 'Interstellar', 'Interstellar', 'Interestelar', 'Inglês', '2014-11-07', 'A team of explorers travel through a wormhole in space in an attempt to ensure humanitys survival.', 'Canada', 'http://www.imdb.com/title/tt0816692/', '/home/films/10s/interstellar.mxf');
INSERT INTO filme VALUES('F10', 'La vita è bella', 'Life Is Beautiful', 'A vida é bela', 'Italiano', '1997-12-20', 'When an open-minded Jewish librarian and his son become victims of the Holocaust, he uses a perfect mixture of will, humor and imagination to protect his son from the dangers around their camp.', 'Itália', 'http://www.imdb.com/title/tt0118799/', '/home/films/90s/life_is_beautiful.mxf');

INSERT INTO historial VALUES('hiago93', 'F2', '2015-06-02');
INSERT INTO historial VALUES('hiago93', 'F3', '2015-07-12');
INSERT INTO historial VALUES('hiago93', 'F6', '2015-08-21');
INSERT INTO historial VALUES('hiago93', 'F7', '2015-08-29');
INSERT INTO historial VALUES('luis69', 'F1', '2015-08-15');
INSERT INTO historial VALUES('luis69', 'F3', '2015-08-20');
INSERT INTO historial VALUES('luis69', 'F5', '2015-09-09');
INSERT INTO historial VALUES('luis69', 'F8', '2015-10-10');
INSERT INTO historial VALUES('luis69', 'F9', '2015-11-27');
INSERT INTO historial VALUES('luis69', 'F10', '2015-12-02');


INSERT INTO director VALUES('D1', 'David', 'Fincher', '1962-08-28', 'Americana');
INSERT INTO director VALUES('D2', 'Andy', 'Wachowski', '1967-12-29', 'Americana');
INSERT INTO director VALUES('D3', 'Lana', 'Wachowski', '1965-06-21', 'Americana');
INSERT INTO director VALUES('D4', 'Wes', 'Ball', '1980-10-28', 'Americana');
INSERT INTO director VALUES('D5', 'Ron', 'Howard', '1954-03-01', 'Americana');
INSERT INTO director VALUES('D6', 'Rob', 'Marshall', '1960-10-17', 'Americana');
INSERT INTO director VALUES('D7', 'Curtis', 'Hanson', '1945-03-24', 'Americana');
INSERT INTO director VALUES('D8', 'Christopher', 'Nolan', '1970-07-30', 'Inglesa');
INSERT INTO director VALUES('D9', 'Roberto', 'Benigni', '1952-10-27', 'Italiana');


INSERT INTO filmeDirectores VALUES('F1', 'D1');
INSERT INTO filmeDirectores VALUES('F2', 'D2');
INSERT INTO filmeDirectores VALUES('F2', 'D3');
INSERT INTO filmeDirectores VALUES('F3', 'D4');
INSERT INTO filmeDirectores VALUES('F4', 'D5');
INSERT INTO filmeDirectores VALUES('F5', 'D6');
INSERT INTO filmeDirectores VALUES('F6', 'D2');
INSERT INTO filmeDirectores VALUES('F6', 'D3');
INSERT INTO filmeDirectores VALUES('F7', 'D2');
INSERT INTO filmeDirectores VALUES('F7', 'D3');
INSERT INTO filmeDirectores VALUES('F8', 'D7');
INSERT INTO filmeDirectores VALUES('F9', 'D8');
INSERT INTO filmeDirectores VALUES('F10', 'D9');

INSERT INTO actor VALUES('A1', 'Brad', 'Pitt', '1963-12-18', 'Americana');
INSERT INTO actor VALUES('A2', 'Edward', 'Norton', '1969-08-18', 'Americana');
INSERT INTO actor VALUES('A3', 'Helena', 'carter', '1966-05-26', 'Inglesa');
INSERT INTO actor VALUES('A4', 'Jared', 'Leto', '1971-12-26', 'Americana');
INSERT INTO actor VALUES('A5', 'Keanu', 'Reeves', '1964-09-02', 'Libanesa');
INSERT INTO actor VALUES('A6', 'Laurence', 'Fishburne', '1961-07-30', 'Americana');
INSERT INTO actor VALUES('A7', 'Carrie-Anne', 'Moss', '1967-08-21', 'Canadense');
INSERT INTO actor VALUES('A8', 'Dylan', 'OBrien', '1991-08-26', 'Americana');
INSERT INTO actor VALUES('A9', 'Kaya', 'Scodelario', '1992-03-13', 'Inglesa');
INSERT INTO actor VALUES('A10', 'Will', 'Poulter', '1993-01-28', 'Inglesa');
INSERT INTO actor VALUES('A11', 'Tom', 'Hanks', '1956-07-09', 'Americana');
INSERT INTO actor VALUES('A12', 'Audrey', 'Tautou', '1976-07-09', 'Francesa');
INSERT INTO actor VALUES('A13', 'Jean', 'Reno', '1948-07-30', 'Francesa');
INSERT INTO actor VALUES('A14', 'Anna', 'Kendrick', '1985-08-09', 'Americana');
INSERT INTO actor VALUES('A15', 'Meryl', 'Streep', '1949-06-22', 'Americana');
INSERT INTO actor VALUES('A16', 'Chris', 'Pine', '1980-08-26', 'Americana');
INSERT INTO actor VALUES('A17', 'Marshall', 'Mathers', '1972-10-17', 'Americana');
INSERT INTO actor VALUES('A18', 'Brittany', 'Murphy', '1977-11-10', 'Americana');
INSERT INTO actor VALUES('A19', 'Kim', 'Basinger', '1953-12-08', 'Americana');
INSERT INTO actor VALUES('A20', 'Matthew', 'McConaughey', '1969-11-04', 'Americana');
INSERT INTO actor VALUES('A21', 'Anne', 'Hathaway', '1982-11-12', 'Americana');
INSERT INTO actor VALUES('A22', 'Jessica', 'Chastain', '1977-03-24', 'Americana');
INSERT INTO actor VALUES('A23', 'Roberto', 'Benigni', '1952-10-27', 'Italiana');
INSERT INTO actor VALUES('A24', 'Nicoletta', 'Braschi', '1960-04-19', 'Italiana');
INSERT INTO actor VALUES('A25', 'Giorgio', 'Cantarini', '1992-04-12', 'Italiana');

INSERT INTO filmeActores VALUES('F1', 'A1');
INSERT INTO filmeActores VALUES('F1', 'A2');
INSERT INTO filmeActores VALUES('F1', 'A3');
INSERT INTO filmeActores VALUES('F1', 'A4');
INSERT INTO filmeActores VALUES('F2', 'A5');
INSERT INTO filmeActores VALUES('F2', 'A6');
INSERT INTO filmeActores VALUES('F2', 'A7');
INSERT INTO filmeActores VALUES('F3', 'A8');
INSERT INTO filmeActores VALUES('F3', 'A9');
INSERT INTO filmeActores VALUES('F3', 'A10');
INSERT INTO filmeActores VALUES('F4', 'A11');
INSERT INTO filmeActores VALUES('F4', 'A12');
INSERT INTO filmeActores VALUES('F4', 'A13');
INSERT INTO filmeActores VALUES('F5', 'A14');
INSERT INTO filmeActores VALUES('F5', 'A15');
INSERT INTO filmeActores VALUES('F5', 'A16');
INSERT INTO filmeActores VALUES('F6', 'A5');
INSERT INTO filmeActores VALUES('F6', 'A6');
INSERT INTO filmeActores VALUES('F6', 'A7');
INSERT INTO filmeActores VALUES('F7', 'A5');
INSERT INTO filmeActores VALUES('F7', 'A6');
INSERT INTO filmeActores VALUES('F7', 'A7');
INSERT INTO filmeActores VALUES('F8', 'A17');
INSERT INTO filmeActores VALUES('F8', 'A18');
INSERT INTO filmeActores VALUES('F8', 'A19');
INSERT INTO filmeActores VALUES('F9', 'A20');
INSERT INTO filmeActores VALUES('F9', 'A21');
INSERT INTO filmeActores VALUES('F9', 'A22');
INSERT INTO filmeActores VALUES('F10', 'A23');
INSERT INTO filmeActores VALUES('F10', 'A24');
INSERT INTO filmeActores VALUES('F10', 'A25');

INSERT INTO etiqFilme VALUES('F1', 'Drama');
INSERT INTO etiqFilme VALUES('F2', 'Acção');
INSERT INTO etiqFilme VALUES('F2', 'Sci-Fi');
INSERT INTO etiqFilme VALUES('F3', 'Acção');
INSERT INTO etiqFilme VALUES('F3', 'Mistério');
INSERT INTO etiqFilme VALUES('F3', 'Sci-Fi');
INSERT INTO etiqFilme VALUES('F3', 'Thriller');
INSERT INTO etiqFilme VALUES('F4', 'Mistério');
INSERT INTO etiqFilme VALUES('F4', 'Thriller');
INSERT INTO etiqFilme VALUES('F5', 'Aventura');
INSERT INTO etiqFilme VALUES('F5', 'Fantasia');
INSERT INTO etiqFilme VALUES('F5', 'Musical');
INSERT INTO etiqFilme VALUES('F6', 'Sci-Fi');
INSERT INTO etiqFilme VALUES('F6', 'Acção');
INSERT INTO etiqFilme VALUES('F7', 'Sci-Fi');
INSERT INTO etiqFilme VALUES('F7', 'Acção');
INSERT INTO etiqFilme VALUES('F8', 'Drama');
INSERT INTO etiqFilme VALUES('F8', 'Musical');
INSERT INTO etiqFilme VALUES('F9', 'Aventura');
INSERT INTO etiqFilme VALUES('F9', 'Drama');
INSERT INTO etiqFilme VALUES('F9', 'Sci-Fi');
INSERT INTO etiqFilme VALUES('F10', 'Comédia');
INSERT INTO etiqFilme VALUES('F10', 'Drama');
INSERT INTO etiqFilme VALUES('F10', 'Romance');

INSERT INTO premioFilme VALUES('F1', 'ACCA - Best Adapted Screenplay');
INSERT INTO premioFilme VALUES('F1', 'Jupiter Award - Best Film Editing');
INSERT INTO premioFilme VALUES('F2', 'Oscar - Best Film Editing');
INSERT INTO premioFilme VALUES('F2', 'Oscar - Best Sound');
INSERT INTO premioFilme VALUES('F2', 'Oscar - Best Sound Effects Editing');
INSERT INTO premioFilme VALUES('F2', 'Oscar - Best Visual Effects');
INSERT INTO premioFilme VALUES('F2', 'BAFTA - Best Sound');
INSERT INTO premioFilme VALUES('F2', 'BAFTA - Best Special Visual Effects');
INSERT INTO premioFilme VALUES('F2', 'Saturn Award - Best Science Fiction Film');
INSERT INTO premioFilme VALUES('F2', 'Empire Award - Best Film');
INSERT INTO premioFilme VALUES('F2', 'Jupiter Award - Best International Film');
INSERT INTO premioFilme VALUES('F5', 'AFI Award - Movie of the Year');
INSERT INTO premioFilme VALUES('F8', 'Oscar - Best Music, Original Song');
INSERT INTO premioFilme VALUES('F9', 'Oscar - Best Visual Effects');
INSERT INTO premioFilme VALUES('F9', 'BAFTA - Best Special Visual Effects');
INSERT INTO premioFilme VALUES('F9', 'Saturn Award - Best Science Fiction Film');
INSERT INTO premioFilme VALUES('F9', 'Saturn Award - Best Special Effects');
INSERT INTO premioFilme VALUES('F9', 'AFI Award - Movie of the Year');
INSERT INTO premioFilme VALUES('F9', 'ACCA - Best Visual Effects');
INSERT INTO premioFilme VALUES('F9', 'Empire Award - Best Film');
INSERT INTO premioFilme VALUES('F10', 'Oscar - Best Foreign Language Film');
INSERT INTO premioFilme VALUES('F10', 'ACCA - Best Foreign Language Film');

INSERT INTO premioActor VALUES('F1', 'A2', 'Jupiter Award - Best International Actor');
INSERT INTO premioActor VALUES('F1', 'A3', 'Empire Award - Best British Actress');
INSERT INTO premioActor VALUES('F2', 'A7', 'Empire Award - Best Debut');
INSERT INTO premioActor VALUES('F3', 'A8', 'MTV Movie Award - Breakthrough Performance');
INSERT INTO premioActor VALUES('F3', 'A8', 'MTV Movie Award - Best Hero');
INSERT INTO premioActor VALUES('F3', 'A8', 'MTV Movie Award - Best Fight');
INSERT INTO premioActor VALUES('F3', 'A10', 'MTV Movie Award - Best Fight');
INSERT INTO premioActor VALUES('F4', 'A12', 'Jupiter Award - Best International Actress');
INSERT INTO premioActor VALUES('F5', 'A15', 'MTV Movie Award - Best Villain');
INSERT INTO premioActor VALUES('F8', 'A17', 'MTV Movie Award - Best Male Performance');
INSERT INTO premioActor VALUES('F8', 'A17', 'MTV Movie Award - Breakthrough Male Performance');
INSERT INTO premioActor VALUES('F10', 'A23', 'Oscar - Best Actor in a Leading Role');

INSERT INTO premioDirector VALUES('F2', 'D2', 'Saturn Award - Best Director');
INSERT INTO premioDirector VALUES('F2', 'D3', 'Saturn Award - Best Director');
INSERT INTO premioDirector VALUES('F2', 'D2', 'Jupiter Award - Best International Director');
INSERT INTO premioDirector VALUES('F2', 'D3', 'Jupiter Award - Best International Director');
INSERT INTO premioDirector VALUES('F9', 'D8', 'Empire Award - Best Director');
