#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
#include <cpr/cpr.h>

int main() {
    std::string api_key = "xhVGNqvWyd8xbNRl7Ltg0rcCSSn6vl1kVYnJiWPn";
    cpr::Response r = cpr::Get(cpr::Url{"https://api.currencyapi.com/v3/latest?apikey=" + api_key + "&currencies=&base_currency=PLN"});
    if (r.status_code != 200) {
        std::cout << "Nie można połączyć się z api!\nSprawdź swoje połączenie internetowe." << std::endl;
        return -1;
    }

    json data = json::parse(r.text);

    while (true) {
        float amount;
        std::string currency;
        std::cout << "Wpisz ilość złotówek oraz skrót waluty do której ma być przekształcona: ";
        if (!(std::cin >> amount >> currency)) {
            // Clear the bad state
            std::cin.clear();
            // Ignore the rest of the line
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Wpisz poprawnie ilość złotówek!" << std::endl;
            continue;
        }
        // Transform all letters in currency to upper case
        std::transform(currency.begin(), currency.end(), currency.begin(), ::toupper);

        if (!data["data"].contains(currency)) {
            std::cout << "Nie istnieje taki skrót waluty!" << std::endl;
            std::cout << "Dostępne skróty walut to:";
            for (const auto& item : data["data"].items()) {
                std::cout << " " << item.key();
            }
            std::cout << std::endl;
        } else {
            float transformed_amount = amount * std::stof(data["data"][currency]["value"].dump());
            transformed_amount = floor(transformed_amount * 100) / 100;
            std::cout << transformed_amount << " " << currency << std::endl;
        }
        char choice;
        while (true) {
            std::cout << "Chcesz wykonać kolejne przekształcenie? [t/n]: ";
            std::cin >> choice;
            if (choice == 't') {
                break;
            } else if (choice == 'n') {
                return 0;
            } else {
                std::cout << "Błędna odpowiedź!" << std::endl;
            }
        }
        }
    return 0;
}
