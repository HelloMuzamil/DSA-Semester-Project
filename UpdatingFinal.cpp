#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <chrono>
#include <thread>
#include <cstdlib> // For random number generation
#include <ctime>

using namespace std;

void clearScreen() {
    system("cls");  
    this_thread::sleep_for(chrono::seconds(1));  
}


struct Guard {
    string name;
    string contact;
    string shift;
};


struct Game {
    string name;
    double pricePerHour;
};


struct outlet {
    string data;
    outlet* next;
};


struct floor {
    outlet* head;
    outlet* tail;
    int count;
};

const int MAX_GUARDS = 10;
const int MAX_GAMES = 5;
const int MAX_OUTLETS = 20;
int guardCount = 0;
double totalRevenue = 0.0; 
floor mall[5];  // 5 floors in the mall
Guard guards[MAX_GUARDS];
int parkingGrid[5][5] = {0};


Game gamingZone[MAX_GAMES] = {
    {"Air Hockey", 5.00},
    {"VR Racing", 10.00},
    {"Bowling", 8.00},
    {"Shooting Game", 6.50},
    {"Arcade Basketball", 7.00}
};

void initializeMall() {
    for (int i = 0; i < 5; i++) {
        mall[i].head = nullptr;
        mall[i].tail = nullptr;
        mall[i].count = 0;
    }
}

// Function to add an outlet at the start of a floor's linked list
void insertAtStart(int floorIndex, string name) {
    if (floorIndex < 1 || floorIndex > 5) {
        cout << "Invalid floor index! Please enter a floor index between 1 and 5.\n";
        return;
    }

    if (mall[floorIndex - 1].count < MAX_OUTLETS) {
        outlet* newOutlet = new outlet;
        newOutlet->data = name;
        newOutlet->next = mall[floorIndex - 1].head;
        mall[floorIndex - 1].head = newOutlet;

        if (mall[floorIndex - 1].tail == nullptr) {
            mall[floorIndex - 1].tail = newOutlet;
        }
        mall[floorIndex - 1].count++;
        cout << "Outlet " << name << " added to Floor " << floorIndex << endl;
    } else {
        cout << "Floor " << floorIndex << " is full!\n";
    }
}

void insertattail(int floorindex, string name) {
    if (floorindex < 1 || floorindex > 5) {
        cout << "Invalid floor index! Please enter a floor index between 1 and 5.\n";
        return;
    }

    if (mall[floorindex - 1].count < MAX_OUTLETS) {
        outlet* newoutlet = new outlet;
        newoutlet->data = name;
        newoutlet->next = nullptr;

        if (mall[floorindex - 1].tail != nullptr) {
            mall[floorindex - 1].tail->next = newoutlet;
        }
        mall[floorindex - 1].tail = newoutlet;

        if (mall[floorindex - 1].head == nullptr) {
            mall[floorindex - 1].head = newoutlet;
        }
        mall[floorindex - 1].count++;
        cout << "OUTLET ADDED " << name << " TO FLOOR " << floorindex << endl;
    } else {
        cout << "FLOOR " << floorindex << " IS FULL!\n";
    }
}

// Function to delete an outlet
void deleteOutlet(int floorIndex, string outletName) {
    if (floorIndex < 1 || floorIndex > 5) {
        cout << "Invalid floor index! Please enter a floor index between 1 and 5.\n";
        return;
    }

    floorIndex -= 1;
    if (mall[floorIndex].head == nullptr) {
        cout << "No outlets on floor " << floorIndex + 1 << " to delete.\n";
        return;
    }
    
    outlet* current = mall[floorIndex].head;
    outlet* prev = nullptr;

    // If the outlet to delete is the first outlet
    if (current != nullptr && current->data == outletName) {
        mall[floorIndex].head = current->next;
        if (mall[floorIndex].tail == current) {
            mall[floorIndex].tail = nullptr;
        }
        delete current;
        mall[floorIndex].count--;
        cout << "Outlet " << outletName << " deleted from Floor " << floorIndex + 1 << ".\n";
        return;
    }

    // Search for the outlet to delete
    while (current != nullptr && current->data != outletName) {
        prev = current;
        current = current->next;
    }

    // If outlet was not found
    if (current == nullptr) {
        cout << "Outlet " << outletName << " not found on Floor " << floorIndex + 1 << ".\n";
        return;
    }

    // Otherwise, remove the outlet from the linked list
    prev->next = current->next;
    if (current == mall[floorIndex].tail) {
        mall[floorIndex].tail = prev;
    }
    delete current;
    mall[floorIndex].count--;
    cout << "Outlet " << outletName << " deleted from Floor " << floorIndex + 1 << ".\n";
}

