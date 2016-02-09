package eda1.indice;

import java.util.Arrays;

public class Stack<E> {

    private int size = 0;
    private static final int CAPACITY = 10;
    private Object elements[];

    public Stack() {
        elements = new Object[CAPACITY];
    }

    public void push(E o) {
        if (size == elements.length) {
            ensureCapacity();
        }
        elements[size++] = o;
    }

    public E top() {
        if (size == 0) {
            return null;
        }

        return (E) elements[size - 1];
    }

    public E pop() {
        if (size == 0) {
            return null;
        }

        E o = (E) elements[--size];
        elements[size] = null;
        return o;
    }

    public int size() {
        return size;
    }

    public void replace(E x, E y) {
        Stack<E> aux = new Stack<>();

        for (int i = 0; i < this.size(); i++) {
            if (this.top() == x) {
                this.pop();
                this.push(y);
            } else {
                aux.push(this.pop());
            }
        }

        for (int i = 0; i < aux.size(); i++) {
            this.push(aux.pop());
        }
    }

    public boolean empty() {
        if (this.top() == null) {
            return true;
        } else {
            return false;
        }
    }

    private void ensureCapacity() {
        int newSize = elements.length * 2;
        elements = Arrays.copyOf(elements, newSize);
    }

    public String toString() {
        String temp = "[";
        for (int i = 0; i < this.size; i++) {
            if (i == this.size - 1) {
                temp += String.valueOf(elements[i]);
            } else {
                temp += String.valueOf(elements[i]) + ", ";
            }
        }

        return temp + "]";
    }
}