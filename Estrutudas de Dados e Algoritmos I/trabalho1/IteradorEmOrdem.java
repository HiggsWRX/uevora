package eda1.indice;

class IteradorEmOrdem<E> implements java.util.Iterator<E> {

    private NoABP<E> atual;
    private Stack<NoABP<E>> choice_points;

    public IteradorEmOrdem(NoABP<E> x) {
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