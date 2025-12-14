#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <cmath>
#include "TextTable.h"
using namespace std;

bool chance(double percentage) {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen) < percentage;
}

int randomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

class Magic;
class Character;
class Hero;
class Hero_Archer;
class Hero_Mage;
class Enemy;
class Enemy_Melee;
class Enemy_Archer;
class Enemy_Mage;
class Shop;
class Game;
class BattleField;

void displayData(Hero* hero);

class Magic {
    private:
    int manaPoints;
    int totalManaPoints;
    public:
    Magic(): manaPoints(60), totalManaPoints(60) {
    }
    Magic(int v1): manaPoints(v1), totalManaPoints(v1) {
    }
    ~Magic() {
    }
    bool useMana() {
        if (manaPoints >= 15) {
            manaPoints -= 15;
            return true;
        } else {
            manaPoints += 10;
            return false;
        }
    }
};

class Character {
    private:
    string name;
    string type;
    int healthPoints;
    int totalHealthPoints;
    int damage;
    int critDamage;
    double critChance;
    int wallet;
    bool isDead;
    public:
    Character() {
    }
    Character(string type, int ID) {
        if (type == "Enemy Melee") {
            this->name = to_string(ID);
            this->type = type;
            totalHealthPoints = 120;
            healthPoints = totalHealthPoints;
            damage = 20;
            critDamage = 35;
            critChance = 0.05;
            wallet = 0;
            isDead = false;
        } else if (type == "Enemy Archer") {
            this->name = to_string(ID);
            this->type = type;
            totalHealthPoints = 90;
            healthPoints = totalHealthPoints;
            damage = 10;
            critDamage = 20;
            critChance = 0.05;
            wallet = 0;
            isDead = false;
        } else if (type == "Enemy Mage") {
            this->name = to_string(ID);
            this->type = type;
            totalHealthPoints = 120;
            healthPoints = totalHealthPoints;
            damage = 15;
            critDamage = 30;
            critChance = 0.10;
            wallet = 0;
            isDead = false;
        }
    }
    Character(string name, string type) {
        if (type == "Hero Archer") {
            this->name = name;
            this->type = type;
            totalHealthPoints = 100;
            healthPoints = totalHealthPoints;
            damage = 50;
            critDamage = 70;
            critChance = 0.30;
            wallet = 2000;
            isDead = false;
        } else if (type == "Hero Mage") {
            this->name = name;
            this->type = type;
            totalHealthPoints = 85;
            healthPoints = totalHealthPoints;
            damage = 60;
            critDamage = 80;
            critChance = 0.30;
            wallet = 2000;
            isDead = false;
        }
    }
    virtual ~Character() {
    }
    bool isAlive() {
        return !isDead;
    }
    virtual void takeDamage(int value) {
        healthPoints = max(healthPoints - value, 0);
        if (healthPoints == 0) {
            isDead = true;
        }
    }
    int getDamage() {
        return damage;
    }
    virtual void attack(Character& target) = 0;
    void reward(int amount) {
        wallet += amount;
    }
    double getCritChance() {
        return critChance;
    }
    int getCritDamage() {
        return critDamage;
    }
    int getHealthPoints() {
        return healthPoints;
    }
    int getTotalHealthPoints() {
        return totalHealthPoints;
    }
    int getWallet() {
        return wallet;
    }
    int increaseHealthPoints(int amount) {
        int value = min (amount, totalHealthPoints-healthPoints);
        healthPoints = min(healthPoints + amount, totalHealthPoints);
        return value;
    }
    void reduceHealthPoints(int value) {
        healthPoints = max(healthPoints - value, 0);
        if (healthPoints == 0) {
            isDead = true;
        }
    }
    void increaseTotalHealthPoints(int amount) {
        totalHealthPoints += amount;
    }
    bool canBuyItem(int price) {
        if (wallet >= price) {
            wallet -= price;
            return true;
        } else {
            return false;
        }
    }
    void increaseDamage(int amount) {
        damage += amount;
    }
    void increaseCritDamage(int amount) {
        critDamage += amount;
    }
    void increaseCritChance(double amount) {
        critChance = min(critChance + amount, 0.6);
    }
    string getType() {
        return type;
    }
    string getName() {
        return name;
    }
    void setName(string n) {
        name = n;
    }
    void setType(string t) {
        type = t;
    }
    void setHealthPoints(int value) {
        healthPoints = value;
    }
    void setTotalHealthPoints(int value) {
        totalHealthPoints = value;

    }
    void setDamage(int value) {
        damage = value;
    }
    void setCritDamage(int value) {
        critDamage = value;
    }
    void setCritChance(double value) {
        critChance = value;
    }
    void setWallet(int value) {
        wallet = value;
    }
    void setIsDead(bool state) {
        isDead = state;
    }
    friend ostream& operator<<(ostream& os, const Character& c);
};

