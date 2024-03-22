//  Asad Khurshid   22i-1585    PROJECT
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<time.h>
#include<iomanip>
#include<string>
using namespace std;

void fileToArray(string symbolName[][37], float stockPrice[][37]);
void copyArrayElements(float first[], float second[]);
void updatePrice(float stockPrice[][37]);
void displayLiveMarket(string symbolName[][37], float stockPrice[][37], string topSymbols[], int numberOfStocks);
void copyRows(float stockPrice[][37]);
void calculateTopSymbol(float stockPrice[][37], string topSymbols[], string symbolName[][37]);
void homeScreen(float stockPrice[][37], string topSymbols[], string symbolName[][37], int numberOfStocks);
void addMoney(float& balance);
void getUserInfo(string& name);
void showPortfolioScreen(string name, string symbolName[][37], float stockPrice[][37], string userStocks[], float buyPrice[][37], float accountBalance);
void addStock(string symbolName[][37], string userStocks[], float buyPrice[][37], float stockPrice[][37], float& accountBalance, int& numberOfStocks);
void removeStock(string userStocks[], float buyPrice[][37], float& accountBalance, float stockPrice[][37], string symbolName[][37], int& numberOfStocks);
void writeCompanies(string symbolName[][37], float stockPrice[][37]);
void withdrawMoney(float& accountBalance);

int main(){
    float stockPrice[6][37];
    string symbolName[2][37];
    string topSymbols[2];
    float accountBalance = 0;
    string name;
    string userStocks[37];
    float buyPrice[2][37];
    int numberOfStocks = 0;

    fileToArray(symbolName, stockPrice);
    copyRows(stockPrice);
    while (1){
        switch(cin.get()){
            case 'L':
                system("clear");
                homeScreen(stockPrice, topSymbols, symbolName, numberOfStocks);
                break;
            case 'M':
                system("clear");
                addMoney(accountBalance);
                system("clear");
                homeScreen(stockPrice, topSymbols, symbolName, numberOfStocks);
                break;
            case 'E':
                writeCompanies(symbolName, stockPrice);
                return 0;
            case 'P':
                system("clear");
                showPortfolioScreen("EHTISHAM", symbolName, stockPrice, userStocks, buyPrice, accountBalance);
                break;
            case 'A':
                system("clear");
                addStock(symbolName, userStocks, buyPrice, stockPrice, accountBalance, numberOfStocks);
                system("clear");
                showPortfolioScreen("EHTISHAM", symbolName, stockPrice, userStocks, buyPrice, accountBalance);
                break;
            case 'R':
                system("clear");
                removeStock(userStocks, buyPrice, accountBalance, stockPrice, symbolName, numberOfStocks);
                system("clear");
                showPortfolioScreen("EHTISHAM", symbolName, stockPrice, userStocks, buyPrice, accountBalance);
                break;
            case 'W':
                system("clear");
                withdrawMoney(accountBalance);
                system("clear");
                showPortfolioScreen("EHTISHAM", symbolName, stockPrice, userStocks, buyPrice, accountBalance);
        }
    }
}

void homeScreen(float stockPrice[][37], string topSymbols[], string symbolName[][37], int numberOfStocks){
    updatePrice(stockPrice);
    calculateTopSymbol(stockPrice, topSymbols, symbolName);
    displayLiveMarket(symbolName, stockPrice, topSymbols, numberOfStocks);
}

void addMoney(float& balance){
    float b;
    system("clear");
    cout << "Enter Amount you want to be added: ";
    cin >> b;
    balance += b;
    cout << "Money added successfully" << endl;
    cout << "Press any key to continue";
    cin.get();
    cin.get();
}

void fileToArray(string symbolName[][37], float stockPrice[][37]){
    int i = 0;
    string line;
    ifstream companies ("companies.txt"); 
    getline (companies, line);
    while (!companies.eof() ) {
        string symbol, name, price;
        getline(companies, symbol, ',');
        getline(companies, name, ',');
        getline(companies, price);
        if (symbol != "")
            symbolName[0][i] = symbol;
        if (name != "")
            symbolName[1][i] = name;
        if (price != "")
            stockPrice[0][i] = stof(price);
        i++;
    }
    companies.close();
}

