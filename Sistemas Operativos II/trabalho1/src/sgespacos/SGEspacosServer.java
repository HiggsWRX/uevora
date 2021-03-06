package sgespacos;

import java.rmi.RemoteException;
import java.util.Vector;

public class SGEspacosServer {

    public static void main(String args[]) {
        int regPort = 1099; // default RMIRegistry port

        if (args.length != 1) {
            System.out.println("Usage: java sgespacos.Server registryPort");
            System.exit(1);
        }

        try {
            // ATENCAO: este porto e' relativo ao binder e nao ao servidor RMI
            regPort = Integer.parseInt(args[0]);

            SGEspacos obj = new SGEspacosImpl();

            // registar este objeto no servico de nomes
            /**
             * Se quiser substituir o processo rmiregisty... pode ativar o
             * servidor de nomes neste mesmo processo (antes do bind)
             */
            java.rmi.registry.LocateRegistry.createRegistry(regPort);            
            // usar o Registry local (em execução na mesma máquina)
            // e no porto regPort
            java.rmi.registry.Registry registry = java.rmi.registry.LocateRegistry.getRegistry(regPort);

            // mas podiamos tb criar um novo, 
            // integrado nesta mesma aplicacao servidor!
            // ... e bind
            registry.rebind("sgespacos", obj);  // NOME DO SERVICO

            /*
	      OUTRO MODO, indicando o servidor onde está o serviço de nomes
	    java.rmi.Naming.rebind("rmi://"+regHost+":" +
				   regPort + "/palavras", stub);
	    
             */
            System.out.println("Bound RMI object in registry");

            System.out.println("servidor pronto");
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

}
