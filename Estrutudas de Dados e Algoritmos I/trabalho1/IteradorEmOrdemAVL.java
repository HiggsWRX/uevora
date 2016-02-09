package eda1.indice;

import eda1.indice.AVL.NoAVL;

class IteradorEmOrdemAVL<E> implements java.util.Iterator<E> {

    private NoAVL<E> atual;
    private Stack<NoAVL<E>> choice_points;

    public IteradorEmOrdemAVL(NoAVL<E> x) {
        atual = x;
        choice_points = new Stack<>();
    }

    @Override
    public boolean hasNext() {
        return (!choice_points.empty() || atual != null);
    }

    @Override
    public E next() {
        if (!hasNext()) {
            throw new java.util.NoSuchElementException();
        }

        while (atual != null) {
            choice_points.push(atual);
            atual = atual.getLeftNode();
        }
        atual = choice_points.pop();

        E toReturn = atual.getElement();
        atual = atual.getRightNode();

        return toReturn;
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }

}