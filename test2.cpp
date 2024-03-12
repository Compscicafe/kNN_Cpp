#include "main.hpp"
#include "kNN.hpp"
#include <chrono>
int main() {
    auto start = std::chrono::high_resolution_clock::now();

    Dataset dataset;

    dataset.loadFromCSV("mnist.csv");
    dataset.printHead();
    cout <<"Bruh bruh lmao\n";
    dataset.printTail();
    kNN(5);
    Dataset X_train, X_test, y_train, y_test;





    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Print the runtime in microseconds
    std::cout << "Runtime: " << duration.count() << " microseconds" << std::endl;
    return 0;  // Return zero to indicate success
}


// kNN