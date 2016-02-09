import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.ArrayList;

public class Boggle {

    private QuadHashTable<String> dictHashed;
    private QuadHashTable<String> dictPrefixes;
    private QuadHashTable<String> wordsFound = new QuadHashTable<>(11);
    private LinkedList<ArrayList<Position>> chavePalavras = new LinkedList<>();
    private String availableLetters = "";
    private Position boardSize;
    private char[][] boggleBoard;

    public static void main(String[] args) {
        //long startTime = System.nanoTime();
        Boggle game = new Boggle();
        String dictPath = args[0];
        String bogglePath = args[1];
        game.lerDicionario(dictPath);
        game.lerBoggle(bogglePath);
        LinkedList<ArrayList<Position>> solution = game.solve();
        //long endTime = System.nanoTime();
        //long duration = (endTime - startTime) / 1000000;
        game.printSolution(solution);
        //System.out.println("Solved in " + duration + " ms.");
    }

    public Boggle() {
    }

    public void lerDicionario(String fileName) {
        BufferedReader reader = null;

        try {
            File file = new File(fileName);
            reader = new BufferedReader(new FileReader(file));
            int numLines = 0;                                                   // Saber o número de linhas do dicionário para
                                                                                // criar uma hashtable com espaço suficiente.
            while (reader.readLine() != null) {
                numLines++;
            }

            int primo = HashTable.procPrimo(numLines);                          // Procurar o próximo primo seguinte ao número
            dictHashed = new QuadHashTable<>(primo);                            // de linhas do dicionário usado.
            dictPrefixes = new QuadHashTable<>(primo);

            String line;
            reader = new BufferedReader(new FileReader(file));                  // Reset do BufferedReader
            while ((line = reader.readLine()) != null) {
                if (!line.equals("")) {                                         // Se a linha lida não for vazia,
                    dictHashed.insere(line);                                    // insere a palavra na hashtable

                    for (int i = line.length()-1; i > 0; i--) {                 // Começamos tambem a guardar todos os prefixos
                        dictPrefixes.insere(line.substring(0, i));              // numa hashtable.
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void lerBoggle(String fileName) {
        BufferedReader reader = null;

        try {                                                                   // Queremos ler o ficheiro do Boggle caracter a
            File file = new File(fileName);                                     // caracter pois sendo um ficheiro tão pequeno
            reader = new BufferedReader(new FileReader(file));                  // não justifica andar com expressoes regulares
            int nextChar;                                                       // para remover espaços e vazios
            int linhasB = 0;                                                    // utilizando o método split() dos arrays.
            int colunasB = 0;                                                   // Sendo assim, se o caracter lido tiver o código
            while ((nextChar = reader.read()) != -1) {                          // 32 (espaço) ou 10 (carriage return) não interessa.
                if (nextChar != 32 && nextChar != 10) {
                    availableLetters += (char) nextChar;                        // Mantemos também duas variaveis para saber o numero
                    colunasB++;                                                 // de linhas e colunas de um jogo de Boggle
                }                                                               // para conseguir jogar com jogos 4x4, 5x5, 6x6, etc.
                if (nextChar == 10) {
                    linhasB++;
                }
            }
            colunasB = colunasB / linhasB;                                      // No fim temos uma string com as letras do boggle.
            availableLetters = availableLetters.toLowerCase();                  // Aproveitamos a classe Position para termos o tamanho
            boardSize = new Position(linhasB, colunasB);                        // do board facilmente acessível, caso necessário.

            boggleBoard = new char[linhasB][colunasB];                          // Neste passo metemos o board num array bi-dimensional
            int counter = 0;                                                    // para ser mais facil aceder.
            for (int i = 0; i < linhasB; i++) {                                 // Assim, dando o exemplo do enunciado, quando queremos
                for (int j = 0; j < colunasB; j++, counter++) {                 // aceder à posição (2,1), no boggleBoard[2][1]
                    boggleBoard[i][j] = availableLetters.charAt(counter);       // iremos obter o char 'm', tal como pretendido.
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public LinkedList<ArrayList<Position>> solve() {
        Position[] moves = {new Position(-1, -1), new Position(-1, 0),          // Todas as posições adjacentes de um dado ponto.
                            new Position (-1, 1), new Position(0, -1),          // NW, N, NE, W, E, SW, S, SE
                            new Position(0, 1), new Position(1, -1),
                            new Position(1, 0), new Position(1, 1)
                            };

        for (int i = 0; i < boardSize.x; i++) {                                 // A partir de cada letra formam-se palavras com
            for (int j = 0; j < boardSize.y; j++) {                             // as suas posições adjacentes.
                Position start = new Position(i, j);                            // Se e palavra encontrada é prefixo de uma palavra
                String word = "" + boggleBoard[start.x][start.y];               // do dicionário, continua-se a guardar na lista
                                                                                // de posições a nova posição.
                ArrayList<Position> visited = new ArrayList<>();                // Quando é uma palavra que está no dicionario
                visited.add(start);                                             // Adiciona-se à lista de palavras encontradas
                solve(word, start, visited, moves);                             // (as suas posiçoes)
            }
        }

        return chavePalavras;
    }

    public void solve(String word, Position newP,
                      ArrayList<Position> visit, Position[] moves) {
        for(Position p : moves) {
            Position newPos = new Position(newP.x + p.x, newP.y + p.y);
            if (validPos(newPos, visit)) {
                String newWord = word + boggleBoard[newPos.x][newPos.y];
                if (dictHashed.procurar(newWord) != null) {
                    if(newWord.length() >= 3) {
                        ArrayList<Position> visited = (ArrayList<Position>) visit.clone();
                        visited.add(newPos);
                        if(wordsFound.procurar(newWord) == null) {
                            wordsFound.insere(newWord);
                            chavePalavras.add(visited);
                        }
                    }
                }
                if (dictPrefixes.procurar(newWord) != null) {
                    ArrayList<Position> visited = (ArrayList<Position>) visit.clone();
                    visited.add(newPos);
                    solve(newWord, newPos, visited, moves);
                }
            }
        }
    }

    public boolean validPos(Position p, ArrayList<Position> visitedPositions) {
        boolean notVisited = true;
        for (Position pos : visitedPositions) {
            if (pos.equals(p))
                notVisited = false;
        }
        return p.x >= 0 && p.y >= 0
            && p.x < boardSize.x && p.y < boardSize.y
            && notVisited;
    }
    //mouse (M:(2,1))–>(O:(2,0))–>(U:(1,1))–>(S:(0,0))–>(E:(0,1))
    public void printSolution(LinkedList<ArrayList<Position>> sol) {
        ArrayList<Position> wordKey;
        for (ArrayList<Position> arr : sol) {
            String word = "";
            for (Position p : arr) {
                word += boggleBoard[p.x][p.y];
            }
            System.out.print(word);
            for (Position p : arr) {
                String letter = "" + boggleBoard[p.x][p.y];
                System.out.print(" (" + letter.toUpperCase() + ":");
                System.out.print(p + ") ->");
            }
            System.out.print("\b\b\b     ");
            System.out.println();
        }
    }

}
