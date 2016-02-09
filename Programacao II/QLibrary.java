import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;
import java.util.NoSuchElementException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Collections;

public class QLibrary {

    ArrayList <Questao_QQSM> library = new ArrayList<Questao_QQSM>();

    public QLibrary(String file) {
        try {
            Scanner sc = new Scanner(new FileReader(file));
            while (sc.hasNextLine()) {
                int templvl = Integer.parseInt(sc.nextLine());
                String tempQst = sc.nextLine() + "\n";
                String tempA = sc.nextLine() + "\n";
                String tempB = sc.nextLine() + "\n";
                String tempC = sc.nextLine() + "\n";
                String tempD = sc.nextLine() + "\n";
                String temp = sc.nextLine();
                char tempAns = temp.charAt(3);
                library.add( new Questao_QQSM(templvl, tempQst, tempA, tempB,
                                              tempC, tempD, tempAns) );
                sc.nextLine();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (NoSuchElementException e) {
            e.printStackTrace();
        }

        long seed = System.nanoTime();
        Collections.shuffle(library, new Random(seed));

    }

    public Questao_QQSM getQuest(int lvl) {
        for (Questao_QQSM q : library) {
            if (q.getLvl() == lvl) {
                if (!q.used()) {
                    q.use();
                    return q;
                }
            }
        }
        return null;
    }

}
