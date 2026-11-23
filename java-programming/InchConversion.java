import java.util.Scanner;

public class InchConversion {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter a value in inches: ");
        double inches = input.nextDouble();

        convertToFeet(inches);
        convertToYards(inches);

        input.close();
    }

    public static void convertToFeet(double inches) {
        double feet = inches / 12;
        System.out.println(inches + " inches is equal to " + feet + " feet.");
    }

    public static void convertToYards(double inches) {
        double yards = inches / 36;
        System.out.println(inches + " inches is equal to " + yards + " yards.");
    }
}