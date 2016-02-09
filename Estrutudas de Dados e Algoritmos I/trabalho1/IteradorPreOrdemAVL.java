package eda1.indice;

import eda1.indice.AVL.NoAVL;

class IteradorPreOrdemAVL<E> implements java.util.Iterator<E> {

    private NoAVL<E> atual;
    private Stack<NoAVL<E>> choice_points;

    public IteradorPreOrdemAVL(NoAVL<E> x) {
        atual = x;
        choice_points = new Stack<>();
    }

    @Override
    public boolean hasNext() {
        return atual != null;
    }

    @Override
    public E next() {
        if (!hasNext()) {
            throw new java.util.NoSuchElementException();
        }

        E toReturn = atual.getElement();
        if (atual.getRightNode() != null) {
            choice_points.push(atual.getRightNode());
        }

        if (atual.getLeftNode() != null) {
            atual = atual.getLeftNode();
        } else {
            if (!choice_points.empty()) {
                atual = choice_points.pop();
            } else {
                atual = null;
            }
        }
        return toReturn;
    }
    /*
    public NoAVL<E> nextNode() {
        if (!hasNext()) {
            throw new java.util.NoSuchElementException();
        }

        NoAVL<E> toReturn = atual;

        if (atual.getRightNode() != null) {
            choice_points.push(atual.getRightNode());
        }

        if (atual.getLeftNode() != null) {
            atual = atual.getLeftNode();
        } else {
            if (!choice_points.empty()) {
                atual = choice_points.pop();
            } else {
                atual = null;
            }
        }
        return toReturn;
    }
    */
    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }

}