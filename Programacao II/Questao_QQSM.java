
class Questao_QQSM {

    private int level;
    private String question;
    private String optA;
    private String optB;
    private String optC;
    private String optD;
    private char answer;
    private boolean used = false;

    public Questao_QQSM(int lvl, String qst, String optA, String optB,
                        String optC, String optD, char answer) {
        level = lvl;
        question = qst;
        this.optA = optA;
        this.optB = optB;
        this.optC = optC;
        this.optD = optD;
        this.answer = answer;
    }

    public boolean used() {
        return used;
    }

    public void use() {
        used = true;
    }

    public int getLvl() {
        return level;
    }

    public char getAnswer() {
        return answer;
    }

    @Override
    public String toString() {
        return question + optA + optB + optC + optD;
    }
}
