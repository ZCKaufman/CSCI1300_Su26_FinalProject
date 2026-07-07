#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------- Item class: represents a single object the player can hold ---------- //
class Item {
private:
    string name;
    string type;        // "Crop", "Fish", "Mineral", "Animal Product", "Forage", "Material", "Food"
    int value;
    bool bundleItem;     // whether this item can satisfy a Community Center bundle category
    int energyRestore;   // energy gained if this item is food

public:
    // Default constructor, used only for placeholder items
    Item() {
        name = "";
        type = "";
        value = 0;
        bundleItem = false;
        energyRestore = 0;
    }

    // Main constructor used when creating real items
    Item(string itemName, string itemType, int itemValue, bool isBundle, int restore) {
        name = itemName;
        type = itemType;
        value = itemValue;
        bundleItem = isBundle;
        energyRestore = restore;
    }

    // Returns the item's name
    string getName() {
        return name;
    }

    // Returns the item's category/type
    string getType() {
        return type;
    }

    // Returns the item's gold value
    int getValue() {
        return value;
    }

    // Returns whether this item counts toward the final bundle
    bool isBundleItem() {
        return bundleItem;
    }

    // Returns how much energy this item restores if eaten
    int getEnergyRestore() {
        return energyRestore;
    }

    // Prints a one-line description of the item
    void displayItem() {
        cout << name << " - " << type;
        if (energyRestore > 0) {
            cout << " (restores " << energyRestore << " energy)";
        }
        cout << endl;
    }
};

// ---------- Bundle class: tracks the required Community Center categories ----------
class Bundle {
private:
    vector<string> requiredCategories;
    vector<bool> donated;

public:
    // Sets up the five required bundle categories, all undonated
    Bundle() {
        requiredCategories.push_back("Crop");
        requiredCategories.push_back("Fish");
        requiredCategories.push_back("Mineral");
        requiredCategories.push_back("Animal Product");
        requiredCategories.push_back("Forage");
        for (int i = 0; i < static_cast<int>(requiredCategories.size()); i++) {
            donated.push_back(false);
        }
    }

    // Returns true if the given category is still needed
    bool needsCategory(string category) {
        for (int i = 0; i < static_cast<int>(requiredCategories.size()); i++) {
            if (requiredCategories[i] == category && !donated[i]) {
                return true;
            }
        }
        return false;
    }

    // Attempts to donate an item; returns true if it filled a needed category
    bool donateItem(Item item) {
        for (int i = 0; i < static_cast<int>(requiredCategories.size()); i++) {
            if (requiredCategories[i] == item.getType() && !donated[i]) {
                donated[i] = true;
                return true;
            }
        }
        return false;
    }

    // Returns true once every category has been donated
    bool isComplete() {
        for (int i = 0; i < static_cast<int>(donated.size()); i++) {
            if (!donated[i]) {
                return false;
            }
        }
        return true;
    }

    // Returns how many categories have been donated so far
    int getProgress() {
        int count = 0;
        for (int i = 0; i < static_cast<int>(donated.size()); i++) {
            if (donated[i]) {
                count++;
            }
        }
        return count;
    }

    // Returns the total number of categories required
    int getTotalRequired() {
        return static_cast<int>(requiredCategories.size());
    }

    // Prints a checklist of donated and missing categories
    void displayBundle() {
        cout << "Final Community Center Bundle:" << endl;
        for (int i = 0; i < static_cast<int>(requiredCategories.size()); i++) {
            if (donated[i]) {
                cout << "[X] " << requiredCategories[i] << endl;
            } else {
                cout << "[ ] " << requiredCategories[i] << endl;
            }
        }
    }
};

// ---------- Character class: a villager the player can meet and talk to ----------
class Character {
private:
    string name;
    string location;
    int friendship;

public:
    // Default constructor for placeholder use
    Character() {
        name = "";
        location = "";
        friendship = 0;
    }

