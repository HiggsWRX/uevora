import java.util.Scanner;

public class QQSM {

    private Player player;
    private boolean lost = false;
    private boolean won = false;
    private boolean surr = false;

    public void newPlayer() {
        System.out.printf("Introduza o nome do novo concorrente:  \b");

        Scanner sc = new Scanner(System.in);
        player = new Player(sc.nextLine());

        System.out.printf("Bem-vindo %s! \n \n", player.getName());
        System.out.println("Pode desistir a qualquer momento, para isso " +
                           "basta escrever a palavra 'desisto'.\n" +
                           "Para responder às perguntas basta usar a " +
                           "letra referente à resposta certa. \n" +
                           "\nVamos começar!\n");
    }

    public void run(String file) {
        QLibrary lib = new QLibrary(file);

        while (!lost) {
            Questao_QQSM quest = lib.getQuest(player.getLevel());
            System.out.println(quest);

            System.out.printf("R:  \b");
            Scanner sc = new Scanner(System.in);
            String temp = sc.next();
            temp = temp.toLowerCase();

            if (temp.equals("desisto")) {
                surr = true;
                break;
            }
            char choice = temp.charAt(0);
            choice = Character.toUpperCase(choice);
            if (choice == quest.getAnswer()) {
                player.correctAnswer();
                System.out.printf("\nCorreto!\nO seu prémio actual é de ");
                System.out.println(player.getPrize() + "€\n");
            } else {
                lost = true;
            }

            if (player.getCorrect() == 15) {
                won = true;
                break;
            }
        }

        if (surr) {
            System.out.printf("Desistiu. Ganhou %d€ \n", player.getPrize());
        }

        if (won) {
            System.out.println("Parabéns! Ganhou o prémio máximo, 250.000€!");
        }

        if (lost) {
            System.out.printf("Oh, perdeu! Ganhou %d€ \n", player.lost());
        }
    }

    public static void main(String[] args) {
        QQSM mainGame = new QQSM();
        mainGame.newPlayer();
        mainGame.run(args[0]);
    }
}
