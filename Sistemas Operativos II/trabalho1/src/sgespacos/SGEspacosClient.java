package sgespacos;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.rmi.RemoteException;
import java.util.Vector;

public class SGEspacosClient {

    public static void main(String args[]) {
        String regHost = "localhost";
        String regPort = "9000";  // porto do binder
        String frase = "";

        if (args.length != 2) {
            System.out.println("Usage: java sgespacos.SGEspacosClient registryHost registryPort");
            System.exit(1);
        }
        regHost = args[0];
        regPort = args[1];

        try {
            SGEspacos obj
                    = (SGEspacos) java.rmi.Naming.lookup("rmi://" + regHost + ":"
                            + regPort + "/sgespacos");

            // invocacao de metodos remotos
            while (true) {
                menu(obj);
            }

        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public static void handleOption1(SGEspacos obj) throws RemoteException {
        Vector<String> v = obj.listarEspacos();
        for (String string : v) {
            System.out.println(string);
        }
    }

    public static void handleOption2(SGEspacos obj) throws RemoteException, IOException {
        System.out.println("Espacos Disponiveis\n"
                + "1 - Campo de Futsal\n"
                + "2 - Campo de Tenis\n"
                + "3 - Campo de Padel\n"
                + "4 - Sair");

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int choice = Integer.parseInt(br.readLine());
        while (choice < 1 && choice > 4) {
            System.out.println("Invalid choice, try again");
            choice = Integer.parseInt(br.readLine());
        }

        String cod = "";
        switch (choice) {
            case 1:
                cod = "FUT01";
                break;
            case 2:
                cod = "TEN01";
                break;
            case 3:
                cod = "PAD01";
                break;
            case 4:
                return;
            default:
                return;
        }

        System.out.println("Insira data no formato AAAA-MM-DD HH:MM:SS\n");
        String data = br.readLine();

        boolean isAvailable = obj.verificarEspaco(cod, data);
        if (isAvailable) {
            System.out.println("Espaço disponivel!");
        } else {
            System.out.println("Espaço indisponivel nesta data");
        }
    }

    public static void handleOption3(SGEspacos obj) throws RemoteException, IOException {
        System.out.println("Espacos Disponiveis\n"
                + "1 - Campo de Futsal\n"
                + "2 - Campo de Tenis\n"
                + "3 - Campo de Padel\n"
                + "4 - Sair");

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int choice = Integer.parseInt(br.readLine());
        while (choice < 1 && choice > 4) {
            System.out.println("Invalid choice, try again");
            choice = Integer.parseInt(br.readLine());
        }
        String cod = "";
        float custo = 0;
        switch (choice) {
            case 1:
                cod = "FUT01";
                custo = 10;
                break;
            case 2:
                cod = "TEN01";
                custo = 15;
                break;
            case 3:
                cod = "PAD01";
                custo = 5;
                break;
            case 4:
                return;
            default:
                return;
        }

        System.out.println("Dia? formato AAAA-MM-DD");
        String dia = br.readLine();
        System.out.println("A partir de que horas? formato HH:MM:SS");
        String horainicio = br.readLine();
        System.out.println("Quantas horas quer reservar?");
        int h = Integer.parseInt(br.readLine());
        custo *= h;
        
        int temp = Integer.parseInt(horainicio.split(":")[0]);
        temp += h;
        String horafim = String.valueOf(temp) + ":00:00";

        String dataInicio = String.format("%s %s", dia, horainicio);
        String dataFim = String.format("%s %s", dia, horafim);

        System.out.println("Quantas pessoas vão usufruir do espaço?");
        int numPessoas = Integer.parseInt(br.readLine());

        System.out.println("Nome do responsavel pela reserva:");
        String nome = br.readLine();
        System.out.println("Telefone do responsavel");
        String telf = br.readLine();
        boolean reserva = obj.reservarEspaco(nome, telf, custo, numPessoas, cod, dataInicio, dataFim);
        if (reserva) {
            System.out.println("Espaço reservado com sucesso.");
        } else {
            System.out.println("Falha ao reservar. Por favor verifique a disponibilidade antes de tentar fazer a reserva!");
        }

    }

    public static void handleOption4(SGEspacos obj) throws RemoteException, IOException {
        System.out.println("Consultar reservas de:\n"
                + "1 - Campo de Futsal\n"
                + "2 - Campo de Tenis\n"
                + "3 - Campo de Padel\n"
                + "4 - Sair");

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int choice = Integer.parseInt(br.readLine());
        while (choice > 4 && choice < 1) {
            System.out.println("Invalid choice, try again.");
            choice = Integer.parseInt(br.readLine());
        }

        String cod = "";

        switch (choice) {
            case 1:
                cod = "FUT01";
                break;
            case 2:
                cod = "TEN01";
                break;
            case 3:
                cod = "PAD01";
                break;
            case 4:
                return;
            default:
                return;
        }

        Vector<String> v = obj.listarReservas(cod);
        for (String string : v) {
            System.out.println(string);
        }

    }

    private static void menu(SGEspacos obj) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int choice = 0;
        System.out.println("Sistema de Gestão de Espaços - Clube Desportivo da Praça do Giraldo\n"
                + "1 - Listar espaços e respetivo custo horário.\n"
                + "2 - Verificar disponibilidade de espaço\n"
                + "3 - Reservar espaço\n"
                + "4 - Listar reservas\n"
                + "5 - Sair");

        choice = Integer.parseInt(br.readLine());
        while (choice < 1 && choice > 5) {
            System.out.println("Invalid option, try again.\n");
            choice = Integer.parseInt(br.readLine());
        }

        switch (choice) {
            case 1:
                handleOption1(obj);
                break;
            case 2:
                handleOption2(obj);
                break;
            case 3:
                handleOption3(obj);
                break;
            case 4:
                handleOption4(obj);
                break;
            case 5:
                break;
            default:
                break;
        }
    }
}
