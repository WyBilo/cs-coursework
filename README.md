Computer Science Coursework
Coursework from my B.S. in Computer Science, with projects in C++, Java, HTML, CSS, and JavaScript.
Featured Project · B-tree Student Database
[Browse the B-tree Student Database source](algorithms-and-data-structures/lab2/)

A C++ command-line program that stores fixed-length student records on disk and maintains two B-tree indexes for lookups by student ID and last name. It processes commands to find records, add records, and list records in index order. A last-name lookup can return multiple students.

Run from the project folder with a C++17 compiler and the sample inputs students.txt and commands.txt.
c++ -std=c++17 *.cpp -o btree
./btree students.txt demo 3 commands.txt report.txt
Open report.txt to see the lookup results and index statistics. The program builds the database and indexes from the input data each time it runs.
Algorithms & Data Structures
Project	What it demonstrates	Build and run from the project folder
[Sorting Benchmark](algorithms-and-data-structures/lab3/)	Compares selection, merge, quick, and heap sort on identical inputs and verifies that each result is sorted.	c++ -O2 -std=c++17 main.cpp -o sort-benchmark && ./sort-benchmark
[Infix-to-Postfix Converter](algorithms-and-data-structures/lab1/)	Uses a templated stack to handle operator precedence and parentheses, then evaluates numeric expressions. Try the space-separated input 2 + 3 * 4.	c++ -std=c++17 in2post.cpp -o in2post && ./in2post


[Browse the individual exercises](algorithms-and-data-structures/exercises/), including Quickselect, Dijkstra’s shortest-path algorithm, and Kruskal’s minimum spanning tree algorithm.
C/C++ Programming
Standalone C++ console programs covering functions, input validation, string handling, and file I/O.
Assignment	What it does	Build and run from the course folder
[Sales Records](c-cpp-programming/Lab14-2.cpp)	Saves sales records to a text file and reads them back to calculate total sales. Choose Add Records first to create Sales.txt.	c++ -std=c++17 Lab14-2.cpp -o sales && ./sales
[Gross Pay Calculator](c-cpp-programming/2Introductory16.cpp)	Calculates regular pay and two tiers of overtime for multiple employees.	c++ -std=c++17 2Introductory16.cpp -o gross-pay && ./gross-pay
[Shipping Charge Calculator](c-cpp-programming/Introductory20.cpp)	Validates region codes and displays the corresponding shipping charge.	c++ -std=c++17 Introductory20.cpp -o shipping && ./shipping


Java Programming
Introductory Java console programs covering user input, methods, arithmetic, and date handling.
- [Month Handling](java-programming/TestMonthHandling.java) demonstrates how LocalDate handles month-end dates and leap years.
- [Paint Calculator](java-programming/PaintCalculator.java) calculates wall area and estimates paint cost from room dimensions.
- [Egg Order Calculator](java-programming/Eggs.java) uses integer division and remainder to price dozens and individual eggs.
Run the month-handling example from the java-programming folder with a JDK.
javac -d out TestMonthHandling.java
java -cp out TestMonthHandling
[Browse all Java exercises](java-programming/).
HTML5 Coursework
Browser-based exercises covering HTML forms, CSS, and JavaScript.
- [Drawing Program](html5/WyattBilodeau_Exercise13-4.html) draws in two colors, erases individual cells, and clears the entire grid.
- [Salesperson Salary Ranges](html5/WyattBilodeau_Exercise10-10.html) updates a salary distribution table as weekly sales are entered.
- [Character Counter](html5/WyattBilodeau_Exercise11-13.html) counts occurrences of a character in a block of text.
To try a demo, download its HTML file and open it in a desktop browser.
