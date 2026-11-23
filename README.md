## HTML5 Coursework

Browser-based exercises covering HTML forms, CSS, and JavaScript, from
native input controls to interactive pages that update in response to user input.

- [Drawing Program](html5/WyattBilodeau_Exercise13-4.html) — Draw in two colors, erase individual cells, or clear the entire grid.
- [Salesperson Salary Ranges](html5/WyattBilodeau_Exercise10-10.html) — Enter weekly sales and see the salary distribution update after each entry.
- [Character Counter](html5/WyattBilodeau_Exercise11-13.html) — Search a block of text for a character and display how many times it appears.

To try a demo, download its HTML file and open it in a desktop browser.

## C/C++ Programming

Standalone C++ console programs covering functions, input validation,
string handling, and file I/O.

| Assignment | What it does | Build and run |
| --- | --- | --- |
| [Sales Records](c-cpp-programming/Lab14-2.cpp) | Saves sales records to a text file and reads them back to calculate total sales. | `c++ -std=c++17 Lab14-2.cpp -o sales && ./sales` |
| [Gross Pay Calculator](c-cpp-programming/2Introductory16.cpp) | Calculates regular pay and two tiers of overtime for multiple employees. | `c++ -std=c++17 2Introductory16.cpp -o gross-pay && ./gross-pay` |
| [Shipping Charge Calculator](c-cpp-programming/Introductory20.cpp) | Validates region codes and displays the corresponding shipping charge. | `c++ -std=c++17 Introductory20.cpp -o shipping && ./shipping` |

Run the commands from the `c-cpp-programming` folder with a C++17 compiler.
For Sales Records, choose **Add Records** first to create `Sales.txt`.

## Algorithms & Data Structures

C++ coursework covering stacks, B-tree indexes, sorting, and graph algorithms.

| Project | What it demonstrates | Build and run from the project folder |
| --- | --- | --- |
| [B-tree Student Database](algorithms-and-data-structures/lab-2/) | Stores student records on disk and uses separate B-tree indexes for ID and last-name lookups. Supports adding records and listing them in index order. | `c++ -std=c++17 *.cpp -o btree && ./btree students.txt demo 3 commands.txt report.txt` |
| [Sorting Benchmark](algorithms-and-data-structures/lab-3/) | Compares selection, merge, quick, and heap sort on identical inputs and checks that each result is sorted. | `c++ -O2 -std=c++17 main.cpp -o sort-benchmark && ./sort-benchmark` |
| [Infix-to-Postfix Converter](algorithms-and-data-structures/lab-1/) | Uses a custom templated stack to handle operator precedence and parentheses, then evaluates numeric expressions. | `c++ -std=c++17 in2post.cpp -o in2post && ./in2post` |

For the database demo, open `report.txt` after running it.
For the expression converter, separate each token with spaces. Try `2 + 3 * 4`.

[Browse the individual exercises](algorithms-and-data-structures/exercises/),
including Quickselect, Dijkstra’s shortest-path algorithm, and Kruskal’s
minimum spanning tree algorithm.
