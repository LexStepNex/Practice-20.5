#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

int main() {
  std::cout << "Pain random picture from 1 and 0\n";

  int height, width;
  std::cout << "Input width picture: ";
  std::cin >> width;
  std::cout << "Input height picture: ";
  std::cin >> height;

  std::ofstream randPic("Random picture.txt", std::ios::binary);

  std::srand(std::time(nullptr));

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      randPic << rand() % 2;
    }
    randPic << "\n";
  }

  std::cout << "Look at your picture in the file \"Random picture.txt\"";

  randPic.close();
}