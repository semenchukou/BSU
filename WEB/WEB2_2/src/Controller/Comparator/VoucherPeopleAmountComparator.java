package Controller.Comparator;

import Model.Voucher;

import java.util.Comparator;

/**
 * Comparator for vouchers using people amount.
 */
public class VoucherPeopleAmountComparator implements Comparator<Voucher> {
    @Override
    public int compare(Voucher o1, Voucher o2) {
        return Integer.compare(o1.getPeopleAmount(), o2.getPeopleAmount());
    }
}
