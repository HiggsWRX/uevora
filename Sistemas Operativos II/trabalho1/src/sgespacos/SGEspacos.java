package sgespacos;

import java.util.Vector;

public interface SGEspacos extends java.rmi.Remote {

    public Vector<String> listarEspacos() throws java.rmi.RemoteException;

    public boolean verificarEspaco(String codEsp, String data) throws java.rmi.RemoteException;
    
    public boolean reservarEspaco(String nome, String tlf, float custo, int numPessoas, String codEsp, String data1, String data2) throws java.rmi.RemoteException;
    
    public Vector<String> listarReservas(String codEsp) throws java.rmi.RemoteException;
    
    public boolean verificarEspaco2(String codEsp, String data1, String data2) throws java.rmi.RemoteException;

}
