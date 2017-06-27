package sgespacos;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Properties;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;

public class SGEspacosImpl extends UnicastRemoteObject implements SGEspacos, java.io.Serializable {

    private String dbhost;
    private String dbname;
    private String dbuser;
    private String dbpasswd;

    public SGEspacosImpl() throws RemoteException {
        super();
        Properties prop = new Properties();
        InputStream input = null;

        try {

            input = new FileInputStream("config.properties");
            prop.load(input);

            this.dbhost = prop.getProperty("dbhost");
            this.dbname = prop.getProperty("dbname");
            this.dbuser = prop.getProperty("dbuser");
            this.dbpasswd = prop.getProperty("dbpassword");

        } catch (IOException ex) {
            ex.printStackTrace();
        } finally {
            if (input != null) {
                try {
                    input.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

    }

    public Vector<String> listarEspacos() throws RemoteException {
        PostgresConnector pc = new PostgresConnector(dbhost, dbname, dbuser, dbpasswd);

        try {
            pc.connect();
        } catch (Exception ex) {
            Logger.getLogger(SGEspacosImpl.class.getName()).log(Level.SEVERE, null, ex);
        }
        Statement stmt = pc.getStatement();
        Vector<String> ret = new Vector<>();

        try {
            ResultSet rs = stmt.executeQuery("SELECT nome_espaco,abertura_espaco,fecho_espaco,custo from espacos");

            while (rs.next()) {
                ret.add(rs.getString("nome_espaco"));
                ret.add(rs.getTime("abertura_espaco").toString());
                ret.add(rs.getTime("fecho_espaco").toString());
                ret.add(String.valueOf(rs.getInt("custo")));
            }
            rs.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        pc.disconnect();

        return ret;
    }

    public boolean verificarEspaco(String codEsp, String data) throws RemoteException {
        boolean isAvailable = false;
        PostgresConnector pc = new PostgresConnector(dbhost, dbname, dbuser, dbpasswd);

        try {
            pc.connect();
        } catch (Exception ex) {
            Logger.getLogger(SGEspacosImpl.class.getName()).log(Level.SEVERE, null, ex);
        }
        Statement stmt = pc.getStatement();
        String query = String.format("SELECT COUNT(*) FROM reservas WHERE cod_espaco = '%s' AND '%s' BETWEEN inicio_reserva AND fim_reserva;", codEsp, data);

        try {
            ResultSet rs = stmt.executeQuery(query);
            rs.next();
            if (rs.getInt("count") == 0) {
                isAvailable = true;
            }
            rs.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        pc.disconnect();

        return isAvailable;
    }

    public boolean reservarEspaco(String nome, String tlf, float custo, int numPessoas, String codEsp, String data1, String data2) throws RemoteException {
        PostgresConnector pc = new PostgresConnector(dbhost, dbname, dbuser, dbpasswd);
        boolean reservado = false;
        try {
            pc.connect();
        } catch (Exception ex) {
            Logger.getLogger(SGEspacosImpl.class.getName()).log(Level.SEVERE, null, ex);
        }
        Statement stmt = pc.getStatement();

        try {
            if (verificarEspaco2(codEsp, data1, data2)) {
                String query = String.format("INSERT INTO reservas VALUES (DEFAULT,'%s','%s','%f','%d','%s','%s','%s');", nome, tlf, custo, numPessoas, codEsp, data1, data2);
                ResultSet rs = stmt.executeQuery(query);
                rs.close();
                reservado = true;
            }

        } catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        pc.disconnect();

        return reservado;

    }

    public Vector<String> listarReservas(String codEsp) throws RemoteException {
        PostgresConnector pc = new PostgresConnector(dbhost, dbname, dbuser, dbpasswd);

        try {
            pc.connect();
        } catch (Exception ex) {
            Logger.getLogger(SGEspacosImpl.class.getName()).log(Level.SEVERE, null, ex);
        }
        Statement stmt = pc.getStatement();
        String query = String.format("SELECT * FROM reservas WHERE cod_espaco = '%s'", codEsp);
        Vector<String> ret = new Vector<>();

        try {
            ResultSet rs = stmt.executeQuery(query);

            while (rs.next()) {
                ret.add(String.valueOf(rs.getInt("cod_reserva")));
                ret.add(rs.getString("nome_resp"));
                ret.add(rs.getString("tlf_resp"));
                ret.add(String.valueOf(rs.getInt("custo_reserva")));
                ret.add(String.valueOf(rs.getInt("num_users")));
                ret.add(rs.getString("cod_espaco"));
                ret.add(rs.getTimestamp("inicio_reserva").toString());
                ret.add(rs.getTimestamp("fim_reserva").toString());
            }
            rs.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        pc.disconnect();

        return ret;
    }

    public boolean verificarEspaco2(String codEsp, String data1, String data2) {
        boolean isAvailable = false;
        PostgresConnector pc = new PostgresConnector(dbhost, dbname, dbuser, dbpasswd);

        try {
            pc.connect();
        } catch (Exception ex) {
            Logger.getLogger(SGEspacosImpl.class.getName()).log(Level.SEVERE, null, ex);
        }
        Statement stmt = pc.getStatement();
        String query = String.format("SELECT COUNT(*) FROM reservas WHERE cod_espaco = '%s' AND (inicio_reserva, fim_reserva) OVERLAPS ('%s', '%s');", codEsp, data1, data2);

        try {
            ResultSet rs = stmt.executeQuery(query);
            rs.next();
            if (rs.getInt("count") == 0) {
                isAvailable = true;
            }
            rs.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        pc.disconnect();

        return isAvailable;
    }

}