ostream& operator<<(ostream& os, const Character& c) {
    os << "    HealthPoints: " << c.healthPoints << "/" << c.totalHealthPoints << endl;
    os << "    Damage: " << c.damage << endl;
    os << "    CritDamage: " << c.critDamage << endl;
    os << "    CritChance: " << c.critChance << endl;
    os << "    Wallet: " << c.wallet << " coins" << endl;
    return os;
}

class Skills {
    private:
    double evasionChance;
    double lifeSteal;
    double defence;
    double looting;
    public:
    Skills() {
    }
    Skills(string type) {
        if (type == "Hero Archer" || type == "Hero Mage") {
            evasionChance = 0;
            lifeSteal = 0;
            defence = 0;
            looting = 0;
        }
    }
    ~Skills() {
    }
    double getEvasionChance() {
        return evasionChance;
    }
    double getLifesteal() {
        return lifeSteal;
    }
    double getDefence() {
        return defence;
    }
    double getLooting() {
        return looting;
    }
    void increaseEvasionChance(double amount) {
        evasionChance = min(evasionChance + amount, 0.6);
    }
    void increaseLifesteal(double amount) {
        lifeSteal = min(lifeSteal + amount, 0.7);
    }
    void increaseDefence(double amount) {
        defence = min(defence + amount, 0.6);
    }
    void increaseLooting(double amount) {
        looting = min(looting + amount, 1.0);
    }
    void setEvasionChance(double value) {
        evasionChance = value;
    }
    void setLifeSteal(double value) {
        lifeSteal = value;
    }
    void setDefence(double value) {
        defence = value;
    }
    void setLooting(double value) {
        looting = value;
    }
};

class temp: public Magic {};
class Hero: public Character, public Skills {
    public:
    Hero() {
    }
    Hero(string name, string type): Character(name, type), Skills(type) {
    }
    ~Hero() {
    }
    void takeDamage(int value) override {
        if (chance(getEvasionChance())) {
            cout << "Attack Evaded!" << endl;
        } else {
            if (getDefence()) {
                value *= (1 - getDefence());
                cout << "Damage to Hero was reduced by " << getDefence() * 100 << "%" << endl;
            }
            reduceHealthPoints(value);
        }
    }
    friend class Shop;
    void operator++(int) {
        increaseHealthPoints(30);
        increaseTotalHealthPoints(30);
        increaseDamage(20);
        increaseCritDamage(30);
        increaseCritChance(0.05);
        increaseEvasionChance(0.05);
        increaseLifesteal(0.05);
        increaseDefence(0.05);
        increaseLooting(0.05);
    }
};

class Hero_Archer: public Hero {
    public:
    Hero_Archer() {
    }
    Hero_Archer(string name): Hero(name, "Hero Archer") {
    }
    Hero_Archer(Hero* h): Hero(h->getName(), "Hero Archer") {}
    ~Hero_Archer() {
    }
    void attack(Character& target) override {
        if (chance(getCritChance())) {
            target.takeDamage(getCritDamage());
            cout << "Hero Attacked An Enemy With Crit Shot dealing " << getCritDamage() << " Damage." << endl;
        } else {
            cout << "Hero Attacked An Enemy Dealing " << getDamage() << " Damage." << endl;
            target.takeDamage(getDamage());
        }
    }
};

class Hero_Mage: public Hero, public temp {
    public:
    Hero_Mage() {
    }
    Hero_Mage(string name): Hero(name, "Hero Mage") {
    }
    Hero_Mage(Hero* h): Hero(h->getName(), "Hero Mage") {}
    ~Hero_Mage() {
    }
    void attack(Character& target) override {
        int damageIncrease = 0;
        if (useMana()) {
            damageIncrease = 10;
        } else {
        }
        if (chance(getCritChance())) {
            cout << "Hero Attacked An Enemy With Crit Shot dealing " << getCritDamage() + damageIncrease << " Damage." << endl;
            target.takeDamage(getCritDamage() + damageIncrease);
        } else {
            cout << "Hero Attacked An Enemy Dealing " << getDamage() + damageIncrease << " Damage." << endl;
            target.takeDamage(getDamage() + damageIncrease);
        }
    }
};

