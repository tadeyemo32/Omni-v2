#include <iostream>
#include <http/httplib.h>
#include <nlohmann/json.hpp>
#include "client.h"
#include "client_logger.h"

using json = nlohmann::json;

bool isRunning = true;
void line() { std::cout << "=============================================\n"; }
void printHeader(const std::string& title) {
    line();
    std::cout << "[INFO] " << title << "\n";
    line();
}

void printMenu() {
    printHeader("Welcome to Omni");
    std::cout<<"1.";
    std::cout<<"2. Check Health ";
    std::cout << "3. Exit\n";
    line();
    std::cout << "Select option: ";
}

int main() {
           

        printMenu();
    while (isRunning){
    


    }
        

    return 0;
}
