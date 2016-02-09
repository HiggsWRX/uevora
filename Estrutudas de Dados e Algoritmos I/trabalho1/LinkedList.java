package eda1.indice;

public class LinkedList<T> implements Iterable<T> {

    SingleNode<T> header;
    SingleNode<T> lastNode;
    int size;

    public LinkedList() {
        header = new SingleNode();
        lastNode = header;
        size = 0;
    }

    public void add(T x) {
        SingleNode<T> newNode = new SingleNode<>(x);

        if (header == lastNode)
            header.setNext(newNode);
        else
            lastNode.setNext(newNode);

        lastNode = newNode;
        size++;
    }

    public void add(int i, T x) {
        SingleNode<T> tempNode = new SingleNode<>(x);
        SingleNode<T> currentNode = header;
        for (int j = 0; j < i && currentNode.getNext() != null; j++) {
            currentNode = currentNode.getNext();
        }
        tempNode.setNext(currentNode.getNext());
        currentNode.setNext(tempNode);
        size++;
    }

    public void remove(int i) {
        SingleNode<T> behindNode;
        if (i == 0)
            behindNode = header;
        else
            behindNode = header.getNext();

        for (int j = 0; j < i - 1 && behindNode.getNext() != null; j++) {
            behindNode = behindNode.getNext();
        }

        SingleNode<T> removedNode = behindNode.getNext();
        behindNode.setNext(removedNode.getNext());
        size--;
    }

    public void remove(T x) {
        SingleNode<T> findNode = header;
        SingleNode<T> tokenNode = new SingleNode<>(x);

        for (int i = 0; i < this.size; i++) {
            if (tokenNode.element() == findNode.getNext().element())
                break;
            else
                findNode = findNode.getNext();
        }
        tokenNode.setNext(findNode.getNext());
        tokenNode = tokenNode.getNext();
        findNode.setNext(tokenNode.getNext());
        size--;
    }

    public T get(int i) {
        SingleNode<T> returnNode;
        returnNode = header.getNext();

        for (int j = 0; j < i && returnNode.getNext() != null; j++) {
            returnNode = returnNode.getNext();
        }

        return returnNode.element();
    }

    public void set(int i, T y) {
        SingleNode<T> newNode = new SingleNode<>(y);
        SingleNode<T> currentNode = header.getNext();

        for (int j = 0; j < i && currentNode.getNext() != null; j++) {
            currentNode = currentNode.getNext();
        }

        currentNode.setElement(y);
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public java.util.Iterator<T> iterator() {
        return new LinkedListIterator(header.getNext());
    }

    public String toString() {
        String r = "[";
        for (T x : this) {
            r += x + "][";
        }
        return r += "\b";
    }
}
