package Model;

/**
 * Represents a point in space.
 */
public class Point {
    private RationalFraction x;
    private RationalFraction y;
    private RationalFraction z;

    public Point() {
        x = new RationalFraction();
        y = new RationalFraction();
        z = new RationalFraction();
    }

    /**
     * Constructor creates a new point ouf of three given dimensions.
     * @param x The value of x dimension.
     * @param y The value of y dimension.
     * @param z The value of z dimension.
     */
    public Point(RationalFraction x, RationalFraction y, RationalFraction z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public RationalFraction getX() {
        return x;
    }

    public RationalFraction getY() {
        return y;
    }

    public RationalFraction getZ() {
        return z;
    }
}
