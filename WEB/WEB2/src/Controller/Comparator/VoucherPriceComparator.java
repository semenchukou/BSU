package Controller.Comparator;

import Model.Voucher;

import java.util.Comparator;

/**
 * Comparator for vouchers using price.
 */
public class VoucherPriceComparator implements Comparator<Voucher> {
    @Override
    public int compare(Voucher o1, Voucher o2) {
        return Integer.compare(o1.getPrice(), o2.getPrice());
    }
}