class Enemy: public Character {
    static int count;
    static int kills;
    int enemyID;
    int laneNumber;
    int columnNumber;
    public:
    Enemy() {
    }
    Enemy(string type, int laneNumber, int columnNumber):Character(type, ++count) {
        enemyID = count;
        this->laneNumber = laneNumber;
        this->columnNumber = columnNumber;
    }
    ~Enemy() {
        kills++;
    }
    int getLaneNumber() {
        return laneNumber;
    }
    int getColumnNumber() {
        return columnNumber;
    }
    void moveForward() {
        columnNumber--;
    }
    static int getEnemyCount() {
        return count;
    }
    static int getKillCount() {
        return kills;
    }
};

class Enemy_Melee: public Enemy {
    public:
    Enemy_Melee() {
    }
    Enemy_Melee(int laneNumber, int columnNumber): Enemy("Enemy Melee", laneNumber, columnNumber) {
    }
    ~Enemy_Melee() {
    }
    void attack(Character& target) override {

        if (!getColumnNumber()) {
            if (chance(getCritChance())) {
                target.takeDamage(getCritDamage());
                cout << "Melee Enemy Attacked Hero With Crit Shot dealing " << getCritDamage() << " Damage." << endl;
            } else {
                target.takeDamage(getDamage());
                cout << "Melee Enemy Attacked Hero dealing " << getDamage() << " Damage." << endl;
            }
        }
    }
};

class Enemy_Archer: public Enemy {
    public:
    Enemy_Archer() {
    }
    Enemy_Archer(int laneNumber, int columnNumber): Enemy("Enemy Archer", laneNumber, columnNumber) {
    }
    ~Enemy_Archer() {
    }
    void attack(Character& target) override {

        if (chance(getCritChance())) {
            target.takeDamage(getCritDamage());
            cout << "Archer Enemy Attacked Hero With Crit Shot dealing " << getCritDamage() << " Damage." << endl;
        } else {
            target.takeDamage(getDamage());
            cout << "Archer Enemy Attacked Hero dealing " << getDamage() << " Damage." << endl;
        }
    }
};

class Enemy_Mage: public Enemy, public temp{
    public:
    Enemy_Mage() {
    }
    Enemy_Mage(int laneNumber, int columnNumber): Enemy("Enemy Mage", laneNumber, columnNumber) {
    }
    ~Enemy_Mage() {
    }
    void attack(Character& target) override {
        int damageIncrease = 10;
        if (chance(getCritChance())) {
            target.takeDamage(getCritDamage() + 10);
            cout << "Mage Enemy Attacked Hero With Crit Shot dealing " << getCritDamage() + damageIncrease << " Damage." << endl;
        } else {
            target.takeDamage(getDamage() + 10);
            cout << "Melee Enemy Attacked Hero dealing " << getCritDamage() + damageIncrease << " Damage." << endl;
        }
    }
};

