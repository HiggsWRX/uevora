package eshop.model;

import eshop.beans.Espaco;
import eshop.beans.Reserva;
import java.util.Vector;
import javax.servlet.ServletContext;

/**
 * Classe com as operações e acesso aos dados (Versão Memory-Only)
 *
 */
public class DataManager implements BusinessLogic {

    /**
     * DB connector instanciado com um dos tipos possíveis (memória, MySQL,
     * HyperSQL...)
     *
     */
    private static BusinessLogic dbManager;

    public DataManager() {
    }

    public DataManager(ServletContext context) {
        dbManager = new PostgreSQLDM(
                (String) context.getAttribute("dbURL"),
                (String) context.getAttribute("dbName"),
                (String) context.getAttribute("dbUser"),
                (String) context.getAttribute("dbPassword")
        );
    }

    @Override
    public Vector<Espaco> getSpaceList() {
        return dbManager.getSpaceList();
    }

    @Override
    public Vector<Reserva> getReservationList(String codEsp) {
        return dbManager.getReservationList(codEsp);
    }

    @Override
    public boolean verifySpace(String codEsp, String data) {
        return dbManager.verifySpace(codEsp, data);
    }

    @Override
    public boolean verifySpace(String codEsp, String data1, String data2) {
        return dbManager.verifySpace(codEsp, data1, data2);
    }
    
    @Override
    public boolean spaceIsOpen(String codEsp, String time) {
        return dbManager.spaceIsOpen(codEsp, time);
    }

    @Override
    public int makeReservation(String nome, String tlf, int custo,
            int numPessoas, String codEsp, String data1, String data2) {
        return dbManager.makeReservation(nome, tlf, custo,
                numPessoas, codEsp, data1, data2);
    }
    
    @Override
    public int getCost(String codEsp) {
        return dbManager.getCost(codEsp);
    }

    // **************
    @Override
    public void finish() {
        dbManager.finish();
    }

}
