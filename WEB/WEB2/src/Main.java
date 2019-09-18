import Controller.VoucherManager;
import Model.*;
import Model.Enums.Food;
import Model.Enums.Transport;

import java.util.List;

public class Main {
    public static void main(String[] args) {
        try {
            Shopping shopping = new Shopping.Builder<>()
                    .placeName("Minsk")
                    .mallName("Stolitsa")
                    .daysAmount(5)
                    .price(12)
                    .peopleAmount(2)
                    .food(Food.ALL)
                    .transport(Transport.PLANE)
                    .build();
            Cruise cruise = new Cruise.Builder<>()
                    .placeName("Malta")
                    .cruiserName("Titanik")
                    .daysAmount(5)
                    .price(100)
                    .peopleAmount(15)
                    .food(Food.ALL)
                    .transport(Transport.CRUISER)
                    .build();
            Therapy therapy = new Therapy.Builder<>()
                    .mainProcedureName("Lungs therapy")
                    .placeName("Hawaii")
                    .daysAmount(6)
                    .price(10)
                    .peopleAmount(5)
                    .food(Food.ALL)
                    .transport(Transport.BUS)
                    .build();
            Vacation vacation = new Vacation.Builder<>()
                    .hotelName("Centr")
                    .placeName("Hawaii")
                    .daysAmount(7)
                    .price(50)
                    .peopleAmount(20)
                    .food(Food.ALL)
                    .transport(Transport.PLANE)
                    .build();
            VoucherManager voucherManager = new VoucherManager();
            voucherManager.vouchers.add(shopping);
            voucherManager.vouchers.add(vacation);
            voucherManager.vouchers.add(therapy);
            voucherManager.vouchers.add(cruise);
            List<Voucher> list = voucherManager.newLookUpBuilder()
                    .setDaysAmount(5)
                    .setTransport(Transport.CRUISER)
                    .build();
            for (Voucher voucher : list) {
                System.out.println(voucher.toString());
            }

            list = voucherManager.sortVouchersByDaysAmount(false);
            System.out.println("Sorted by days amount: ");
            for (Voucher voucher : list) {
                System.out.println(voucher.toString());
            }

            list = voucherManager.sortVouchersByPrice(true);
            System.out.println("Sorted by days price reversed: ");
            for (Voucher voucher : list) {
                System.out.println(voucher.toString());
            }

            list = voucherManager.sortVouchersByPeopleAmount(false);
            System.out.println("Sorted by people amount: ");
            for (Voucher voucher : list) {
                System.out.println(voucher.toString());
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }
}
