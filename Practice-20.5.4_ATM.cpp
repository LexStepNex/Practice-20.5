#include <fstream>
#include <iostream>

void upload_to_file(int bills[], int total_money) {  // загрузка в файл
  std::ofstream atm("ATM.txt");
  for (int i = 0; i < 6; i++) {
    atm << bills[i] << ' ';
  }
  atm << total_money;
  atm.close();
}

void unload_from_file(int bills[], int& total_money) {  // выгрузка из файла
  std::ifstream atm("ATM.txt");
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
  int deposit_bills[6] = {0};

  do {
    for (int i = 0; i < 6; i++) {
      std::cout << "Enter the number of " << banknote_par(i)
                << " ruble banknotes: ";
      std::cin >> deposit_bills[i];
    }

    if (amount_bills(bills) + amount_bills(deposit_bills) > 1000) {
      std::cout << "The ATM cannot accept so many bills\n"
                << "Try again\n";
    }
  } while (amount_bills(bills) + amount_bills(deposit_bills) > 1000);

  for (int i = 0; i < 6; i++) {
    bills[i] += deposit_bills[i];
  }
}

void cash_withdrawal() {  // снятие наличных
}

bool valid_file_atm() {  // проверка наличия/валидности файла
  std::ifstream atm("ATM.txt");
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

  std::ifstream atm("ATM.txt");
  int bills[6] = {0};
  int total_money = 0;

  unload_from_file(bills, total_money);  // выгрузка из файла
  print_current(bills, total_money);
  std::cout << amount_bills(bills) << "\n";

  deposit_cash(bills);
  total_money = sum_money(bills);
  print_current(bills, total_money);

  std::cout << amount_bills(bills);
  atm.close();
}