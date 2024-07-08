#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

void upload_to_file(int bills[], int total_money) {  // загрузка в файл
  std::ofstream atm("ATM.bin", std::ios::binary);
  for (int i = 0; i < 6; i++) {
    atm << bills[i] << ' ';
  }
  atm << total_money;
  atm.close();
}

void unload_from_file(int bills[], int& total_money) {  // выгрузка из файла
  std::ifstream atm("ATM.bin", std::ios::binary);
  for (int i = 0; i < 6; i++) {
    atm >> bills[i];
  }
  atm >> total_money;
  atm.close();
}

int banknote_par(int index) {  // номинал банкноты
  int denomination;
  int x = (index + 1);

  if (index > 2) x -= 3;

  if (x == 3) x = 5;

  if (index < 3)
    denomination = x * 100;
  else
    denomination = x * 1000;

  return denomination;
}

void print_current(int bills[], int total_money) {
  std::cout << "Current bills in ATM: \n";
  for (int i = 0, begin, x = 0, y = 1; i < 6; i++) {
    std::cout << banknote_par(i) << " ruble bills: " << bills[i] << "\n";
    if (x == 5) x = 0;
  }
  std::cout << "Total money amount: " << total_money << "\n";
}

int sum_money(int bills[]) {  // сумма денег
  int sum = 0;
  for (int i = 0, x = 0; i < 6; i++) {
    sum += bills[i] * banknote_par(i);
  }
  return sum;
}

int amount_bills(int bills[]) {  // сумма банкнот
  int sum = 0;
  for (int i = 0; i < 6; i++) {
    sum += bills[i];
  }
  return sum;
}

void deposit_cash(int bills[]) {  // внести наличные
  std::srand(std::time(nullptr));
  do {
    bills[rand() % 6]++;
  } while (amount_bills(bills) < 1000);

  std::cout << "The ATM is completely full\n\n";
}

bool valid_input_cash(std::string cash) {
  int lenCash = cash.length();
  for (int i = 0; i < lenCash; i++) {
    if (!isdigit(cash[i])) {
      std::cout << "Please enter the cash amount as a positive number, try again.\n";
      return false;
    }
  }

  if (stoi(cash) % 100 != 0) {
    std::cout << "Enter an amount that is a multiple of 100 and try again.\n";
    return false;
  }

  return true;
}

void cash_withdraw(int bills[], int total_money) {  // снятие наличных
  int bills_copy[6] = {0};
  std::string moneyStr;
  do {
    std::cout << "Enter the amount you want to withdraw: ";
    std::cin >> moneyStr;
  } while (!valid_input_cash(moneyStr));

  int money = stoi(moneyStr);
  if (money > total_money) {
    std::cout << "There is not enough money in the ATM\n\n";
    return;
  }
  for (int i = 5; i >= 0;) {
    if (bills_copy[i] < bills[i] && money >= banknote_par(i)) {
      bills_copy[i]++;
      money -= banknote_par(i);
    } else {
      i--;
    }
  }
  if (money != 0) {
    std::cout << "This amount cannot be withdrawn, there are not enough bills "
                 "in the ATM.\n\n";
    return;
  } else {
    for (int i = 0; i < 6; i++) {
      bills[i] -= bills_copy[i];
    }
  }
  std::cout << "The desired amount has been issued\n\n";
}

bool possibilities(int bills[], std::string answer) {
  if (answer != "+" && answer != "-") return false;

  if (answer == "+" && amount_bills(bills) >= 1000) {
    std::cout << "ATM is already full.\n\n";
    return false;
  }

  if (answer == "-" && amount_bills(bills) == 0) {
    std::cout << "Unfortunately, there is no money in the ATM.\n\n";
    return false;
  }
  return true;
}

bool valid_file_atm() {  // проверка наличия/валидности файла
  std::ifstream atm("ATM.bin");
  int element, countElement = 0;
  int bills[6] = {0};
  int total_money = 0;

  if (!atm.is_open()) {
    upload_to_file(bills, total_money);
    return true;
  }

  while (atm >> element) countElement++;
  if (countElement == 0) {
    upload_to_file(bills, total_money);
    return true;
  } else if (countElement != 7) {
    return false;
  }
  atm.close();
  return true;
}

std::string lower_case(std::string str) {
  int sizeStr = str.size();
  for (int i = 0; i < sizeStr; i++) {
    str[i] = std::tolower(str[i]);
  }
  return str;
}

bool repeat() {
  std::string answer;
  std::cout << "Want to add more data?\n";
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

// банкомат с помощью массива
//  i = 0 - 100
//  i = 1 - 200
//  i = 2 - 500
//  i = 3 - 1000
//  i = 4 - 2000
//  i = 5 - 5000

int main() {
  if (!valid_file_atm()) {
    std::cerr << "The ATM is faulty, call customer service.\n";
    return 0;
  }

  int bills[6] = {0};
  int total_money = 0;
  do {
    unload_from_file(bills, total_money);  // выгрузка из файла
    print_current(bills, total_money);

    std::string options;
    do {
      std::cout << "Enter + to fill the ATM with money\n";
      std::cout << "Enter – to withdraw money.\n";
      std::cout << "Input + or -: ";
      std::cin >> options;
    } while (!possibilities(bills, options));

    if (options == "+") deposit_cash(bills); //заполнение деньгами
    if (options == "-") cash_withdraw(bills, total_money); //Снятие наличных

    total_money = sum_money(bills);
    print_current(bills, total_money);

    upload_to_file(bills, total_money); // загрузка в файл
  } while (repeat());

  std::cout << "You have successfully exited the program. Have a good day.\n";
}