// Function to display all outlets on a floor
void displayAllOutlets(int floorIndex) {
    if (floorIndex < 1 || floorIndex > 5) {
        cout << "Invalid floor index! Please enter a floor index between 1 and 5.\n";
        return;
    }

    outlet* temp = mall[floorIndex - 1].head;
    if (temp == nullptr) {
        cout << "No outlets found on floor " << floorIndex << ".\n";
    } else {
        cout << "Outlets on floor " << floorIndex << ": ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
}

// Function to display available games
void displayGames() {
    cout << "\n=== Mall Play Arcade ===\n";
    for (int i = 0; i < MAX_GAMES; ++i) {
        cout << i + 1 << ". " << gamingZone[i].name
             << " - $" << fixed << setprecision(2) << gamingZone[i].pricePerHour << "/hr\n";
    }
    cout << "=========================\n";
}

// Function for a customer to play a game
void playGame() {
    displayGames();
    int choice;
    cout << "Pick a game (1-" << MAX_GAMES << "): ";
    cin >> choice;

    if (choice < 1 || choice > MAX_GAMES) {
        cout << "Oops, that's not a valid game.\n";
        return;
    }

    Game selectedGame = gamingZone[choice - 1];
    cout << "You picked: " << selectedGame.name << "\n";

    double hoursPlayed;
    cout << "How many hours? ";
    cin >> hoursPlayed;

    if (hoursPlayed <= 0) {
        cout << "You need to play for at least one hour!\n";
        return;
    }

    double totalCost = hoursPlayed * selectedGame.pricePerHour;
    totalRevenue += totalCost;

    cout << "\nTotal for " << selectedGame.name << ": $" << fixed << setprecision(2) << totalCost << "\n";
}

// Function to view total revenue from games
void viewRevenue() {
    cout << "\nTotal Revenue: $" << fixed << setprecision(2) << totalRevenue << "\n";
}


/////////////////////////////////////////////Security Mangement//////////////////////////////////////////////////////


void addGuard() {
    if (guardCount >= MAX_GUARDS) {
        cout << "Cannot add more guards. Maximum limit reached.\n";
        return;
    }

    // Name validation loop
    string name;
    while (true) {
        cout << "Enter Guard Name (alphabets only): ";
        getline(cin, name);

        bool valid = true;
        for (int i = 0; i < name.length(); i++) {
            if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && name[i] != ' ') {
                valid = false;
                break;
            }
        }

        if (valid) {
            guards[guardCount].name = name;
            cout << "Guard Name added successfully!\n";
            break;  // Exit the loop if valid input is entered
        } else {
            cout << "Invalid name! Please enter alphabets only.\n";
        }
    }

    // Contact number validation
    while (true) {
        cout << "Enter Contact Number (digits only): ";
        getline(cin, guards[guardCount].contact);

        bool valid = true;
        for (char c : guards[guardCount].contact) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (valid) break;
        else cout << "Invalid contact number! Please enter digits only.\n";
    }

    // Random shift assignment
    srand(time(0)); // Seed the random number generator
    int shiftIndex = rand() % 3; // Generate a random number between 0 and 2

    // Assign shift based on the random number
    switch (shiftIndex) {
        case 0:
            guards[guardCount].shift = "Morning";
            break;
        case 1:
            guards[guardCount].shift = "Afternoon";
            break;
        case 2:
            guards[guardCount].shift = "Night";
            break;
    }

    cout << "Guard " << name << " assigned to " << guards[guardCount].shift << " shift.\n";

    // Increment the guard count
    guardCount++;
}


// Function to display guard schedule
void displayGuardSchedule() {
    if (guardCount == 0) {
        cout << "No guards found.\n";
    } else {
        cout << "\n===========================================\n";
        cout << "                 Guard Schedule             \n";
        cout << "===========================================\n";
        cout << left << setw(5) << "No." 
             << setw(20) << "Name" 
             << setw(15) << "Contact" 
             << setw(15) << "Shift" << "\n";
        cout << "-------------------------------------------\n";
        for (int i = 0; i < guardCount; i++) {
            cout << left << setw(5) << i + 1
                 << setw(20) << guards[i].name
                 << setw(15) << guards[i].contact
                 << setw(15) << guards[i].shift << "\n";
        }
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}


// Function to rotate guard shifts
void rotateShifts() {
    if (guardCount < 2) {
        cout << "Insufficient guards to rotate shifts.\n";
        return;
    }

    stack<string> shiftStack;

    for (int i = 0; i < guardCount; i++) {
        shiftStack.push(guards[i].shift);
    }

    string firstShift = shiftStack.top();
    shiftStack.pop(); 

    for (int i = guardCount - 1; i >= 1; i--) {
        guards[i].shift = shiftStack.top();
        shiftStack.pop();
    }

    guards[0].shift = firstShift;

    cout << "\nShifts rotated successfully!\n";
    displayGuardSchedule(); 
}

////////////////////////////////////////////////////parking system/////////////////////////////////////////////////

bool Duplicate(int grid[5][5], int vehicle) {
    for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
    if (grid[i][j] == vehicle) {
    return true;
    }
    }
    }
    return false;
}


