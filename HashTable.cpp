#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <compare>
#include <unordered_map>
#include "Timer.h"
using namespace std;

/// Defines the School Struct
/// School contains a name, address, city, state, and county as strings
/// Contains a reference to the key for easier display
/// Manages variable initialization
///

struct School {
    int key;
    string name;
    string address;
    string city;
    string state;
    string county;
    School* next;

    /// Constructor for struct School
    /// Initializes data variables
    School(string schoolName, string schoolAddress, string schoolCity, string schoolState, string schoolCounty) {
        name = schoolName;
        address = schoolAddress;
        city = schoolCity;
        state = schoolState;
        county = schoolCounty;
        next = nullptr;
    }

    /// Mutator for int Key
    /// Paramaters: Key value as an int
    void SetKey(int keyVal) {
        key = keyVal;
    }
};

class SchoolHashList {
public:
    School* justDeleted;
    School* head;

    SchoolHashList() {
        head = nullptr;
    }


    void insert(School school) {
        if (head == nullptr || head->name == school.name) {
            head = new School(school);
        }
        else {
            School *temp = head;
            while (temp->next != nullptr)
            {
                if (temp->next -> name == school.name) {
                    return;
                }
                temp = temp->next;
            }
            temp->next = new School(school);
            temp->next->next = nullptr;
        }
    }

    vector<School*> split() {
        cout << "Entered split" << endl;
        vector<School*> schools;
        School* node = head;
        while (node!=nullptr) {
            schools.push_back(node);
            node = node->next;
        }
        return schools;
    }

    ///This item should look through items in the list
    char deleteSchoolFromList(string name)
    {
        School* node = head;

        // If the head is null, the list is null.
        // Return 'd' to indicate empty list
        if (head == nullptr) {
            justDeleted = nullptr;
            return 'd';
        }

        //If the head is the school to be deleted
        //Save a reference to the head and set head to the next node
        //Return 't' for found
        if (head -> name == name)
        {
            justDeleted = head;
            head = head->next;
            return 't';
        }

        //If the next node is not null
        while (node->next!=nullptr)
        {
            //If the next node is the school to be deleted
            if (node->next ->name == name) {

                //Save a reference to the node and set this node's next to the next next node
                //Return 't' for found
                justDeleted = node->next;
                node -> next = node -> next -> next;
                return 't';
            }
            node = node->next;
        }

        //It's something with a hashkey of -84. it only happens with that key
        cout << "FAILURE: COULD NOT FIND " << name << endl;
        justDeleted = nullptr;
        return 'f';

    }

    School* findSchoolInList(string name) {
        School* node = head;
        while (node!=nullptr)
        {
            if (node->name == name) {
                return node;
            }
            node = node->next;

        }
        return nullptr;
    }

};

/// Defines the Class SchoolHash, or School HashMap
/// Private helper functions are called to consolidate calls
/// Public functions can be called from other classes
/// Function List:
///     Constructor
///     Destructor
///     Insert
///     Display
///     Delete By Name
///     Find By Name
class SchoolHash
{
// Private functions help main functions occur
private:
    //  Creates the Hashmap
    unordered_map<int, SchoolHashList> schools;

    //  Controls information about the hashmap for the algorithm
    int base = 43;
    int tableSize = 100;

    /// Helper function for many things
    /// Creates a Hash Key for a school given the school name
    /// Uses a prime number to reduce collisions
    int polynomialHash(string key) {
        long hash = 0;
        long power = 1;
        for (char c:key) {
            hash = (hash + (c - 'a'+1) * power) % tableSize;
            power = (power*base) % tableSize;
        }
        return hash;
    }

    /// Helper function to display table header
    /// It creates and labels columns for each bit of data
    void displayHeader()
    {
        cout << left << setw(7) << "Key" << setw(30) << "| School Name " << setw(30) << "| Address " << setw(20) << "| City " <<
            setw(10) << "| State " << setw(20) << "| County" << endl;
        cout << setfill('-') << setw(107) << "-" << setfill(' ') << endl;
    }

    /// Helper function to display a school
    /// It formats and displays information from a provided key
    /// Paramaters: The entry to be displayed as a School*
    void displayEntry(School* node)
    {
        // Return if the current node is empty
        if (node == nullptr) {
            return;
        }
        cout << left << setw(7) << node ->key << "| " << setw(28) << node ->name << "| " << setw(28) << node->address << "| " << setw(18) <<
                node->city << "| " <<  setw(8) << node->state << "| " <<  setw(18) << node->county << endl;

    }

//  Public functions allow other functions to access the map
public:

