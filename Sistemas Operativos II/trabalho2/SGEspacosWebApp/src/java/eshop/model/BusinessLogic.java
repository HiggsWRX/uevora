package eshop.model;

import eshop.beans.Espaco;
import eshop.beans.Reserva;
import java.util.Vector;

/**
 * Interface com as operações a implementar pelo gestor de acesso aos dados.
 */
public interface BusinessLogic {
    
    public abstract Vector<Espaco> getSpaceList();
    
    public abstract Vector<Reserva> getReservationList(String codEsp);
    
    public abstract boolean verifySpace(String codEsp, String data);
    
    public abstract boolean verifySpace(String codEsp, String data1, String data2);
    
    public abstract boolean spaceIsOpen(String codEsp, String time);
    
    public abstract int makeReservation(String nome, String tlf, int custo,
            int numPessoas, String codEsp, String data1, String data2);

    public abstract int getCost(String codEsp);

    public void finish();

}
