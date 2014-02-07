/* 
 * File:   gradelogger2.cpp
 * Author: Roy Van Liew and Saqib Zahid
 * 
 * Created on February 5, 2014
 */

// Mutator and accessor functions are public.

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
    /***** These are 4 static accessor (get) functions for each quiz weight. *****/
    static int getQ1w() //static member function
    { return qweight[0]; }
    static int getQ2w() //static member function
    { return qweight[1]; }
    static int getQ3w() //static member function
    { return qweight[2]; }
    static int getQ4w() //static member function
    { return qweight[3]; }
    /***** End accessor functions *****/
    
    /***** Start grade mutator (set) functions *****/
    void qgr(int n){
        int gCheck = 1;
        while(gCheck == 1){
            cout << "Input grade for this assessment: ";
            cin >> qgrade[n];
            if(qgrade[n] >= 0 && qgrade[n] <= 100)
                gCheck = 0;
            else
                cout << "Invalid grade, please try again.\n";
        }
    }
    /***** End grade mutator (set) functions *****/

private:
    string sname; // Name of the student.
    int qgrade[4]; // Each array cell indicates the quiz number's grade.
    static int qweight[4]; // Each array cell indicates the quiz number's weight.
    // 0 for quiz1, 1 for quiz2, 2 for midterm, 3 for final exam.
    double avweight;
    char lettergrade;

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
            cout << "Input Grades for " << sname << "\n";
            cout << "0 - Don't change any more grades for " << sname << "\n";
            cout << "1 - Change Quiz #1 grade\n";
            cout << "2 - Change Quiz #2 grade\n";
            cout << "3 - Change Midterm Exam grade\n";
            cout << "4 - Change Final Exam grade\n";

            cout << "Please select an item from the menu list: ";
            cin >> choice;
          

            if( choice == 0 )
                break;
            // For cases 1-4, user inputs new grade, then average is recalculated.
            else if( choice > 0 && choice < 5 ) {
                    qgr(choice-1); // The -1 is for the index
                    calc_ave();
                    calc_letter();
                    cout << "\n";
            }
            else cout << "\nInvalid input.\n";
            
        }
        cout << "Grades successfully entered for " << sname << "\n\n";
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
             // cout << sGrade[n-1].sname << endl;

             // Store the four quiz grades.
             for( q = 0 ; q < 4 ; q++ ) {
                getline(in, sdata); 
                std::size_t found = sdata.find(": "); // Search for ": " string
                quizstr[q] = sdata.substr(found + 2); // Save everything after ": " into qgrade string.      
                // cout << quizstr[q] << endl;
             }
             // cout << "\n"; // This is simply for formatting

            // Now we need to convert the quiz strings into integers.
            for (q = 0; q < 4; q++) {
                std::istringstream tempgrade(quizstr[q]);
                tempgrade >> sGrade[n - 1].qgrade[q]; // Store quiz integer value into current student.
                // cout << sGrade[n - 1].qgrade[q] << "\n";
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
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(1); // Output with one decimal point of precision.
        cout << "Here are the grades for " << sname << "\n";
        cout << "Quiz 1: " << qgrade[0] << " weighted " << qweight[0] << "%\n";
        cout << "Quiz 2: " << qgrade[1] << " weighted " << qweight[1] << "%\n";
        cout << "Miderm Exam: " << qgrade[2] << " weighted " << qweight[2] << "%\n";
        cout << "Final Exam: " << qgrade[3] << " weighted " << qweight[3] << "%\n";
        cout << "This student scored " << avweight << " and got a "
                << lettergrade << " grade for the course.\n\n";
    }
    
    // If 1 was entered, we write the data to an output text file.
    if( n == 1 )
    {
        ofstream write("output.txt"); // write here will be used to insert text into our output file
        int s, t; // s for students, t for the quiz counter
        string numoutput; // string for containing the number to output to .txt file
        ostringstream convert; // stream used for the conversion from integer to string
        for (s = 0; s < 3; s++) {
            t = 0; // t here is the variable that states which quiz grade to print out.
            write << "Student: " << sGrade[s].sname << "\n";
            convert << sGrade[s].qgrade[t]; // Insert text representation of the grade into stream
            numoutput = convert.str(); // Set the string to the contents of the stream.
            write << "quiz 1: " << numoutput << "\n";
            t++; // Go to the next quiz index.
            convert.str(""); // Clear the contents of the stream. This must be done every time.
            numoutput.clear(); // Clear the contents of the string. This must be done every time.
            convert << sGrade[s].qgrade[t];
            numoutput = convert.str();
            write << "quiz 2: " << numoutput << "\n";
            t++;
            convert.str("");
            numoutput.clear();
            convert << sGrade[s].qgrade[t];
            numoutput = convert.str();
            write << "midterm exam: " << numoutput << "\n";
            t++;
            convert.str("");
            numoutput.clear();
            convert << sGrade[s].qgrade[t];
            numoutput = convert.str();
            write << "final exam: " << numoutput << "\n\n";
            convert.str("");
            numoutput.clear();
        }

        write.close(); // Close our output file, we're done writing its contents
        cout << "Grades have been written to output.txt\n\n";
        
    }
    
}

// Calculate average weighted grade
void Student::calc_ave(){

    int i;
    avweight = 0; // Reinitialize to zero in case of changed grades
    for (i = 0; i < 4; i++) {
        avweight += (double)(Student::qgrade[i] * (Student::qweight[i] / 100.0)); // Add up all weighted scores
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

    cout << "\nPlease load from the input file first for student grades.\n";
    // Test the accessor functions for the weights.
    cout << "Quiz weights already included: " << Student::getQ1w() << "%, " << Student::getQ2w()
         << "%, " << Student::getQ3w() << "%, and " << Student::getQ4w() << "%." << endl;
    int s = 0; // For the students in the loops
    int user = 3; // For deciding inputs and outputs

    int choice = 1; // This is to get the while loop working
    while (choice != 0) {
        cout << "Student Grade Evaluator\n";
        cout << "This program enters grades for 3 students and calculates them.\n";
        cout << "0 - Quit Program\n";
        cout << "1 - Input Grades\n";
        cout << "2 - Output Grades\n";

        cout << "Please select an item from the menu list: ";
        cin >> choice;

        switch (choice) {
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
                if (user == 1) {
                    sGrade[0].input(user);
                    cout << "Grades have been read from input file.\n\n";
                } else for (s = 0; s < 3; s++) {
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
                if (user == 2)
                    for (s = 0; s < 3; s++) {
                        sGrade[s].output(user);
                    } else {
                    sGrade[0].output(user);
                }
                break;

            default:
                cout << "\nInvalid input.\n";
        }
    }
    
    return 0;
    
}