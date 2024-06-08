#include "../include/implements.hh"
#include "../include/result.hh"
#include <iostream>

template <typename U> ucpp::Result<int, int> divide(U a, U b) {
  if (b == 0) {
    return ucpp::Result<int, int>::Err(0);
  }
  return ucpp::Result<int, int>::Ok(a / b);
}

int main() {
  while (true) {
    // auto result = divide(10, 2);
    // if (result.is_err()) {
    //   std::cout << "Error: " << result.unwrap_err() << std::endl;
    // } else {
    //   std::cout << "Result: " << result.unwrap() << std::endl;
    // }

    std::string num1, num2;
    std::cout << "Enter a number: ";
    std::cin >> num1;
    if (num1 == "q") {
      break;
    }
    std::cout << "Enter a number: ";
    std::cin >> num2;

    try {
      auto result = divide(std::stof(num1), std::stof(num2));
      if (result.is_err()) {
        std::cout << "Error: " << result.unwrap_err() << std::endl;
      } else {
        std::cout << "Result: " << result.unwrap() << std::endl;
      }
    } catch (const std::invalid_argument &e) {
      std::cout << "Invalid argument" << std::endl;
    } catch (const std::out_of_range &e) {
      std::cout << "Out of range" << std::endl;
    }
  }
  return 0;
}