class Shop {
    Hero*& hero;
    public:
    Shop(Hero*& h): hero(h) {}
    void enter() {
        bool flag = true;
        int choice;
        system("cls");
        displayData(hero);
        cout << "Choice: ";
        cin >> choice;
        while (choice) {
            switch(choice) {
                case 0:
                    flag = false;
                break;
                case 1:
                if (hero->canBuyItem(200)) {
                    hero->increaseHealthPoints(50);
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                case 2:
                if (hero->canBuyItem(200)) {
                    hero->increaseTotalHealthPoints(50);
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                case 3:
                if (hero->canBuyItem(300)) {
                    hero->increaseDamage(30);
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                case 4:
                if (hero->canBuyItem(450)) {
                    hero->increaseCritDamage(40);
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                case 5:
                if (hero->canBuyItem(400)) {
                    hero->increaseCritChance(0.1);
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                case 6:
                if (hero->canBuyItem(300)) {
                    hero->increaseEvasionChance(0.1);
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                case 7:
                if (hero->canBuyItem(300)) {
                    hero->increaseLifesteal(0.1);
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                case 8:
                if (hero->canBuyItem(300)) {
                    hero->increaseDefence(0.1);
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                case 9:
                if (hero->canBuyItem(300)) {
                    hero->increaseLooting(0.1);
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                case 10:
                if (hero->canBuyItem(1800)) {
                    (*hero)++;
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                case 11:
                if (hero->canBuyItem(2000)) {
                    changeHero();
                } else {
                    cout << "Not enough coins. Try another option." << endl;
                }
                break;
                default:
                    cout << "Choose one of the options. " << endl;
            }
            if (flag) {
                system("cls");
                displayData(hero);
            }
            cout << "Choice: ";
            cin >> choice;
        }
    }
    void changeHero() {
        if (dynamic_cast<Hero_Archer*>(hero)) {
            string name = hero->getName();
            hero = new Hero_Mage(hero);
            cout << "Hero Type Changed To Mage!" << endl;
        } else if (dynamic_cast<Hero_Mage*>(hero)) {
            string name = hero->getName();
            hero = new Hero_Archer(hero);
            cout << "Hero Type Changed To Archer!" << endl;
        }
        cout << "Press Enter to Continue. " << endl;
        cin.ignore();
        cin.get();
    }
};

class BattleField {
    private:
    Enemy*** grid;
    vector<Enemy*> allEnemies;
    int level;
    int levelEnemyCount;
    int pendingEnemies;
    double mageChance;
    double meleeChance;
    double archerChance;
    public:
    BattleField(int level) {
        grid = new Enemy**[3];
        for (int i = 0; i < 3; ++i) {
            grid[i] = new Enemy*[8];
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 8; ++j) {
                grid[i][j] = nullptr;
            }
        }
        this->level = level;
        levelEnemyCount = ceil(1 + 5 * pow((level - 1) / 9.0, 0.9));
        pendingEnemies = levelEnemyCount;
        double progress = (level - 1) / 8.0;
        double meleeWeight = 1.0 - progress;
        double archerWeight = 0.7 * progress;
        double mageWeight = 0.3 * progress;
        double total = archerWeight + mageWeight + meleeWeight;
        meleeChance  = meleeWeight / total;
        archerChance = archerWeight / total;
        mageChance   = mageWeight / total;
    }
    ~BattleField() {
        for (int i = 0; i < 3; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }
    bool isSpawnable() {
        return (grid[0][7] == nullptr || grid[1][7] == nullptr || grid[2][7] == nullptr);
    }
    void attemptSpawn() {
        int lane = randomNumber(0,2);
        if (grid[lane][7] == nullptr) {
            if (chance(mageChance)) {
                grid[lane][7] = new Enemy_Mage(lane, 7);
            } else if (chance(archerChance)) {
                grid[lane][7] = new Enemy_Archer(lane, 7);
            } else {
                grid[lane][7] = new Enemy_Melee(lane, 7);
            }
            allEnemies.push_back(grid[lane][7]);
            pendingEnemies--;
        }
    }
    void spawnEnemies() {
        while (pendingEnemies and isSpawnable()) {
            attemptSpawn();
        }
    }
    void displayGrid() {
        cout << "========== Battle Grid ==========" << endl;
        cout << "Level: " << setw(12) << level << "Enemy Count: " << levelEnemyCount << endl;
        cout << "Enemies Killed: " << Enemy::getKillCount() << endl;
        TextTable table('-', '|', '+');
        table.add("Lane/Column");
        table.add("1");
        table.add("2");
        table.add("3");
        table.add("4");
        table.add("5");
        table.add("6");
        table.add("7");
        table.add("8");
        table.endOfRow();
        for (int i = 0; i < 3; ++i) {
            table.add(to_string(i+1));
            for (int j = 0; j < 8; ++j) {
                if (grid[i][j] != nullptr) {
                    char enemyType = ' ';
                    if (dynamic_cast<Enemy_Mage*>(grid[i][j])) {
                        enemyType = 'M';
                    } else if (dynamic_cast<Enemy_Archer*>(grid[i][j])) {
                        enemyType = 'A';
                    } else if (dynamic_cast<Enemy_Melee*>(grid[i][j])) {
                        enemyType = 'R';
                    }
                    table.add(string(1, enemyType));
                } else {
                    table.add(" ");
                }
            }
            table.endOfRow();
        }
        cout << table;
    }
    friend class Game;
    friend TextTable displayData (Hero* hero, BattleField* field);
};

class Game {
    int level;
    BattleField* field = nullptr;
    string name;
    Hero* hero = nullptr;
    public:
    Game(): level(1) {
    }
    ~Game() {
    }
    void setup() {
        int choice;
        cout << "=========================" << endl;
        cout << " Welcome to Enemy Mayhem" << endl;
        cout << "=========================" << endl;
        cout << "Enter your name: ";
        cin >> name;
        cout << "Choose your character: " << endl;
        cout << "1. Archer Stats" << endl << Hero_Archer("Example") << endl << "2. Mage Stats" << endl << Hero_Mage("Example") << endl;
        cout << "Option Number: ";
        while (!hero) {
            cin >> choice;
            switch (choice) {
                case 1: hero = new Hero_Archer(name);
                break;
                case 2: hero = new Hero_Mage(name);
                break;
                default:
                cout << "Please choose one of the given options" << endl;
            }
        }
        cout << *hero;
        startLevel();
    }
    void startLevel() {
        field = new BattleField(level);
        field->spawnEnemies();
        while (hero->isAlive() && !field->allEnemies.empty()) {
            field->spawnEnemies();
            progressRound();
        }
        if (hero->isAlive()) {
            cout << "Level " << level << " completed successfully." << endl;
            if (level < 10) {
                cout << "Loading next level." << endl;
                delete field;
                Shop(hero).enter();
                level++;
                startLevel();
            } else {
                cout << "Game Completed. Thank you for playing!" << endl;
            }
        } else {
            cout << "Game over. Better Luck Next Time!" << endl;
        }
    }
    void playerAttack() {
        int lane;
        bool attacked = false;
        cout << "Select lane to attack: ";
        cin >> lane;
        lane--;
        cout << "====================== Combat Log ======================" << endl;
        for (int i = 0; i < 8; i++) {
            if (field->grid[lane][i] != nullptr) {
                hero->attack(*field->grid[lane][i]);
                attacked = true;
                int hp = (hero->getLifesteal())*(hero->getDamage());
                hp = hero->increaseHealthPoints(hp);
                if(hp) {
                    cout << "Hero Healed " << hp << " health points." << endl;
                }
                break;
            }
        }
        if (!attacked) {
            cout << "Shot missed!" << endl;
        }
    }
    void checkEnemies() {
        for (auto it = field->allEnemies.begin(); it != field->allEnemies.end(); ) {
            if ((*it)->isAlive()) {
                ++it;
            } else {
                int lane = (*it)->getLaneNumber();
                int column = (*it)->getColumnNumber();
                field->grid[lane][column] = nullptr;
                delete *it;
                it = field->allEnemies.erase(it);
                int coins = 150;
                if (hero->getLooting()) {
                    coins *= (1 + hero->getLooting());
                }
                hero->reward(coins);
                cout << "Hero was rewarded " << coins << " coins for defeating an enemy. " << endl;
            }
        }
    }
    void enemiesAttack() {
        for (Enemy* enemy : field->allEnemies) {
            if (dynamic_cast<Enemy_Melee*>(enemy))  {
                int lane = enemy->getLaneNumber();
                int column = enemy->getColumnNumber();
                if (enemy->getColumnNumber() == 0) {
                    enemy->attack(*hero);
                } else if  (field->grid[lane][column-1] == nullptr) {
                    field->grid[lane][column-1] = field->grid[lane][column];
                    field->grid[lane][column] = nullptr;
                    enemy->moveForward();
                    cout << "Melee Enemy Moved Forward By One Space." << endl;
                }
            }
            enemy->attack(*hero);
        }
    }
    void progressRound() {
        system("cls");
        cout << displayData(hero, field);
        field->displayGrid();
        playerAttack();
        checkEnemies();
        enemiesAttack();
        cout << "========================================================" << endl;
        cout << "Press Enter To Continue." << endl;
        cin.ignore();
        cin.get();
    }
};

void displayData (Hero* hero) {
    cout << "====================================================== Shop ========================================================" << endl;
    TextTable t('-', '|', '+');
    t.add("Option");
    t.add("Upgrade");
    t.add("Current Value");
    t.add("Value After Upgrade");
    t.add("Upgrade Cost");
    t.endOfRow();
    t.add("1");
    t.add("Instant Health");
    t.add(to_string(hero->getHealthPoints()));
    t.add(to_string(min(hero->getTotalHealthPoints(), hero->getHealthPoints() + 50)));
    t.add("200");
    t.endOfRow();
    t.add("2");
    t.add("Increase Total Health");
    t.add(to_string(hero->getTotalHealthPoints()));
    t.add(to_string(hero->getTotalHealthPoints() + 50));
    t.add("200");
    t.endOfRow();
    t.add("3");
    t.add("Increase Damage");
    t.add(to_string(hero->getDamage()));
    t.add(to_string(hero->getDamage() + 30));
    t.add("300");
    t.endOfRow();
    t.add("4");
    t.add("Increase Crit Damage");
    t.add(to_string(hero->getCritDamage()));
    t.add(to_string(hero->getCritDamage() + 20));
    t.add("450");
    t.endOfRow();
    t.add("5");
    t.add("Increase Crit Chance");
    t.add(to_string((int) (hero->getCritChance()*100)) + "%");
    t.add(to_string(min((int) ((hero->getCritChance() + 0.1)*100), 60))+"%");
    t.add("400");
    t.endOfRow();
    t.add("6");
    t.add("Increase Evasion Chance");
    t.add(to_string((int) (hero->getEvasionChance()*100)) + "%");
    t.add(to_string(min((int) ((hero->getEvasionChance() + 0.1)*100), 60))+"%");
    t.add("300");
    t.endOfRow();
    t.add("7");
    t.add("Increase Lifesteal");
    t.add(to_string((int) (hero->getLifesteal()*100)) + "%");
    t.add(to_string(min((int) ((hero->getLifesteal() + 0.1)*100), 70))+"%");
    t.add("300");
    t.endOfRow();
    t.add("8");
    t.add("Increase Defence");
    t.add(to_string((int) (hero->getDefence()*100)) + "%");
    t.add(to_string(min((int) ((hero->getDefence() + 0.1)*100), 60))+"%");
    t.add("300");
    t.endOfRow();
    t.add("9");
    t.add("Increase Looting");
    t.add(to_string((int) (hero->getLooting()*100)) + "%");
    t.add(to_string(min((int)(round((hero->getLooting() + 0.1) * 100)), 100)) + "%");
    t.add("300");
    t.endOfRow();
    t.add("10");
    t.add("Combo Upgrade");
    t.add("Upgrades all parameters by a little bit.");
    t.add(" ");
    t.add("1800");
    t.endOfRow();
    t.add("11");
    t.add("Switch Hero");
    t.add(hero->getType());
    if (hero->getType() == "Hero Archer") {
        t.add("Hero Mage");
    } else {
        t.add("Hero Archer");
    };
    t.add("2000");
    t.endOfRow();
    cout << t;
    cout << "Current Balance: " << hero->getWallet() << endl;
    cout << "Enter option number to purchase Item. Enter 0 to exit shop." << endl;
}

TextTable displayData (Hero* hero, BattleField* field) {
    cout << "============================= All Charcter Stats =============================" << endl;
    TextTable table('-', '|', '+');
    table.add("Character Type");
    table.add("HealthPoints");
    table.add("Damage");
    table.add("Crit Damage");
    table.add("Crit Chance");
    table.add("Wallet");
    table.add("Position");
    table.endOfRow();
    table.add(hero->getType());
    table.add(to_string(hero->getHealthPoints()) + "/" + to_string(hero->getTotalHealthPoints()));
    table.add(to_string(hero->getDamage()));
    table.add(to_string(hero->getCritDamage()));
    table.add(to_string((int) (hero->getCritChance()*100)) + "%");
    table.add(to_string(hero->getWallet()));
    table.add("-");
    table.endOfRow();
    for (Enemy* enemy: field->allEnemies) {
        char enemyType = ' ';
                if (dynamic_cast<Enemy_Mage*>(enemy)) {
                    enemyType = 'M';
                } else if (dynamic_cast<Enemy_Archer*>(enemy)) {
                    enemyType = 'A';
                } else if (dynamic_cast<Enemy_Melee*>(enemy)) {
                    enemyType = 'R';
                }
        table.add(enemy->getType() + " [" + string(1, enemyType) + ']');
        table.add(to_string(enemy->getHealthPoints()) + "/" + to_string(enemy->getTotalHealthPoints()));
        table.add(to_string(enemy->getDamage()));
        table.add(to_string(enemy->getCritDamage()));
        table.add(to_string((int) (enemy->getCritChance()*100)) + "%");
        table.add("-");
        table.add(to_string(enemy->getLaneNumber())+","+to_string(enemy->getColumnNumber()));
        table.endOfRow();
    }
    return table;
}

int Enemy::count = 0;
int Enemy::kills = 0;
int main() {
    Game().setup();
    cout << "Press Enter To Exit Programm." << endl;
    cin.ignore();
    cin.get();
    return 0;
}