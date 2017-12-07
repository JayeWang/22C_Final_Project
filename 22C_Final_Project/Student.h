//
// Zhou Wang
//  Student.hpp
//  TempProject
//
////////////

#ifndef Student_h
#define Student_h

#include <iostream>
#include <stdio.h>
using namespace std;

class Student
{
    string studentID;   /* the unique key */
    string Name;        /* the search second key */
    string enroll_Date;
    bool status;        /* true for Full-time, false for Part-time */
    float GPA; /* 0 - 4.0 */
    int unitCompleted;

public:
    Student(){};
    Student(const string& theID, const string& theName, const string &enroll_Date,  bool isfullTime, const float& theGpa, const int& theUnits);

    /* Accessor funtions */
    string getStudentID() const;
    string getEnrollDate() const;
    string getName() const;
    bool getStatus() const;
    float getGpa() const;
    int getUnitsCompleted() const;

    /* Mutator funtions */
    void setStudentID(string ID){this->studentID = ID;}
    void setName(string name){this->Name = name;}
    void setEnrollDate(string date){this->enroll_Date = date;}
    void setStatus(bool status){this->status = status;}
    void setGpa(float gpa){this->GPA = gpa;}
    void setUnitsCompleted(int unitsCompleted){this->unitCompleted = unitsCompleted;}



    /* overloaded operators, comparing students based on the studentID*/
    bool operator>(const Student&) const;
    bool operator<(const Student&) const;
    bool operator>=(const Student&) const;
    bool operator<=(const Student&) const;
    bool operator==(const Student&) const;
    bool operator!=(const Student&) const;

    friend ostream &operator << (ostream &output, const Student &student){
        output << "StudentId: " << student.getStudentID() << endl;
        output << "Enroll Date : " << student.getEnrollDate() << endl;
        output << "Name: " << student.getName() << endl;
        output << "Status: ";
        if(student.getStatus())
            output << "FullTime" << endl;
        else
            output << "PartTime" << endl;
        output << "GPA: " << student.getGpa() << endl;
        output << "Units Completed: " << student.getUnitsCompleted() << endl;

        return output;
    }

};

Student::Student(const string& theID, const string& theName, const string& theDate,  bool fullTime, const float& theGpa, const int& theUnits):
        studentID(theID), Name(theName), GPA(theGpa), unitCompleted(theUnits), status(fullTime), enroll_Date(theDate){}


string Student::getStudentID() const {return studentID;}
string Student::getEnrollDate() const {return enroll_Date;}
string Student::getName() const {return Name;}
bool Student::getStatus() const {return status;}
float Student::getGpa() const {return GPA;}
int Student::getUnitsCompleted() const {return unitCompleted;}

bool Student::operator>(const Student& theStudent) const
{
    return studentID > theStudent.studentID;
}

bool Student::operator<(const Student& theStudent) const
{
    return studentID < theStudent.studentID;
}

bool Student::operator>=(const Student& theStudent) const
{
    return studentID >= theStudent.studentID;
}

bool Student::operator<=(const Student& theStudent) const
{
    return studentID <= theStudent.studentID;
}

bool Student::operator==(const Student& theStudent) const
{
    return studentID == theStudent.studentID;
}

bool Student::operator!=(const Student& theStudent) const
{
    return studentID != theStudent.studentID;
}


/*
 Name                    ID         GPA       IsFullTime      EnrollDate    UnitsCompleted
 Stanley Griffin     44918524     3.56         part-time    03/04/15     33
 Kyle Aguilar        12466249     3.29         full-time    03/04/12     92
 Carmen Holmes       98833494     1.37         full-time    03/04/15     22
 Meredith Lambert    29099997     2.97         full-time    03/08/11     23
 Brendan Marsh       52894630     3.89         full-time    03/04/12     99
 Kristen Mccarthy    87789460     2.57         part-time    12/04/13     37
 Dora Blake          55898602     1.45         part-time    02/04/11     99
 Raymond Lamb        89619733     2.68         part-time    03/04/15     22
 Suzanne Briggs      18528076     3.4          full-time    03/08/13     97
 Dana Miles          52972391     0.38         full-time    03/04/15     122
 Tim Nichols         77370250     2.45         part-time    03/04/12     87
 Edward Massey       54688476     3.66         part-time    03/01/15     32
 Wesley Valdez       84301406     0.34         part-time    07/04/12     89
 Mary Lee            94500541     3.67         full-time    01/04/13     98
 Isabel Zimmerman    55418766     1.23         full-time    03/04/15     72
 Barny Bas           24253552     3.35         part-time    03/12/12     23
 Lillian Porter      24622366     1.5          full-time    10/12/14     12
 Bernadette Taylor   57086018     0.98         part-time    03/11/15     32
 Akane ka            24325235     3.9          full-time    03/12/15     34
 Yvette Morgan       69459190     4            part-time    01/03/12     24
 Jimmie Cook         94234524     0.98         full-time    08/04/11     87
 Denise Goodman      83615900     3.45         part-time    03/03/14     22
 Justin Moore        48544988     3.78         full-time    03/04/16     23
 Kirk Holt           32667798     4            part-time    03/04/15     8
 Nancy Cox           70892940     2.96         full-time    03/04/15     100
*/
#endif

