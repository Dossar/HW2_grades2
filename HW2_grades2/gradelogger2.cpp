/* 
 * File:   gradelogger.cpp
 * Author: Roy Van Liew
 *
 * Created on January 29, 2014, 12:01 PM
 */

// Code works but calc_ave and calc_letter are not void.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student
{
    
public:
    void input();
    void output();
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
    char name[50]; // Name of the student, max 50 characters.
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

// Input grades
void Student::input(){   

    int choice = 1;  // This is to get the while loop working
    while (choice != 0)
    {
        cout << "\nInput Grades for student.\n";
        cout << "0 - Don't change any more grades\n";
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
        
}
    


// Output all the students' grades.
void Student::output(){
    
    cout << "Quiz 1: " << Student::qgrade[0] << " weighted " << Student::qweight[0] << "%\n";
    cout << "Quiz 2: " << Student::qgrade[1] << " weighted " << Student::qweight[1] << "%\n";
    cout << "Miderm Exam: " << Student::qgrade[2] << " weighted " << Student::qweight[2] << "%\n";
    cout << "Final Exam: " << Student::qgrade[3] << " weighted " << Student::qweight[3] << "%\n";
    cout << "This student scored " << Student::avweight << " and got a "
            << Student::lettergrade << " grade for the course.\n";
    
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
    
    Student sGrade[3]; // Three students are getting grades evaluated
    int s; // For the students in the loops

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
            for( s = 0 ; s < 3 ; s++ )
            {
                cout << "\nPlease input student " << (s+1) << "'s grades.\n";
                cout << "Grades should be integers between 0 and 100.\n";
                sGrade[s].input();
                cout << "Student " << (s+1) << "'s grades successfully entered.\n";
            }
			break;
	
        case 2:	
            for( s = 0 ; s < 3 ; s++ )
            {
                cout << "\nStudent " << (s+1) << "'s grades are:\n";
                sGrade[s].output();
            }
			break;
		
        default:
            cout << "\nInvalid input.\n";
        }
    }
    
    return 0;
}

