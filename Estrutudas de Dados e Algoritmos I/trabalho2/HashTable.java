@SuppressWarnings({"unchecked","rawtypes"})
public abstract class HashTable<T> {
    Elemento<T> table[];
    int ocupados = 0;

    public HashTable() {
    }

    public HashTable(int n) {
        table = new Elemento[n];
    }

    public int ocupados() {
        return ocupados;
    }

    public float factorCarga() {
        return ocupados / (float) table.length;
    }

    protected abstract int procPos(T s);

    public void alocarTabela(int dim) {
        table = new Elemento[dim];
        ocupados = 0;
    }

    public void tornarVazia() {
        alocarTabela(table.length);
    }

    public T procurar (T t) {
        int possiblePlace = procPos(t);
        if (table[possiblePlace] != null) {
            if (table[possiblePlace].elem.equals(t))
                return table[possiblePlace].elem;
        }
        return null;

        // for (int i = 0; i < table.length; i++) {
        //     if (table[i] != null) {
        //         if (table[i].elem.equals(t))
        //             return table[i].elem;
        //     }
        // }
        // return null;
    }

    public void remove(T t) {
        for (int i = 0; i < table.length; i++) {
            if (table[i] != null) {
                if (table[i].elem.equals(t)) table[i].delete();
                ocupados--;
            }
        }
    }

    public void insere(T t) {
        int insertPos = procPos(t);
        if(table[insertPos] == null || table[insertPos].del == true) {

            table[insertPos] = new Elemento<T>(t);
            ocupados++;
        }
        if (factorCarga() > 0.5) {
            rehash();
        }
    }

    public void rehash() {
        Elemento<T> tempTable[] = table;
        alocarTabela(procPrimo(table.length * 2));
        for (int i = 0; i < tempTable.length; i++) {
            if (tempTable[i] != null) {
                if (tempTable[i].del == false) {
                    insere(tempTable[i].elem);
                }
            }
        }
    }

    public static int procPrimo(int n) {
        boolean found = false;
        while(!found) {
            if (isPrime(n))
                found = true;
            else
                n++;
        }
        return n;
    }

    public int procPrimoAnterior(int n) {
        boolean found = false;
        while(!found) {
            if (isPrime(n))
                found = true;
            else
                n--;
        }
        return n;
    }

    static boolean isPrime(long n) {
        if(n < 2) return false;
        if(n == 2 || n == 3) return true;
        if(n%2 == 0 || n%3 == 0) return false;
        long sqrtN = (long)Math.sqrt(n)+1;
        for(long i = 6L; i <= sqrtN; i += 6) {
            if(n%(i-1) == 0 || n%(i+1) == 0) return false;
        }
        return true;
    }

    public void print() {
        for (int i = 0; i < table.length; i++) {
            if (table[i] != null) {
                if (table[i].del == false) {
                    System.out.println(table[i]);
                }
            }
        }
    }

    public void debugPrint() {
        for (int i = 0; i < table.length; i++) {
            if(table[i] != null) {
                if (table[i].del == true) {
                    System.out.println("[" + table[i] + "] - deleted");
                } else {
                    System.out.println("[" + table[i] + "]");
                }
            } else {
                System.out.println("[ ]");
            }
        }
    }

}
