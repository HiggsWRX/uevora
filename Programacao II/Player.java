
public class Player {

    private String name;
    private int correct = 0;
    private int level = 1;
    private int safeLevel = 0;
    private int[] prizes = {0, 25, 50, 125, 250, 500, 750, 1500, 2500,
                            5000, 7500, 12500, 25000, 50000, 100000, 250000
                           };
    private int[] safePrizes = {0, 500, 7500};

    public Player(String name) {
        this.name = name;
    }

    public int getCorrect() {
        return correct;
    }

    public String getName() {
        return name;
    }

    public int getPrize() {
        return prizes[correct];
    }

    public int lost() {
        return safePrizes[safeLevel];
    }

    public int getLevel() {
        return level;
    }

    public int getSafeLevel() {
        return safeLevel;
    }

    public void correctAnswer() {
        correct++;
        if (correct == 5 || correct == 10) {
            safeLevel++;
            level++;
        }
    }
}