void entering(int grid[5][5]) {
    string type;

    for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
    if (grid[i][j] == 0) {
    int slotnum = i * 5 + j + 1;

    int vehiclenum;
    cout << "Enter Vehicle Number: ";
    cin >> vehiclenum;

    if (Duplicate(grid, vehiclenum)) {
    cout << "Vehicle number " << vehiclenum << " already exists! Please enter a different vehicle number." << endl;
    return;
    }

    cout << "Enter Vehicle Type (TRUCK, CAR, BIKE): ";
    cin >> type;

    if (type == "TRUCK" || type == "truck") {
    cout << "Your Parking Fee is 500" << endl;
    } else if (type == "CAR" || type == "car") {
    cout << "Your Parking Fee is 200" << endl;
    } else if (type == "BIKE" || type == "bike") {
    cout << "Your Parking Fee is 100" << endl;
    } else {
    cout << "Invalid Vehicle Type!" << endl;
    return;
    }

    grid[i][j] = vehiclenum;
    cout << "Vehicle " << vehiclenum << " (" << type << ") is parked at slot " << slotnum << endl;
    return;
    }
    }
    }
    cout << "Parking Full!" << endl;
}


void exiting(int grid[5][5]) {
    int vehiclenumb;
    cout << "Enter Vehicle Number you want to delete: ";
    cin >> vehiclenumb;

    for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
    if (grid[i][j] == vehiclenumb) {
    int slotnum = i * 5 + j + 1;
    grid[i][j] = 0;
    cout << "Vehicle number " << vehiclenumb << " is removed from slot " << slotnum << "." << endl;
    return;
    }
    }
    }

    cout << "Vehicle not found in the parking lot." << endl;
}

void searchVehicle(int grid[5][5]) {
    int vehiclenumbr;
    cout << "Enter Vehicle Number to search: ";
    cin >> vehiclenumbr;

    for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
    if (grid[i][j] == vehiclenumbr) {
    int slotnum = i * 5 + j + 1;
    cout << "Vehicle number " << vehiclenumbr << " is parked at slot " << slotnum << "." << endl;
    return;
    }
    }
    }

    cout << "Vehicle number " << vehiclenumbr << " is not found in the parking lot." << endl;
}

void gamingzone(){
	
	int choice;
    do {
        cout << "\n=== Arcade Menu ===\n";
        cout << "1. See Games\n";
        cout << "2. Play Game\n";
        cout << "3. Check Revenue\n";
        cout << "4. Exit\n";
        cout << "====================\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            	clearScreen();
                displayGames();
                break;
            case 2:
            	clearScreen();
                playGame();
                break;
            case 3:
            	clearScreen();
                viewRevenue();
                break;
            case 4:
                cout << "Thanks for visiting the arcade! See you next time!\n";
                break;
            default:
                cout << "Hmm, that's not a valid option. Try again.\n";
        }
    } while (choice != 4);

	
}

void displayGrid(int grid[5][5]) {
    cout << "\nCurrent Parking Grid:" << endl;
    for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 5; y++) {
    if (grid[x][y] == 0) {
    cout << setw(5) << "[ O ]";
    } else {
    cout << setw(5) << "[ " << grid[x][y] << " ]";
    }
    }
    cout << endl;
    }
}


// Function to manage parking system


void parkingSystem() {
    int grid[5][5] = {0}; // Initialize parking grid
    int choice;

    do {
        cout << "\n=== Parking System ===" << endl;
        cout << "1. Enter Vehicle" << endl;
        cout << "2. Exit Vehicle" << endl;
        cout << "3. Search Vehicle" << endl;
        cout << "4. Display Parking Grid" << endl;
        cout << "5. Exit Parking System" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice! Please enter a number between 1 and 5." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                entering(grid);
                break;
            case 2:
                exiting(grid);
                break;
            case 3:
                searchVehicle(grid);
                break;
            case 4:
                displayGrid(grid);
                break;
            case 5:
                cout << "Exiting Parking System..." << endl;
                break;
        }
    } while (choice != 5);
}