void updatePrice(float stockPrice[][37]){
    srand(time(0));
    for (int i = 0; i < 37; i++){
        stockPrice[4][i] = stockPrice[1][i];
    }
    for (int i = 0; i < 37; i++){
        int change = rand() % 16;
        if (rand() % 2){
            if ((stockPrice[0][i]/(stockPrice[1][i] + (stockPrice[1][i]*(change / 100.0))))*100 >= 85 && (stockPrice[0][i]/(stockPrice[1][i] + (stockPrice[1][i]*(change / 100.0))))*100 <= 115){
                stockPrice[1][i] += (stockPrice[1][i]*(change / 100.0));
            }
        }
        else{
            if ((stockPrice[0][i]/(stockPrice[1][i] - (stockPrice[1][i]*(change / 100.0))))*100 >= 85 && (stockPrice[0][i]/(stockPrice[1][i] - (stockPrice[1][i]*(change / 100.0))))*100 <= 115){
                stockPrice[1][i] -= (stockPrice[1][i]*(change / 100.0));
            }
        }
        if (stockPrice[1][i] > stockPrice[2][i]){
            stockPrice[2][i] = stockPrice[1][i];
        }  
        if(stockPrice[1][i] < stockPrice[3][i]){
            stockPrice[3][i] = stockPrice[1][i];
        }
    }
}

void displayLiveMarket(string symbolName[][37], float stockPrice[][37], string topSymbols[], int numberOfStocks){
    cout << right << "\033[46m" << setw(70) << "Karachi Stock Market (Live)" << setw(55) << " " << "\033[0m" << endl;
    cout << left << "\033[33m" << setw(20) << "Show Updates: \u21B5" << setw(20) << "Show Portfolio: P" << setw(20) << "Add Stock: A" << setw(20) << "Remove Stock: R" << setw(30) << "Add Money to Account: M" << setw(20) << "Exit: E" << "\033[0m" << endl;
    cout << left << setw(30) << "Stocks" << setw(50) << "Company Name" << setw(12) << "Prev Price" << setw(15) << "Curr Price" << setw(10) << "High" << setw(10) << "Low" << endl;
    for (int i = 0; i < 37; i++){
        cout << left << setw(30) << symbolName[0][i] << setw(50) << symbolName[1][i] << setw(12) << stockPrice[4][i];
        if (stockPrice[1][i] < stockPrice[4][i]){
            cout << fixed << "\033[31m" << setprecision(2) << setw(8) << stockPrice[1][i] << setw(9) << "\u2193" << "\033[0m";
        }
        else if(stockPrice[1][i] > stockPrice[4][i]){
            cout << fixed <<  "\033[32m" << setprecision(2) << setw(8) << stockPrice[1][i] << setw(9) << "\u2191" << "\033[0m";
        }
        else {
            cout << left << "\033[0m" << setw(15) << stockPrice[1][i];
        }
        cout << fixed << setw(10) << setprecision(2) << stockPrice[2][i] << setw(10) << setprecision(2) << stockPrice[3][i] << endl;
    }
    cout << endl;
    cout << left << setw(30) << "Total shares traded today" << numberOfStocks << endl;
    cout << left << "\033[32m" << setw(30) << "Top \% advancer symbol" << topSymbols[0] << "\033[0m" << endl;
    cout << left << "\033[31m" << setw(30) << "Top \% decliner symbol" << topSymbols[1] << "\033[0m" << endl;

}

void copyRows(float stockPrice[][37]){
    for (int i = 0; i < 37; i++){
        stockPrice[1][i] = stockPrice[0][i];
        stockPrice[2][i] = stockPrice[0][i];
        stockPrice[3][i] = stockPrice[0][i];
        stockPrice[4][i] = stockPrice[0][i];
    }
}

