#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct School {
    string name;
    string address;
    string city;
    string state;
    string country;
    School* next;

    School(string schoolName, string schoolAddress, string schoolCity, string schoolState, string schoolCountry) {
        name = schoolName;
        address = schoolAddress;
        city = schoolCity;
        state = schoolState;
        country = schoolCountry;
        next = nullptr;
    }
};

class SchoolList {
    School* head;
public:
    SchoolList() : head(nullptr) {}

    void insertFirst(School school)
    {
        School *temp = head;
        head = new School(school);
        head->next = temp;
    }

}

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