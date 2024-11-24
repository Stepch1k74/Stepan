#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

// Структура для хранения курса валют
struct CurrencyConverter {
    unordered_map<string, double> rates;

    // Загрузка курсов из файла
    void loadRatesFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Ошибка открытия файла!" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            string from, to;
            double rate;
            stringstream ss(line);
            ss >> from >> to >> rate;

            // Заполняем курс для каждой валюты по отношению к рублю
            if (from != "RUB") {
                string key = from + to;
                rates[key] = rate;
                rates[to + from] = 1.0 / rate; // Обратный курс
            }

        }

        file.close();
    }

    // Конвертация одной валюты в другую
    double convert(const string& from, const string& to, double amount) {
        string key = from + to;
        if (rates.find(key) != rates.end()) {
            return amount * rates[key];
        }
        else {
            cout << "Курс для данной валюты не найден!" << endl;
            return -1;
        }
    }
};

int main() {

    setlocale(LC_ALL, "Russian");

    CurrencyConverter converter;

    // Загружаем курсы из файла
    converter.loadRatesFromFile("kurs.txt");

    // Переменные для ввода данных пользователем
    string fromCurrency, toCurrency;
    double amount;

    cout << "Добро пожаловать в конвертер валют NERAZVOD банка!" << endl;
    cout << "Доступные валюты: RUB (рубль), USD (доллар), EUR (евро), CNY (юань), BYN (белорусский рубль), KZT (тенге), GBP (фунт)" << endl;

    // Ввод валют и суммы для конвертации
    cout << "Введите валюту для конвертации (например, RUB): ";
    cin >> fromCurrency;

    cout << "Введите валюту, в которую хотите конвертировать (например, USD): ";
    cin >> toCurrency;

    cout << "Введите сумму для конвертации: ";
    cin >> amount;

    // Выполняем конвертацию
    double result = converter.convert(fromCurrency, toCurrency, amount);

    if (result != -1) {
        cout << amount << " " << fromCurrency << " = " << result << " " << toCurrency << endl;
    }

    return 0;
}