    // Creates a character with a name and home location
    Character(string charName, string homeLocation) {
        name = charName;
        location = homeLocation;
        friendship = 0;
    }

    // Returns the character's name
    string getName() {
        return name;
    }

    // Returns the location where this character is found
    string getLocation() {
        return location;
    }

    // Returns the player's current friendship level with this character
    int getFriendship() {
        return friendship;
    }

    // Raises friendship by the given amount
    void increaseFriendship(int amount) {
        friendship += amount;
    }
};

// ---------- Location class: a place on the map the player can visit ----------
class Location {
private:
    string name;
    bool unlocked;

public:
    // Default constructor for placeholder use
    Location() {
        name = "";
        unlocked = false;
    }

    // Creates a location with a name and starting lock state
    Location(string locName, bool startUnlocked) {
        name = locName;
        unlocked = startUnlocked;
    }

    // Returns the location's name
    string getName() {
        return name;
    }

    // Returns whether the player is currently able to travel here
    bool isUnlocked() {
        return unlocked;
    }

    // Marks this location as reachable
    void unlock() {
        unlocked = true;
    }
};

// ---------- Player class: the farmer, their stats, and their inventory ----------
class Player {
private:
    string name;
    string currentLocation;
    int energy;
    int maxEnergy;
    int money;
    int day;
    vector<Item> inventory;

public:
    // Sets up a new farmer with starting stats
    Player() {
        name = "Farmer";
        currentLocation = "Farm";
        maxEnergy = 10;
        energy = 10;
        money = 100;
        day = 1;
    }

    // Sets the farmer's name
    void setName(string playerName) {
        name = playerName;
    }

    // Returns the farmer's name
    string getName() {
        return name;
    }

    // Moves the player to a new location
    void setLocation(string loc) {
        currentLocation = loc;
    }

    // Returns the player's current location
    string getLocation() {
        return currentLocation;
    }

    // Returns the player's current energy
    int getEnergy() {
        return energy;
    }

    // Returns the player's maximum energy
    int getMaxEnergy() {
        return maxEnergy;
    }

    // Attempts to spend energy; returns false if there is not enough
    bool spendEnergy(int amount) {
        if (energy < amount) {
            return false;
        }
        energy -= amount;
        return true;
    }

    // Restores energy, capped at the maximum
    void restoreEnergy(int amount) {
        energy += amount;
        if (energy > maxEnergy) {
            energy = maxEnergy;
        }
    }

    // Refills energy back to full at the start of a new day
    void resetEnergyForNewDay() {
        energy = maxEnergy;
    }

    // Returns the player's current gold
    int getMoney() {
        return money;
    }

    // Adds gold to the player's total
    void addMoney(int amount) {
        money += amount;
    }

    // Attempts to spend gold; returns false if there is not enough
    bool spendMoney(int amount) {
        if (money < amount) {
            return false;
        }
        money -= amount;
        return true;
    }

    // Returns the current day number
    int getDay() {
        return day;
    }

    // Advances the game to the next day
    void advanceDay() {
        day++;
    }

    // Adds a new item to the inventory
    void addItem(Item newItem) {
        inventory.push_back(newItem);
    }

    // Counts how many items of a given type are in the inventory
    int countItemType(string type) {
        int count = 0;
        for (int i = 0; i < static_cast<int>(inventory.size()); i++) {
            if (inventory[i].getType() == type) {
                count++;
            }
        }
        return count;
    }

    // Removes up to 'count' items of a type; returns true if enough were found and removed
    bool removeItemsOfType(string type, int count) {
        if (countItemType(type) < count) {
            return false;
        }
        int removed = 0;
        vector<Item> updatedInventory;
        for (int i = 0; i < static_cast<int>(inventory.size()); i++) {
            if (inventory[i].getType() == type && removed < count) {
                removed++;
            } else {
                updatedInventory.push_back(inventory[i]);
            }
        }
        inventory = updatedInventory;
        return true;
    }

