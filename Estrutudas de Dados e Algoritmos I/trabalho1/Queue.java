package eda1.indice;

public class Queue<E> {

    LinkedList<E> queue;

    public Queue() {
        queue = new LinkedList<>();
    }

    public void enqueue(E e) {
        queue.add(e);
    }

    public E dequeue() {
        return queue.get(0);
    }

    public E front() {
        return queue.get(0);
    }

    public int size() {
        return queue.size();
    }

    public boolean empty() {
        return queue.isEmpty();
    }

    public String toString() {
        return queue.toString();
    }
}
