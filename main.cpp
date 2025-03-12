#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <compare>
using namespace std;

/*
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

    School* findByName(string schoolName)
    {
        if (head == nullptr) {
            cout << "School list is empty." << endl;
            return nullptr;
        }

        School *temp = head;
        while (temp->next != nullptr)
        {
            if (temp->name == schoolName)
            {
                cout << schoolName << " found." << endl;
                return temp;
            }
            temp = temp->next;
        }
        cout << schoolName << " not found." << endl;
        return nullptr;
    }

    void display()
    {
        cout << endl;
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

};*/

struct School {
    string name;
    string address;
    string city;
    string state;
    string county;
    School* left;
    School* right;

    School(string schoolName, string schoolAddress, string schoolCity, string schoolState, string schoolCounty) {
        name = schoolName;
        address = schoolAddress;
        city = schoolCity;
        state = schoolState;
        county = schoolCounty;
        left = nullptr;
        right = nullptr;
    }
};

class SchoolBST
{
private:
    School* root;
    School* insertRecursive(School* node, School* school)
    {
        if (node == nullptr) {
            node = school;
            return school;
        }
        if  (school -> name < node->name)
        {
            node -> left = insertRecursive(node -> left, school);
        }
        else
        {
            node -> right = insertRecursive(node -> right, school);
        }
        return node;
    }

    void deleteTree(School* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    School* deleteByNameHelper(School* node, string schoolName)
    {
        if (node == nullptr) {
            return node;;
        }
        if (node->name == schoolName)
        {
            //  Case 1: Node has no children
            if (node->left == nullptr && node->right == nullptr) {
                School* temp = node->right;
                delete node;
                cout << "Deletion case 1" << endl;
                return temp;
            }
            //  Case 2: Node has two children
            if (node->left != nullptr && node->right != nullptr)
            {
                School* temp = node->right;
                while (temp!=nullptr && temp->left != nullptr)
                {
                    temp = temp->left;
                }
                if (temp != node->right) {
                    temp->right = node->right;
                }
                else {
                    temp->right = nullptr;
                }
                temp->left = node->left;
                delete(node);
                cout << "Deletion case 3" << endl;
                return temp;

            }
            //  Case 3: Node has one child
            else {
                School* temp = node;
                (node->left == nullptr) ? node = node->left : node= node->right;
                delete temp;
                cout << "Deletion case 2" << endl;
                return temp;


            }

        }
        if (node->name < schoolName)
        {
            node -> left = deleteByNameHelper(node->left, schoolName);
        }
        node -> right = deleteByNameHelper(node->right, schoolName);
        return node;

    }

    School* findByNameHelper(School* node, string schoolName)
    {
        if (node==nullptr) {
            return node;
        }
        if (node->name == schoolName) {
            return node;
        }
        if (node->name < schoolName) {
            return findByNameHelper(node->left, schoolName);
        }
        return findByNameHelper(node->right, schoolName);
    }

    void preOrderTraversalHelper(School* node)
    {
        if (node == nullptr) return;
        displayNode(node);
        preOrderTraversalHelper(node->left);
        preOrderTraversalHelper(node->right);
    }

    void inOrderTraversalHelper(School* node)
    {
        if (node == nullptr) return;
        inOrderTraversalHelper(node->left);
        displayNode(node);
        inOrderTraversalHelper(node->right);
    }

    void postOrderTraversalHelper(School* node)
    {
        if (node == nullptr) return;
        postOrderTraversalHelper(node->left);
        postOrderTraversalHelper(node->right);
        displayNode(node);
    }
public:

    SchoolBST()
    {
        root = nullptr;
    }

    ~SchoolBST() {
        //deleteTree(root);
    }
    void insert(School* school)
    {
        root = insertRecursive(root, school);
    }

    //Modified files begin here!
    void preOrderTraversal()
    {
        cout << endl << "Pre-Order Traversal" << endl;
        displayHeader();
        preOrderTraversalHelper(root);
        cout << endl;
    }

    void inOrderTraversal()
    {
        cout << endl << "In-Order Traversal" << endl;
        displayHeader();
        inOrderTraversalHelper(root);
        cout << endl;
    }

    void postOrderTraversal() {
        cout << endl << "Post-Order Traversal" << endl;
        displayHeader();
        postOrderTraversalHelper(root);
        cout << endl;
    }

    void deleteByName(string name) {
        root = deleteByNameHelper(root, name);
    }


    void displayHeader() {
        cout << left << setw(30) << "School Name " << setw(30) << "| Address " << setw(20) << "| City " <<
            setw(10) << "| State " << setw(20) << "| County" << endl;
        cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    }

    void displayNode(School* node) {
        cout << left << setw(30) << node ->name << "| " << setw(28) << node->address << "| " << setw(18) <<
                node->city << "| " <<  setw(8) << node->state << "| " <<  setw(18) << node->county << endl;

    }

    void findByName(string name) {

    }

};
;

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


void displayMenu()
{
    cout << setfill('~') << setw(50) << "~" << setfill(' ') << endl;
    cout << "Enter the letter corresponding with the action you wish to take." << endl;
    cout << "a) Display School information using a Pre-Order Traversal" << endl;
    cout << "b) Display School information using an In-Order Traversal" << endl;
    cout << "c) Display School information using a Post-Order Traversal" << endl;
    cout << "d) Search and Display School by Name " << endl;
    cout << "e) Delete a School by Name" << endl;
    cout << "f) Exit" << endl;
    cout << setfill('~') << setw(50) << "~" << setfill(' ') << endl;
}

int main()
{
    SchoolBST schoolBST;
    /*School* s = new School("University of Minnesota","1501 W Bradley Avenue","Peoria","IL","Peoria");
    schoolBST.insert(s);
    s = new School("Wayzata", "idfk", "Plymouth", "MN", "Hennepin");
    schoolBST.insert(s);
    s = new School("Bradley University", "idk", "Minneapolis", "MN", "Hennepin");
    schoolBST.insert(s);
    schoolBST.inOrderTraversal();
    schoolBST.preOrderTraversal();
    schoolBST.postOrderTraversal();
    schoolBST.deleteByName("University of Minnesota");
    schoolBST.inOrderTraversal();*/


    string fileName = "Schools.csv";
    vector<vector<string>> data = CSVReader::readCSV(fileName);

    // Adding all items to the list's tail
    // Index starts at 1 to remove the CSV file headers
    for (int i=1; i<data.size(); i++)
    {
        School* s = new School(data[i][0], data[i][1], data[i][2],
            data[i][3], data[i][4]);
        schoolBST.insert(s);
    }

    cout << "Schools loaded." << endl;

    char input = 'z';

    string name = "";
    while (input != 'f')
    {
        displayMenu();
        cin >> input;
        cin.ignore(100, '\n');
        switch (input) {
            case 'a':
                schoolBST.preOrderTraversal();
                break;
            case 'b':
                schoolBST.inOrderTraversal();
                break;
            case 'c':
                schoolBST.postOrderTraversal();
                break;
            case 'd':
                cout << "Enter the name of the School to find: " << endl;
                getline(cin, name);
                schoolBST.findByName(name);
                break;
            case 'e':
                cout << "Enter the name of the School to delete: " << endl;
                getline(cin, name);
                schoolBST.deleteByName(name);
                break;
            case 'f':
                break;
            default:
                cout << "Invalid input." << endl;
                break;
        }
    }
}