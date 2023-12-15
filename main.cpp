#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

double getRandomNumber(double min, double max) {
    return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}

double crash() {
    return getRandomNumber(1.5, 3.0);
}

void saveBalance(double balance) {
    std::ofstream outFile("balance.txt");
    if (outFile.is_open()) {
        outFile << balance;
        outFile.close();
    }
    else {
        std::cerr << "Unable to save balance to file." << std::endl;
    }
}

double readBalance() {
    double balance = 100.0; // Default initial balance
    std::ifstream inFile("balance.txt");
    if (inFile.is_open()) {
        inFile >> balance;
        inFile.close();
    }
    return balance;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << "Welcome to Retro's Crash" << std::endl;

    double balance = readBalance(); // Load the saved balance

    while (balance > 0.0) {
        std::cout << "Current balance: $" << balance << std::endl;

        // Ask the player to place a bet
        double bet;
        std::cout << "Place your bet: $";
        std::cin >> bet;

        // Ensure the bet is positive and not greater than the current balance
        if (bet <= 0.0 || bet > balance) {
            std::cout << "Invalid bet amount. Please try again." << std::endl;
            continue;
        }

        // Simulate the crash point
        double crashPoint = crash();

        std::cout << "Crash point: " << crashPoint << "x" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Check if the player won or lost
        if (crashPoint >= 2.0) {
            // Player won
            std::cout << "Congratulations! You won $" << bet * (crashPoint - 1.0) << std::endl;
            balance += bet * (crashPoint - 1.0);
        }
        else {
            // Player lost
            std::cout << "Sorry, you lost $" << bet << std::endl;
            balance -= bet;
        }

        // Save the updated balance
        saveBalance(balance);

        // Ask if the player wants to play again
        char playAgain;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
        system("CLS");

        if (playAgain != 'y' && playAgain != 'Y') {
            break; // Exit the loop if the player doesn't want to play again
        }
    }

    std::cout << "Thank you for playing! Your final balance is: $" << balance << std::endl;

    return 0;
}