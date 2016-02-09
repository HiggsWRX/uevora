import java.lang.Math;

public class QuadHashTable<T> extends HashTable<T> {

    public QuadHashTable() {
        super();
    }

    public QuadHashTable(int n) {
        super(n);
    }

    public int procPos(T s) {
        int hash = s.hashCode();
        hash = hash % table.length;
        hash = Math.abs(hash);
        int counter = 0;

        for (int i = hash; i < table.length; i = (hash + (counter * counter)) % table.length) {
            if(table[i] == null || table[i].del == true) return i;
            else if(table[i].elem.equals(s)) return i;
            counter++;
        }

        return -1;
    }
}
