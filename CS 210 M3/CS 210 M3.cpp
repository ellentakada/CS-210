// 09/09/2023, Ellen Takada
// This program include functions to simulate clock display in both 12 hour and 24 hour format

// 09/09/16, UPDATE: addHour, addMinute, addSecond were adjusted to format correctly

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cctype>

using namespace std;

string format(int time) {
    stringstream s;

    s << setfill('0') << setw(2) << time;
    return s.str();
}

void asterisk(string input1, string input2, string input3, string input4) {
    // display Display menu
    cout << "*************************" << endl;
    cout << "* " << left << setw(22) << input1 << "*" << endl;
    cout << "* " << left << setw(22) << input2 << "*" << endl;
    cout << "* " << left << setw(22) << input3 << "*" << endl;
    cout << "* " << left << setw(22) << input4 << "*" << endl;
    cout << "*************************" << endl;
}

void asterisk(string* S, string input1, string input2, int hour, int minute, int second) {
    // function overloading used for 12 hour display clocks
    stringstream s;
    s << "*************************" ;
    S[0] = s.str();
    s.str("");
    s << "* " << left << setw(3) << " " << input1 << setw(4) << " " << "*" ;
    S[1] = s.str();
    s.str("");
    s << "* " << left << setw(5) << " " << format(hour) << ":" << format(minute) << ":" << format(second) << input2 << right << setw(5) << " " << "*" ;
    S[2] = s.str();
    s.str("");
    s << "*************************" ;
    S[3] = s.str();
}

void asterisk(string* S, string input1, int hour, int minute, int second) {
    // function overloading used for 24 hour display clocks
    stringstream s;
    s << "*************************";
    S[0] = s.str();
    s.str("");
    s << "* " << left << setw(3) << " " << input1 << setw(4) << " " << "*" ;
    S[1] = s.str();
    s.str("");
    s << "* " << left << setw(7) << " " << format(hour) << ":" << format(minute) << ":" << format(second) << right << setw(7) << " " << "*" ;
    S[2] = s.str(); 
    s.str("");
    s << "*************************" ;
    S[3] = s.str();
}

bool choiceProcess(int& choice) {
    // validate the choice
    cin >> choice;

    if ((choice > 0) && (choice < 5)) {
        return true;
    }
    else {
        // invalid input
        return false;
    }
}

void twelveHour(string* S, int hour, int minute, int sec) {
    // function for 12 hour clock
    // adjust hour to display between 0 to 12
    string ampm;
    string input1 = "12 - Hour Clock";

    if (hour > 12) {
        ampm = " P M";
        hour %= 12;
        if (hour == 0) {
            ampm = " A M";
        }
    }
    else {
        ampm = " A M";
    }
    asterisk(S, input1, ampm, hour, minute, sec);
}

void twentyFourHour(string* S, int hour, int minute, int sec) {
    // function for 24 hour clock
    string input1 = "24 - Hour Clock";

    if (hour == 24) {
        hour = 0;
    }

    asterisk(S, input1, hour, minute, sec);
}

void displayClocks(int hour,int minute,int sec) {
    // call functions used to display clocks
    string S1[4];
    string S2[4];
    twelveHour(S1, hour, minute, sec);
    twentyFourHour(S2, hour, minute, sec);
    cout << S1[0] << "      " << S2[0] << endl;
    cout << S1[1] << "      " << S2[1] << endl;
    cout << S1[2] << "      " << S2[2] << endl;
    cout << S1[3] << "      " << S2[3] << endl;
}

int addHour(int hour) {
    // function to update hour
    int newHour = hour + 1;
    if (newHour == 24) {
        newHour = 0;
    }
    return newHour;
}

int addMinute(int& hour, int minute) {
    // function to update minute
    int newMinute = minute + 1;
    if (newMinute == 60) {
        newMinute = 0;
        hour += 1;
    }
    return newMinute;
}

int addSecond(int &hour, int& minute, int second) {
    // function to update second
    int newSec = second + 1;
    if (newSec == 60) {
        newSec = 0;
        minute += 1;
        if (minute == 60) {
            minute = 0;
            hour += 1;
        }
    }
    return newSec;
}

int DisplayMenu() {
    // function for display menu
    int choice;
    int INVALID = -1;
    // display menu allows four selection
    string first = "1-Add One Hour";
    string second = "2-Add One Minute";
    string third = "3-Add One Second";
    string fourth = "4-Exit Program";
    asterisk(first, second, third, fourth);

    if (choiceProcess(choice)) {
        return choice;
    }
    else {
        return INVALID;
    }
}

int main()
{
    int hour;
    int minute;
    int second;
    char quit;
    bool run = true;
    bool initial = true;

    while (initial) {
        // validate the initial input
        cout << "Enter the hour in 24 hour format: " << endl;
        cin >> hour;
        if (!((hour >= 0) && (hour <= 24))) {
            continue;
        }
        cout << "Enter the minute: " << endl;
        cin >> minute;
        if (!((minute >= 0) && (minute <= 59))) {
            continue;
        }
        cout << "Enter the second: " << endl;
        cin >> second;
        if (!((second >= 0) && (second <= 59))) {
            continue;
        }

        displayClocks(hour, minute, second);
        initial = false;
    }


    while (run == true) {
        int selected = DisplayMenu();
        if (selected == 1) {
            hour = addHour(hour);
            displayClocks(hour,minute,second);
        }
        else if (selected == 2) {
            minute = addMinute(hour, minute);
            displayClocks(hour, minute, second);
        }
        else if (selected == 3) {
            second = addSecond(hour, minute, second);
            displayClocks(hour, minute, second);
        }
        else if (selected == 4) {
            cout << "Do you want to exit the program? Answer y or Y: ";
            cin >> quit;
            if (tolower(quit) == 'y') {
                run = false;
            }
        }
    }
}


