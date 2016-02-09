package eda1.indice;

public class LinkedListIterator<T> implements java.util.Iterator<T> {

    SingleNode<T> currentNode;

    public LinkedListIterator(SingleNode<T> n) {
        currentNode = n;
    }

    public boolean hasNext() {
        return currentNode != null;
    }

    public boolean hasPrevious() {
        return currentNode != null;
    }

    public T next() {
        T x = currentNode.element();
        currentNode = currentNode.getNext();
        return x;
    }

    public T previous() {
        T x = currentNode.element();
        currentNode = currentNode.getPrevious();
        return x;
    }

    public void remove() {
        throw new UnsupportedOperationException();
    }

}
