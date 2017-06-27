package eshop.beans;

import java.io.Serializable;

public class Espaco implements Serializable {

    private String name;
    private String openT;
    private String closeT;
    private int cost;

    public Espaco(String name, String openT, String closeT, int cost) {
        this.name = name;
        this.openT = openT;
        this.closeT = closeT;
        this.cost = cost;
    }

    public String getName() {
        return name;
    }

    public String getOpenT() {
        return openT;
    }

    public String getCloseT() {
        return closeT;
    }

    public int getCost() {
        return cost;
    }

    @Override
    public String toString() {
        return "Espaco{" + "name=" + name + ", openT=" + openT + ", closeT=" + closeT + ", cost=" + cost + '}';
    }
}
