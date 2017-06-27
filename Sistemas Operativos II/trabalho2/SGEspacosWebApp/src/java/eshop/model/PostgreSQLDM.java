package eshop.model;

import eshop.beans.Espaco;
import eshop.beans.Reserva;
import java.sql.*;
import java.util.Vector;

/**
 * @author roses-are-red
 */
public class PostgreSQLDM implements BusinessLogic {

    Connection connection;

    public PostgreSQLDM(String dbURL, String dbName, String dbUser, String dbPassword) {
        try {
            Class.forName("org.postgresql.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace(System.out);
        }
        try {
            connection = DriverManager.getConnection("jdbc:postgresql://" + dbURL + ":5432/" + dbName,
                    dbUser,
                    dbPassword);
        } catch (SQLException e) {
            e.printStackTrace(System.out);
            System.err.println("Problems setting the connection");
        }
    }

    public Vector<Espaco> getSpaceList() {
        Vector<Espaco> spaces = new Vector<Espaco>();

        if (connection != null) {
            try {
                Statement s = connection.createStatement();
                String sql = "SELECT nome_espaco, abertura_espaco, fecho_espaco, custo from espacos";
                try {
                    ResultSet rs = s.executeQuery(sql);
                    try {
                        while (rs.next()) {
                            spaces.add(new Espaco(rs.getString("nome_espaco"),
                                    rs.getTime("abertura_espaco").toString(),
                                    rs.getTime("fecho_espaco").toString(),
                                    rs.getInt("custo")));
                        }
                    } finally {
                        rs.close();
                    }
                } finally {
                    s.close();
                }
            } catch (SQLException e) {
                System.out.println("Could not get spaces: " + e.getMessage());
            }
        }

        return spaces;
    }

    public Vector<Reserva> getReservationList(String codEsp) {
        Vector<Reserva> reservations = new Vector<Reserva>();

        if (connection != null) {
            try {
                Statement s = connection.createStatement();
                String sql = String.format("SELECT * FROM reservas WHERE cod_espaco = '%s'", codEsp);
                try {
                    ResultSet rs = s.executeQuery(sql);
                    try {
                        while (rs.next()) {
                            reservations.add(new Reserva(rs.getInt("cod_reserva"),
                                    rs.getString("nome_resp"),
                                    rs.getString("tlf_resp"),
                                    rs.getInt("custo_reserva"),
                                    rs.getInt("num_users"),
                                    rs.getString("cod_espaco"),
                                    rs.getTimestamp("inicio_reserva").toString(),
                                    rs.getTimestamp("fim_reserva").toString()));
                        }
                    } finally {
                        rs.close();
                    }
                } finally {
                    s.close();
                }
            } catch (SQLException e) {
                System.out.println("Could not get reservations: " + e.getMessage());
            }
        }

        return reservations;
    }

    public boolean verifySpace(String codEsp, String data) {
        boolean isAvailable = false;
        
        String time = data.split(" ")[1];
        
        if (!spaceIsOpen(codEsp, time)) {
            return isAvailable;
        }

        if (connection != null) {
            try {
                Statement s = connection.createStatement();
                String sql = String.format("SELECT COUNT(*) FROM reservas WHERE cod_espaco = '%s' "
                        + "AND '%s' >= inicio_reserva AND '%s' < fim_reserva;", codEsp, data, data);
                try {
                    ResultSet rs = s.executeQuery(sql);
                    try {
                        rs.next();
                        if (rs.getInt("count") == 0) {
                            isAvailable = true;
                        }
                    } finally {
                        rs.close();
                    }
                } finally {
                    s.close();
                }
            } catch (SQLException e) {
                System.out.println("Could not get availability: " + e.getMessage());
            }
        }

        return isAvailable;
    }

    public boolean verifySpace(String codEsp, String data1, String data2) {
        boolean isAvailable = false;
        String time1 = data1.split(" ")[1];
        String time2 = data2.split(" ")[1];
        
        if (!spaceIsOpen(codEsp, time1, time2)) {
            return isAvailable;
        }

        if (connection != null) {
            try {
                Statement s = connection.createStatement();
                String sql = String.format("SELECT COUNT(*) FROM reservas WHERE cod_espaco = '%s' "
                        + "AND (inicio_reserva, fim_reserva) OVERLAPS ('%s', '%s');", codEsp, data1, data2);
                try {
                    ResultSet rs = s.executeQuery(sql);
                    try {
                        rs.next();
                        if (rs.getInt("count") == 0) {
                            isAvailable = true;
                        }
                    } finally {
                        rs.close();
                    }
                } finally {
                    s.close();
                }
            } catch (SQLException e) {
                System.out.println("Could not get availability: " + e.getMessage());
            }
        }

        return isAvailable;
    }

    public boolean spaceIsOpen(String codEsp, String time) {
        boolean isOpen = false;

        if (connection != null) {
            try {
                Statement s = connection.createStatement();
                String sql = String.format("SELECT count(*) FROM espacos WHERE cod_espaco = '%s' AND '%s' BETWEEN abertura_espaco AND fecho_espaco;", codEsp, time);
                try {
                    ResultSet rs = s.executeQuery(sql);
                    try {
                        rs.next();
                        if (rs.getInt("count") != 0) {
                            isOpen = true;
                        }
                    } finally {
                        rs.close();
                    }
                } finally {
                    s.close();
                }
            } catch (Exception e) {
            }
        }

        return isOpen;
    }
    
    public boolean spaceIsOpen(String codEsp, String time1, String time2) {
        boolean isOpen = false;

        if (connection != null) {
            try {
                Statement s = connection.createStatement();
                String sql = String.format("SELECT count(*) FROM espacos WHERE cod_espaco = '%s' AND '%s' BETWEEN abertura_espaco AND fecho_espaco AND '%s' BETWEEN abertura_espaco AND fecho_espaco;", codEsp, time1, time2);
                try {
                    ResultSet rs = s.executeQuery(sql);
                    try {
                        rs.next();
                        if (rs.getInt("count") != 0) {
                            isOpen = true;
                        }
                    } finally {
                        rs.close();
                    }
                } finally {
                    s.close();
                }
            } catch (Exception e) {
            }
        }

        return isOpen;
    }

    public int makeReservation(String nome, String tlf, int custo,
            int numPessoas, String codEsp, String data1, String data2) {
        int codReserva = -1;

        if (connection != null) {
            try {
                if (verifySpace(codEsp, data1, data2)) {
                    Statement s = connection.createStatement();
                    String sql = String.format("INSERT INTO reservas VALUES (DEFAULT,'%s','%s','%d','%d','%s','%s','%s');",
                            nome, tlf, custo, numPessoas, codEsp, data1, data2);
                    try {
                        ResultSet rs = s.executeQuery(sql);
                        rs.close();
                    } finally {
                        s.close();
                    }
                }
            } catch (SQLException e) {
                System.out.println("Could not get data from db: " + e.getMessage());
            }
        }

        if (connection != null) {
            try {
                Statement s2 = connection.createStatement();
                String sql2 = String.format("SELECT cod_reserva FROM reservas WHERE cod_espaco = '%s' AND inicio_reserva = '%s' AND fim_reserva = '%s';",
                        codEsp, data1, data2);
                try {
                    ResultSet rs2 = s2.executeQuery(sql2);
                    rs2.next();
                    codReserva = rs2.getInt("cod_reserva");
                    rs2.close();
                } finally {
                    s2.close();
                }
            } catch (SQLException e) {
                System.out.println("Could not get data from db: " + e.getMessage());
            }
        }

        return codReserva;
    }

    @Override
    public int getCost(String codEsp) {
        int custo = -1;
        if (connection != null) {
            try {
                Statement s = connection.createStatement();
                String sql = String.format("SELECT custo FROM espacos WHERE cod_espaco = '%s';", codEsp);
                try {
                    ResultSet rs = s.executeQuery(sql);
                    try {
                        rs.next();
                        custo = rs.getInt("custo");
                    } finally {
                        rs.close();
                    }
                } finally {
                    s.close();
                }
            } catch (SQLException e) {
                System.out.println("Could not get cost: " + e.getMessage());
            }
        }

        return custo;
    }

    @Override
    public void finish() {
        if (connection != null) {
            try {
                connection.close();
            } catch (SQLException e) {
            }
        }
    }
}