void calculateTopSymbol(float stockPrice[][37], string topSymbols[], string symbolName[][37]){
    for (int i = 0; i < 37; i++){
        stockPrice[5][i] = (stockPrice[1][i]/stockPrice[0][i]) * 100;
    }
    int advancer = stockPrice[5][0];
    int advancerIndex = 0;
    for (int i = 0; i < 37; i++){
        if (stockPrice[5][i] > advancer){
            advancer = stockPrice[5][i];
            advancerIndex = i;
        }
    }
    int decliner = stockPrice[5][0];
    int decllinerIndex = 0;
    for (int i = 0; i < 37; i++){
        if (stockPrice[5][i] < decliner){
            decliner = stockPrice[5][i];
            decllinerIndex = i;
        }
    }
    topSymbols[0] = symbolName[0][advancerIndex];
    topSymbols[1] = symbolName[0][decllinerIndex];
}

void getUserInfo(string& name){
    cout << "Enter Your Name: ";
    cin >> name;
}

void showPortfolioScreen(string name, string symbolName[][37], float stockPrice[][37], string userStocks[], float buyPrice[][37], float accountBalance){
    float todayGainLoss = 0;
    float prevBalance = accountBalance;
    float newBalance = accountBalance;
    cout << right << "\033[46m" << setw(55) << "Portfolio owner: " << name << "(Live)" << setw(52) << " " << "\033[0m" << endl;
    cout << left << "\033[33m" << setw(20) << "Show Updates: \u21B5" << setw(20) << "Live Market: L" << setw(20) << "Add Stock: A" << setw(20) << "Remove Stock: R" << setw(30) << "Add Money to Account: M" << setw(20) << "Withdraw money: W" << "\033[0m" << endl;
    cout << setw(20) << "Stock" << setw(45) << "Company Name" << setw(10) << "Shares" << setw(10) << "Current" << setw(10) << "Previous" << setw(16) << "Gain/Loss" << setw(10) << "High" << setw(10) << "Low" << endl;
    for (int i = 0; userStocks[i] != ""; i++){
        int k = 0;
        for (k; k < 37; k++){
            if (userStocks[i] == symbolName[0][k]){
                break;
            }
        }
        cout << setw(20) << userStocks[i] << setw(45) << symbolName[1][k] << setw(10) << buyPrice[1][i] << setw(10) << stockPrice[1][k] << setw(10) << buyPrice[0][i];
        if ((stockPrice[1][k] - buyPrice[0][i]) < 0){
            cout << "\033[31m" << setw(16) << (stockPrice[1][k] - buyPrice[0][i])*buyPrice[1][i] << "\033[0m";
        }
        else if ((stockPrice[1][k] - buyPrice[0][i]) > 0){
            cout << "\033[32m" << "+" << setw(15) << (stockPrice[1][k] - buyPrice[0][i])*buyPrice[1][i] << "\033[0m";
        }
        else{
            cout << setw(16) << (stockPrice[1][k] - buyPrice[0][i])*buyPrice[1][i];
        }
        cout << setw(10) << stockPrice[2][k] << setw(10) << stockPrice[3][k] << endl;
        todayGainLoss += (stockPrice[1][k] - buyPrice[0][i])*buyPrice[1][i];
        prevBalance += buyPrice[0][i]*buyPrice[1][i];
        newBalance += buyPrice[1][i]*stockPrice[1][k];
    }
    if (todayGainLoss > 0){
        cout << setw(95) << "Today's Gain or Loss (Rs.) " << "\033[32m" << "+" << todayGainLoss << "\033[0m" << endl;
    }
    else if (todayGainLoss < 0){
        cout << setw(95) << "Today's Gain or Loss (Rs.) " << "\033[31m" << todayGainLoss << "\033[0m" << endl;
    }
    else {
        cout << setw(95) << "Today's Gain or Loss (Rs.) " << todayGainLoss << endl;
    }
    if (prevBalance > 0){
        cout << setw(95) << "Previous Balance (Rs.) " << "\033[32m" << "+" << prevBalance << "\033[0m" << endl;
    }
    else if (prevBalance < 0){
        cout << setw(95) << "Previous Balance (Rs.) " << "\033[31m" << prevBalance << "\033[0m" << endl;
    }
    else {
        cout << setw(95) << "Previous Balance (Rs.) " << prevBalance << endl;
    }
    if (newBalance > 0){
        cout << setw(95) << "New Balance (Rs.) " << "\033[32m" << "+" << newBalance << "\033[0m" << endl;
    }
    else if (newBalance < 0){
        cout << setw(95) << "New Balance (Rs.) " << "\033[31m" << newBalance << "\033[0m" << endl;
    }
    else {
        cout << setw(95) << "New Balance (Rs.) " << newBalance << endl;
    }

}

