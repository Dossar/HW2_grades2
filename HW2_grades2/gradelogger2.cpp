/* 
 * File:   gradelogger.cpp
 * Author: Roy Van Liew
 *
 * Created on January 29, 2014, 12:01 PM
 */

// Code works but calc_ave and calc_letter are not void.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Student
{
    
public:
    void input(int);
    void output(int);
    // These are 4 static accessor (get) functions for each quiz weight.
    static int getQ1w() //static member function
    { return qweight[0]; }
    static int getQ2w() //static member function
    { return qweight[1]; }
    static int getQ3w() //static member function
    { return qweight[2]; }
    static int getQ4w() //static member function
    { return qweight[3]; }

private:
    string sname; // Name of the student.
    int qgrade[4]; // Each array cell indicates the quiz number's grade.
    static int qweight[4]; // Each array cell indicates the quiz number's weight.
    // 0 for quiz1, 1 for quiz2, 2 for midterm, 3 for final exam.
    double avweight;
    char lettergrade;
    //// Start grade mutator (set) functions ////
    void qgr1(){
        int gCheck = 1;
        while(gCheck == 1){
            cout << "Input grade for Quiz #1: ";
            cin >> qgrade[0];
            if(qgrade[0] >= 0 && qgrade[0] <= 100)
                gCheck = 0;
            else
                cout << "Invalid grade, please try again.\n";
        }
    }
    void qgr2(){
        int gCheck = 1;
        while(gCheck == 1){
            cout << "Input grade for Quiz #2: ";
            cin >> qgrade[1];
            if(qgrade[1] >= 0 && qgrade[1] <= 100)
                gCheck = 0;
            else
                cout << "Invalid grade, please try again.\n";
        }
    }
    void qgr3(){
        int gCheck = 1;
        while(gCheck == 1){
            cout << "Input grade for Midterm Exam: ";
            cin >> qgrade[2];
            if(qgrade[2] >= 0 && qgrade[2] <= 100)
                gCheck = 0;
            else
                cout << "Invalid grade, please try again.\n";
        }
    }
    void qgr4(){
        int gCheck = 1;
        while(gCheck == 1){
            cout << "Input grade for Final Exam: ";
            cin >> qgrade[3];
            if(qgrade[3] >= 0 && qgrade[3] <= 100)
                gCheck = 0;
            else
                cout << "Invalid grade, please try again.\n";
        }
    }
    //// End grade mutator (set) functions ////

    void calc_ave();
    void calc_letter();

};

// Initialize our static quiz weights respectively.
int Student::qweight[4] = { 10, 20, 30, 40 };
    Student sGrade[3]; // Three students are getting grades evaluated

// Input grades
void Student::input(int n){   

    // In this case the user is entering the input
    if( n == 2 )
    {
        int choice = 1;  // This is to get the while loop working
        while (choice != 0)
        {
            cout << "\nInput Grades for " << sname << ".\n";
            cout << "0 - Don't change any more grades for " << sname << "\n";
            cout << "1 - Change Quiz #1 grade\n";
            cout << "2 - Change Quiz #2 grade\n";
            cout << "3 - Change Midterm Exam grade\n";
            cout << "4 - Change Final Exam grade\n";

            cout << "Please select an item from the menu list: ";
            cin >> choice;

            switch (choice)
            {
            case 0:	
                    cout << "Going back to main menu.\n";
                    break;
            // For cases 1-4, user inputs new grade, then average is recalculated.
            case 1:	
                    qgr1();
                    calc_ave();
                    calc_letter();
                    break;
            case 2:	
                    qgr2();
                    calc_ave();
                    calc_letter();
                    break;                
            case 3:	
                    qgr3();
                    calc_ave();
                    calc_letter();                
                    break;
            case 4:	
                    qgr4();
                    calc_ave();
                    calc_letter();                
                    break;		
            default:
                    cout << "\nInvalid input.\n";
            }
        }
        cout << sname << "'s grades were successfully entered.\n";
    }
    // End user input
    
    // In this case the input is received from the text file
    if( n == 1 )
    {
        int q; // For getline on the quiz parts.
        string quizstr[4]; // From a text file, the grades are strings.
        
        /*      The format of the text file is basically this:
                - Name \n
                - Quiz \n (4 lines)
                - Newline gap to next name */
    
        ifstream in("input.txt");
        string sdata; // String storing variable for the getline stuff.
        
        // This while loop is basically saying "get each line until end of file is reached".
        while (getline(in, sdata)) {

             // getline in the while condition is for the name.
             std::size_t found = sdata.find(": "); // Search for ": " string
             sGrade[n-1].sname = sdata.substr(found + 2); // Save everything after ": " into sname string.
             cout << sGrade[n-1].sname << endl;

             // Store the four quiz grades.
             for( q = 0 ; q < 4 ; q++ ) {
                getline(in, sdata); 
                std::size_t found = sdata.find(": "); // Search for ": " string
                quizstr[q] = sdata.substr(found + 2); // Save everything after ": " into qgrade string.      
                cout << quizstr[q] << endl;
             }
             cout << "\n"; // This is simply for formatting

            // Now we need to convert the quiz strings into integers.
            for (q = 0; q < 4; q++) {
                std::istringstream tempgrade(quizstr[q]);
                tempgrade >> sGrade[n - 1].qgrade[q]; // Store quiz integer value into current student.
                cout << sGrade[n - 1].qgrade[q] << "\n";
            }

             // Recalculate the students' grade.
             sGrade[n-1].calc_ave();
             sGrade[n-1].calc_letter();
             getline(in, sdata); // Compensate for newline gap format in text file
             
             n++;
         } // End of while loop
        

    }
    // End file input
        
}
    


