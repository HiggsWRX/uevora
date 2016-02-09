package eda1.indice;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.StringTokenizer;

public class Indice {

    public static void main(String[] args) {
        BufferedReader reader = null;

        try {
            File file = new File(args[0]);
            reader = new BufferedReader(new FileReader(file));
            AVL<Capitulo> AVLindice = new AVL<>();
            String line;

            while ((line = reader.readLine()) != null) {
                if (line.startsWith("IX:")) {
                    // Constroi uma nova string sem o 'IX:'
                    line = line.substring(3);

                    StringTokenizer st = new StringTokenizer(line, "{}");
                    String token1 = null;
                    String token2 = null;

                    while (st.hasMoreElements()) {
                        token1 = st.nextToken();
                        token2 = st.nextToken();
                    }

                    StringTokenizer nst = new StringTokenizer(token1, "!");
                    // Se countTokens for maior que 1, a linha contém um capitulo
                    // com subcapitulos, senão é apenas um capitulo
                    if (nst.countTokens() > 1) {
                        String token3 = nst.nextToken();
                        String token4 = nst.nextToken();
                        // Capitulo dummy apenas para saber se existe um igual na abp.
                        Capitulo fakeChap = new Capitulo(token3);
                        if (AVLindice.contains(fakeChap))
                            buildSubChapter(AVLindice, token3, token4, Integer.parseInt(token2));

                    } else
                        buildChapter(AVLindice, token1, Integer.parseInt(token2));
                }
            }

            printIndex(AVLindice);

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Modifica a abp recebida. Recebe um token, e adiciona os capitulos à abp
     * consoante o token recebido.
     *
     * @param abp    a abp recebida que vai ser usada para construir o indice
     * @param name   o token recebido. Contém o nome do capitulo assim como
     *               o token que indica se é inicio de subcapitulo ou não.
     * @param p      o numero da pagina
     */
    static void buildChapter(AVL<Capitulo> abp, String name, int p) {
        // Extrair o prefixo do nome (se é |(, |), ou nenhum.)
        String prefix = name.substring(name.length() - 2);
        switch (prefix) {
        case "|(":
            // Remover o prefixo do nome e criar um novo capitulo
            String nomeCap1 = name.substring(0, name.length() - 2);
            abp.insert(new Capitulo(nomeCap1, false, p));
            break;
        case "|)":
            String nomeCap2 = name.substring(0, name.length() - 2);
            for (Capitulo c : abp) {
                if (c.getNomeCap().equals(nomeCap2))
                    c.addPage(p);
            }
            break;
        default:
            // Capitulo dummy apenas para saber se existe um igual na abp.
            Capitulo fakeCap = new Capitulo(name);
            if (abp.contains(fakeCap)) {
                for (Capitulo c : abp) {
                    if (c.getNomeCap().equals(name))
                        c.addPage(p);
                }
            } else
                abp.insert(new Capitulo(name, true, p));
        }
    }
    /**
     * Caso a linha lida seja contenha um subcapitulo, este metodo é chamado
     *
     * @param abp       a abp recebida que contem os capitulos. os subcapitulos
     *                  serão inseridos aos capitulos presentes da abp
     * @param chapName o nome do capitulo para saber onde o subcapitulo pertence
     * @param subName  o nome dado ao subcapitulo. O string recebido ainda contém
     *                 o token para saber se é o inicio ou inicio do subcapitulo.
     *                 |( ou |).
     * @param p
     */
    static void buildSubChapter(AVL<Capitulo> abp, String chapName, String subName, int p) {
        String prefix = subName.substring(subName.length() - 2);

        switch (prefix) {
        case "|(":
            String nomeSub1 = subName.substring(0, subName.length() - 2);
            for (Capitulo c : abp) {
                if (c.getNomeCap().equals(chapName)) {
                    c.addSub(new SubCapitulo(nomeSub1, false, p));
                }
            }
            break;
        case "|)":
            String nomeSub2 = subName.substring(0, subName.length() - 2);
            for (Capitulo c : abp) {
                for (SubCapitulo s : c.getSubs()) {
                    if (s.getNomeSub().equals(nomeSub2))
                        s.addPage(p);
                }
            }
            break;
        default:
            SubCapitulo fakeSub = new SubCapitulo(subName);
            for (Capitulo c : abp) {
                if (c.getNomeCap().equals(chapName)) {
                    if (c.getSubs().contains(fakeSub)) {
                        for (SubCapitulo s : c.getSubs()) {
                            if (s.getNomeSub().equals(subName))
                                s.addPage(p);
                        }
                    } else
                        c.addSub(new SubCapitulo(subName, true, p));
                }
            }
        }

    }

    static void printIndex(AVL<Capitulo> abp) {
        for (Iterator<Capitulo> it = abp.inOrderIterator(); it.hasNext();) {
            Capitulo c = it.next();
            System.out.println(c);
            for (Iterator<SubCapitulo> it2 = c.getSubs().inOrderIterator(); it2.hasNext();) {
                SubCapitulo s = it2.next();
                System.out.println("    " + s);
            }
        }
    }


}

class Capitulo implements Comparable<Capitulo> {
    private final String nomeCap;
    private boolean singlePage;
    private Queue<Integer> paginas = new Queue<>();
    private AVL<SubCapitulo> subCap = new AVL<>();

    public Capitulo(String nome, boolean sp, int p) {
        nomeCap = nome;
        singlePage = sp;
        paginas.enqueue(p);
    }

    public Capitulo(String nome) {
        nomeCap = nome;
    }

    public AVL<SubCapitulo> getSubs() {
        return subCap;
    }

    public void addSub(SubCapitulo s) {
        subCap.insert(s);
    }

    public String getNomeCap() {
        return nomeCap;
    }

    public void addPage(int i) {
        paginas.enqueue(i);
    }

    @Override
    public int compareTo(Capitulo o) {
        return nomeCap.compareTo(o.nomeCap);
    }

    @Override
    public String toString() {
        String s = String.format("%s: ", nomeCap);
        String delim = singlePage ? "," : "-";
        if (!singlePage) {
            int startPage = paginas.dequeue();
            int endPage = paginas.dequeue();
            if (startPage == endPage)
                s += String.valueOf(endPage);
            else
                s += String.valueOf(startPage) + delim + String.valueOf(endPage);
        } else {
            int numPages = paginas.size();
            for (int i = 0; i < numPages; i++) {
                s += String.valueOf(paginas.dequeue()) + delim;
                if (i == numPages - 1)
                    s += "\b";
            }
        }

        return s;
    }
}

class SubCapitulo implements Comparable<SubCapitulo> {
    private final String nomeSub;
    private boolean singlePage;
    private Queue<Integer> paginas = new Queue<>();

    public SubCapitulo(String nome, boolean sp, int p) {
        nomeSub = nome;
        singlePage = sp;
        paginas.enqueue(p);
    }

    public SubCapitulo(String nome) {
        nomeSub = nome;
    }

    public String getNomeSub() {
        return nomeSub;
    }

    public void addPage(int i) {
        paginas.enqueue(i);
    }

    @Override
    public int compareTo(SubCapitulo o) {
        return nomeSub.compareTo(o.nomeSub);
    }

    @Override
    public String toString() {
        String s = String.format("%s: ", nomeSub);
        String delim = singlePage ? "," : "-";
        if (!singlePage) {
            int startPage = paginas.dequeue();
            int endPage = paginas.dequeue();
            if (startPage == endPage)
                s += String.valueOf(endPage);
            else
                s += String.valueOf(startPage) + delim + String.valueOf(endPage);
        } else {
            int numPages = paginas.size();
            for (int i = 0; i < numPages; i++) {
                s += String.valueOf(paginas.dequeue()) + delim;
                if (i == numPages - 1)
                    s += "\b";
            }
        }

        return s;
    }
}