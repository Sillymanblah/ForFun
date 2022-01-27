/*
 | Name: John Grzegorczyk
 | Date: 1/27/22
 | Title: Calculator Attempt
 |
 | Details: 
 |
 | Required Files:
 | Calculator.cpp
 | Calculations.h
*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main() {
  
  const int pi = 3.1419265
  unsigned int selection = 0;
  int num1 = 0,
      num2 = 0,
      solution = 0;
  bool badInput = true;
  
  while (badInput = true) {
    cout << "Welcome to the basic calculator!" << endl;
    cout << "Please select calculation type:" << endl;
    cout << " (1) Addition" << endl << " (2) Subtraction" << endl;
    cout << " (3) Multiplication" << endl << " (4) Division" << endl;
    cout << " (5) Squares" << endl << " (6) Square Root" << endl;
    cout << " (7) Factorial" << endl;

    // Using %10 we can ensure we get a single digit and then check that value.
    cout << endl << "Input: ";
    cin >> selection % 10;

    /* Selection is reduced by one so values 1-7 are 0-6 and because it is unsigned, a zero selection is now at max value.
    This allows us to check the value of the 
    selection--
    
    if (selection < 7) {
      cout << "\nInput first number: ";
      cin >> num1;
      badInput = false;
    }
    else {
      cout << "Invalid selection"
    }
    if (selection < 4) {
      cout << "Input second number: ";
      cin >> num2;
    }
  }
  
  switch selection
    case 1:
      Addition(num1, num2)
    case 2:
      Subtraction(num1, num2)
    case 3:
      Multiplication(num1, num2)
    case 4:
      
    case 5:
      
    case 6:
      
    case:
      break
  
  return 0;
}
