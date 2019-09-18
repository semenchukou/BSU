package Model;

import java.util.Objects;

/**
 * Represents cruise voucher.
 * @param <B>
 */
public class Cruise<B extends Cruise.Builder<B>> extends Voucher {
    /**
     * Cruiser name.
     */
    private String cruiserName;

    /**
     * Cruiser name getter.
     * @return Cruiser name value.
     */
    public String getCruiserName() {
        return cruiserName;
    }

    /**
     * Creates cruise object.
     * @param builder cruise builder.
     */
    private Cruise(Builder<B> builder) {
        super(builder);
        this.cruiserName = builder.cruiserName;
    }

    @Override
    public String toString() {
        return super.toString() + ", cruiser name " + cruiserName;
    }

    /**
     * Cruiser name setter.
     * @param cruiserName cruiser name.
     */
    void setCruiserName(String cruiserName) {
        this.cruiserName = cruiserName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Cruise<?> cruise = (Cruise<?>) o;
        return Objects.equals(cruiserName, cruise.cruiserName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), cruiserName);
    }

    /**
     * Represents builder pattern.
     * @param <B>
     */
    public static class Builder<B extends Cruise.Builder<B>> extends Voucher.BaseBuilder<B> {

        /**
         * Cruiser name.
         */
        String cruiserName;

        /**
         * Method to set cruiser name.
         * @param cruiserName cruiser name.
         * @return builder object.
         */
        public B cruiserName(String cruiserName) {
            this.cruiserName = cruiserName;
            return (B) this;
        }

        @Override
        public Cruise<B> build() {
            return new Cruise<>(this);
        }
    }
}
