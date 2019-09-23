package Controller.Comparator;

import Model.Voucher;

import java.util.Comparator;

/**
 * Comparator for vouchers using name.
 */
public class VoucherPlaceNameComparator implements Comparator<Voucher> {
    @Override
    public int compare(Voucher o1, Voucher o2) {
        return o1.getPlaceName().compareTo(o2.getPlaceName());
    }
}
