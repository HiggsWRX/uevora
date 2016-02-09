package eda1.indice;

import java.util.Iterator;

public class AVL<E extends Comparable<? super E>> extends ABP<E> {

    static class NoAVL<E> extends NoABP<E> {
        private int height;

        public NoAVL(E e) {
            super(e);
            height = 0;
        }

        public void updateHeight(int i) {
            height = i;
        }

        public int getHeight() {
            return height;
        }

        @Override
        public NoAVL<E> getLeftNode() {
            return (NoAVL<E>) super.getLeftNode();
        }

        @Override
        public NoAVL<E> getRightNode() {
            return (NoAVL<E>) super.getRightNode();
        }

    }

    private NoAVL<E> raiz;

    public AVL() {}

    public AVL(E e) {
        raiz = new NoAVL<>(e);
    }

    @Override
    public E findMin() {
        if (isEmpty())
            return null;

        return findMin(raiz);
    }

    public E findMin(NoAVL<E> n) {
        if (n.getLeftNode() == null)
            return n.getElement();
        else
            return findMin(n.getLeftNode());
    }

    @Override
    public boolean contains(E x) {
        return contains(x, raiz);
    }

    public boolean contains(E x, NoAVL<E> n) {
        if (n == null)
            return false;
        else if (n.getElement().compareTo(x) == 0)
            return true;
        else if (n.getElement().compareTo(x) < 0)
            return contains(x, n.getRightNode());
        else
            return contains(x, n.getLeftNode());
    }

    @Override
    public E findMax() {
        if (isEmpty())
            return null;

        return findMax(raiz);
    }

    public E findMax(NoAVL<E> n) {
        if (n.getRightNode() == null)
            return n.getElement();
        else
            return findMax(n.getRightNode());
    }

    @Override
    public void remove(E x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void insert(E x) {
        raiz = insert(x, raiz);
    }

    public NoAVL<E> insert(E x, NoAVL<E> n) {
        if (n == null)
            n = new NoAVL<>(x);
        else if (n.getElement().compareTo(x) > 0)
            n.setLeftNode(insert(x, n.getLeftNode()));
        if (height(n.getLeftNode()) - height(n.getRightNode()) == 2) {
            if (x.compareTo(n.getLeftNode().getElement()) < 0) {
                n = rodaEsq(n);
            } else {
                n = rodaDirEsq(n);
            }
        } else if (n.getElement().compareTo(x) < 0)
            n.setRightNode(insert(x, n.getRightNode()));
        if (height(n.getRightNode()) - height(n.getLeftNode()) == 2) {
            if (x.compareTo(n.getRightNode().getElement()) > 0) {
                n = rodaDir(n);
            } else {
                n = rodaEsqDir(n);
            }
        }

        n.updateHeight(max(height(n.getLeftNode()), height(n.getRightNode())) + 1);
        return n;
    }

    private static NoAVL rodaEsq(NoAVL c2) {
        NoAVL c1 = c2.getLeftNode();
        c2.setLeftNode(c1.getRightNode());
        c1.setRightNode(c2);
        c2.updateHeight(max(height(c2.getLeftNode()), height(c2.getRightNode())) + 1);
        c1.updateHeight(max(height(c1.getLeftNode()), c2.getHeight()) + 1);

        return c1;
    }

    private static NoAVL rodaDir(NoAVL c1) {
        NoAVL c2 = c1.getRightNode();
        c1.setRightNode(c2.getLeftNode());
        c2.setLeftNode(c1);
        c1.updateHeight(max(height(c1.getLeftNode()), height(c1.getRightNode())) + 1);
        c2.updateHeight(max(height(c2.getRightNode()), c1.getHeight()) + 1);

        return c2;
    }

    private static NoAVL rodaDirEsq(NoAVL c3) {
        c3.setLeftNode(rodaDir(c3.getLeftNode()));
        return rodaEsq(c3);
    }

    private static NoAVL rodaEsqDir(NoAVL c1) {
        c1.setRightNode(rodaEsq(c1.getRightNode()));
        return rodaDir(c1);
    }

    public static int height(NoAVL n) {
        return n == null ? -1 : n.getHeight();
    }

    public static int max(int lh, int rh) {
        return lh > rh ? lh : rh;
    }

    @Override
    public Iterator<E> iterator() {
        return new IteradorPreOrdemAVL<>(raiz);
    }

    @Override
    public Iterator<E> inOrderIterator() {
        return new IteradorEmOrdemAVL<>(raiz);
    }

    public StringBuilder toString(NoAVL<E> n, StringBuilder prefix, boolean isTail, StringBuilder sb) {
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
