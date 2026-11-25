#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Patient {
    int id;
    string fullName;
    int age;
    string gender;
    string illness;
};

const int LIMIT = 100;

int readRecords(Patient records[]);
void writeRecords(Patient records[], int total);
int findIndexById(Patient records[], int total, int targetId);
void registerPatient(Patient records[], int& total);
void displayAll(Patient records[], int total);
void searchById(Patient records[], int total);
void editPatient(Patient records[], int total);
void removePatient(Patient records[], int& total);

int main() {
    Patient records[LIMIT];
    int totalPatients = readRecords(records);
    int option = 0;

    while (option != 6) {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Register New Patient\n";
        cout << "2. Show All Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Update Patient Details\n";
        cout << "5. Delete Patient Record\n";
        cout << "6. Exit\n";
        cout << "Select an option: ";

        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        if (option == 1) {
            registerPatient(records, totalPatients);
        }
        else if (option == 2) {
            displayAll(records, totalPatients);
        }
        else if (option == 3) {
            searchById(records, totalPatients);
        }
        else if (option == 4) {
            editPatient(records, totalPatients);
        }
        else if (option == 5) {
            removePatient(records, totalPatients);
        }
        else if (option == 6) {
            cout << "Goodbye!\n";
        }
        else {
            cout << "Wrong choice, try again.\n";
        }
    }

    return 0;
}

int readRecords(Patient records[]) {
    ifstream fin("patients.txt");
    if (!fin.is_open()) {
        return 0;
    }

    int count = 0;
    while (count < LIMIT && (fin >> records[count].id)) {
        fin.ignore();
        getline(fin, records[count].fullName);
        fin >> records[count].age;
        fin.ignore();
        getline(fin, records[count].gender);
        getline(fin, records[count].illness);
        count++;
    }

    fin.close();
    return count;
}

void writeRecords(Patient records[], int total) {
    ofstream fout("patients.txt");
    for (int i = 0; i < total; i++) {
        fout << records[i].id << endl;
        fout << records[i].fullName << endl;
        fout << records[i].age << endl;
        fout << records[i].gender << endl;
        fout << records[i].illness << endl;
    }
    fout.close();
}

int findIndexById(Patient records[], int total, int targetId) {
    for (int i = 0; i < total; i++) {
        if (records[i].id == targetId) {
            return i;
        }
    }
    return -1;
}

void registerPatient(Patient records[], int& total) {
    if (total >= LIMIT) {
        cout << "Storage limit reached. Cannot add more patients.\n";
        return;
    }

    int newId;
    cout << "\nEnter Patient ID: ";
    cin >> newId;

    if (findIndexById(records, total, newId) != -1) {
        cout << "This ID is already registered.\n";
        return;
    }

    records[total].id = newId;
    cin.ignore();

    cout << "Enter Patient Name: ";
    getline(cin, records[total].fullName);

    cout << "Enter Age: ";
    cin >> records[total].age;
    cin.ignore();

    cout << "Enter Gender: ";
    getline(cin, records[total].gender);

    cout << "Enter Disease: ";
    getline(cin, records[total].illness);

    total++;
    writeRecords(records, total);
    cout << "Patient saved successfully.\n";
}

void displayAll(Patient records[], int total) {
    if (total == 0) {
        cout << "\nNo patient records available.\n";
        return;
    }

    cout << "\n--- Patient List ---\n";
    for (int i = 0; i < total; i++) {
        cout << "ID: " << records[i].id
            << " | Name: " << records[i].fullName
            << " | Age: " << records[i].age
            << " | Gender: " << records[i].gender
            << " | Disease: " << records[i].illness << endl;
    }
}

void searchById(Patient records[], int total) {
    int id;
    cout << "\nEnter ID to search: ";
    cin >> id;

    int index = findIndexById(records, total, id);
    if (index == -1) {
        cout << "Record not found.\n";
        return;
    }

    cout << "\nPatient Details:\n";
    cout << "ID: " << records[index].id << endl;
    cout << "Name: " << records[index].fullName << endl;
    cout << "Age: " << records[index].age << endl;
    cout << "Gender: " << records[index].gender << endl;
    cout << "Disease: " << records[index].illness << endl;
}

void editPatient(Patient records[], int total) {
    int id;
    cout << "\nEnter ID to update: ";
    cin >> id;

    int index = findIndexById(records, total, id);
    if (index == -1) {
        cout << "Record not found.\n";
        return;
    }

    cin.ignore();
    cout << "Enter New Name: ";
    getline(cin, records[index].fullName);

    cout << "Enter New Age: ";
    cin >> records[index].age;
    cin.ignore();

    cout << "Enter New Gender: ";
    getline(cin, records[index].gender);

    cout << "Enter New Disease: ";
    getline(cin, records[index].illness);

    writeRecords(records, total);
    cout << "Record updated.\n";
}

void removePatient(Patient records[], int& total) {
    int id;
    cout << "\nEnter ID to delete: ";
    cin >> id;

    int index = findIndexById(records, total, id);
    if (index == -1) {
        cout << "Record not found.\n";
        return;
    }

    for (int i = index; i < total - 1; i++) {
        records[i] = records[i + 1];
    }
    total--;

    writeRecords(records, total);
    cout << "Record deleted.\n";
}