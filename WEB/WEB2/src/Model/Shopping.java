package Model;

import java.util.Objects;

/**
 * Represents shopping voucher.
 * @param <B>
 */
public class Shopping<B extends Shopping.Builder<B>> extends Voucher<B> {
    /**
     * Mall name.
     */
    String mallName;

    /**
     * Mall name getter.
     * @return mall name.
     */
    public String getMallName() {
        return mallName;
    }

    /**
     * Creates shopping object.
     * @param builder builder object.
     */
    public Shopping(Builder<B> builder) {
        super(builder);
        this.mallName = builder.mallName;
    }

    @Override
    public String toString() {
        return super.toString() + ", mall name " + mallName;
    }

    /**
     * Mall name setter.
     * @param mallName mall name.
     */
    void setMallName(String mallName) {
        this.mallName = mallName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Shopping<?> shopping = (Shopping<?>) o;
        return Objects.equals(mallName, shopping.mallName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), mallName);
    }

    /**
     * Represents builder pattern.
     * @param <B>
     */
    public static class Builder<B extends Shopping.Builder<B>> extends Voucher.BaseBuilder<B> {

        /**
         * Mall name.
         */
        protected String mallName;

        /**
         * Method to set mall name.
         * @param mallName mall name.
         * @return builder object.
         */
        public B mallName(String mallName) {
            this.mallName = mallName;
            return (B) this;
        }

        @Override
        public Shopping<B> build() {
            return new Shopping<>(this);
        }
    }
}
