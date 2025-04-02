#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <compare>
#include <unordered_map>
using namespace std;

/// Defines the School Struct
/// School contains a name, address, city, state, and county as strings
/// Manages variable initialization
struct School {
    int key;
    string name;
    string address;
    string city;
    string state;
    string county;

    /// Constructor for struct School
    /// Initializes data variables
    School(string schoolName, string schoolAddress, string schoolCity, string schoolState, string schoolCounty) {
        name = schoolName;
        address = schoolAddress;
        city = schoolCity;
        state = schoolState;
        county = schoolCounty;
    }

    void SetKey(int keyVal) {
        key = keyVal;
    }
};

class SchoolHash
{
private:
    unordered_map<int, School*> schools;
    int base = 43;
    int tableSize = 100;

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
        cout << left << setw(10) << "Key" << setw(30) << "| School Name " << setw(30) << "| Address " << setw(20) << "| City " <<
            setw(10) << "| State " << setw(20) << "| County" << endl;
        cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    }

    /// Helper function to display a school
    /// It formats and displays information from a provided node
    /// Paramaters: The node to be displayed as a School*
    void displayEntry(School* node)
    {
        // Return if the current node is empty
        if (node == nullptr) {
            return;
        }
        cout << left << setw(10) << node ->key << "| " << setw(28) << node ->name << "| " << setw(28) << node->address << "| " << setw(18) <<
                node->city << "| " <<  setw(8) << node->state << "| " <<  setw(18) << node->county << endl;

    }
public:
    SchoolHash() {
        schools.clear();
    }

    void insert(School* school) {
        int hashKey = polynomialHash(school->name);
        school->SetKey(hashKey);
        schools[school->key] = school;
    }

    void display()
    {
        displayHeader();
        for (auto entry : schools) {
            displayEntry(entry.second);
        }
    }

    void deleteByName(string name)
    {
        int hashKey = polynomialHash(name);
        unordered_map<int, School*>::iterator it = schools.find(hashKey);
        if (it != schools.end()) {
            auto school = it->second;
            cout << "Deleted " << school->name << endl;
            schools.erase(it);
        }
        else {
            cout << "School not found in database." << endl;
        }

    }

    void findByName(string name)
    {
        int hashKey = polynomialHash(name);
        unordered_map<int, School*>::iterator it = schools.find(hashKey);
        if (it != schools.end()) {
            displayHeader();
            displayEntry(it->second);
        }
        else {
            cout << "School not found in database." << endl;
        }
    }

};



/// Provided class
class CSVReader {
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
void displayMenu()
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

    //  Create the schoolBST
    SchoolHash schoolHash;

    //  Pull information from the file
    string fileName = "Schools.csv";
    vector<vector<string>> data = CSVReader::readCSV(fileName);

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
        displayMenu();

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
}