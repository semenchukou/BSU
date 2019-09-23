package Controller;
import Model.*;
import Model.Enums.Food;
import Model.Enums.Transport;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

/**
 * Class to work with fxml file.
 */
public class Controller {

    /**
     * Manager to work with.
     */
    VoucherManager voucherManager;

    /**
     * Is days param set when searching for vouchers.
     */
    boolean daysSet = false;

    /**
     * Is food param set when searching for vouchers.
     */
    boolean foodSet = false;

    /**
     * Is transport param set when searching for vouchers.
     */
    boolean transportSet = false;

    /**
     * No-param constructor.
     */
    public Controller() {
        voucherManager = new VoucherManager();
    }

    /**
     * place name when adding new voucher.
     */
    @FXML
    private TextField place_name;

    /**
     * Result text area.
     */
    @FXML
    private TextArea result_text;

    /**
     * Days amount when adding new voucher.
     */
    @FXML
    private TextField days_amount;

    /**
     * Days amount when searching for vouchers.
     */
    @FXML
    private TextField days_amount_to_get;

    /**
     * price when adding new voucher.
     */
    @FXML
    private TextField price;

    /**
     * people amount when adding new voucher.
     */
    @FXML
    private TextField people_amount;

    /**
     * food when adding new voucher.
     */
    @FXML
    private TextField food;

    /**
     * food when searching for vouchers.
     */
    @FXML
    private TextField food_to_get;

    /**
     * Days amount when searching for vouchers.
     */
    @FXML
    private TextField transport;

    /**
     * transport when adding new voucher.
     */
    @FXML
    private TextField transport_to_get;

    /**
     * Special field for every voucher when adding new voucher.
     */
    @FXML
    private TextField additional;

    /**
     * Button for selecting cruise voucher.
     */
    @FXML
    private RadioButton cruiseRB;

    /**
     * Button for selecting days amount when searching for vouchers.
     */
    @FXML
    private RadioButton daysAmountRB;

    /**
     * Button for selecting food amount when searching for vouchers.
     */
    @FXML
    private RadioButton foodRB;

    /**
     * Button for selecting transport amount when searching for vouchers.
     */
    @FXML
    private RadioButton transportRB;

    /**
     * Button for selecting food amount when searching for vouchers.
     */
    @FXML
    private RadioButton excursionRB;

    /**
     * Button for selecting shopping voucher.
     */
    @FXML
    private RadioButton shoppingRB;

    /**
     * Button for selecting therapy voucher.
     */
    @FXML
    private RadioButton therapyRB;

    /**
     * Button for selecting vacation voucher.
     */
    @FXML
    private RadioButton vacationRB;

