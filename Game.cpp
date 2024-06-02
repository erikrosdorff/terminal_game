#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

class Weapons {
public:
    string name;
    string type;
    string description;
    int damage;
    float defence;
    int cost;

    Weapons(const string& name, const string& type, const string& description, 
            int damage, float defence, int cost)
        : name(name), type(type), description(description), 
          damage(damage), defence(defence), cost(cost) {}

    void displayStats() const {
        cout << "\nName: " << name << endl;
        cout << "Category: " << type << endl;
        cout << "Description: " << description << endl;
        cout << "Damage: " << damage << endl;
        cout << "Defence: " << defence << endl;
        cout << "Cost: " << cost << endl;
    }
};

class Player {
private:
    int number;
    string surname;
    string first_name;
    int points;
    int birth_year;
    int attack_power;
    vector<Weapons> ownedWeapons;
    Weapons* equippedWeapon;

public:
    Player(int num, string sur, string fname, int yr, int ap)
        : number(num), surname(sur), first_name(fname), 
          points(100), birth_year(yr), attack_power(ap),
          equippedWeapon(nullptr) {}  // Initialize equippedWeapon to nullptr 

    ~Player() {
        delete equippedWeapon; // Deallocate memory
        equippedWeapon = nullptr;  // Assign nullptr 
    }

    string getSurname() const { return surname; }
    int getPoints() const { return points; }
    int getNumber() const { return number; }

    void attack(Player& target) {
        int totalDamage = this->attack_power;
        if (this->equippedWeapon != nullptr) {
            totalDamage += this->equippedWeapon->damage;
        }

        target.points -= totalDamage;
        cout << this->surname << " attacks " << target.surname 
             << ", " << target.surname << " loses " 
             << totalDamage << " health points!\n";
    }

    bool buyWeapon(const Weapons& weapon) {
        if (points >= weapon.cost) {
            points -= weapon.cost;
            ownedWeapons.push_back(weapon);
            return true;
        }
        return false;
    }

    void equipWeapon(Weapons* new_weapon) {
        delete equippedWeapon;  // if there was a weapon equipped before, release old memory
        equippedWeapon = new_weapon;  // point equippedWeapon to the new Weapon
    }
};

class CombatGame {
private:
    vector<Player> players;
    vector<Weapons> availableWeapons;

public:
    void createPlayer(int num, string sur, string fname, int yr, int ap) {
        players.push_back(Player(num, sur, fname, yr, ap));
    }

void initShop() {
    availableWeapons.push_back(Weapons("Divide by Zero", "Now I am Death: Destroyer of worlds", 
                                        "I don't mean to sound like a conspiracy theorist but come closer... *We're living in a program* No one has ever tried to use this weapon but legend has it that it will destroy everything in the simulation. Use it wisely but remember No One will win!", 
                                        0/0, 1000, 0/0)); //breaks the code
    availableWeapons.push_back(Weapons("Sword", "Meleweapon", "I mean... you know.... a sword", 35, 20, 20));
    availableWeapons.push_back(Weapons("Shield", "Meleweapon", "Pretty strong it will keep you safe! You can try to hit someone with it, but it doesn't really do much damage", 3, 10, 50));
    availableWeapons.push_back(Weapons("Stick", "'Meleweapon'", "It may break, but hey it is something", 8, 2, 6));
    availableWeapons.push_back(Weapons("TurtleShell", "Earth", "Good for cheap protection.", 2, 9, 8));
    availableWeapons.push_back(Weapons("Rock", "Earth", "Earth made object of millions of years of compression", 16, 10, 2));
    availableWeapons.push_back(Weapons("Spear", "Mideavil", "A strong weapon that can break through a lot of things", 45, 40, 9));
    availableWeapons.push_back(Weapons("Gun", "American", "Good ol' Cowboy Gun. Magically has endless bullets in this version", 100, 150, 0));
    availableWeapons.push_back(Weapons("Armor", "Helpful for defence", "Great defence", 0, 150, 150));
}

    void viewShop() {
        for (const Weapons& weapon : availableWeapons) {
            weapon.displayStats();
        }
    }
    
