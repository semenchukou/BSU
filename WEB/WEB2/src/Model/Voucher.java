package Model;

import Model.Enums.Food;
import Model.Enums.Transport;

import java.util.Objects;

/**
 * Represents voucher.
 * @param <B>
 */
public abstract class Voucher<B extends Voucher.BaseBuilder<B>> {

    /**
     * place name.
     */
    private String placeName;

    /**
     * days amount.
     */
    private int daysAmount;

    /**
     * food.
     */
    private Food food;

    /**
     * transport.
     */
    private Transport transport;

    /**
     * price.
     */
    private int price;

    /**
     * people amount.
     */
    private int peopleAmount;

    /**
     * Creates voucher object.
     * @param builder voucher builder.
     */
    public Voucher(BaseBuilder builder) {
        this.placeName = builder.placeName;
        this.daysAmount = builder.daysAmount;
        this.food = builder.food;
        this.transport = builder.transport;
        this.price = builder.price;
        this.peopleAmount = builder.peopleAmount;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Voucher<?> voucher = (Voucher<?>) o;
        return daysAmount == voucher.daysAmount &&
                price == voucher.price &&
                peopleAmount == voucher.peopleAmount &&
                Objects.equals(placeName, voucher.placeName) &&
                food == voucher.food &&
                transport == voucher.transport;
    }

    @Override
    public int hashCode() {
        return Objects.hash(placeName, daysAmount, food, transport, price, peopleAmount);
    }

    /**
     * Represents builder pattern.
     * @param <B>
     */
    protected static abstract class BaseBuilder<B extends Voucher.BaseBuilder<B>> {
        /**
         * place name.
         */
        protected String placeName;

        /**
         * days amount.
         */
        protected int daysAmount;

        /**
         * food.
         */
        protected Food food;

        /**
         * transport.
         */
        protected Transport transport;

        /**
         * price.
         */
        protected int price;

        /**
         * people amount.
         */
        protected int peopleAmount;

        public B placeName(String placeName) {
            this.placeName = placeName;
            return (B)this;
        }

        public B daysAmount(int daysAmount) {
            this.daysAmount = daysAmount;
            return (B)this;
        }

        public B food(Food food) {
            this.food = food;
            return (B)this;
        }

        public B transport(Transport transport) {
            this.transport = transport;
            return (B)this;
        }

        public B price(int price) {
            this.price = price;
            return (B)this;
        }

        public B peopleAmount(int peopleAmount) {
            this.peopleAmount = peopleAmount;
            return (B)this;
        }
        abstract Voucher<B> build();
    }

    void setPlaceName(String placeName) {
        this.placeName = placeName;
    }

    public String getPlaceName() {
        return placeName;
    }

    public int getDaysAmount() {
        return daysAmount;
    }

    void setDaysAmount(int daysAmount) {
        this.daysAmount = daysAmount;
    }

    public Food getFood() {
        return food;
    }

    void setFood(Food food) {
        this.food = food;
    }

    public Transport getTransport() {
        return transport;
    }

    void setTransport(Transport transport) {
        this.transport = transport;
    }

    public int getPrice() {
        return price;
    }

    public int getPeopleAmount() {
        return peopleAmount;
    }

    @Override
    public String toString() {
        return "Voucher: place " + this.placeName + ", price " + this.price + ", amount of people " +
                this.peopleAmount + ", days amount " + this.daysAmount + ", food " + this.food.toString() +
                ", transport " + this.transport.toString();
    }
}