    /// Constructor for SchoolHash
    /// Clears lingering data
    SchoolHash() {
        schools.clear();
    }

    /// Destructor for SchoolHash
    /// Deallocates Memory
    ~SchoolHash() {
        schools.clear();
    }

    /// Public function to insert a new school
    /// Cals private hashkey function
    /// Paramaters: School to add as a School*
    void insert(School* school) {

        //cout << "enter" << school->name << endl;
        int hashKey = polynomialHash(school->name);
        school->SetKey(hashKey);
        SchoolHashList second;

        if (schools.find(hashKey) == schools.end()) {
            //cout << "case1";
            second = SchoolHashList();
        }
        else {
            //cout << "case2";
            second = schools.find(hashKey)->second;
        }
        second.insert(*school);
        schools[school->key] = second;
    }

    /// Public function to display the school Table
    /// Calls private helper functions
    void display()
    {
        displayHeader();
        for (auto entry : schools) {
            vector<School*> splitSchools = entry.second.split();
            for (School* school : splitSchools) {
                displayEntry(school);
            }
        }
    }

    /// Public function to delete a school, given a name
    /// Cals private hashkey function
    /// Paramaters: School to delete as a string
    School* deleteByName(string name)
    {

        int hashKey = polynomialHash(name);
        cout << name << " : " << hashKey << endl;
        unordered_map<int, SchoolHashList>::iterator it = schools.find(hashKey);
        if (it != schools.end()) {
            auto schoolList = it->second;

            char result = schoolList.deleteSchoolFromList(name);
            if (result =='t') {
                cout << name << " deleted from database." << endl;
                return schoolList.justDeleted;
            }
            else if (result == 'd') {
                schools.erase(hashKey);
                cout << endl;
                return schoolList.justDeleted;
            }


        }
        //cout << "School not found in database." << endl;
        return nullptr;

    }

    /// Public function to find and display a school, given a name
    /// Calls private hashkey functiona
    /// Paramaters: School to find as a string
    void findByName(string name)
    {
        int hashKey = polynomialHash(name);
        unordered_map<int, SchoolHashList>::iterator it = schools.find(hashKey);
        if (it != schools.end()) {
            auto schoolList = it->second;

            School* result = schoolList.findSchoolInList(name);
            /*if (result == nullptr) {
                //cout << "School not found in database." << endl;
                return;
            }
            else {
                //displayHeader();
                //displayEntry(result);
                return;
            }*/

        }
        //cout << "School not found in database." << endl;
    }

};



/// Provided class
class hashCSVReader {
public:
    static vector<vector<string>> readCSV(const string& filename) {
        ifstream file(filename);
        vector<vector<string>> data;
        string line, word;

        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return data;
        }

        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> row;
            while (getline(ss, word, ',')) {
                row.push_back(word);
            }
            data.push_back(row);
        }
        file.close();
        return data;
    }
};


/// Non-Class-Specifiec function to display a formatted menu with options available to the user
void hashDisplayMenu()
{
    cout << setfill('~') << setw(50) << "~" << setfill(' ') << endl;
    cout << "Enter the letter corresponding with the action you wish to take." << endl;
    cout << "a) Display Schools and Positions" << endl;
    cout << "b) Search and Display School by Name " << endl;
    cout << "c) Delete a School by Name" << endl;
    cout << "d) Exit" << endl;
    cout << setfill('~') << setw(50) << "~" << setfill(' ') << endl;
}

/// Handles the main logic of the program
/// Creates a list of schools from an external CSV file
/// Reads in input from a user and calls corresponding functions

