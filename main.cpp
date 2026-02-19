#include <fstream>
#include <iomanip>
#include <ios>
#include <limits>
#include <iostream>
#include <string>

using namespace std;

#define MAX_ENTRIES 50

void menu(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);
void save_entries(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);
void display_saved_entries(string& filename);
void display_pending_entries(string names[MAX_ENTRIES], int ages[MAX_ENTRIES]);
void add_entry(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);
void modify_entry(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename, int line);
int get_line_count(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);
void get_oldest_student(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);
void get_youngest_student(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);
void get_average_age(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename);

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
        cout << "\n[1] Display Entries" << endl;
        cout << "[2] Add Entry" << endl;
        cout << "[3] Modify Entry" << endl;
        cout << "[4] Get Youngest Student" << endl;
        cout << "[5] Get Oldest Student" << endl;
        cout << "[6] Get Average Age" << endl;
        cout << "[7] Save Entries" << endl;
        cout << "[8] Exit" << endl;
        cout << "\nEnter an option: ";

        if (!(cin >> option)) {
            cout << "Please pick a valid option." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        int line = 0;
        switch (option) {
        case 1:
            display_saved_entries(filename);
            break;
        case 2:
            add_entry(names, ages, filename);
            break;
        case 3:
            display_saved_entries(filename);
            cout << "\nEnter a record number to modify: ";
            cin >> line;
            modify_entry(names, ages, filename, line);
            break;
        case 4:
            get_youngest_student(names, ages, filename);
            break;
        case 5:
            get_oldest_student(names, ages, filename);
            break;
        case 6:
            get_average_age(names, ages, filename);
            break;
        case 7:
            save_entries(names, ages, filename);
            break;
        case 8:
            cout << "\nGoodbye!" << endl;
            break;
        default:
            cout << "Please pick a valid option." << endl;
        }

    } while (option != 8);
}

void save_entries(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename) {
    ofstream file(filename);    
    if (!file.is_open()) {
        cout << "An error occurred while attempting to open " << filename << endl;
        return;
    }

    for (int i = 0; i <= MAX_ENTRIES; i++) {
        // only save lines with content, the lines without
        // will show zero
        if (!(ages[i] == 0 || names[i] == "")) {
            file << ages[i] <<  " " << names[i] << endl; 
            ages[i] = 0;
            names[i] = "";
        }
    }
    
    cout << "\nYou have saved the entries." << endl;

    file.close();
}

int get_line_count(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "An error occurred while attempting to open " << filename << endl;
        return 0;
    }

    int line_count = 0;
    while (file >> ages[line_count]) {
        file.ignore();
        getline(file, names[line_count]);
        line_count++;
    }
    file.close();

    return line_count;
}

void display_saved_entries(string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "The file '" << filename << "' does not exist. Creating it now." << endl;
        ofstream out(filename);
        out << "";
        return;
    }

    string line;
    int line_count = 0;
    cout << "\n[" << filename << "]" << endl;
    while (getline(file, line)) {
        cout << line_count + 1 << ": " << line << endl;
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
            int line_count = 0;
            while (getline(file, line)) {
                cout << line_count + 1 << ": " << line << endl;
                line_count++;
            }
            file.close();
        }

    }
    int pending_entry_line = get_line_count(names, ages, filename) + 1;
    if (!(ages[pending_entry_line] == 0 || names[pending_entry_line] == "")) {
        cout << pending_entry_line << ": " << ages[pending_entry_line] << " " << names[pending_entry_line] << endl;
    }
}

void add_entry(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename) {
    ofstream file(filename, ios::app);    
    if (!file.is_open()) {
        cout << "An error occurred while attempting to open " << filename << endl;
        return;
    }

    int line_count = get_line_count(names, ages, filename);
    if (line_count < MAX_ENTRIES) {
        // FIX: input validation
        cout << "\nEnter an age: ";
        if (!(cin >> ages[line_count + 1])) {
            cout << "The age entered was invalid." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore();

        cout << "Enter a full name: ";
        if (!(getline(cin, names[line_count + 1]))) {
            cout << "The full name entered was invalid." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
    } else {
        cout << "You can only have a maximum of 50 students." << endl;
        return;
    }

    display_pending_entries(names, ages, filename);
}

void modify_entry(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename, int line) {
    if (line < 1 || line > MAX_ENTRIES) {
        cout << "Please enter a valid record number." << endl;
        return;
    }

    ifstream in_file(filename);
    if (!in_file.is_open()) {
        cout << "An error occurred while attempting to open " << filename << endl;
        return;
    }

    int line_count = 0;
    while (in_file >> ages[line_count]) {
        in_file.ignore();
        getline(in_file, names[line_count]);
        line_count++;
    }
    in_file.close();

    if (line > line_count) {
        cout << "Please enter a valid record number." << endl;
        return;
    }

    // FIX: input validation
    cout << "\nEnter an age: ";
    if (!(cin >> ages[line - 1])) {
        cout << "The age entered was invalid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore();

    cout << "Enter a full name: ";
    if (!(getline(cin, names[line - 1]))) {
        cout << "The full name entered was invalid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    ofstream out_file(filename);
    for (int i = 0; i < line_count; i++) {
        out_file << ages[i] << " " << names[i] << endl;
    }
    out_file.close();

    for (int i = 0; i < line_count; i++) {
        ages[i] = 0;
        names[i] = "";
    }

    display_pending_entries(names, ages, filename);
}

void get_youngest_student(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename) {
    int line_count = get_line_count(names, ages, filename);

    if (line_count == 0) {
        cout << "No students found." << endl;
        return;
    }

    int youngest_age = ages[0];
    string youngest_name = names[0];
    for (int i = 1; i < line_count; i++) {
        if (youngest_age > ages[i]) {
            youngest_age = ages[i];
            youngest_name = names[i];
        }
    }
    cout << "The youngest student is " << youngest_name << " at " << youngest_age << " years old." << endl;
}

void get_oldest_student(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename) {
    int line_count = get_line_count(names, ages, filename);

    if (line_count == 0) {
        cout << "No students found." << endl;
        return;
    }

    int oldest_age = ages[0];
    string oldest_name = names[0];
    for (int i = 1; i < line_count; i++) {
        if (oldest_age < ages[i]) {
            oldest_age = ages[i];
            oldest_name = names[i];
        }
    }
    cout << "The oldest student is " << oldest_name << " at " << oldest_age << " years old." << endl;
}

void get_average_age(string names[MAX_ENTRIES], int ages[MAX_ENTRIES], string& filename) {
    int total_age = 0;
    int line_count = get_line_count(names, ages, filename);
    for (int i = 0; i < line_count; i++) {
        total_age += ages[i];
    }

    double average_age = static_cast<double>(total_age) / line_count;
    cout << "The average age is " << fixed << setprecision(2) << average_age << " years old." << endl;
}

