#include <fstream>
#include <iostream>

std::string lower_case(std::string str) {
  int sizeStr = str.size();
  for (int i = 0; i < sizeStr; i++) {
    str[i] = std::tolower(str[i]);
  }
  return str;
}

void fish_in_bucket(std::string fish) {
  std::ofstream basket("basket.txt", std::ios::app);
  basket << fish << ' ';
  basket.close();
}

void remove_fish_from_river(int positionFish, int sizeWord) {
  std::fstream riverWrite("river.txt");
  riverWrite.seekp(positionFish);

  for (int i = 0; i <= sizeWord; i++) {
    riverWrite << ' ';
  }
  
  riverWrite.close();
}

bool repeat() {
  std::string answer;
  std::cout << "Shall we continue fishing??\n";
  do {
    std::cout << "Input \"yes\" or \"no\": ";
    std::cin >> answer;
    answer = lower_case(answer);
  } while (answer != "yes" && answer != "no");

  if (answer == "yes")
    return true;
  else
    return false;
}

void space_at_end() {
  std::ifstream river("river.txt", std::ios::ate | std::ios::binary);

  if (!river.is_open()) {
    return;
  }

  int lastSignPos = river.tellg();
  lastSignPos--;

  char lastSign[1];

  river.seekg(lastSignPos);
  river.read(lastSign, 1);

  river.close();

  if (lastSign[0] != ' ') {
    std::ofstream add_space("river.txt", std::ios::app);
    add_space << ' ';
    add_space.close();
  }
}

int main() {
  space_at_end();
  int countFish = 0;

  do {
    std::ifstream river("river.txt", std::ios::binary);
    
    if (!river.is_open()) {
      std::cerr << "File \"river.txt\" not found\n";
      return 0;
    }

    std::string fish;
    std::cout << "Input type of fish: ";
    std::cin >> fish;
    fish = lower_case(fish);

    std::string fish_in_river = "";
    int wordPosition = river.tellg();
    while (river >> fish_in_river && fish != fish_in_river);

    int sizeWord = fish.length();
    wordPosition = river.tellg();
    wordPosition -= sizeWord;

    if (fish_in_river == fish) {
      fish_in_bucket(fish);

      remove_fish_from_river(wordPosition, sizeWord);
      countFish++;
    } else {
      std::cout << "There is no such fish in the river\n";
    }
    river.close();
  } while (repeat());

  std::cout << "Total fish caught on this attempt: " << countFish << std::endl;
}