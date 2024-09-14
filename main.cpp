#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Student {
    string name;
    string id;
};

vector<Student> readCSV(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Tidak dapat membuka file " << filename << endl;
        exit(EXIT_FAILURE);
    }
    string line, name, id;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, id, ',');
        students.push_back({name, id});
    }

    return students;
}

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream date;
    date << 1900 + ltm->tm_year << "-"
         << 1 + ltm->tm_mon << "-"
         << ltm->tm_mday;
    return date.str();
}

void savePresentStudents(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    file << "Nama,NIU" << "\n";
    for (const auto& student : students) {
        file << student.name << "," << student.id << "\n";
    }
}

int main() {
    vector<Student> students = readCSV("./niu.csv");
    vector<Student> presentStudents;
    string inputID;
    char continueInput;

    do {
        cout << "Input NIU mahasiswa: ";
        cin >> inputID;

        bool studentFound = false;
        for (const auto& student : students) {
            if (student.id == inputID) {
                studentFound = true;
                bool alreadyPresent = false;
                for (const auto& presentStudent : presentStudents) {
                    if (presentStudent.id == inputID) {
                        alreadyPresent = true;
                        break;
                    }
                }
                if (alreadyPresent) {
                    cout << "Mahasiswa a/n " << student.name << " (NIU " << student.id << ") sudah didata hadir." << endl;
                } else {
                    cout << "Mahasiswa a/n " << student.name << " (NIU " << student.id << ") didata hadir." << endl;
                    presentStudents.push_back(student);
                }
                break;
            }
        }
        if (!studentFound) {
            cout << "Tidak ditemukan mahasiswa dengan NIU " << inputID << endl;
        }

        cout << "Apakah Anda ingin melanjutkan? (Y/N): ";
        cin >> continueInput;
    } while (continueInput == 'Y' || continueInput == 'y');

    string filename = getCurrentDate() + "_students.csv";
    savePresentStudents(presentStudents, filename);

    cout << "Daftar mahasiswa yang hadir telah disimpan di ./" << filename << endl;
    cout << "Anda dapat mengupload file tersebut ke Excel untuk kemudahan pendataan." << endl;

    return 0;
}




