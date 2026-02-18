#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#define MAX_ENTRIES 50

void menu(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);
void get_student_data(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);
void save_entries(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);
void display_saved_entries(string& filename);
void display_pending_entries(string names[MAX_ENTRIES], int ages[MAX_ENTRIES]);
void add_entry(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);

int main(void) {
    string names[MAX_ENTRIES] = {""};
    int ages[MAX_ENTRIES] = {0};
    string filename("students.txt");

    menu(names, ages, filename);

    return 0;
}

void menu(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename) {
    int option = 0; 
    cout << "--- Student Database ---" << endl;
    do {
        cout << "\n[1] Display" << endl;
        cout << "[2] Modify" << endl;
        cout << "[3] Save" << endl;
        cout << "[4] Exit" << endl;
        cout << "\nEnter an option: ";

        if (!(cin >> option)) {
            cout << "Please pick a valid option." << endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }

        switch (option) {
        case 1:
            display_saved_entries(filename);
            break;
        case 2:
            add_entry(names, ages, filename);
            break;
        case 3:
            save_entries(names, ages, filename);
            break;
        case 4:
            cout << "\nGoodbye!" << endl;
            break;
        default:
            cout << "Please pick a valid option." << endl;
        }

    } while (option != 4);
}

void save_entries(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename) {
    ofstream file(filename, std::ios::app);    
    if (!file.is_open()) {
        cout << "An error occurred while attempting to open " << filename << endl;
        return;
    }

    for (int i = 0; i < MAX_ENTRIES; i++) {
        // only save lines with content, the lines without
        // will show zero
        if (!(ages[i] == 0 || names[i] == "")) {
            file << ages[i] <<  " " << names[i] << endl; 
        }
    }
    
    cout << "\nYou have saved the entries." << endl;

    file.close();
}

int get_line_count(string& filename) {
    int line_count = 0;
    string line;
    ifstream count_file(filename);
    while (getline(count_file, line)) {
        if (!line.empty()) {
            line_count++;
        }    
    }
    count_file.close();
    return line_count;
}

void display_saved_entries(string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "An error occurred while attempting to open " << filename << endl;
        return;
    }

    string line;
    int line_count = 0;
    cout << "\n[" << filename << "]" << endl;
    while (getline(file, line)) {
        cout << line << endl;
        line_count++;
    }
    file.close();

    if (line_count == 0) {
        cout << "There was nothing to display." << endl;    
        return;
    }
}

void display_pending_entries(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename) {
    cout << "\n[PENDING ENTRIES]" << endl;
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (i == 0) {
            ifstream file(filename);
            if (!file.is_open()) {
                cout << "An error occurred while attempting to open " << filename << endl;
                return;
            }
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
    }

    int line_count = get_line_count(filename);
    cout << ages[line_count + 1] << " " << names[line_count + 1] << endl;
}

void add_entry(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename) {
    ofstream file(filename, std::ios::app);    
    if (!file.is_open()) {
        cout << "An error occurred while attempting to open " << filename << endl;
        return;
    }

    int line_count = get_line_count(filename);
    if (line_count < MAX_ENTRIES) {
        cout << "\nEnter an age: ";
        cin >> ages[line_count + 1];
        std::cin.ignore();

        cout << "Enter a full name: ";
        getline(std::cin, names[line_count + 1]);
    } else {
        cout << "You can only have a maximum of 50 students." << endl;
        return;
    }

    display_pending_entries(names, ages, filename);
}
