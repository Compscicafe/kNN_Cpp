#include "kNN.hpp"
#include <chrono>
void tc1(){
    /*
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead();
    //dataset.printTail();
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    dataset.printTail();
    kNN knn(5);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, 3, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    cout << "It's still here\n";
    //Dataset y_pred = knn.predict(X_test);
    //double accuracy = knn.score(y_test, y_pred);
//    cout << "Accuracy: " << accuracy << endl;
*/
}

int main()
{

    auto start = std::chrono::high_resolution_clock::now();
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead();
    //dataset.printTail();
   // int nRows, nCols;
  //  dataset.getShape(nRows, nCols);
   // cout << "Shape: " << nRows << "x" << nCols << endl;

    dataset.printTail();
    kNN knn(5);
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, 3, 1, -1);
//    feature.printDim();
  //  feature.printHead();
   // feature.printTail();

   // Dataset label = dataset.extract(0, -1, 0, 0);
    //train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
  //  knn.fit(X_train, y_train);
    cout << "It's still here\n";
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Print the runtime in microseconds
    std::cout << "Runtime: " << duration.count() << " microseconds" << std::endl;
    return 0;  // Return zero to indicate success
}