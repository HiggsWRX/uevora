package eda1.indice;

public class NoABP<E> {
    private E element;
    private NoABP<E> leftNode;
    private NoABP<E> rightNode;

    public NoABP(E e) {
        element = e;
        leftNode = null;
        rightNode = null;
    }

    public E getElement() {
        return element;
    }

    void setElement(E e) {
        element = e;
    }

    public NoABP<E> getLeftNode() {
        return leftNode;
    }

    void setLeftNode(NoABP<E> n) {
        leftNode = n;
    }

    public NoABP<E> getRightNode() {
        return rightNode;
    }

    void setRightNode(NoABP<E> n) {
        rightNode = n;
    }

    @Override
    public String toString() {
        return element.toString();
    }
}