int main()
{
    SchoolHash schoolHash;
    Timer t;

    string filename = "Illinois_Schools.csv";
    //Import Illinois data first
    vector<vector<string>> data = hashCSVReader::readCSV(filename);
    string results = "SchoolHashData.csv";
    ofstream outFile(results);
    if (!outFile.is_open())
    {
        cerr << "Failed to open " << results << "for writing.\n";
        return 1;
    }


    outFile << "List" << endl;
    outFile << "Index, Insert, Find, Delete" << endl;
    float f1 = 0;
    float f2 = 0;
    float f3 = 0;
    float f4 = 0;
    float f5 = 0;
    float f6 = 0;
    int findMe;
    int savedDataSize = data.size();
    srand(time(NULL));
    // Adding all items to the list's tail
    // Index starts at 1 to remove the CSV file headers
    for (int i=1; i<data.size(); i++)
    {
        School* s = new School(data[i][0], data[i][1], data[i][2],
            data[i][3], data[i][4]);
        f1 = t.get_time();
        schoolHash.insert(s);
        f2 = t.get_time();


        findMe = rand()%i + 1;
        if (findMe == i) {
            findMe = i-1;
        }
        if (findMe == 0) {
            findMe = 1;
        }

        f3 = t.get_time();
        schoolHash.findByName(data[findMe][0]);
        f4 = t.get_time();


        findMe = rand()%i + 1;
        if (findMe == i) {
            findMe = i-1;
        }
        if (findMe == 0) {
            findMe = 1;
        }

        f5 = t.get_time();
        School* saved = schoolHash.deleteByName(data[findMe][0]);
        f6 = t.get_time();

        if (saved == nullptr) {
            cout << "Saved is null on iteration " << i << endl;
        }

        schoolHash.insert(saved);


        outFile << i << "," << f2-f1 << "," << f4-f3 << "," << f6-f5 << endl;
    }

    cout << "Finished Illinois Schools" << endl;

    schoolHash.display();
/*
    filename = "USA_Schools.csv";
    data = hashCSVReader::readCSV(filename);
    // Adding all items to the list's tail
    // Index starts at 1 to remove the CSV file headers
    School* s;
    for (int i=1; i<data.size(); i++)
    {
        if (data[i].size() <5) {
            s = new School(data[i][0], data[i][1], data[i][2],
                data[i][3], "Unknown");

        }
        else {
            s = new School(data[i][0], data[i][1], data[i][2],
                data[i][3], data[i][4]);
        }
        f1 = t.get_time();
        schoolHash.insert(s);
        f2 = t.get_time();


        findMe = rand()%i + 1;
        if (findMe == i) {
            findMe = i-1;
        }
        if (findMe == 0) {
            findMe = 1;
        }

        f3 = t.get_time();
        schoolHash.findByName(data[findMe][0]);
        f4 = t.get_time();

        findMe = rand()%i + 1;
        if (findMe == i) {
            findMe = i-1;
        }
        if (findMe == 0) {
            findMe = 1;
        }

        f5 = t.get_time();
        School* saved = schoolHash.deleteByName(data[findMe][0]);
        f6 = t.get_time();

        schoolHash.insert(saved);



        outFile << i << "," << f2-f1 << "," << f4-f3 << "," << f6-f5 << endl;
    }
    cout << "Finished USA Schools." << endl;*/

}
/*
void hashOldMain() {

    //  Create the schoolBST
    SchoolHash schoolHash;

    //  Pull information from the file
    string fileName = "Schools.csv";
    vector<vector<string>> data = hashCSVReader::readCSV(fileName);

    // Adding all items to the BST
    // Index starts at 1 to remove the CSV file headers
    for (int i=1; i<data.size(); i++)
    {
        School* s = new School(data[i][0], data[i][1], data[i][2],
            data[i][3], data[i][4]);
        schoolHash.insert(s);
    }


    //  Initializes variables for looping menu
    char input = 'z';
    string name = "";



    //  Run until the user wants to end the program
    //  Displays the options menu and calls functions to carry out their choice
    while (input != 'd')
    {
        hashDisplayMenu();

        //  Take input from the user
        cin >> input;
        cin.ignore(100, '\n');


        //  Examine their input and take the correct course of action
        switch (input) {
            case 'a':   // Display School information and Hash Keys
                schoolHash.display();
                break;
            case 'b':   // Search and Display School by Name
                //  Gets a school name from the user
                cout << "Enter the name of the School to find: " << endl;
                getline(cin, name);
                schoolHash.findByName(name);
                break;
            case 'c':   //  Delete a School by Name
                //  Gets a school name from the user
                cout << "Enter the name of the School to delete: " << endl;
                getline(cin, name);
                schoolHash.deleteByName(name);
                break;
            case 'd':   // Exit
                break;
            default:    // Other input
                cout << "Invalid input." << endl;
                break;
        }
    }
}*/