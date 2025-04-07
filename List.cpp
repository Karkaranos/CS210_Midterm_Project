#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <compare>
using namespace std;


struct School {
    string name;
    string address;
    string city;
    string state;
    string county;
    School* next;

    School(string schoolName, string schoolAddress, string schoolCity, string schoolState, string schoolCounty) {
        name = schoolName;
        address = schoolAddress;
        city = schoolCity;
        state = schoolState;
        county = schoolCounty;
        next = nullptr;
    }
};

class SchoolList {
    School* head;
private:
    /// Helper function to display table header
    /// It creates and labels columns for each bit of data
    void displayHeader()
    {
        cout << left << setw(30) << "School Name " << setw(30) << "| Address " << setw(20) << "| City " <<
            setw(10) << "| State " << setw(20) << "| County" << endl;
        cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    }

    /// Helper function to display a school
    /// It formats and displays information from a provided node
    /// Paramaters: The node to be displayed as a School*
    void displayNode(School* node)
    {
        // Return if the current node is empty
        if (node == nullptr) {
            return;
        }
        cout << left << setw(30) << node ->name << "| " << setw(28) << node->address << "| " << setw(18) <<
                node->city << "| " <<  setw(8) << node->state << "| " <<  setw(18) << node->county << endl;

    }
public:
    SchoolList() : head(nullptr) {}

    void insertFirst(School school)
    {
        School *temp = head;
        head = new School(school);
        head->next = temp;
    }

    void insertLast(School school) {
        if (head == nullptr) {
            head = new School(school);
            head->next = nullptr;
        }
        else
        {
            School *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = new School(school);
            temp->next->next = nullptr;
        }
    }

    void deleteByName(string schoolName)
    {
        if (head == nullptr) {
            cout << "School list is empty." << endl;
            return;
        }
        if (head->name == schoolName) {
            head = head->next;
            cout << "Deleted " << schoolName << "." << endl;
            return;
        }
        School *temp = head;
        while (temp->next != nullptr)
        {
            if (temp->next->name == schoolName)
            {
                temp->next = temp->next->next;
                cout << "Deleted " << schoolName << "." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << schoolName << " not found." << endl;
    }

    void findByName(string schoolName)
    {
        if (head == nullptr) {
            cout << "School list is empty." << endl;
            return;
        }

        School *temp = head;
        while (temp->next != nullptr)
        {
            if (temp->name == schoolName)
            {
                cout << schoolName << " found." << endl;
                displayHeader();
                displayNode(temp);
                return;
            }
            temp = temp->next;
        }
        cout << schoolName << " not found." << endl;
        return;
    }

    void display()
    {
        cout << endl;
        displayHeader();
        cout << left << setw(30) << "School Name " << setw(30) << "| Address " << setw(20) << "| City " <<
            setw(10) << "| State " << setw(20) << "| County" << endl;
        cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
        School *temp = head;
        while (temp != nullptr)
        {
            cout << left << setw(30) << temp ->name << "| " << setw(28) << temp->address << "| " << setw(18) <<
                temp->city << "| " <<  setw(8) << temp->state << "| " <<  setw(18) << temp->county << endl;
            temp = temp->next;

        }

    }

};


class ListCSVReader {
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


void listDisplayMenu()
{
    cout << setfill('~') << setw(50) << "~" << setfill(' ') << endl;
    cout << "Enter the letter corresponding with the action you wish to take." << endl;
    cout << "a) Display School information" << endl;
    cout << "b) Search for School by Name" << endl;
    cout << "c) Delete a School by Name" << endl;
    cout << "d) Exit" << endl;
    cout << setfill('~') << setw(50) << "~" << setfill(' ') << endl;
}

int main()
{
    SchoolList schoolList;

    string fileName = "Schools.csv";
    vector<vector<string>> data = ListCSVReader::readCSV(fileName);

    // Adding all items to the list's tail
    // Index starts at 1 to remove the CSV file headers
    for (int i=1; i<data.size(); i++)
    {
        School* s = new School(data[i][0], data[i][1], data[i][2],
            data[i][3], data[i][4]);
        schoolList.insertLast(*s);
    }

    cout << "Schools loaded." << endl;

    /*
    char input = 'z';

    string name = "";
    while (input != 'd')
    {
        listDisplayMenu();
        cin >> input;
        cin.ignore(100, '\n');
        switch (input) {
            case 'a':
                schoolList.display();
                break;
            case 'b':
                cout << "Enter the name of the School to find: " << endl;
                getline(cin, name);
                schoolList.findByName(name);
                break;
            case 'c':
                cout << "Enter the name of the School to delete: " << endl;
                getline(cin, name);
                schoolList.deleteByName(name);
                break;
            case 'd':
                break;
            default:
                cout << "Invalid input." << endl;
                break;
        }
    }*/
}
