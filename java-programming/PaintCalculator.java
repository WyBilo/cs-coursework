import java.util.Scanner;

public class PaintCalculator {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter the length of the room: ");
        double length = input.nextDouble();

        System.out.print("Enter the width of the room: ");
        double width = input.nextDouble();

        System.out.print("Enter the height of the room: ");
        double height = input.nextDouble();

        double wallArea = calculateWallArea(length, width, height);
        double price = calculatePaintCost(wallArea);

        System.out.println("The total cost to paint the room is $" + price);

        input.close();
    }

    public static double calculateWallArea(double length, double width, double height) {
        double area = 2 * (length * height) + 2 * (width * height);
        return area;
    }

    public static double calculatePaintCost(double wallArea) {
        final double COVERAGE_PER_GALLON = 350;
        final double PRICE_PER_GALLON = 32;

        double gallonsNeeded = wallArea / COVERAGE_PER_GALLON;
        double totalCost = gallonsNeeded * PRICE_PER_GALLON;

        return totalCost;
    }
}