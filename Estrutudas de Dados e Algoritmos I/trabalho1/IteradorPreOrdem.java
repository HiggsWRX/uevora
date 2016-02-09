package eda1.indice;

class IteradorPreOrdem<E> implements java.util.Iterator<E> {

    private NoABP<E> atual;
    private Stack<NoABP<E>> choice_points;

    public IteradorPreOrdem(NoABP<E> x) {
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
    public NoABP<E> nextNode() {
        if (!hasNext()) {
            throw new java.util.NoSuchElementException();
        }

        NoABP<E> toReturn = atual;

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