int main() {
    initializeMall();
    int choice;

    do {
        clearScreen();
        cout << "=== Mall Management System ===\n";
        cout << "1. Security Management\n";
        cout << "2. Outlet Management\n";
        cout << "3. Gaming Zone\n";
        cout << "4. Parking System\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate the main menu choice
        if (cin.fail() || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid option! Please select a number between 1 and 6.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                clearScreen();
                  int securityChoice;
            
			
			do{
			
                cout << "=== Security Management ===\n";
                cout << "1. Add Guard\n";
                cout << "2. View Guard Schedule\n";
                cout << "3. Rotate Guard Shifts\n";
                cout<<"4. Exit"<<endl;
                cout << "Enter your choice: ";
                
                cin >> securityChoice;
                cin.ignore();

                if (cin.fail() || securityChoice < 1 || securityChoice > 4) {
                    cin.clear();
                    cin.ignore( '\n');
                    cout << "Invalid choice! Please select a valid option.\n";
                    break;
                }
            
                switch (securityChoice) {
                    case 1:
                        addGuard();
                        break;
                    case 2:
                        clearScreen();
                        displayGuardSchedule();
                        break;
                    case 3:
                        clearScreen();
                        rotateShifts();
                        break;
                }
            } while (securityChoice != 4);
                break;
            }

            case 2: {
                clearScreen();
                int outletChoice;
                int floorIndex;
                string outletName, category;
         do{
		      
                cout << "1. Add Outlet\n";
                cout << "2. Delete Outlet\n";
                cout << "3. Display All Outlets\n";
                cout<<"4. Exit\n";
                cout << "Enter your choice: ";
              
                cin >> outletChoice;

                if (cin.fail() || outletChoice < 1 || outletChoice > 4) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid choice! Please select a valid option.\n";
                    break;
                }

             

                switch (outletChoice) {
                   
                   case 1: // Add Outlet
      
                cout << "FOR FLOOR 1 RENT IS 100000\n";
                cout << "FOR FLOOR 2 RENT IS 80000\n";
                cout << "FOR FLOOR 3 RENT IS 60000\n";
                cout << "FOR FLOOR 4 RENT IS 40000\n";
                cout << "FOR FLOOR 5 RENT IS 20000\n";
                cout << "3RD FLOOR IS JUST FOR FOOD OUTLET\n";
// Loop until a valid floor index is entered
while (true) {
    cout << "Enter floor index (1-5): ";
    cin >> floorIndex;

    // Validate floor index
    if (cin.fail() || floorIndex < 1 || floorIndex > 5) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid floor index. Please enter a number between 1 and 5.\n";
        continue; // Prompt again for floor index
    }
    break; // Valid floor index, exit the loop
}

cout << "ENTER CATEGORY OF YOUR SHOP (CLOTHING, FOOTWEAR, FOOD): ";
cin >> category;

// Validate category and floor-specific rules
if (floorIndex == 3 && category != "FOOD" && category != "food") {
    cout << "Only FOOD outlets can be added to FLOOR 3.\n";
    break; // Exit or break to avoid further processing
} else if (category != "CLOTHING" && category != "FOOTWEAR" && category != "food" && category != "clothing" && category != "footwear") {
    cout << "Invalid category! Please enter CLOTHING, FOOTWEAR, or FOOD.\n";
    break; // Exit or break to avoid further processing
}

cout << "ENTER THE NAME OF YOUR OUTLET: ";
cin.ignore(); // Clear the newline character from the input buffer
getline(cin, outletName);

// Validate outlet name
if (outletName.empty()) {
    cout << "Invalid outlet name. Please enter a valid name.\n";
    break; // Exit or break to avoid further processing
}

insertAtStart(floorIndex, outletName);

    break;


                    case 2:
                        cout << "Enter floor index (1-5): ";
                        cin >> floorIndex;

                        if (cin.fail() || floorIndex < 1 || floorIndex > 5) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid floor index. Please enter a number between 1 and 5.\n";
                            break;
                        }

                        cout << "Enter the name of outlet you want to delete: ";
                        cin.ignore();
                        getline(cin, outletName);

                        deleteOutlet(floorIndex, outletName);
                        break;

                    case 3:
                        cout << "Enter floor index (1-5): ";
                        cin >> floorIndex;

                        if (cin.fail() || floorIndex < 1 || floorIndex > 5) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid floor index. Please enter a number between 1 and 5.\n";
                            break;
                        }

                        displayAllOutlets(floorIndex);
                   
					  break;
                }
              
			    } while (outletChoice != 4) ;
				 break;
            }

            case 3:
                clearScreen();
                gamingzone();
                break;

            case 4:
                clearScreen();
                parkingSystem();
                break;


            case 5:
                cout << "Exiting the system... Goodbye!\n";
                break;
        }

        if (choice != 5) {
            cout << "\nPress any key to return to the main menu...\n";
            cin.get();
        }

    } while (choice != 5);

    return 0;
}
