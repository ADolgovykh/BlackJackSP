//blackjack
//main.cpp
//By: Anton Dolgovykh
//ICS4U



#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime> 

using namespace std;

int money, money1, choice, choice1, total, total1, n, counter2, y;
string name, choicee, line;
bool deck[52];
int currentCard;
int currentCardD;
int deckV[52];
bool gameCounter = true;
bool counter = true;
bool firstDeal = true;
int bet = 0;
int current = 0;
int x = 0;
bool options = true;

void checkCard() {
    //initializes random

    choice = rand() % (51); // random number between 0-51
    //cout << choice << endl;
    while (deck[choice] == true) { //checking if card has already been taken,
        choice = rand() % (51); //if so, picking another number.
    }
    deck[choice] = true; // Sets card value in boolean array to true

}

void dealD() {
    cout << "\nDealing to Dealer... " << endl;
    checkCard(); //picks and checks for an avaliable card
    cout << "Dealing Dealers Card #" << currentCardD << "... Value: " << deckV[choice] << endl;
    if (deckV[choice] == 0) {
        cout << "Dealer got an ace!" << endl;
        if (total1 < 11) {
            x = 11;
            deckV[choice] = x;
            cout << "Value: " << deckV[choice] << endl;
        } else {
            x = 1;
            deckV[choice] = x;
            cout << "Value: " << deckV[choice] << endl;
        }
    }

    total1 = total1 + deckV[choice];
    if (firstDeal == true) {
        checkCard();
        cout << "Dealing Dealers Card #1 (It is Hidden) \n" << endl;
        if (deckV[choice] == 0) {
            if (total1 < 11) {
                x = 11;
                deckV[choice] = x;
                cout << "Value: " << deckV[choice] << endl;
            } else {
                x = 1;
                deckV[choice] = x;
                cout << "Value: " << deckV[choice] << endl;
            }

        }
        total1 = total1 + deckV[choice];
    }
    if (firstDeal == true) {

        currentCardD = 1;
    }
    currentCardD = currentCardD + 1;
    firstDeal = false;

}

void deal() {
    checkCard(); //picks and checks for an avaliable card
    cout << "Dealing Card " << currentCard + 1 << "... Value: " << deckV[choice] << "\n" << endl;


    if (deckV[choice] == 0) {
        cout << "You have an ace!" << endl;
        cout << "Type (e) for 11, (o) for 1" << endl;
        cin >> choicee;
        cin.ignore();
        if (choicee == "e") {
            x = 11;
        }
        if (choicee == "o") {

            x = 1;
        }
        deckV[choice] = x;
        cout << "Value of Card: " << deckV[choice] << endl;
    }

    current = current + deckV[choice];
    if (currentCard != 0) {
        cout << "\nYOUR TOTAL IS: " << current << endl;
    }

    currentCard = currentCard + 1;


}

void initialDeal() {
    deal();
    deal();
}

void setValues() { //initializes the value of each cards.
    counter = true;
    firstDeal = true;
    current = 0;
    total1 = 0;
    x = 0;
    options = true;
    for (n = 0; n < 52; n++) {
        deck[n] = false;
    }
    for (n = 0; n < 4; n++) {
        deckV[n] = 2;
    }
    for (n = 4; n < 8; n++) {
        deckV[n] = 3;
    }
    for (n = 8; n < 12; n++) {
        deckV[n] = 4;
    }
    for (n = 12; n < 16; n++) {
        deckV[n] = 5;
    }
    for (n = 16; n < 20; n++) {
        deckV[n] = 6;
    }
    for (n = 20; n < 24; n++) {
        deckV[n] = 7;
    }
    for (n = 24; n < 28; n++) {
        deckV[n] = 8;
    }
    for (n = 28; n < 32; n++) {
        deckV[n] = 9;
    }
    for (n = 32; n < 48; n++) {
        deckV[n] = 10;
    }
    for (n = 48; n < 52; n++) {
        deckV[n] = x;
    }

}

void cardOptions() {
    while (options == true) {
        cout << "Options: " << endl;
        cout << "Type (s) to stay. Type (h) to hit" << endl;
        cin >> choicee;
        cin.ignore();
        if (choicee == "s") {

            options = false;
        }
        if (choicee == "h") {

            deal();
        }
        if (current > 21) {

            cout << "You Bust!\n " << endl;
            options = false;
            money = money - bet;
        }

    }
}

void compare() {
    cout << "Your Total: " << current << endl;
    cout << endl;
    cout << "Dealer's Total: " << total1 << endl;
    if (current > total1 && current < 21 || total1 > 21) {

        cout << "You Win! " << endl;
        money = money + bet;
    } else if (current == total1) {
        cout << "Tie! " << endl;


    } else if (current < total1 && total1 < 22) {
        cout << "You Lose! " << endl;
        money = money - bet;
    } else if (current == 21 && total1 != 21) {
        cout << "BLACK JAAACKKKKKKKKKKKKKKKKKKKKKKKKKKK" << endl;
        money = money + bet * 1.5;

    }
}

void dealer() {
    cout << endl;
    cout << "Dealer's Turn: " << endl;
    cout << endl;
    cout << "Dealer's Total: " << total1 << endl;
    while (total1 < 17) {
        dealD();
        cout << "Dealer's Total: " << total1 << "\n" << endl;

        if (total1 > 21) {
            cout << "Dealer Busts! \n" << endl;
        }
    }
}

int main() { //main.
    srand(time(NULL));
    fstream myfile;
    myfile.open("save.txt");
    if (myfile.is_open()) {
        while (myfile.good()) {
            getline(myfile, line);
            //cout << line << endl;
            istringstream convert(line);
            convert >> money;
        }
        myfile.close();
    }
    while (gameCounter == true) {
        setValues(); //sets the initial values
        cout << "\nYou have: " << money << " Dollars" << endl;
        if (money > 0) {
            cout << "How much would you like to bet?\n" << endl;
            cin >> bet;
            cin.ignore();
            if (bet > money) {
                cout << "Input a new amount..." << endl;
                cin >> bet;
                cin.ignore();
            }

            initialDeal(); //deals a card.
            dealD();
            cardOptions();
            if (current < 22) {
                dealer();
                compare();
            }
            cout << "You have: " << money << " Dollars" << endl;
            fstream myfile;
            myfile.open("save.txt");
            myfile << money << endl;
            myfile.close();
            cout << "\nWould you like to keep playing? (press any key)" << endl;
            cout << "To Quit: (q)\n" << endl;
            cin >> choicee;
            cin.ignore();
            if (choicee == "q") {
                gameCounter = false;
            }
        } else {
            cout << "You're out of money, the game will reset." << endl;
            fstream myfile;
            myfile.open("save.txt");
            myfile << "500" << endl;
            myfile.close();
            gameCounter = false;
        }

    }

    return 0; // program exits successfully

}