    /**
     * Handling adding button pressure.
     */
    @FXML
    private void add_pressed(ActionEvent event) {
        Food fd = Food.ALL;
        if (food.getText().equals("all")) {
            fd = Food.ALL;
        } else if (food.getText().equals("vegan")) {
            fd = Food.VEGAN;
        } else if (food.getText().equals("vegetarian")) {
            fd = Food.VEGETARIAN;
        }
        Transport tr = Transport.PLANE;
        if (transport.getText().equals("plane")) {
            tr = Transport.PLANE;
        } else if (transport.getText().equals("bus")) {
            tr = Transport.BUS;
        } else if (transport.getText().equals("cruiser")) {
            tr = Transport.CRUISER;
        } else if (transport.getText().equals("railway")) {
            tr = Transport.RAILWAY;
        }
        if (cruiseRB.isSelected()) {
            Cruise cruise = new Cruise.Builder<>()
                    .placeName(place_name.getText())
                    .cruiserName(additional.getText())
                    .daysAmount(Integer.parseInt(days_amount.getText()))
                    .price(Integer.parseInt(price.getText()))
                    .peopleAmount(Integer.parseInt(people_amount.getText()))
                    .food(fd)
                    .transport(tr)
                    .build();
            voucherManager.vouchers.add(cruise);
            result_text.setText("Cruise added!");
        } else if (excursionRB.isSelected()) {
            Excursion excursion = new Excursion.Builder<>()
                    .placeName(place_name.getText())
                    .guideName(additional.getText())
                    .daysAmount(Integer.parseInt(days_amount.getText()))
                    .price(Integer.parseInt(price.getText()))
                    .peopleAmount(Integer.parseInt(people_amount.getText()))
                    .food(fd)
                    .transport(tr)
                    .build();
            voucherManager.vouchers.add(excursion);
            result_text.setText("Excursion added!");
        } else if (shoppingRB.isSelected()) {
            Shopping shopping = new Shopping.Builder<>()
                    .placeName(place_name.getText())
                    .mallName(additional.getText())
                    .daysAmount(Integer.parseInt(days_amount.getText()))
                    .price(Integer.parseInt(price.getText()))
                    .peopleAmount(Integer.parseInt(people_amount.getText()))
                    .food(fd)
                    .transport(tr)
                    .build();
            voucherManager.vouchers.add(shopping);
            result_text.setText("Shopping added!");
        } else if (therapyRB.isSelected()) {
            Therapy therapy = new Therapy.Builder<>()
                    .placeName(place_name.getText())
                    .mainProcedureName(additional.getText())
                    .daysAmount(Integer.parseInt(days_amount.getText()))
                    .price(Integer.parseInt(price.getText()))
                    .peopleAmount(Integer.parseInt(people_amount.getText()))
                    .food(fd)
                    .transport(tr)
                    .build();
            voucherManager.vouchers.add(therapy);
            result_text.setText("Therapy added!");
        } else if (vacationRB.isSelected()) {
            Vacation vacation = new Vacation.Builder<>()
                    .placeName(place_name.getText())
                    .hotelName(additional.getText())
                    .daysAmount(Integer.parseInt(days_amount.getText()))
                    .price(Integer.parseInt(price.getText()))
                    .peopleAmount(Integer.parseInt(people_amount.getText()))
                    .food(fd)
                    .transport(tr)
                    .build();
            voucherManager.vouchers.add(vacation);
            result_text.setText("Vacation added!");
        }
        place_name.clear();
        additional.clear();
        days_amount.clear();
        price.clear();
        people_amount.clear();
        food.clear();
        transport.clear();
    }

    /**
     * Handling cruise voucher selecting.
     */
    @FXML
    private void cruise_selected(ActionEvent event) {
        additional.setPromptText("Cruiser name:");
    }

    /**
     * Handling excursion voucher selecting.
     */
    @FXML
    private void excursion_selected(ActionEvent event) {
        additional.setPromptText("Guide name:");
    }

    /**
     * Handling shopping voucher selecting.
     */
    @FXML
    private void shopping_selected(ActionEvent event) {
        additional.setPromptText("Mall name:");
    }

    /**
     * Handling therapy voucher selecting.
     */
    @FXML
    private void therapy_selected(ActionEvent event) {
        additional.setPromptText("Main procedure name:");
    }

    /**
     * Handling vacation voucher selecting.
     */
    @FXML
    private void vacation_selected(ActionEvent event) {
        additional.setPromptText("Hotel name:");
    }

    /**
     * Handling days amount sorting button pressed..
     */
    @FXML
    private void days_amount_sort(ActionEvent event) {
        result_text.setText(voucherManager.sortVouchersByDaysAmount(false).toString());
    }

    /**
     * Handling price sorting button pressed..
     */
    @FXML
    private void price_sort(ActionEvent event) {
        result_text.setText(voucherManager.sortVouchersByPrice(false).toString());
    }

    /**
     * Handling people amount sorting button pressed..
     */
    @FXML
    private void people_amount_sort(ActionEvent event) {
        result_text.setText(voucherManager.sortVouchersByPeopleAmount(false).toString());
    }

