// Student management system using file handling

#include <iostream>
#include <fstream> // to both read and write from/to file
#include <stdlib.h> 
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

class Student {
    private:
        string name, roll_no, course, address, email, contact_info;
    public:
        void menu();
        void insert() { // insert a new student record
            system("clear");
            fstream file;
            cout << "\n--------------------------------------------------------------------------------------------------------------";
            cout << "\n---------------------------------------------ADD STUDENT PROFILE----------------------------------------------" << endl;
            cout << endl << "\t\t\tEnter Name          : ";
            cin >> name;
            cout << "\t\t\tEnter Roll No.      : ";
            cin >> roll_no;
            cout << "\t\t\tEnter Course        : ";
            cin >> course;
            cout << "\t\t\tEnter Email Address : ";
            cin >> email;
            cout << "\t\t\tEnter Contact Info  : ";
            cin >> contact_info;
            cout << "\t\t\tEnter Address       : ";
            cin >> address;
            file.open("student_record.txt", ios::app | ios::out);
            string new_record = name + ", " + roll_no + ", " + course + ", " 
                                + email + ", " + contact_info + ", " + address + "\n";
            file << new_record;
            file.close();
        }
        void display() { // display the entire record - permission required
            system("clear");
            fstream file;
            cout << "\n--------------------------------------------------------------------------------------------------------------";
            cout << "\n------------------------------------------------STUDENT RECORD------------------------------------------------" << endl;
            file.open("student_record.txt", ios::in);
            if(!file) {
                //cout << "\n\t\t\tNo Record Is Found";
                file.close();
            } else {
                file >> name >> roll_no >> course >> email >> contact_info >> address;
                int line = 0;
                while(!file.eof()) {
                    line += 1;
                    cout << "\n\t\t\t[" << name << " " << roll_no  << " " << course << " " << email 
                                << " " << contact_info << " " << address << "]" << endl;
                    file >> name >> roll_no >> course >> email >> contact_info >> address;
                }
                if(line == 0) {
                    //cout << "\n\t\t\tNo Record Is Found";
                }
                file.close();
            }
        }
        void modify() {// NEED A FIX modify the record of a student
            system("clear");
            fstream file;
            fstream new_file;
            cout << "\n--------------------------------------------------------------------------------------------------------------";
            cout << "\n-----------------------------------------------MODIFY RECORD------------------------------------------------" << endl;
            string number;
            bool exist = false;
            file.open("student_record.txt", ios::in);
            if(!file) {
                file.close();
            } else {
                cout << "\n\t\t\tEnter Roll No, of student which you modify: ";
                cin >> number;
                new_file.open("new_student_record.txt", ios::app | ios::out);
                file >> name >> roll_no >> course >> email >> contact_info >> address;
                while(!file.eof()) {
                    if(roll_no != number + ",") {
                        string record_copy = name + " " + roll_no + " " + course + " " 
                                + email + " " + contact_info + " " + address + "\n";
                        new_file << record_copy;
                    } else {
                        exist = true;
                        cout << endl << "\t\t\tEnter Name          : ";
                        cin >> name;
                        cout << "\t\t\tEnter Roll No.      : ";
                        cin >> roll_no;
                        cout << "\t\t\tEnter Course        : ";
                        cin >> course;
                        cout << "\t\t\tEnter Email Address : ";
                        cin >> email;
                        cout << "\t\t\tEnter Contact Info  : ";
                        cin >> contact_info;
                        cout << "\t\t\tEnter Address       : ";
                        cin >> address;
                        string record_copy = name + ", " + roll_no + ", " + course + ", " 
                                + email + ", " + contact_info + ", " + address + "\n";
                        new_file << record_copy;
                    }
                    file >> name >> roll_no >> course >> email >> contact_info >> address;
                }
                if(!exist) {
                    cout << "\n\t\t\tStudent with Roll No. " << number << " does not exist"; 
                    //chrono::seconds duration(1);
                    //this_thread::sleep_for(duration);     
                }
                new_file.close();
                file.close();
                remove("student_record.txt");
                rename("new_student_record.txt", "student_record.txt");
            }
        }
        void search() { // search the record of a student
            system("clear");
            fstream file;
            string number;
            bool exist;
            cout << "\n--------------------------------------------------------------------------------------------------------------";
            cout << "\n-----------------------------------------------STUDENT RECORD------------------------------------------------" << endl;
            file.open("student_record.txt", ios::in);
            if(!file) {
                file.close();
            } else {
                cout << "\n\t\t\tEnter Roll No, of student which you look up: ";
                cin >> number;
                file >> name >> roll_no >> course >> email >> contact_info >> address;
                while(!file.eof()) {
                    if(roll_no == number + ",") {
                        exist = true;
                        cout << "\n\t\t\tStudent Name: " << name.substr(0,name.size()-1) << endl;
                        cout << "\t\t\tRoll No: " << roll_no.substr(0,roll_no.size()-1) << endl;
                        cout << "\t\t\tCourse: " << course.substr(0,course.size()-1) << endl;
                        cout << "\t\t\tEmail: " << email.substr(0,email.size()-1) << endl;
                        cout << "\t\t\tContact Info: " << contact_info.substr(0,contact_info.size()-1) << endl;
                        cout << "\t\t\tAddress: " << address.substr(0,address.size()) << endl;
                        break;
                    }
                    file >> name >> roll_no >> course >> email >> contact_info >> address;
                }
                if(!exist) {
                    cout << "\n\t\t\tStudent with Roll No. " << number << " does not exist";
                }
                file.close();
            }
        }
        void delete_record() { // delete a record
            system("clear");
            fstream file, new_file;
            string number;
            bool exist = false;
            cout << "\n-------------------------------------------------------------------------------------------------------------";
            cout << "\n----------------------------------------------DELETE RECORD------------------------------------------------" << endl;
            file.open("student_record.txt", ios::in);
            if(!file) {
                file.close();
            } else {
                cout << "\n\t\t\tEnter Roll No, of student which you delete: ";
                cin >> number;
                new_file.open("new_student_record.txt", ios::app | ios::out);
                file >> name >> roll_no >> course >> email >> contact_info >> address;
                while(!file.eof()) {
                    if(roll_no != number + ",") {
                        string record_copy = name + " " + roll_no + " " + course + " " 
                                + email + " " + contact_info + " " + address + "\n";
                        new_file << record_copy;
                    } else {
                        exist = true;
                    }
                    file >> name >> roll_no >> course >> email >> contact_info >> address;
                }
                if(!exist) {
                    cout << "\n\t\t\tStudent with Roll No. " << number << " does not exist"; 
                }
                file.close();
                new_file.close();
                remove("student_record.txt");
                rename("new_student_record.txt", "student_record.txt");
            }
        }
};

