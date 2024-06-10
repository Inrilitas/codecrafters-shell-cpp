#include <iostream>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // You can use print statements as follows for debugging, they'll be visible when running tests.
  // std::cout << "Logs from your program will appear here!\n";

  while(true){
      std::cout << "$ ";
      std::string input;
      std::getline(std::cin, input);
      if(input == "exit 0") return 0;
      std::cout << input + ": command not found\n";
  }
}
