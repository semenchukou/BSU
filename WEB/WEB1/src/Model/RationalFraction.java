package Model;

/**
 * The class represents rational fraction.
 */
public class RationalFraction {
    private int nominator;
    private int denominator;
    private double value;

    /**
     * Constructor creates a new fraction.
     * @param num numerator of the fraction.
     * @param denom denominator of the fraction.
     * @throws IllegalArgumentException When denominator is equal to zero.
     */
    public RationalFraction(int num, int denom) throws IllegalArgumentException {
        this.nominator = num;
        if (denom == 0) {
            throw new IllegalArgumentException("Denominator cant be equal to zero.");
        }
        this.denominator = denom;
        this.value = calculateValue();
    }

    public RationalFraction() {
        this.nominator = 0;
        this.denominator = 1;
        this.value = calculateValue();
    }

    /**
     * Divides the numerator by the denominator.
     * @return Double value of the fraction.
     */
    private double calculateValue() {
        return (double) (this.nominator / this.denominator);
    }

    public double getValue() {
        return value;
    }
}
