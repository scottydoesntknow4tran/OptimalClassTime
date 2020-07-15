#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

class Names {  // class for name nodes for name linked list
public:
    string _name;
    Names* _nxtNamePtr;
};

class TimeNode { //class for time ndoes for time linked list
public:
	double _time;
	int _matches;
	TimeNode* _nxtNodePtr; 
    Names* _namePtr; // pointer to name linked list
};

int main() {

    Names* namePtr = nullptr;
    Names* namePtr2 = nullptr;
    Names* ptr2 = nullptr;

    TimeNode* days[7] = { 0 }; //array of pointers pointing to each linked list
    
    TimeNode* head = nullptr;
    TimeNode* ptr = nullptr;
    TimeNode* tail = nullptr;

    // stuff used for reading in data
    string FileName;
    string day;
    string line;
    ifstream myfile;
    string a;
    int w = 0;
    for (;;) {
        cout << "Enter a text file with preffered times or e to end" << endl;
        cin >> FileName;
        if (FileName == "e") {
            break;
        }
        myfile.open(FileName);
        if (!myfile) {
            cout << "Unable to open file or invalid data" << endl;
            myfile.close();
            exit(1);
        }

        if (myfile.is_open()) {
            while (getline(myfile, line)) { 
                stringstream ss(line);
                getline(ss, day, ':'); // takes the day from the begining of the line
                double num = 1;
                double lastnum = 0;
                while (lastnum != num) { //takes the time from the line until it hits the same number twice, signaling the end of the line
                    lastnum = num;
                    getline(ss, a, ',');
                    num = stod(a);
                    if (num == 0) { //catches non numbers
                        cout << "invalid data" << endl;
                        exit(1);
                    }
                    if (lastnum != num) { //finds the pointer in the array of pointer based on the day of the week
                        
                        if (day == "sun") {
                            w = 0;
                        }
                        else if (day == "mon") {
                            w = 1;
                        }
                        else if (day == "tue") {
                            w = 2;
                        }
                        else if (day == "wed") {
                            w = 3;
                        }
                        else if (day == "thu") {
                            w = 4;
                        }
                        else if (day == "fri") {
                            w = 5;
                        }
                        else if (day == "sat") {
                            w = 6;
                        }
                        else { 
                            cout << "invalid data" << endl;
                            exit(1);
                        }

                        if (days[w] == nullptr) { // creates first node if the list is empty
                            days[w] = new TimeNode;
                            (days[w])->_time = num;
                            (days[w])->_matches = 1;
                            (days[w])->_namePtr = new Names;
                            (days[w])->_namePtr->_name = FileName;
                            (days[w])->_namePtr->_nxtNamePtr = nullptr;
                            (days[w])->_nxtNodePtr = nullptr;
                        }
                        else {
                            for (ptr = days[w]; nullptr != ptr; ptr = ptr->_nxtNodePtr) { // runs intil the end of the list or break
                                if ((ptr->_time) == (num)) {//adds to pre-existing node, increments matches and add name to name list
                                    namePtr = new Names();
                                    namePtr->_name = FileName;
                                    namePtr->_nxtNamePtr = nullptr;
                                    ptr->_matches++;
                                    for (namePtr2 = ptr->_namePtr; nullptr != namePtr2; namePtr2 = namePtr2->_nxtNamePtr) { //runs through name list until end and adds new name
                                        if (namePtr2->_nxtNamePtr == nullptr) {
                                            namePtr2->_nxtNamePtr = namePtr;
                                            break;
                                        }
                                    }
                                }
                                else if ((ptr != days[w]) && (ptr != nullptr) && (ptr->_nxtNodePtr != nullptr)) { 
                                    // if not at the begining or end of list (if between 2 existing nodes
                                        if (((ptr->_nxtNodePtr->_time) > num) && ((ptr->_time) < num)) {
                                            //creates new node after ptr, if is less and next node is more than our time
                                            head = new TimeNode();
                                            head->_time = num;
                                            head->_matches = 1;
                                            head->_namePtr = new Names;
                                            head->_namePtr->_name = FileName;
                                            head->_namePtr->_nxtNamePtr = nullptr;
                                            head->_nxtNodePtr = ptr->_nxtNodePtr;
                                            ptr->_nxtNodePtr = head;
                                            break;
                                        }
                                    
                                }
                                else if (ptr->_nxtNodePtr == nullptr) {
                                    // new node at end of the list
                                    tail = new TimeNode();
                                    tail->_time = num;
                                    tail->_matches = 1;
                                    tail->_namePtr = new Names;
                                    tail->_namePtr->_name = FileName;
                                    tail->_namePtr->_nxtNamePtr = nullptr;
                                    tail->_nxtNodePtr == nullptr;
                                    ptr->_nxtNodePtr = tail;
                                    break;
                                }
                                else if ((ptr->_nxtNodePtr->_time) > num) { // new node at the begining of the list if first time is greater
                                    head = new TimeNode();
                                    head->_time = num;
                                    head->_matches = 1;
                                    head->_namePtr = new Names;
                                    head->_namePtr->_name = FileName;
                                    head->_namePtr->_nxtNamePtr = nullptr;
                                    head->_nxtNodePtr = ptr->_nxtNodePtr;
                                    ptr->_nxtNodePtr = head;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        myfile.close();
    }

    int matches = 1; // filters list for minimum matches, defaults to 1 match
    cout << "What is the minimum number of matches you want?" << endl; 
    cin >> matches;
    for (int p = 0; p < 7; p++) { // uses array to find the day of the week
        if (p == 0) {
            day = "sunday";
        }
        else if (p ==1) {
            day = "monday";
        }
        else if (p == 2) {
            day = "tuesday";
        }
        else if (p == 3) {
            day = "wednsday";
        }
        else if (p == 4) {
            day = "thursday";
        }
        else if (p == 5) {
            day ="friday";
        }
        else if (p == 6) {
            day = "saturday";
        }
        
        cout << "Time(s) for " << day << ":" << endl;
        for (ptr = days[p]; nullptr != ptr; ptr = ptr->_nxtNodePtr) { // loops through the list displaying times and names 
            if ((ptr->_matches) >=matches) { //if above match minimum
                cout << ptr->_time << endl;
                cout << "Matches: " << ptr->_matches << endl;
                cout << "Names: ";
                ptr2 = ptr->_namePtr;
                for (int k = 0; k < (ptr->_matches); k++) { // loops through name list displaying names
                    if (k > 0) {
                        cout << ", ";
                    }
                    cout << ptr2->_name;
                    ptr2 = ptr2->_nxtNamePtr;
                }

                cout << endl;
            }
        }
    }
   
    // dealocating memory for later use
    namePtr = nullptr;
    namePtr2 = nullptr;
    ptr2 = nullptr;

    days[0]= nullptr;
    days[1] = nullptr;
    days[2] = nullptr;
    days[3] = nullptr;
    days[4] = nullptr;
    days[5] = nullptr;
    days[6] = nullptr;

    head = nullptr;
    ptr = nullptr;
    tail = nullptr;

    delete namePtr;
    delete  namePtr2;
    delete  ptr2;

    delete days[0];
    delete days[1];
    delete days[2];
    delete days[3];
    delete days[4];
    delete days[5];
    delete days[6];


    delete head;
    delete ptr;
    delete  tail;

}