void addStock(string symbolName[][37], string userStocks[], float buyPrice[][37], float stockPrice[][37], float& accountBlanace, int& numberOfStocks){
    string input;
    float quantity;
    cout << "Enter The Symbol Of The Stock You want to buy: ";
    cin >> input;
    cout << "Number of Stocks: ";
    cin >> quantity;
    int i = 0;
    for (i; i < 37; i++){
        if (symbolName[0][i] == input){
            break;
        }
        if (i == 37){
            i++;
        }
    }
    if (i == 38){
        system("clear");
        cout << "Stock Not Found" << endl;
        cout << "Press any key to continue";
        cin.get();
        cin.get();
    }
    else{
        if (quantity*stockPrice[1][i] > accountBlanace){
            cout << "INSUFFICIENT FUNDS" << endl;
            cout << "Enter any key to continue";
            cin.get();
            cin.get();
        }
        else {
            accountBlanace -= quantity*stockPrice[1][i];
            if (!(quantity == 0)){
                for (int k = 0; k < 37; k++){
                    if (userStocks[k] == ""){
                        userStocks[k] = input;
                        buyPrice[0][k] = stockPrice[1][i];
                        buyPrice[1][k] = quantity;
                        numberOfStocks++;
                        cout << "Stock Added Successfully" << endl;
                        cout << "Press any key to continue";
                        cin.get();
                        cin.get();
                        break;
                    }
                }
            }
        }
    }
}

void removeStock(string userStocks[], float buyPrice[][37], float& accountBalance, float stockPrice[][37], string symbolName[][37], int& numberOfStocks){
    string stock;
    cout << "Enter Stock You want to remove: ";
    cin >> stock;
    bool isStock = false;
    for (int i = 0; i < 37; i++){
        if (userStocks[i] == stock){
            isStock = true;
        }
    }
    if (isStock){
        int i;
        for (i = 0; i < 37; i++){
            if (userStocks[i] == stock){
                break;
            }
        }
        int k;
        for (k = 0; k < 37; k++){
            if (symbolName[0][k] == stock){
                break;
            }
        }
        accountBalance += buyPrice[1][i] * stockPrice[1][k];
        for (int j = i; j < 37; j++){
            userStocks[j] = userStocks[j+1];
            buyPrice[0][j] = buyPrice[0][j+1];
            buyPrice[1][j] = buyPrice[1][j+1];
        }
        numberOfStocks++;
        cout << "Stock Removed Successfully" << endl;
        cout << "Press any Key to continue.";
        cin.get();
        cin.get();
    }
    else{
        cout << "Stock Not Found" << endl;
        cout << "Press any Key to continue.";
        cin.get();
        cin.get();
    }
}

void writeCompanies(string symbolName[][37], float stockPrice[][37]){
    ofstream file("companies.txt");
    file << "Symbol,Company Name,Stock Price\n";
    for (int i = 0; i < 37; i++){
        file << symbolName[0][i] << "," << symbolName[1][i] << "," << stockPrice[1][i] << "\n";
    }
    file.close();
}

void withdrawMoney(float& accountBalance){
    float input;
    cout << "Enter the Money You want to withdraw: ";
    cin >> input;
    if (input < accountBalance){
        accountBalance -= input;
        cout << "Withdrawl Successful" << endl;
        cout << "Press any key to continue.";
        cin.get();
        cin.get();
    }
    else {
        cout << "INSUFICIENT FUNDS!\nPress any key to contunue!";
        cin.get();
        cin.get();
    }
}