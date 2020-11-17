#include "Registrar.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {

    string fileName = "";
    bool running = true;

    // get command line input
    if(argc != 2) {
        cout << "Invalid command line parameters, please enter a file name." << endl;
        return -1;
    } else {
        fileName = argv[1];
    }

    cout << "\n\n\n}----------------| Registrar's Office Simulation |----------------{\n" << endl;

    // loops for each file loaded
    while(running) {
        ifstream file;
        vector<int> *info = new vector<int>();
        Registrar *registrar;

        // open file
        file.open(fileName);
        while(!file.is_open()) {
            cout << "Unable to locate file \'" << fileName << "\'. Please input name of a file: ";
            cin >> fileName;
            file.open(fileName);
        }

        // save file into info vector
        while(!file.eof()) {
            string currLine;
            // get next line from file
            getline(file, currLine);
            if(!file.eof()) // stop file from reading last line
                info->push_back(stoi(currLine));
        }
        file.close();

        // create registrar
        registrar = new Registrar(info);

        // simulate registrar and display statistics
        registrar->simulate();
        registrar->calcStats();
        registrar->printStats();

        // prompt if want to try another file
        string userInput;
        cout << "Would you like to test another file? Enter \'yes\' or \'no\': ";
        while(true) {
            cin >> userInput;
            if(userInput == "yes") {
                break;
            } else if (userInput == "no") {
                running = false;
                break;
            }
            cout << "Incorrect input. Please enter \'yes\' or \'no\': ";
        }

        // get new file name
        if(running) {
            cout << "Please input name of a file: ";
            cin >> fileName;
        }

        // clean-up
        delete info;
        delete registrar;
    }

    cout << "\nExiting program.\n" << endl;
    return 0;
}
