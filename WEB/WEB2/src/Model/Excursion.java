package Model;

/**
 * Represents excursion voucher.
 * @param <B>
 */
public class Excursion<B extends Excursion.Builder<B>> extends Voucher {
    /**
     * Guide name.
     */
    private String guideName;

    /**
     * Guide name getter
     * @return guide name.
     */
    public String getGuideName() {
        return guideName;
    }

    /**
     * Creates excursion object.
     * @param builder excursion builder.
     */
    private Excursion(Builder<B> builder) {
        super(builder);
        this.guideName = builder.guideName;
    }

    @Override
    public String toString() {
        return super.toString() + ", guide name " + guideName;
    }

    /**
     * guide name setter.
     * @param guideName guide name.
     */
    void setGuideName(String guideName) {
        this.guideName = guideName;
    }

    /**
     * Represents builder pattern.
     * @param <B>
     */
    public static class Builder<B extends Excursion.Builder<B>> extends Voucher.BaseBuilder<B> {

        /**
         * giude name.
         */
        String guideName;

        /**
         * Method to set guide name.
         * @param guideName guide name.
         * @return builder object.
         */
        public B guideName(String guideName) {
            this.guideName = guideName;
            return (B)this;
        }

        @Override
        public Excursion<B> build() {
            return new Excursion<>(this);
        }
    }
}
