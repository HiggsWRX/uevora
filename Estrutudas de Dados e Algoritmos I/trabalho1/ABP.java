package eda1.indice;

import java.util.Iterator;

public class ABP<E extends Comparable<? super E>> implements Iterable<E> {
    private NoABP<E> raiz;

    public ABP() {}

    public ABP(E e) {
        raiz = new NoABP<>(e);
    }

    public void insert(E x) {
        raiz = insert(x, raiz);
    }

    public NoABP<E> insert(E x, NoABP<E> n) {
        if (n == null)
            n = new NoABP<>(x);
        else if (n.getElement().compareTo(x) > 0)
            n.setLeftNode(insert(x, n.getLeftNode()));
        else if (n.getElement().compareTo(x) < 0)
            n.setRightNode(insert(x, n.getRightNode()));

        return n;
    }

    public E findMin() {
        if (isEmpty())
            return null;

        return findMin(raiz);
    }

    public E findMin(NoABP<E> n) {
        if (n.getLeftNode() == null)
            return n.getElement();
        else
            return findMin(n.getLeftNode());
    }

    public E findMax() {
        if (isEmpty())
            return null;

        return findMax(raiz);
    }

    public E findMax(NoABP<E> n) {
        if (n.getRightNode() == null)
            return n.getElement();
        else
            return findMax(n.getRightNode());
    }

    public boolean isEmpty() {
        return raiz == null;
    }

    public boolean contains(E x) {
        return contains(x, raiz);
    }

    public boolean contains(E x, NoABP<E> n) {
        if (n == null)
            return false;
        else if (n.getElement().compareTo(x) == 0)
            return true;
        else if (n.getElement().compareTo(x) < 0)
            return contains(x, n.getRightNode());
        else
            return contains(x, n.getLeftNode());
    }

    public void remove(E x) {
        raiz = remove(x, raiz);
    }

    public NoABP<E> remove(E x, NoABP<E> n) {
        if (n == null)
            return n;

        if (n.getElement().compareTo(x) < 0)
            n.setRightNode(remove(x, n.getRightNode()));
        else if (n.getElement().compareTo(x) > 0)
            n.setLeftNode(remove(x, n.getLeftNode()));
        else if (n.getLeftNode() != null && n.getRightNode() != null) {
            E min = findMin(n.getRightNode());
            n.setElement(min);
            n.setRightNode(remove(min, n.getRightNode()));
        } else if (n.getRightNode() == null)
            n = n.getLeftNode();
        else if (n.getLeftNode() == null)
            n = n.getRightNode();
        else
            n = null;

        return n;
    }

    @Override
    public Iterator<E> iterator() {
        return new IteradorPreOrdem<>(raiz);
    }

    public Iterator<E> inOrderIterator() {
        return new IteradorEmOrdem<>(raiz);
    }

    public StringBuilder toString(NoABP<E> n, StringBuilder prefix, boolean isTail, StringBuilder sb) {
        if (n.getRightNode() != null)
            this.toString(n.getRightNode(), new StringBuilder().append(prefix).append(isTail ? "│   " : "    "), false, sb);

        sb.append(prefix).append(isTail ? "└── " : "┌── ").append(n.getElement().toString()).append("\n");

        if (n.getLeftNode() != null)
            this.toString(n.getLeftNode(), new StringBuilder().append(prefix).append(isTail ? "    " : "│   "), true, sb);

        return sb;
    }

    @Override
    public String toString() {
        if (raiz != null)
            return this.toString(raiz, new StringBuilder(), true, new StringBuilder()).toString();
        else
            return "Empty tree";
    }

}
