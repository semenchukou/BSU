package Controller;

import Model.Point;

/**
 * Gives methods for working with Points.
 */
public class PointController {
    /**
     * Finds the distance between 2 given points.
     * @param first The first point.
     * @param second The second point.
     * @return Distance between points.
     */
    public static double findDistance(Point first, Point second) {
        return Math.sqrt(Math.pow(first.getX().getValue() - second.getX().getValue(), 2) +
                Math.pow(first.getY().getValue() - second.getY().getValue(), 2) +
                Math.pow(first.getZ().getValue() - second.getZ().getValue(), 2));
    }

    /**
     * Finds the distance from the (0, 0, 0) point to the given.
     * @param point The given point.
     * @return Distance between the beginning and the point.
     */
    public static double findDistanceFromBeginning(Point point) {
        return Math.sqrt(Math.pow(point.getX().getValue(), 2) +
                Math.pow(point.getY().getValue(), 2) +
                Math.pow(point.getZ().getValue(), 2));
    }

    /**
     * Checks if the three given points lie on one line.
     * @param first The first point.
     * @param second The second point.
     * @param third The third point.
     * @return True if the points are on one line, false otherwise.
     */
    public static boolean areOnOneLine(Point first, Point second, Point third) {
        double firstPart = third.getY().getValue() - first.getY().getValue()
                / second.getY().getValue() - first.getY().getValue();
        double secondPart = third.getX().getValue() - first.getX().getValue()
                / second.getX().getValue() - first.getX().getValue();
        double thirdPart = third.getZ().getValue() - first.getZ().getValue()
                / second.getZ().getValue() - first.getZ().getValue();
        return firstPart == secondPart && secondPart == thirdPart;
    }
}
