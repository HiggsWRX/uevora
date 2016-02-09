public class Elemento<T> {
    boolean del;
    T elem;

    public Elemento(T t) {
        del = false;
        elem = t;
    }

    public void delete() {
        del = true;
    }

    public String toString() {
        return elem.toString();
    }
}