    /**
     * Handling days amount setting.
     */
    @FXML
    private void days_amount_set(ActionEvent event) {
        daysSet = !daysSet;
        days_amount_to_get.setVisible(!days_amount_to_get.isVisible());
    }

    /**
     * Handling food setting.
     */
    @FXML
    private void food_set(ActionEvent event) {
        foodSet = !foodSet;
        food_to_get.setVisible(!food_to_get.isVisible());
    }

    /**
     * Handling transport setting.
     */
    @FXML
    private void transport_set(ActionEvent event) {
        transportSet = !transportSet;
        transport_to_get.setVisible(!transport_to_get.isVisible());
    }

    /**
     * Handling getting vouchers according to set params.
     */
    @FXML
    private void get_vouchers(ActionEvent event) {
        int days = 0;
        Food fd = Food.ALL;
        Transport tr = Transport.BUS;
        if (daysAmountRB.isSelected()) {
            days = Integer.parseInt(days_amount_to_get.getText());
        }
        if (foodRB.isSelected()) {
            if (food_to_get.getText().equals("all")) {
                fd = Food.ALL;
            } else if (food_to_get.getText().equals("vegan")) {
                fd = Food.VEGAN;
            } else if (food_to_get.getText().equals("vegetarian")) {
                fd = Food.VEGETARIAN;
            }
        }
        if (transportRB.isSelected()) {
            if (transport_to_get.getText().equals("plane")) {
                tr = Transport.PLANE;
            } else if (transport_to_get.getText().equals("bus")) {
                tr = Transport.BUS;
            } else if (transport_to_get.getText().equals("cruiser")) {
                tr = Transport.CRUISER;
            } else if (transport_to_get.getText().equals("railway")) {
                tr = Transport.RAILWAY;
            }
        }
        if (daysAmountRB.isSelected() && foodRB.isSelected() && transportRB.isSelected()) {
            result_text.setText(
                    voucherManager.newLookUpBuilder()
                            .setDaysAmount(days)
                            .setTransport(tr)
                            .setFood(fd)
                            .build()
                            .toString()
            );
        }
        if (daysAmountRB.isSelected() && foodRB.isSelected() && !transportRB.isSelected()) {
            result_text.setText(
                    voucherManager.newLookUpBuilder()
                            .setDaysAmount(days)
                            .setFood(fd)
                            .build()
                            .toString()
            );
        }
        if (daysAmountRB.isSelected() && !foodRB.isSelected() && transportRB.isSelected()) {
            result_text.setText(
                    voucherManager.newLookUpBuilder()
                            .setDaysAmount(days)
                            .setTransport(tr)
                            .build()
                            .toString()
            );
        }
        if (!daysAmountRB.isSelected() && foodRB.isSelected() && transportRB.isSelected()) {
            result_text.setText(
                    voucherManager.newLookUpBuilder()
                            .setTransport(tr)
                            .setFood(fd)
                            .build()
                            .toString()
            );
        }
        if (daysAmountRB.isSelected() && !foodRB.isSelected() && !transportRB.isSelected()) {
            result_text.setText(
                    voucherManager.newLookUpBuilder()
                            .setDaysAmount(days)
                            .build()
                            .toString()
            );
        }
        if (!daysAmountRB.isSelected() && !foodRB.isSelected() && transportRB.isSelected()) {
            result_text.setText(
                    voucherManager.newLookUpBuilder()
                            .setTransport(tr)
                            .build()
                            .toString()
            );
        }
        if (!daysAmountRB.isSelected() && foodRB.isSelected() && !transportRB.isSelected()) {
            result_text.setText(
                    voucherManager.newLookUpBuilder()
                            .setFood(fd)
                            .build()
                            .toString()
            );
        }
        if (!daysAmountRB.isSelected() && !foodRB.isSelected() && !transportRB.isSelected()) {
            result_text.setText(
                    voucherManager.newLookUpBuilder()
                            .build()
                            .toString()
            );
        }
    }
}
