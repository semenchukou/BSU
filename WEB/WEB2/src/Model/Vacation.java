package Model;

import java.util.Objects;

/**
 * Represents vacation.
 * @param <B>
 */
public class Vacation<B extends Vacation.Builder<B>> extends Voucher {
    /**
     * Hotel name.
     */
    private String hotelName;

    /**
     * Getter for hotel name.
     * @return hotel name value.
     */
    public String getHotelName() {
        return hotelName;
    }

    /**
     * Creates vacation object.
     * @param builder vacation builder.
     */
    private Vacation(Builder<B> builder) {
        super(builder);
        this.hotelName = builder.hotelName;
    }

    @Override
    public String toString() {
        return super.toString() + ", hotel name " + hotelName;
    }

    /**
     * Hotel name setter.
     * @param hotelName Hotel name.
     */
    void setHotelName(String hotelName) {
        this.hotelName = hotelName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Vacation<?> vacation = (Vacation<?>) o;
        return Objects.equals(hotelName, vacation.hotelName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), hotelName);
    }

    /**
     * Represents builder pattern.
     * @param <B>
     */
    public static class Builder<B extends Vacation.Builder<B>> extends Voucher.BaseBuilder<B> {

        /**
         * Hotel name.
         */
       String hotelName;

        /**
         * Method to set hotel name.
         * @param hotelName Hotel name.
         * @return builder object.
         */
       public B hotelName(String hotelName) {
           this.hotelName = hotelName;
           return (B)this;
       }

       @Override
       public Vacation<B> build() {
           return new Vacation<>(this);
       }
    }
}
