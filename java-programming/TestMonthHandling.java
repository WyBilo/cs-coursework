import java.time.LocalDate;
import java.util.Scanner;

public class TestMonthHandling {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.println("Enter the first date");
        System.out.print("Year: ");
        int year1 = input.nextInt();
        System.out.print("Month: ");
        int month1 = input.nextInt();
        System.out.print("Day: ");
        int day1 = input.nextInt();

        System.out.println("\nEnter the second date");
        System.out.print("Year: ");
        int year2 = input.nextInt();
        System.out.print("Month: ");
        int month2 = input.nextInt();
        System.out.print("Day: ");
        int day2 = input.nextInt();

        LocalDate date1 = LocalDate.of(year1, month1, day1);
        LocalDate date2 = LocalDate.of(year2, month2, day2);

        System.out.println("\nFirst date: " + date1);
        showMonthChanges(date1);

        System.out.println("\nSecond date: " + date2);
        showMonthChanges(date2);

        input.close();
    }

    public static void showMonthChanges(LocalDate date) {
        System.out.println("After 1 month: " + date.plusMonths(1));
        System.out.println("After 2 months: " + date.plusMonths(2));
        System.out.println("After 3 months: " + date.plusMonths(3));
    }
}