    // Returns true if the inventory contains an item with the given exact name
    bool hasItemNamed(string itemName) {
        for (int i = 0; i < static_cast<int>(inventory.size()); i++) {
            if (inventory[i].getName() == itemName) {
                return true;
            }
        }
        return false;
    }

    // Removes the first item found with the given exact name
    void removeItemNamed(string itemName) {
        vector<Item> updatedInventory;
        bool removedOne = false;
        for (int i = 0; i < static_cast<int>(inventory.size()); i++) {
            if (inventory[i].getName() == itemName && !removedOne) {
                removedOne = true;
            } else {
                updatedInventory.push_back(inventory[i]);
            }
        }
        inventory = updatedInventory;
    }

    // Prints the full inventory list
    void displayInventory() {
        if (inventory.size() == 0) {
            cout << "Your inventory is empty." << endl;
            return;
        }
        cout << "Inventory:" << endl;
        for (int i = 0; i < static_cast<int>(inventory.size()); i++) {
            cout << i + 1 << ". ";
            inventory[i].displayItem();
        }
    }

    // Returns how many items are currently in the inventory
    int getInventorySize() {
        return static_cast<int>(inventory.size());
    }

    // Returns a copy of the item stored at the given index
    Item getItemAt(int index) {
        return inventory[index];
    }

    // Removes the item stored at the given index
    void removeItemAt(int index) {
        vector<Item> updatedInventory;
        for (int i = 0; i < static_cast<int>(inventory.size()); i++) {
            if (i != index) {
                updatedInventory.push_back(inventory[i]);
            }
        }
        inventory = updatedInventory;
    }
};

