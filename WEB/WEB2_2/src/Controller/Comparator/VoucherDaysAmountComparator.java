package Controller.Comparator;

import Model.Voucher;

import java.util.Comparator;

/**
 * Comparator for vouchers using days amount.
 */
public class VoucherDaysAmountComparator implements Comparator<Voucher> {
    @Override
    public int compare(Voucher o1, Voucher o2) {
        return Integer.compare(o1.getDaysAmount(), o2.getDaysAmount());
    }
}
