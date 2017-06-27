package eshop.beans;

import java.io.Serializable;

public class Reserva implements Serializable {

    private int resCode;
    private String resName;
    private String resTlf;
    private int resCost;
    private int resNumUsers;
    private String resSpaceCode;
    private String resStartT;
    private String resEndT;

    public Reserva(int resCode, String resName, String resTlf, int resCost, int resNumUsers, String resSpaceCode, String resStartT, String resEndT) {
        this.resCode = resCode;
        this.resName = resName;
        this.resTlf = resTlf;
        this.resCost = resCost;
        this.resNumUsers = resNumUsers;
        this.resSpaceCode = resSpaceCode;
        this.resStartT = resStartT;
        this.resEndT = resEndT;
    }

    public int getResCode() {
        return resCode;
    }

    public String getResName() {
        return resName;
    }

    public String getResTlf() {
        return resTlf;
    }

    public int getResCost() {
        return resCost;
    }

    public int getResNumUsers() {
        return resNumUsers;
    }

    public String getResSpaceCode() {
        return resSpaceCode;
    }

    public String getResStartT() {
        return resStartT;
    }

    public String getResEndT() {
        return resEndT;
    }

    @Override
    public String toString() {
        return "Reserva{" + "resCode=" + resCode + ", resName=" + resName + ", resTlf=" + resTlf + ", resCost=" + resCost + ", resNumUsers=" + resNumUsers + ", resSpaceCode=" + resSpaceCode + ", resStartT=" + resStartT + ", resEndT=" + resEndT + '}';
    }
}