// ---------- Game class: owns the player, world, and the main game loop ----------
class Game {
private:
    Player player;
    vector<Character> characters;
    vector<Location> locations;
    Bundle bundle;
    int jojaInfluence;
    int maxDays;
    bool gameOver;
    bool playerQuit;

public:
    // Safely reads a menu number, protecting against non-numeric input
    int readChoice() {
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            choice = -1;
        }
        cin.ignore(1000, '\n');
        return choice;
    }

    // Sets starting values before the world is built
    Game() {
        jojaInfluence = 0;
        maxDays = 7;
        gameOver = false;
        playerQuit = false;
    }

    // Builds the map, villagers, and starting conditions
    void setupGame() {
        locations.push_back(Location("Farm", true));
        locations.push_back(Location("Town Square", true));
        locations.push_back(Location("Beach", true));
        locations.push_back(Location("Mountain", true));
        locations.push_back(Location("Marnie's Ranch", true));
        locations.push_back(Location("Forest", false));
        locations.push_back(Location("Community Center", true));
        locations.push_back(Location("JojaMart", true));

        characters.push_back(Character("Lewis", "Town Square"));
        characters.push_back(Character("Pierre", "Town Square"));
        characters.push_back(Character("Robin", "Town Square"));
        characters.push_back(Character("Willy", "Beach"));
        characters.push_back(Character("Clint", "Mountain"));
        characters.push_back(Character("Marnie", "Marnie's Ranch"));
        characters.push_back(Character("Linus", "Forest"));
        characters.push_back(Character("Morris", "JojaMart"));

        player.setLocation("Farm");
    }

    // Finds the index of a location by name, or -1 if not found
    int findLocationIndex(string locName) {
        for (int i = 0; i < static_cast<int>(locations.size()); i++) {
            if (locations[i].getName() == locName) {
                return i;
            }
        }
        return -1;
    }

    // Finds the index of a character by name, or -1 if not found
    int findCharacterIndex(string charName) {
        for (int i = 0; i < static_cast<int>(characters.size()); i++) {
            if (characters[i].getName() == charName) {
                return i;
            }
        }
        return -1;
    }

    // Prints the header, day, and stat readout at the top of every turn
    void displayDashboard() {
        cout << endl;
        cout << "==================================================" << endl;
        cout << "         STARDEW VALLEY: THE FINAL BUNDLE" << endl;
        cout << "==================================================" << endl;
        cout << "Farmer: " << player.getName() << "     Day: " << player.getDay() << " / " << maxDays << endl;
        cout << "Energy: " << player.getEnergy() << " / " << player.getMaxEnergy();
        cout << "     Money: " << player.getMoney() << "g" << endl;
        cout << "Joja Influence: " << jojaInfluence << endl;
        cout << "Location: " << player.getLocation() << endl;
        cout << "Bundle Progress: " << bundle.getProgress() << " / " << bundle.getTotalRequired() << " items donated" << endl;
        cout << "==================================================" << endl;
    }

    // Prints a simple connected map with the player's location marked
    void displayMap() {
        cout << "Map:" << endl;
        cout << "         [" << mapLabel("Mountain") << "]" << endl;
        cout << "            |" << endl;
        cout << "[" << mapLabel("Forest") << "] -- [" << mapLabel("Farm") << "] -- [" << mapLabel("Town Square") << "] -- [" << mapLabel("Beach") << "]" << endl;
        cout << "                        |" << endl;
        cout << "                 [" << mapLabel("Marnie's Ranch") << "]" << endl;
        cout << endl;
        cout << "[" << mapLabel("Community Center") << "]        [" << mapLabel("JojaMart") << "]" << endl;
        cout << "(* = you are here, LOCKED = not reachable yet)" << endl;
    }

    // Builds the text shown for a single location on the map
    string mapLabel(string locName) {
        int idx = findLocationIndex(locName);
        string label = locName;
        if (!locations[idx].isUnlocked()) {
            label += " (LOCKED)";
        }
        if (player.getLocation() == locName) {
            label = "*" + label;
        }
        return label;
    }

    // Prints the villagers currently standing at the player's location
    void displayCharactersHere() {
        bool anyoneHere = false;
        cout << "Characters nearby:" << endl;
        for (int i = 0; i < static_cast<int>(characters.size()); i++) {
            if (characters[i].getLocation() == player.getLocation()) {
                cout << "- " << characters[i].getName() << endl;
                anyoneHere = true;
            }
        }
        if (!anyoneHere) {
            cout << "- No one is here right now." << endl;
        }
    }

    // Prints the main list of actions available every turn
    void showMainMenu() {
        displayCharactersHere();
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Move to another location" << endl;
        cout << "2. Talk to someone here" << endl;
        cout << "3. Location action" << endl;
        cout << "4. View inventory" << endl;
        cout << "5. View bundle" << endl;
        cout << "6. End day" << endl;
        cout << "7. Quit game" << endl;
        cout << "Choose an option: ";
    }

    // Lets the player travel to any unlocked location besides their current one
    void handleMove() {
        cout << "Where would you like to go?" << endl;
        vector<int> travelOptions;
        for (int i = 0; i < static_cast<int>(locations.size()); i++) {
            if (locations[i].isUnlocked() && locations[i].getName() != player.getLocation()) {
                travelOptions.push_back(i);
                cout << travelOptions.size() << ". " << locations[i].getName() << endl;
            }
        }
        cout << travelOptions.size() + 1 << ". Stay here" << endl;
        cout << "Choose an option: ";
        int choice = readChoice();
        if (choice >= 1 && choice <= static_cast<int>(travelOptions.size())) {
            int locIndex = travelOptions[choice - 1];
            player.setLocation(locations[locIndex].getName());
            cout << "You travel to " << player.getLocation() << "." << endl;
        } else {
            cout << "You decide to stay put." << endl;
        }
    }

    // Lets the player choose a villager here and starts their dialogue
    void handleTalk() {
        vector<int> presentCharacters;
        cout << "Who would you like to talk to?" << endl;
        for (int i = 0; i < static_cast<int>(characters.size()); i++) {
            if (characters[i].getLocation() == player.getLocation()) {
                presentCharacters.push_back(i);
                cout << presentCharacters.size() << ". " << characters[i].getName() << endl;
            }
        }
        if (presentCharacters.size() == 0) {
            cout << "There is no one here to talk to." << endl;
            return;
        }
        cout << presentCharacters.size() + 1 << ". Never mind" << endl;
        cout << "Choose an option: ";
        int choice = readChoice();
        if (choice < 1 || choice > static_cast<int>(presentCharacters.size())) {
            return;
        }
        int idx = presentCharacters[choice - 1];
        string charName = characters[idx].getName();
        if (charName == "Lewis") {
            talkToLewis(idx);
        } else if (charName == "Pierre") {
            talkToPierre(idx);
        } else if (charName == "Robin") {
            talkToRobin(idx);
        } else if (charName == "Willy") {
            talkToWilly(idx);
        } else if (charName == "Clint") {
            talkToClint(idx);
        } else if (charName == "Marnie") {
            talkToMarnie(idx);
        } else if (charName == "Linus") {
            talkToLinus(idx);
        } else if (charName == "Morris") {
            talkToMorris(idx);
        }
    }

    // Lewis reminds the player of bundle progress and offers encouragement
    void talkToLewis(int idx) {
        cout << "Lewis says:" << endl;
        cout << "\"The Community Center is counting on you. Check the bundle" << endl;
        cout << "board to see what we still need.\"" << endl;
        bundle.displayBundle();
        characters[idx].increaseFriendship(1);
    }

    // Pierre offers to sell a Cauliflower crop for the bundle
    void talkToPierre(int idx) {
        cout << "Pierre says:" << endl;
        cout << "\"Welcome to the shop! I've got a fine Cauliflower for 60 gold.\"" << endl;
        cout << "1. Buy Cauliflower - 60g" << endl;
        cout << "2. Leave" << endl;
        cout << "Choose an option: ";
        int choice = readChoice();
        if (choice == 1) {
            if (player.spendMoney(60)) {
                player.addItem(Item("Cauliflower", "Crop", 60, true, 0));
                cout << "You bought a Cauliflower." << endl;
                characters[idx].increaseFriendship(1);
            } else {
                cout << "You don't have enough gold." << endl;
            }
        } else {
            cout << "You leave the shop." << endl;
        }
    }

    // Robin runs the bridge-repair quest that unlocks the Forest
    void talkToRobin(int idx) {
        int forestIdx = findLocationIndex("Forest");
        if (locations[forestIdx].isUnlocked()) {
            cout << "Robin says:" << endl;
            cout << "\"That bridge repair turned out great, if I do say so myself!\"" << endl;
            characters[idx].increaseFriendship(1);
            return;
        }
        cout << "Robin says:" << endl;
        cout << "\"The bridge to the Forest is broken. Bring me 3 Wood and 2 Stone" << endl;
        cout << "and I'll get it fixed.\"" << endl;
        int woodCount = 0;
        int stoneCount = 0;
        for (int i = 0; i < player.getInventorySize(); i++) {
            if (player.getItemAt(i).getName() == "Wood") {
                woodCount++;
            }
            if (player.getItemAt(i).getName() == "Stone") {
                stoneCount++;
            }
        }
        cout << "Wood: " << woodCount << " / 3     Stone: " << stoneCount << " / 2" << endl;
        if (woodCount >= 3 && stoneCount >= 2) {
            cout << "1. Give Robin the materials" << endl;
            cout << "2. Not yet" << endl;
            cout << "Choose an option: ";
            int choice = readChoice();
            if (choice == 1) {
                removeNamedItems("Wood", 3);
                removeNamedItems("Stone", 2);
                locations[forestIdx].unlock();
                characters[idx].increaseFriendship(3);
                cout << "Robin repaired the bridge! The Forest is now unlocked." << endl;
            }
        }
    }

    // Removes up to 'count' items that match the given exact name
    void removeNamedItems(string itemName, int count) {
        int removed = 0;
        while (removed < count && player.hasItemNamed(itemName)) {
            player.removeItemNamed(itemName);
            removed++;
        }
    }

    // Willy welcomes the player and teaches them to fish here
    void talkToWilly(int idx) {
        cout << "Willy says:" << endl;
        cout << "\"The fish are bitin' today! Head down to the water and give it a try.\"" << endl;
        characters[idx].increaseFriendship(1);
    }

    // Clint offers mining tips that unlock ore prospecting at the Mountain
    void talkToClint(int idx) {
        cout << "Clint says:" << endl;
        cout << "\"Look for veins in the rock, that's where the good ore hides.\"" << endl;
        characters[idx].increaseFriendship(1);
    }

    // Marnie will trade a Wild Horseradish for a fresh Egg
    void talkToMarnie(int idx) {
        cout << "Marnie says:" << endl;
        cout << "\"If you bring me some Wild Horseradish, I'll trade you a fresh Egg.\"" << endl;
        if (player.hasItemNamed("Wild Horseradish")) {
            cout << "1. Trade Wild Horseradish for an Egg" << endl;
            cout << "2. Not right now" << endl;
            cout << "Choose an option: ";
            int choice = readChoice();
            if (choice == 1) {
                player.removeItemNamed("Wild Horseradish");
                player.addItem(Item("Egg", "Animal Product", 30, true, 0));
                characters[idx].increaseFriendship(2);
                cout << "Marnie hands you a fresh Egg." << endl;
            }
        } else {
            cout << "(You don't have any Wild Horseradish to trade yet.)" << endl;
        }
    }

    // Linus teaches the player to forage here in the Forest
    void talkToLinus(int idx) {
        cout << "Linus says:" << endl;
        cout << "\"The forest provides, if you know where to look.\"" << endl;
        characters[idx].increaseFriendship(1);
    }

    // Morris pitches Joja shortcuts that cost gold and raise Joja Influence
    void talkToMorris(int idx) {
        cout << "Morris says:" << endl;
        cout << "\"Why waste time gathering everything yourself? Joja can help... for a price.\"" << endl;
        cout << "1. Buy a bundle-ready Egg - 75g" << endl;
        cout << "2. Buy a Joja Cola - 20g, restores 3 energy" << endl;
        cout << "3. Leave JojaMart" << endl;
        cout << "Choose an option: ";
        int choice = readChoice();
        if (choice == 1) {
            if (player.spendMoney(75)) {
                player.addItem(Item("Joja Egg", "Animal Product", 75, true, 0));
                jojaInfluence++;
                cout << "You bought a Joja Egg. Joja Influence increased by 1." << endl;
            } else {
                cout << "You don't have enough gold." << endl;
            }
        } else if (choice == 2) {
            if (player.spendMoney(20)) {
                player.restoreEnergy(3);
                jojaInfluence++;
                cout << "You drink a Joja Cola. Energy restored. Joja Influence increased by 1." << endl;
            } else {
                cout << "You don't have enough gold." << endl;
            }
        } else {
            cout << "You leave JojaMart." << endl;
        }
        characters[idx].increaseFriendship(1);
    }

    // Routes to the correct set of actions based on the player's location
    void handleLocationAction() {
        string loc = player.getLocation();
        if (loc == "Farm") {
            farmActions();
        } else if (loc == "Beach") {
            beachActions();
        } else if (loc == "Mountain") {
            mountainActions();
        } else if (loc == "Forest") {
            forestActions();
        } else if (loc == "Community Center") {
            donateAction();
        } else {
            cout << "There is nothing to do here besides talk or move on." << endl;
        }
    }

    // Farm actions: growing crops or chopping wood
    void farmActions() {
        cout << "1. Work the fields (3 energy) - gather a Parsnip" << endl;
        cout << "2. Chop wood (2 energy) - gather Wood" << endl;
        cout << "3. Never mind" << endl;
        cout << "Choose an option: ";
        int choice = readChoice();
        if (choice == 1) {
            if (player.spendEnergy(3)) {
                player.addItem(Item("Parsnip", "Crop", 15, true, 0));
                cout << "You harvest a Parsnip." << endl;
            } else {
                cout << "You are too tired to work the fields." << endl;
            }
        } else if (choice == 2) {
            if (player.spendEnergy(2)) {
                player.addItem(Item("Wood", "Material", 5, false, 0));
                cout << "You chop some Wood." << endl;
            } else {
                cout << "You are too tired to chop wood." << endl;
            }
        }
    }

    // Beach actions: fishing, unlocked once Willy has been met
    void beachActions() {
        int willyIdx = findCharacterIndex("Willy");
        if (characters[willyIdx].getFriendship() <= 0) {
            cout << "Talk to Willy first, he knows the best fishing spots." << endl;
            return;
        }
        cout << "1. Go fishing (3 energy) - catch a Sunfish" << endl;
        cout << "2. Never mind" << endl;
        cout << "Choose an option: ";
        int choice = readChoice();
        if (choice == 1) {
            if (player.spendEnergy(3)) {
                player.addItem(Item("Sunfish", "Fish", 20, true, 0));
                cout << "You catch a Sunfish!" << endl;
            } else {
                cout << "You are too tired to fish." << endl;
            }
        }
    }

    // Mountain actions: gathering stone, and mining ore once Clint is met
    void mountainActions() {
        int clintIdx = findCharacterIndex("Clint");
        cout << "1. Mine for Stone (3 energy)" << endl;
        if (characters[clintIdx].getFriendship() > 0) {
            cout << "2. Search for Copper Ore (4 energy)" << endl;
        }
        cout << "3. Never mind" << endl;
        cout << "Choose an option: ";
        int choice = readChoice();
        if (choice == 1) {
            if (player.spendEnergy(3)) {
                player.addItem(Item("Stone", "Material", 5, false, 0));
                cout << "You gather a Stone." << endl;
            } else {
                cout << "You are too tired to mine." << endl;
            }
        } else if (choice == 2 && characters[clintIdx].getFriendship() > 0) {
            if (player.spendEnergy(4)) {
                player.addItem(Item("Copper Ore", "Mineral", 25, true, 0));
                cout << "You find a Copper Ore!" << endl;
            } else {
                cout << "You are too tired to mine." << endl;
            }
        }
    }

    // Forest actions: foraging, unlocked once Linus has been met
    void forestActions() {
        int linusIdx = findCharacterIndex("Linus");
        if (characters[linusIdx].getFriendship() <= 0) {
            cout << "Talk to Linus first, he can show you what's safe to forage." << endl;
            return;
        }
        cout << "1. Forage (2 energy) - search for Wild Horseradish" << endl;
        cout << "2. Never mind" << endl;
        cout << "Choose an option: ";
        int choice = readChoice();
        if (choice == 1) {
            if (player.spendEnergy(2)) {
                player.addItem(Item("Wild Horseradish", "Forage", 10, true, 0));
                cout << "You forage a Wild Horseradish." << endl;
            } else {
                cout << "You are too tired to forage." << endl;
            }
        }
    }

    // Community Center action: donate an eligible item toward the bundle
    void donateAction() {
        if (player.getInventorySize() == 0) {
            cout << "You have nothing to donate." << endl;
            return;
        }
        cout << "You enter the Community Center." << endl;
        bundle.displayBundle();
        cout << endl;
        player.displayInventory();
        cout << player.getInventorySize() + 1 << ". Never mind" << endl;
        cout << "What would you like to donate? ";
        int choice = readChoice();
        if (choice < 1 || choice > player.getInventorySize()) {
            cout << "You leave without donating." << endl;
            return;
        }
        Item chosen = player.getItemAt(choice - 1);
        if (!chosen.isBundleItem()) {
            cout << "That item isn't meant for the bundle." << endl;
            return;
        }
        if (bundle.donateItem(chosen)) {
            player.removeItemAt(choice - 1);
            cout << "You donated " << chosen.getName() << " to the Final Bundle!" << endl;
            cout << "Bundle Progress: " << bundle.getProgress() << " / " << bundle.getTotalRequired() << endl;
        } else {
            cout << "The bundle no longer needs a " << chosen.getType() << "." << endl;
        }
    }

    // Advances time to the next day and refills energy
    void handleEndDay() {
        player.advanceDay();
        player.resetEnergyForNewDay();
        cout << "Night falls on Pelican Town..." << endl;
        cout << "Day " << player.getDay() << " begins." << endl;
    }

    // Returns true once the final bundle has been fully donated
    bool checkWin() {
        return bundle.isComplete();
    }

    // Returns true once the player has run out of days
    bool checkLoss() {
        return player.getDay() > maxDays;
    }

    // Reads the main menu choice and calls the matching handler
    void processChoice(int choice) {
        if (choice == 1) {
            handleMove();
        } else if (choice == 2) {
            handleTalk();
        } else if (choice == 3) {
            handleLocationAction();
        } else if (choice == 4) {
            player.displayInventory();
        } else if (choice == 5) {
            bundle.displayBundle();
        } else if (choice == 6) {
            handleEndDay();
        } else if (choice == 7) {
            playerQuit = true;
            gameOver = true;
        } else {
            cout << "Invalid option." << endl;
        }
    }

    // Prints the correct ending message based on how the game finished
    void displayEnding() {
        cout << endl;
        cout << "==================================================" << endl;
        if (checkWin()) {
            cout << "The Final Bundle is complete! The Junimos rejoice" << endl;
            cout << "and the Community Center is fully restored!" << endl;
            if (jojaInfluence == 0) {
                cout << "COMMUNITY HERO ENDING: Pelican Town thrives, restored" << endl;
                cout << "entirely through your own hard work and friendship." << endl;
            } else if (jojaInfluence <= 2) {
                cout << "RESTORED ENDING: The town celebrates, though a few" << endl;
                cout << "neighbors whisper about Joja's fingerprints on the win." << endl;
            } else {
                cout << "JOJA SHORTCUT ENDING: The bundle is complete, but Joja" << endl;
                cout << "has quietly gained real power in the valley." << endl;
            }
        } else if (checkLoss()) {
            if (bundle.getProgress() > 0) {
                cout << "ALMOST THERE ENDING: The season ends with " << bundle.getProgress();
                cout << " / " << bundle.getTotalRequired() << " items donated." << endl;
                cout << "So close! Maybe next season." << endl;
            } else {
                cout << "SEASON OVER ENDING: The season ends and the Community" << endl;
                cout << "Center remains in disrepair." << endl;
            }
        } else if (playerQuit) {
            cout << "You pack up early. Final bundle progress: " << bundle.getProgress();
            cout << " / " << bundle.getTotalRequired() << "." << endl;
        }
        cout << "Thanks for playing, " << player.getName() << "!" << endl;
        cout << "==================================================" << endl;
    }

    // Runs the full game from introduction through the ending screen
    void run() {
        setupGame();
        cout << "Welcome to Pelican Town!" << endl;
        cout << "What is your farmer's name? ";
        string playerName;
        getline(cin, playerName);
        player.setName(playerName);
        cout << "The Community Center needs one final bundle before the" << endl;
        cout << "season ends. You have " << maxDays << " days. Good luck, " << playerName << "!" << endl;

        while (!gameOver) {
            displayDashboard();
            displayMap();
            showMainMenu();
            int choice = readChoice();
            if (cin.eof()) {
                playerQuit = true;
                gameOver = true;
                break;
            }
            processChoice(choice);
            if (checkWin() || checkLoss()) {
                gameOver = true;
            }
        }
        displayEnding();
    }
};

// Creates the game and starts it
int main() {
    Game game;
    game.run();
    return 0;
}