void Student::menu() {
    
    menustart:
    // system() lets you pass a string to the target system's command line
    // interpreter to rum "cls" is to clears the console (screen)

    system("clear"); 
    
    cout << endl << "\t\t\t---------------------------------" << endl;
    cout << "\t\t\t|   STUDENT MANAGEMENT SYSTEM   |" << endl;
    cout << "\t\t\t---------------------------------" << endl << endl;
    cout << "\t\t\t 0. Exit" << endl;
    cout << "\t\t\t 1. Enter New Record" << endl;
    cout << "\t\t\t 2. Modify Record" << endl;
    cout << "\t\t\t 3. Search Record" << endl;
    cout << "\t\t\t 4. Delete Record" << endl;
    cout << "\t\t\t 5. Display Record" << endl << endl;

    int choice;
    cout << "\t\t\t CHOOSE OPTION [0/1/2/3/4/5]: ";
    cin >> choice;

    char x;
    string passcode;
    switch(choice) {
        case 0:
            exit(0);
        case 1:
            do {
                insert();
                cout << "\n\t\t\t Add Another Student Record [Y/n]: ";
                cin  >> x;
            } while(x == 'Y');
            break;
        case 2:
            modify();
            break;
        case 3:
            search();
            break; 
        case 4:
            delete_record();
            break;
        case 5:
            cout << "\n\t\t\t Authorized Personnal Only " << endl;
            cout << "\t\t\t Insert passcode to access the record: ";
            cin >> passcode;
            if(passcode == "ABC") {
                cout << "\n\t\t\t Passcode Verified " << endl;
                system("read");
                display();
            } else {
                cout << "\n\t\t\t Invalid Passcode " << endl;
            }
            break;
        default:
            cout << "\n\t\t\t Invalid Choice - Please Try Again" << endl;
            break;
    }
    system("read");
    goto menustart; // an unconditional jump statement that allows you to jump to
    // the place within the function where "string" is placed
}

int main() {

    Student student;
    student.menu();

    return 0;
}