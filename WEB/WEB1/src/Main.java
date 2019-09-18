import Controller.PointController;
import Model.Point;
import Model.RationalFraction;

public class Main {
    public static void main(String[] args) {
        RationalFraction rf1 = new RationalFraction(1, 1);
        RationalFraction rf2 = new RationalFraction(1, 1);
        RationalFraction rf3 = new RationalFraction(1, 1);
        Point p1 = new Point(rf1, rf2, rf3);

        RationalFraction rf4 = new RationalFraction(2, 1);
        RationalFraction rf5 = new RationalFraction(2, 1);
        RationalFraction rf6 = new RationalFraction(2, 1);
        Point p2 = new Point(rf4, rf5, rf6);

        RationalFraction rf7 = new RationalFraction(3, 1);
        RationalFraction rf8 = new RationalFraction(3, 1);
        RationalFraction rf9 = new RationalFraction(3, 1);
        Point p3 = new Point(rf7, rf8, rf9);

        System.out.println(PointController.findDistance(p1, p2));
        System.out.println(PointController.areOnOneLine(p1, p2, p3));
    }
}
