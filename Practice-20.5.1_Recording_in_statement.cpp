#include <fstream>
#include <iostream>
#include <string>

bool dateControl(std::string date) {
  int sizeDateStr = date.length();
  int countDots = 0;
  int dotAfterDay, dotAfterMonth;

  for (int i = 0; i < sizeDateStr; i++) {
    if (!isdigit(date[i]) && date[i] != '.') {
      std::cerr << "The date must only contain numbers and dots\n";
      return false;
    }

    if (date[i] == '.') {
      countDots++;
    }

    if (countDots > 2) {
      std::cerr << "The date must be separated by two dots\n";
      return false;
    }

    if (countDots == 1 && date[i] == '.') {
      dotAfterDay = i;
    }

    if (countDots == 2 && date[i] == '.') {
      dotAfterMonth = i;
    }
  }

  if (countDots != 2) {
    std::cerr << "The date must be separated by TWO dots\n";
    return false;
  }

  if (dotAfterMonth == dotAfterDay + 1) {
    std::cerr << "You need to enter the month number between the points\n";
    return false;
  }

  int dd = stoi(date.substr(
      0, dotAfterDay));  // для разных форматов 01.01.2024 или 1.1.2024
  int mm =
      stoi(date.substr((dotAfterDay + 1), (dotAfterMonth - (dotAfterDay + 1))));
  int yyyy =
      stoi(date.substr((dotAfterMonth + 1), (sizeDateStr - dotAfterMonth)));

  if (1 > mm || mm > 12) {
    std::cerr << "The month must be from 1 to 12\n";
    return false;
  } else if (1 > dd || dd > 31) {
    std::cerr << "The day must be from 1 to 31\n";
    return false;
  } else if (yyyy < 0) {
    std::cerr << "Year must be greater than 0\n";
    return false;
  } else if (mm == 2) {
    if ((yyyy % 400 == 0) || (yyyy % 4 == 0 && yyyy % 100 != 0)) {
      if (dd > 29) {
        std::cerr << "In february " << yyyy << " year 29 days\n";
        return false;
      } else
        return true;
    } else {
      if (dd > 28) {
        std::cerr << "In february " << yyyy << " year 28 days\n";
        return false;
      } else
        return true;
    }
  } else if (mm == 4 || mm == 6 || mm == 9 || mm == 11) {
    if (dd > 30) {
      std::cerr << "This month has 30 days\n";
      return false;
    } else
      return true;
  } else {
    if (dd > 31) {
      std::cerr << "This month has 31 days\n";
      return false;
    } else
      return true;
  }
}

double moneyControl(std::string moneyStr) {
  int sizeMoneyStr = moneyStr.length();
  int countDot = 0;
  for (int i = 0; i < sizeMoneyStr; i++) {
    if (i == 0 && moneyStr[i] == '-') {
      std::cerr << "The monetary amount must be positive\n";
      return -1;
    }

    if (!std::isdigit(moneyStr[i]) && moneyStr[i] != '.') {
      std::cerr << "Error entering monetary amount\n";
      return -1;
    }
    if (moneyStr[i] == '.') {
      countDot++;
    }
    if (countDot > 1) {
      std::cerr << "There cannot be more than one dot in a monetary amount.\n";
      return -1;
    }
  }
  return stoi(moneyStr);
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

int main() {
  std::cout << "Fill out the payroll\n";

  std::ofstream statement("Statement.txt", std::ios::app);
  do {
    std::string name, surname, date, moneyStr;

    std::cout << "Input name and surname: ";
    std::cin >> name;
    statement << name << ' ';

    std::cout << "Input surname: ";
    std::cin >> surname;
    statement << surname << ' ';

    do {
      std::cout << "Input date (format dd.mm.yyyy): ";
      std::cin >> date;
      if (!dateControl) std::cerr << "Please, try again.\n";
    } while (!dateControl(date));
    statement << date << ' ';

    do {
      std::cout << "Enter payment: ";
      std::cin >> moneyStr;
      if (moneyControl(moneyStr) < 0) std::cerr << "Please, try again.\n";
    } while (moneyControl(moneyStr) < 0);

    double money = stod(moneyStr);
    statement.setf(std::ios::showpoint);
    statement.setf(std::ios::fixed);
    statement.precision(2);

    statement << money << " RUB\n";
  } while (repeat());
  
  std::cout << "Data sent to document Statement.txt\n\n";

  statement.close();
}