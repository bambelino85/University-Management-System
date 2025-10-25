#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string hashPassword(const string& password) {
    unsigned long hash = 5381;
    for(char c : password) {
        hash = ((hash << 5) + hash) + c;
    }
    return to_string(hash);
}

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while(getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    ifstream inFile("data/users.dat");
    if(!inFile.is_open()) {
        cerr << "Error: Could not open data/users.dat" << endl;
        return 1;
    }
    
    ofstream outFile("data/users_hashed.dat");
    if(!outFile.is_open()) {
        cerr << "Error: Could not create data/users_hashed.dat" << endl;
        return 1;
    }
    
    string line;
    int count = 0;
    
    while(getline(inFile, line)) {
        vector<string> fields = split(line, '|');
        
        if(fields.size() >= 12) {
            string plainPassword = fields[10];
            fields[10] = hashPassword(plainPassword);
            
            for(size_t i = 0; i < fields.size(); i++) {
                outFile << fields[i];
                if(i < fields.size() - 1) outFile << "|";
            }
            outFile << endl;
            count++;
        }
    }
    
    inFile.close();
    outFile.close();
    
    cout << "Successfully hashed passwords for " << count << " users!" << endl;
    cout << "Original file: data/users.dat" << endl;
    cout << "Hashed file: data/users_hashed.dat" << endl;
    cout << "\nTo use the hashed file, run:" << endl;
    cout << "  mv data/users_hashed.dat data/users.dat" << endl;
    
    return 0;
}
