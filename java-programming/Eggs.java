import java.util.Scanner;

public class Eggs {
    public static void main(String[] args) {

        final double DOZEN_PRICE = 3.25;
        final double SINGLE_EGG_PRICE = 0.45;

        Scanner input = new Scanner(System.in);

        System.out.print("Enter the number of eggs ordered: ");
        int eggsOrdered = input.nextInt();

        int dozens = eggsOrdered / 12;
        int looseEggs = eggsOrdered % 12;

        double dozenCost = dozens * DOZEN_PRICE;
        double looseEggCost = looseEggs * SINGLE_EGG_PRICE;
        double totalCost = dozenCost + looseEggCost;

        System.out.println("You ordered " + eggsOrdered + " eggs.");
        System.out.println("That's " + dozens + " dozen at $" + DOZEN_PRICE +
                " per dozen and " + looseEggs + " loose eggs at $" +
                SINGLE_EGG_PRICE + " each for a total of $" +
                String.format("%.2f", totalCost) + ".");

        input.close();
    }
}
