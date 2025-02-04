#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

class Student {
public:
    int id;
    string name;
    float gpa;

    void getData() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter GPA: ";
        cin >> gpa;
    }

    void display() const {
        cout << left << setw(10) << id << setw(20) << name << setw(10) << gpa << endl;
    }
};

void addStudent();
void viewStudents();
void searchStudent(int id);
void updateStudent(int id);
void deleteStudent(int id);
void sortStudents();
void displayGUI();

const string filename = "students.txt";

int main() {
    int choice, id;
    while (true) {
        displayGUI();
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); system("pause"); break;
            case 3: cout << "Enter ID: "; cin >> id; searchStudent(id); system("pause"); break;
            case 4: cout << "Enter ID: "; cin >> id; updateStudent(id); system("pause"); break;
            case 5: cout << "Enter ID: "; cin >> id; deleteStudent(id); system("pause"); break;
            case 6: sortStudents(); system("pause"); break;
            case 7: exit(0);
            default: cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}

void addStudent() {
    ofstream file(filename, ios::app);
    Student s;
    s.getData();
    file << s.id << " " << s.name << " " << s.gpa << endl;
    file.close();
    cout << "Student added successfully!" << endl;
    system("pause");
}

void viewStudents() {
    ifstream file(filename);
    Student s;
    cout << "\nStudent Records:" << endl;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "GPA" << endl;
    while (file >> s.id) {
        file.ignore();
        getline(file, s.name, ' ');
        file >> s.gpa;
        s.display();
    }
    file.close();
}

void searchStudent(int id) {
    ifstream file(filename);
    Student s;
    while (file >> s.id) {
        file.ignore();
        getline(file, s.name, ' ');
        file >> s.gpa;
        if (s.id == id) {
            cout << "Student Found:" << endl;
            s.display();
            file.close();
            return;
        }
    }
    cout << "Student not found!" << endl;
    file.close();
}

void updateStudent(int id) {
    ifstream file(filename);
    ofstream temp("temp.txt");
    Student s;
    bool found = false;
    while (file >> s.id) {
        file.ignore();
        getline(file, s.name, ' ');
        file >> s.gpa;
        if (s.id == id) {
            cout << "Enter new details: " << endl;
            s.getData();
            found = true;
        }
        temp << s.id << " " << s.name << " " << s.gpa << endl;
    }
    file.close();
    temp.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
    if (found)
        cout << "Student updated successfully!" << endl;
    else
        cout << "Student not found!" << endl;
}

void deleteStudent(int id) {
    ifstream file(filename);
    ofstream temp("temp.txt");
    Student s;
    bool found = false;
    while (file >> s.id) {
        file.ignore();
        getline(file, s.name, ' ');
        file >> s.gpa;
        if (s.id != id) {
            temp << s.id << " " << s.name << " " << s.gpa << endl;
        } else {
            found = true;
        }
    }
    file.close();
    temp.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
    if (found)
        cout << "Student deleted successfully!" << endl;
    else
        cout << "Student not found!" << endl;
}

void sortStudents() {
    ifstream file(filename);
    vector<Student> students;
    Student s;
    while (file >> s.id) {
        file.ignore();
        getline(file, s.name, ' ');
        file >> s.gpa;
        students.push_back(s);
    }
    file.close();

    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.gpa > b.gpa;
    });

    cout << "\nSorted Students by GPA:" << endl;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "GPA" << endl;
    for (const auto& student : students) {
        student.display();
    }
}

void displayGUI() {
    system("cls");
    cout << "====================================" << endl;
    cout << "       Student Management System   " << endl;
    cout << "====================================" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. View Students" << endl;
    cout << "3. Search Student" << endl;
    cout << "4. Update Student" << endl;
    cout << "5. Delete Student" << endl;
    cout << "6. Sort Students by GPA" << endl;
    cout << "7. Exit" << endl;
    cout << "====================================" << endl;
}
