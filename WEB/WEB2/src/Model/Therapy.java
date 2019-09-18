package Model;

import java.util.Objects;

/**
 * Represents therapy voucher.
 * @param <B>
 */
public class Therapy<B extends Therapy.Builder<B>> extends Voucher {
    /**
     * main procedure name.
     */
    private String mainProcedureName;

    /**
     * main procedure name getter.
     * @return main procedure name.
     */
    public String getMainProcedureName() {
        return mainProcedureName;
    }

    /**
     * Creates therapy builder.
     * @param builder therapy builder.
     */
    private Therapy(Builder<B> builder) {
        super(builder);
        this.mainProcedureName = builder.mainProcedureName;
    }

    @Override
    public String toString() {
        return super.toString() + ", main procedure name " + mainProcedureName;
    }

    /**
     * main procedure name setter.
     * @param mainProcedureName main procedure name.
     */
    void setMainProcedureName(String mainProcedureName) {
        this.mainProcedureName = mainProcedureName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Therapy<?> therapy = (Therapy<?>) o;
        return Objects.equals(mainProcedureName, therapy.mainProcedureName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), mainProcedureName);
    }

    /**
     * Represents builder pattern.
     * @param <B>
     */
    public static class Builder<B extends Therapy.Builder<B>> extends Voucher.BaseBuilder<B> {

        /**
         * main procedure name.
         */
        String mainProcedureName;

        /**
         * Method to set main procedure name.
         * @param mainProcedureName main procedure name.
         * @return builder object.
         */
        public B mainProcedureName(String mainProcedureName) {
            this.mainProcedureName = mainProcedureName;
            return (B)this;
        }

        @Override
        public Therapy<B> build() {
            return new Therapy<>(this);
        }
    }
}
