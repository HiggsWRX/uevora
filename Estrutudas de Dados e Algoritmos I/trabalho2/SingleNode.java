public class SingleNode<T> {

    private T element;
    private SingleNode<T> next;
    private SingleNode<T> previous;

    public SingleNode(T e) {
        element = e;
        next = null;
        previous = null;
    }

    public SingleNode() {
        this(null);
    }

    public SingleNode(T e, SingleNode<T> n) {
        element = e;
        next = n;
        previous = null;
    }

    public SingleNode(T e, SingleNode<T> p, SingleNode<T> n) {
        element = e;
        next = n;
        previous = p;
    }

    public T element() throws InvalidNodeException {
        if (this == null)
            throw new InvalidNodeException("Null Node");
        return element;
    }

    public void setElement(T e) {
        this.element = e;
    }

    public void setNext(SingleNode<T> n) {
        next = n;
    }

    public void setPrevious(SingleNode<T> p) {
        previous = p;
    }

    public SingleNode<T> getNext() {
        return next;
    }

    public SingleNode<T> getPrevious() {
        return previous;
    }


    public String toString() {
        return element.toString();
    }

}

@SuppressWarnings("serial")
class InvalidNodeException extends RuntimeException {
    public InvalidNodeException() {
        super();
    }

    public InvalidNodeException(String message) {
        super(message);
    }
}