    void displayPlayers(int currentPlayer) {
    cout << "Available players to battle: \n";
    for (const Player& player : players) {
        if (player.getNumber() != currentPlayer) {
            cout << "Player number: " << player.getNumber() << ", Name: " <<
                    player.getSurname() << ", Points: " << player.getPoints() << endl;
        }
    }
}
    
    bool buyFromShop(int playerNum, int weaponIndex) {
        if (weaponIndex >= 0 && weaponIndex < availableWeapons.size()) {
            Player* player = getPlayerByNumber(playerNum);
            if (player != nullptr) {
                return player->buyWeapon(availableWeapons[weaponIndex]);
            }
        }
        return false;
    }

    size_t getPlayersCount() const { return players.size(); }

    size_t getWeaponsCount() const { return availableWeapons.size(); }

    void engageInBattle(int playerNum1, int playerNum2) {
        Player* player1 = getPlayerByNumber(playerNum1);
        Player* player2 = getPlayerByNumber(playerNum2);
        if (player1 != nullptr && player2 != nullptr) {
            player1->attack(*player2);
            if (player2->getPoints() > 0) {
                player2->attack(*player1);
            }

            if (player1->getPoints() > player2->getPoints()) {
                cout << player1->getSurname() << " wins!\n";
            } else if (player2->getPoints() > player1->getPoints()) {
                cout << player2->getSurname() << " wins!\n";
            } else {
                cout << "It's a tie!\n";
            }
        }
    }

private:
    Player* getPlayerByNumber(int playerNum) {
        for (Player& player : players) {
            if (player.getNumber() == playerNum) {
                return &player;
            }
        }
        return nullptr;
    }
};


int main() {
    CombatGame game;
    game.initShop(); 
    
    int choice = 0;
    bool isLoggedIn = false; 
    std::string name, surname;
    int birth_year;

    while(choice != 4) {
        std::cout << "\nWelcome to the Combat Game";
        std::cout << "\n1. Create Profile";
        std::cout << "\n2. Engage in Battle";
        std::cout << "\n3. Shop for Weapons";
        std::cout << "\n4. Quit";
        std::cout << "\nEnter your choice: ";

        std::cin >> choice;
switch(choice) {
    case 1: {
        std::cout << "\nEnter First Name:";
        std::cin >> name; 
        std::cout << "\nEnter Surname:";
        std::cin >> surname; 
        std::cout << "\nEnter Birth Year:";
        std::cin >> birth_year; 
        int attack_power;
        std::cout << "\nEnter attack power:";
        std::cin >> attack_power; 

        game.createPlayer(game.getPlayersCount() + 1, surname, name, birth_year, attack_power);

        // Added code for creating a random player
        // Change the range of rand() % 33 and rand() % 101 as per your game requirements
        std::string random_name = "Player" + std::to_string(game.getPlayersCount() + 1);
        int random_year = rand() % 33 + 1985; // Random year between 1985 and 2018
        int random_attack_power = rand() % 101; // Random attack power between 0 and 100
        game.createPlayer(game.getPlayersCount() + 1, "RandomSurname", random_name, random_year, random_attack_power);
        
        isLoggedIn = true; 
        break;
}
case 2: {
    if (!isLoggedIn) {
        std::cout << "Please log in to engage in a battle.\n";
        break;
    }
    game.displayPlayers(1); // Assuming the current player's number is 1
    int opponentNum;
    std::cout << "Enter the number of the player you want to battle:";
    std::cin >> opponentNum;
    game.engageInBattle(1, opponentNum); // Assuming the current player's number is 1
    break;
}
            case 3: {
                if (!isLoggedIn) {
                    std::cout << "Please create profile to access the shop.\n";
                    break;
                }
                std::cout << "\nAvailable weapons:\n";
                game.viewShop();
    
                int weaponNum;
                std::cout << "\nEnter the index of weapon you want to buy (1 - " << game.getWeaponsCount() << "):";
                std::cin >> weaponNum;
                if(game.buyFromShop(1, weaponNum - 1)) { // Adjusted to 0-based index
                std::cout << "Purchase successful.\n";
                } else {
                    std::cout << "Purchase failed.\n";
                }
                break;
            }
            case 4:
                break;
            default:
                std::cout << "Invalid option, please try again.\n";
                break;
        }
    }
    
    return 0;
}
