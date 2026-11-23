// a. Display the seventh element of f.
console.log(f[6]);

// b. Initialize all five elements of g to 8.
const g = [8, 8, 8, 8, 8];

// c. Add the 100 elements of c.
let total = 0;

for (let i = 0; i < c.length; i++) {
    total += c[i];
}

console.log("Total:", total);

// d. Copy the 11 elements of a into the first 11 positions of b.
for (let i = 0; i < a.length; i++) {
    b[i] = a[i];
}

// e. Find and print the smallest and largest values in w.
let smallest = w[0];
let largest = w[0];

for (let i = 1; i < w.length; i++) {
    if (w[i] < smallest) {
        smallest = w[i];
    }

    if (w[i] > largest) {
        largest = w[i];
    }
}

console.log("Smallest:", smallest);
console.log("Largest:", largest);