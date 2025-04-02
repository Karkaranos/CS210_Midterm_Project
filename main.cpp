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


/// Defines the School Struct
/// School contains a name, address, city, state, and county as strings
/// It also contains pointers to a left and right School node
/// Manages variable initialization
struct School {
    string name;
    string address;
    string city;
    string state;
    string county;
    School* left;
    School* right;

    /// Constructor for struct School
    /// Initializes data variables
    /// Sets pointers to nullptrs
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

/// Defines the Class SchoolBST, or School Binary Search Tree
/// Private helper functions are recursive
/// Public functions can be called from other classes
/// Function List:
///     Constructor
///     Destructor
///     Insert
///     Pre-Order Traversal
///     In-Order Traversal
///     Post-Order Traversal
///     Delete By Name
///     Find By Name
class SchoolBST
{
// Private functions help main functions occur
// Paramater names are kept more ambiguous
private:
    //  Reference to the BST's root
    School* root;

    /// Helper function for Insert
    /// Uses recursion to find the best location for the new node and sets it
    /// Paramaters: potential parent and node to be added as a School*
    School* insertHelper(School* node, School* newSchool)
    {
        //  If the provided potential parent is null
        if (node == nullptr)
        {
            node = newSchool;
            return node;
        }

        //  If the name of this school is less than the parent's name
        if  (newSchool -> name < node->name)
        {
            //  Recursively call on the left subtree
            node -> left = insertHelper(node -> left, newSchool);
        }
        //  If the name of this school is equal to or greater than the parent's name
        else
        {
            //  Recursively call on the right subtree
            node -> right = insertHelper(node -> right, newSchool);
        }

        //  Return the parent node
        return node;
    }

    /// Deallocates the tree to help manage memory
    /// Recursively deletes all nodes in the tree
    /// Paramaters: node to be deleted as a School*
    void deleteTree(School* node)
    {
        //  No need to delete if the current node is null
        if (node == nullptr)
        {
            return;
        }

        //  Delete the left and right subtrees
        deleteTree(node->left);
        deleteTree(node->right);

        //  Delete this node
        delete node;
    }

    /// Helper function for deleting School nodes by name
    /// Uses recursion to find an instance of the school and deletes it
    /// Paramaters: node to search as a School*, school name to find as a string
    School* deleteByNameHelper(School* node, string name)
    {
        //  Return if the current node is empty
        if (node == nullptr)
        {
            return node;
        }

        //  If the name of this node is greater than the name to find
        if (node->name > name)
        {
            //  Recursively search the left subtree
            node -> left = deleteByNameHelper(node->left, name);
        }
        //  If the name of this node is less than the name to find
        else if (node-> name < name)
        {
            //  Recursively search the right subtree
            node -> right = deleteByNameHelper(node->right, name);
        }
        //  If the names are equal
        else
        {
            //  Case 1: The left pointer is null
            //  Handles instances with 0 children or only a right child
            if (node->left == nullptr)
            {
                School* temp = node->right;
                delete node;
                return temp;
            }

            //  Case 2: The right pointer is null (and the left was not)
            //  Handles remaining instances with 1 child
            if (node->right == nullptr)
            {
                School* temp = node->left;
                delete node;
                return temp;
            }

            //  Case 3: The node has two children
            School* temp = node->right;

            //  Search for the next greatest value in the tree
            //  AKA the minimum of the right child
            while (temp!=nullptr && temp->left != nullptr)
            {
                temp = temp->left;
            }
            temp->right = node->right;
            temp->left = node->left;
            delete(node);
            return temp;
        }
        //  Helps avoid errors
        return node;
    }

    /// Helper function for finding and displaying School nodes by name
    /// Uses recursion to find an instance of the school and display it
    /// Paramaters: node to search as a School*, school name to find as a string
    School* findByNameHelper(School* node, string name)
    {
        //  Return if the current node is empty
        if (node==nullptr)
        {
            return node;
        }

        // If the current node has the name being searched for, return it
        if (node->name == name)
        {
            return node;
        }

        //  If the current node's name is greater than the name to find
        if (node->name > name)
        {
            //  Recursively search the left tree
            return findByNameHelper(node->left, name);
        }

        //  If the current node's name is less than the name to find
        //  Recursively search the right tree
        return findByNameHelper(node->right, name);
    }

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

    /// Helper function for Pre-Order Traversal
    /// Uses recursion to display the schools, with the root of each subtree
        /// before the left and right children
    /// Paramaters: the starting node as a School*
    void preOrderTraversalHelper(School* node)
    {
        //  Returns if the current node is empty
        if (node == nullptr)
        {
            return;
        }

        //  Calls a helper function to display this node
        displayNode(node);

        //  Recursive calls for child nodes
        preOrderTraversalHelper(node->left);
        preOrderTraversalHelper(node->right);
    }

    /// Helper function for In-Order Traversal
    /// Uses recursion to display the schools, with the root of each subtree
    /// between the left and right children
    /// Paramaters: the starting node as a School*
    void inOrderTraversalHelper(School* node)
    {
        //  Returns if the current node is empty
        if (node == nullptr)
        {
            return;
        }

        //  Recursive call for the left child
        inOrderTraversalHelper(node->left);

        //  Calls a helper function to display this node
        displayNode(node);

        //  Recursive call for the right child
        inOrderTraversalHelper(node->right);
    }