// Output all the students' grades.
void Student::output(int n){
    
    if( n == 2 )
    {
    cout << sname << "'s grades are:\n";
    cout << "Quiz 1: " << qgrade[0] << " weighted " << qweight[0] << "%\n";
    cout << "Quiz 2: " << qgrade[1] << " weighted " << qweight[1] << "%\n";
    cout << "Miderm Exam: " << qgrade[2] << " weighted " << qweight[2] << "%\n";
    cout << "Final Exam: " << qgrade[3] << " weighted " << qweight[3] << "%\n";
    cout << sname << " scored " << avweight << " and got a "
            << lettergrade << " grade for the course.\n";
    }
    
    if( n == 1 )
        return;
    
}

// Calculate average weighted grade
void Student::calc_ave(){

    int i;
    for (i = 0; i < 4; i++) {
        avweight += (double) (Student::qgrade[i] * (Student::qweight[i] / 100.0)); // Add up all weighted scores
    }
}

// Calculate final letter grade
void Student::calc_letter(){
    if( avweight < 65.0 )
        lettergrade = 'F';
    else if( avweight >= 65.0 && avweight < 70.0 )
        lettergrade = 'D';
    else if( avweight >= 70.0 && avweight < 80.0 )
        lettergrade = 'C';
    else if( avweight >= 80.0 && avweight < 90.0 )
        lettergrade = 'B';
    else if( avweight >= 90.0 && avweight <= 100.0 )
        lettergrade = 'A';
}

/*
 * 
 */
int main() {
    
    int s = 0; // For the students in the loops
    int user = 3; // For deciding inputs and outputs

    int choice = 1;  // This is to get the while loop working
    while (choice != 0)
    {
        cout << "\nStudent Grade Evaluator\n";
        cout << "This program enters grades for 3 students and calculates them.\n";
        cout << "0 - Quit Program\n";
        cout << "1 - Input Grades\n";
        cout << "2 - Output Grades\n";		

        cout << "Please select an item from the menu list: ";
        cin >> choice;

        switch (choice)
        {
        case 0:	
            cout << "Thank you for your time.\n";
			break;
        case 1:
                user = 3;
                while (user != 2 && user != 1) {
                    cout << "Enter 1 for text file input, 2 for user input.\n";
                    cin >> user;
                    cout << "\n";
                }
                if (user == 1)
                    sGrade[0].input(user);
                else for (s = 0; s < 3; s++) {
                        sGrade[s].input(user);
                    }
	    break;
	
        case 2:
                user = 3;
                while (user != 2 && user != 1) {
                    cout << "Enter 1 for text file output, 2 for console output.\n";
                    cin >> user;
                    cout << "\n";
                }
                if( user == 2 )
                        for( s = 0 ; s < 3 ; s++ )
                        {
                                sGrade[s].output(user);
                        }
                else
                    sGrade[0].output(user);
			break;
		
        default:
            cout << "\nInvalid input.\n";
        }
    }
    
    return 0;
}

