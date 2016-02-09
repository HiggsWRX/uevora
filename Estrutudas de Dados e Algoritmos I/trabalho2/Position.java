public class Position {
    int x;
    int y;

    public Position() {
        this(0, 0);
    }

    public Position(int l, int c) {
        x = l;
        y = c;
    }

    public String toString() {
        return String.format("(%d,%d)", x, y);
    }

    public boolean equals(Position p) {
        return this.x == p.x && this.y == p.y;
    }
}