    /// Helper function for Post-Order Traversal
    /// Uses recursion to display the schools, with the root of each subtree
    /// after the left and right children
    /// Paramaters: the starting node as a School*
    void postOrderTraversalHelper(School* node)
    {
        //  Returns if the current node is empty
        if (node == nullptr)
        {
            return;
        }

        //  Recursive calls for child nodes
        postOrderTraversalHelper(node->left);
        postOrderTraversalHelper(node->right);

        //  Calls a helper function to display this node
        displayNode(node);
    }
//  Public functions allow other functions to access the tree
//  Variable names are less ambigous here
public:

    /// Constructor for SchoolBST
    /// Initializes the root
    SchoolBST()
    {
        root = nullptr;
    }

    /// Destructor for SchoolBST
    /// Deallocates memory
    ~SchoolBST()
    {
        deleteTree(root);
    }

    /// Public function to insert a new school
    /// Calls private helper function
    /// Paramaters: School to add as a School*
    void insert(School* school)
    {
        //  Call to recursive helper function
        root = insertHelper(root, school);
    }

    /// Public function to perform a Pre-Order Traversal
    /// Calls private helper functions
    void preOrderTraversal()
    {
        cout << endl << "Pre-Order Traversal" << endl;

        //  Calls to private helpers to create table and recursively traverse tree
        displayHeader();
        preOrderTraversalHelper(root);

        cout << endl;
    }

    /// Public function to perform an In-Order Traversal
    /// Calls private helper functions
    void inOrderTraversal()
    {
        cout << endl << "In-Order Traversal" << endl;

        //  Calls to private helpers to create table and recursively traverse tree
        displayHeader();
        inOrderTraversalHelper(root);

        cout << endl;
    }

    /// Public function to perform a Post-Order Traversal
    /// Calls private helper functions
    void postOrderTraversal()
    {
        cout << endl << "Post-Order Traversal" << endl;

        //  Calls to private helpers to create table and recursively traverse tree
        displayHeader();
        postOrderTraversalHelper(root);

        cout << endl;
    }

    /// Public function to delete a school, given a name
    /// Calls private helper function
    /// Paramaters: School to delete as a string
    void deleteByName(string schoolName)
    {
        //  Call to recursive helper function
        root = deleteByNameHelper(root, schoolName);
    }

    /// Public function to find and display a school, given a name
    /// Calls private helper function
    /// Paramaters: School to find as a string
    void findByName(string schoolName) {
        //  Calls to private helpers to create table and find the requested school
        displayHeader();
        displayNode(findByNameHelper(root, schoolName));
    }

};
/*
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
    cout << "a) Display School information using a Pre-Order Traversal" << endl;
    cout << "b) Display School information using an In-Order Traversal" << endl;
    cout << "c) Display School information using a Post-Order Traversal" << endl;
    cout << "d) Search and Display School by Name " << endl;
    cout << "e) Delete a School by Name" << endl;
    cout << "f) Exit" << endl;
    cout << setfill('~') << setw(50) << "~" << setfill(' ') << endl;
}

/// Handles the main logic of the program
/// Creates a list of schools from an external CSV file
/// Reads in input from a user and calls corresponding functions

int main()
{

    //  Create the schoolBST
    SchoolBST schoolBST;

    //  Pull information from the file
    string fileName = "Schools.csv";
    vector<vector<string>> data = CSVReader::readCSV(fileName);

    // Adding all items to the BST
    // Index starts at 1 to remove the CSV file headers
    for (int i=1; i<data.size(); i++)
    {
        School* s = new School(data[i][0], data[i][1], data[i][2],
            data[i][3], data[i][4]);
        schoolBST.insert(s);
    }
    //  Initializes variables for looping menu
    char input = 'z';
    string name = "";

    //  Run until the user wants to end the program
    //  Displays the options menu and calls functions to carry out their choice
    while (input != 'f')
    {
        displayMenu();

        //  Take input from the user
        cin >> input;
        cin.ignore(100, '\n');

        /*
        //  Examine their input and take the correct course of action
        switch (input) {
            case 'a':   // Display School information using a Pre-Order Traversal
                //schoolBST.preOrderTraversal();
                break;
            case 'b':   // Display School information using an In-Order Traversal
                schoolBST.inOrderTraversal();
                break;
            case 'c':   // Display School information using a Post-Order Traversal
                schoolBST.postOrderTraversal();
                break;
            case 'd':   // Search and Display School by Name
                //  Gets a school name from the user
                cout << "Enter the name of the School to find: " << endl;
                getline(cin, name);
                schoolBST.findByName(name);
                break;
            case 'e':   //  Delete a School by Name
                //  Gets a school name from the user
                cout << "Enter the name of the School to delete: " << endl;
                getline(cin, name);
                schoolBST.deleteByName(name);
                break;
            case 'f':   // Exit
                break;
            default:    // Other input
                cout << "Invalid input." << endl;
                break;
        }
    }
}*/