//  main.cpp
//  22C_Team_Project
//
//  Created by Yunyi Ren on 12/1/17.
//  Copyright © 2017. All rights reserved.

#include "BinarySearchTree.h"  // BST ADT
#include "Student.h"
#include "HashTable.hpp"
#include "StackADT.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
using namespace std;

const char inputFileName[] = "";

/***************************************************************** Menu Functions ***************/
bool addNewData(HashTable<Student*>*, BinarySearchTree<Student*>&, BinarySearchTree<Student*>&);                        // Case 1
bool deleteData(HashTable<Student*>*, BinarySearchTree<Student*>&, BinarySearchTree<Student*>&, Stack<Student*>&);      // Case 2
void searchData(HashTable<Student*>*, BinarySearchTree<Student*>&, BinarySearchTree<Student*>&);                        // Case 3
void listData(const HashTable<Student*>*,const BinarySearchTree<Student*>&,const BinarySearchTree<Student*>&);          // Case 4
void writeDataToFile(HashTable<Student*>*,const BinarySearchTree<Student*>&,const BinarySearchTree<Student*>&);   // Case 5
void showStats(HashTable<Student*>*);                                                                                   // Case 6
void undoDelete(HashTable<Student*>*, BinarySearchTree<Student*>&, BinarySearchTree<Student*>&, Stack<Student*>&);      // Case 7
void showmenu();                                                                                                        // Case 8
void function2017();                        //Hidden option. When chosen, display the name of the developer, Print Team Information

/***************************************************************** Other related functions ******/
void chooseMenu(int&); // get the menu option on switch
int getSize();
void inputFile(HashTable<Student*>*, BinarySearchTree<Student*>&, BinarySearchTree<Student*>&);
int comparePrime(Student *& Std1, Student *& Std2)
{
    if(Std1->getStudentID() > Std2->getStudentID()) return 1;
    else if(Std1->getStudentID() < Std2->getStudentID()) return -1;
    else return 0;
}
int compareSecond(Student *& Std1, Student *& Std2)
{
    if(Std1->getName() > Std2->getName()) return 1;
    else if(Std1->getName() < Std2->getName()) return -1;
    else return 0;
}
void displayTitle();
void display(Student*& );
void displayIndented(Student* & , int&); //overloading function
void myprint(int n,int m,char *p);
bool isPrime(long long number);
int getNextPrime(long long);
bool checkNameInput(string);
bool checkIdInput(string);
bool checkGPAInput(string);
bool checkEnrollDateInput(string);
bool checkUnitsCompleted(string);
void deletePointer (Student*& );

/******************************* Main Function - Starts Here *******************************/
int main()
{
    BinarySearchTree<Student*> PrimeTree;
    BinarySearchTree<Student*> SecondTree;
    Stack<Student*> recycleBin;
    HashTable<Student*>* htable = new HashTable<Student*>(getSize());
    inputFile(htable,PrimeTree,SecondTree);

    int menu;
    bool quitMenu = 1;

    displayTitle();
    while (quitMenu == 1)
    {
        cout << "\n -- Main Menu --";
        chooseMenu(menu);
        switch(menu)
        {
            case 1:
                if (addNewData(htable,PrimeTree,SecondTree))
                    cout << "Add data successful!\n";
                else
                    cout << "Error! The student ID has been used. . .\n";           break;
            case 2:
                deleteData(htable,PrimeTree,SecondTree,recycleBin);           break;
            case 3:
                searchData(htable,PrimeTree,SecondTree);             break;
            case 4:
                listData(htable,PrimeTree,SecondTree);               break;
            case 5:
                writeDataToFile(htable,PrimeTree,SecondTree);        break;
            case 6:
                showStats(htable);              break;
            case 7:
                undoDelete(htable,PrimeTree,SecondTree,recycleBin);               break;
            case 2017:
                function2017();             break;
            case 8:
                showmenu();  recycleBin.clear(deletePointer);                   break;

            case 9:
                quitMenu = 0;
              writeDataToFile(htable, PrimeTree, SecondTree);
              break;
            default:
                cout << "The option does not exist. . . (Enter 8 to see the menu)\n";
        }
    }
    PrimeTree.clear(deletePointer);
    recycleBin.clear(deletePointer);
    delete htable;
    return 0;
}

/******************************* Get Text Size ******************************
    Count the line of file that we know the size of hash table
****************************************************************************/
int getSize()
{
    int size = 0;
    string inputString;
    ifstream infile("Data.txt");
    while(getline(infile, inputString))
        size++;
    infile.close();
   return getNextPrime(size * 2);
   //return 7;
}
/******************************* Input File ********************************* Done
    Read file into three tables
****************************************************************************/
void inputFile(HashTable<Student*>* htable, BinarySearchTree<Student*>& PrimeTree, BinarySearchTree<Student*>& SecondTree)
{
   int units;
   string name;
   float gpa;
   bool s;
   string inputString, firstName, lastName, id, GPA, status, enroll_Date, units_Completed;
   ifstream infile("Data.txt");

   while(infile >> firstName >> lastName >> id >> gpa >> status >> enroll_Date >> units){

      if(status == "full-time")
         s = true;
      else
         s = false;

      name = firstName + " " + lastName;
       name[0] = toupper(name[0]);
      Student*  student = new Student(id, name, enroll_Date, s, gpa, units);
      PrimeTree.insert(comparePrime, student);
      SecondTree.insert(compareSecond, student);
      htable->insert(student->getStudentID(), student);
   }
   infile.close();
}

bool checkIdInput(string id){
    if(id.size() < 1)
        return false;
    else{
        for(char ch : id)
            if(!isdigit(ch))
                return false;
        return true;
    }
}

/******************************* Case 1: Insert Function ******************** Almost done, need add word process
    Add a new point into three tables
****************************************************************************/
bool addNewData(HashTable<Student*>* htable, BinarySearchTree<Student*>& PrimeTree, BinarySearchTree<Student*>& SecondTree)
{
    string id;
    string name;
    string GPA;
    string units_Completed;
    string option;
    string enroll_Date;
    bool status;
    Student* checkStudent;

    cout << "\n -- Insert --\n";

    cout << "Enter the student's ID: " << endl;
    cin.ignore();
    getline(cin, id);
    while (!checkIdInput(id))
    {
        cout << "Id Invalid!! Please Input Again: \n";
        cout << endl;
        getline(cin,id);
    }
    if (htable->getItem(id,checkStudent))
        return false;

    cout << "Enter the student's Name: \n";
    getline(cin,name);
    while (!checkNameInput(name))
    {
        cout << endl;
        getline(cin,name);
    }

    cout << "Enter the student's enroll date (MM/DD/YY): \n";
    getline(cin,enroll_Date);
    while (!checkEnrollDateInput(enroll_Date))
    {
        cout << "Enroll Date Invalid!! Please Input Again: \n";
        cout << endl;
        getline(cin, enroll_Date);
    }

    cout << "Enter the student's GPA: \n";
    getline(cin, GPA);
    while (!checkGPAInput(GPA))
    {
        cout << "GPA Invalid!! Please Input Again: \n";
        cout << endl;
        getline(cin, GPA);
    }

    cout << "Enter the student's Completed Unit: \n";
    getline(cin, units_Completed);
    while (!checkUnitsCompleted(units_Completed))
    {
        cout << "Units Invalid!! Please Input Again: \n";
        cout << endl;
        getline(cin, units_Completed);
    }

    cout << "Is the student a full-time student (Y) or part-time student (N): ";
    cin >> option;
    do{
    if (option == "Y" || option == "y")
        status = true;
    else if (option == "N" || option == "n")
        status = false;
    else option = "";
    } while (option=="");

    Student* tempStudent = new Student(id, name, enroll_Date, status, 10, 10/*stof(GPA), stoi(units_Completed)*/);
    string tempitem = tempStudent->getStudentID();

    if (htable->insert(tempStudent->getStudentID(),tempStudent))
    {
        PrimeTree.insert(comparePrime,tempStudent);
        SecondTree.insert(compareSecond,tempStudent);
    }
    return true;
}
/******************************* Case 2: Delete Function ******************** haven't completed due to the BST function haven't completed
    Delete selected student from three tables
****************************************************************************/
bool deleteData(HashTable<Student*>* htable, BinarySearchTree<Student*>& PrimeTree, BinarySearchTree<Student*>& SecondTree, Stack<Student*>& recycleBin) //"delete data.. Have't complete.";
{
    string targetID;
    Student* tStudent;
    string option;
    bool repeat = true;
    cout << "\n -- Delete --\n";
    cin.ignore();
    do{
    cout << "Enter the student ID for delete (Enter 0 to exit) : ";
    getline(cin, targetID);
    if (targetID == "0")
        return false;
    else if (htable->getItem(targetID,tStudent))
    {
        cout << "------------ Student Information --------------\n";
        cout << *tStudent;
        cout << "-----------------------------------------------\n";
        cout << "Do you want to delete this student? (Enter Y to confirm) ";
        cin >> option;
        if (option == "Y" || option == "y")
        {
            htable->remove(targetID);
            PrimeTree.remove(comparePrime,tStudent);
            SecondTree.remove(compareSecond,tStudent);
            recycleBin.push(tStudent);
            cout << "Delete successful!" << endl;
            repeat = false;
        }
        else
            repeat = true;
    }
    else
        cout << "<" << targetID << ">" << " was not found\n";
    } while (repeat == true);

    cout << "___________________\n";
    return true;
}

/******************************* Case 3: Searching ************************** Haven't do the BST part
    Searching student(s) by primary key & secondary key(all matched)
****************************************************************************/
void searchData(HashTable<Student*>* htable, BinarySearchTree<Student*>& PrimeTree, BinarySearchTree<Student*>& SecondTree)
{
    int menu;
    string tempKey;
    Student* tempStudent = new Student;
    cout << endl;
    cout << "      +--------------------------------------------------+\n";
    cout << "      |        1. Searching by Student ID                |\n";
    cout << "      |        2. Searching by Student Name              |\n";
    cout << "      +--------------------------------------------------+\n";
    cout << " -- Searching --";
    chooseMenu(menu);
        switch(menu)
        {
            case 1:
                cout << "Please enter the student's ID: ";
                cin.ignore();
                getline(cin, tempKey);
                if (htable->getItem(tempKey,tempStudent))
                    cout << *tempStudent;
                else
                    cout << "Haven't found this student.\n";
                break;

            case 2:

                    cout << endl << "Enter the student's name for search : ";
                    cin.ignore();
                    getline(cin, tempKey);
                    tempStudent->setName(tempKey);
                    cout << "------------ Student Information --------------\n";
                    if (!SecondTree.search(display,compareSecond,tempStudent))
                        cout << "<" << tempKey << ">" << " was not found\n";
                    cout << "-----------------------------------------------\n";

                cout << "___________________\n";
                break;
            default:
                cout << "The option " << menu << " does not exist. . . ()\n";
        }
}

/******************************* Case 4: Listing Function ******************* Done
    Listing data from four ways
****************************************************************************/
void listData(const HashTable<Student*>* htable,const BinarySearchTree<Student*>& PrimeTree,const BinarySearchTree<Student*>& SecondTree)
{
    int menu;
    cout << endl;
    cout << "      +--------------------------------------------------+\n";
    cout << "      |        1. Display List Unsorted                  |\n";
    cout << "      |        2. Display Sorted List by Student ID      |\n";
    cout << "      |        3. Display Sorted List by Student Name    |\n";
    cout << "      |        4. Display Indented List                  |\n";
    cout << "      +--------------------------------------------------+\n";
    cout << " -- Listing --";
    chooseMenu(menu);
        switch(menu)
        {
            case 1:
                cout << "------------ Display unsorted list ---------------------------------\n";
                cout << left << setw(11) << "StudentID" << setw(20) << "Name" << setw(12) << "EnrollDate" << setw(6)
                << "GPA" << setw (6) << "Units" << setw(10) << "Status" << endl;
                htable->displayItems(display);
                cout << "--------------------------------------------------------------------\n";
                break;
            case 2:
                cout << "------------ Display Sorted Data by Student ID --------------------\n";
                cout << left << setw(11) << "StudentID" << setw(20) << "Name" << setw(12) << "EnrollDate" << setw(6)
                << "GPA" << setw (6) << "Units" << setw(10) << "Status" << endl;
                PrimeTree.inOrder(display);
                cout << "--------------------------------------------------------------------\n";
                break;
            case 3:
                cout << "------------ Display Sorted Data by Student Name --------------------\n";
                cout << left << setw(11) << "StudentID" << setw(20) << "Name" << setw(12) << "EnrollDate" << setw(6)
                << "GPA" << setw (6) << "Units" << setw(10) << "Status" << endl;
                SecondTree.inOrder(display);
                cout << "--------------------------------------------------------------------\n";
                break;
            case 4:
                PrimeTree.printIndented(displayIndented);
                break;
            default:
                cout << "The option " << menu << " does not exist. . . ()\n";
        }
}

/******************************* Case 5: Write Data into file *************** Haven't start
    Write whole student data base into file based on a BST or the Hash Table
****************************************************************************/
void writeDataToFile(HashTable<Student*>* htable,const BinarySearchTree<Student*>& PrimeTree,const BinarySearchTree<Student*>& SecondTree)
{
   ofstream outfile("Data.txt");
   if(outfile.fail()){
      cout << "Failure to open file!!!" << endl;
      return;
   }
   std::vector<Entry<Student *>> items = htable->getItems();
   Student *temp;
   for(unsigned int i = 0; i < items.size(); i++){
      temp = items[i].getItem();
      outfile << setw(20) << left << temp->getName();
      outfile << setw(10) << left <<  temp->getStudentID() << '\t';
      outfile << setw(10) << temp->getGpa() << '\t';
      if(temp->getStatus())
         outfile << setw(10) << "full-time" << '\t';
      else
         outfile << setw(10) << "part-time" << '\t';
      outfile << setw(10) << temp->getEnrollDate() << '\t';
      outfile << setw(10) << temp->getUnitsCompleted() << endl;
   }
   outfile.close();
}

/******************************* Case 6: Showing Statistics ***************** Done
    Display statistics information from hash table
****************************************************************************/
void showStats(HashTable<Student*>* htable)
{
    cout << "\n -- Show Statistics --\n";
    htable->displayStatistics();
}
/******************************* Case 7: Undo Delete *********************** Need add BST recovery
    Undo the deleted data back to three tables
****************************************************************************/
void undoDelete(HashTable<Student*>* htable, BinarySearchTree<Student*>& PrimeTree, BinarySearchTree<Student*>& SecondTree, Stack<Student*>& recycleBin)
{
    cout << " -- Undo Delete --\n";
    string choice = "Y";
    Student* item;
    cin.ignore();
    while (recycleBin.getTop(item)&&(choice == "Y" || choice=="y"))
    {
        cout << "Do you want to recover the next recent deleted student data? (Y/N)\n";
        cout << *item;

        getline(cin,choice);
        if (choice=="Y"||choice=="y")
        {
            recycleBin.pop(item);
            htable->insert(item->getStudentID(),item);
            PrimeTree.insert(comparePrime,item);
            SecondTree.insert(compareSecond,item);
            cout << "Recover student data successful! \n";
        }
    }
    if (recycleBin.isEmpty())
        cout << "* There is no data in the Recycle Bin anymore. . .\n";
}
/******************************* Case 8: Showing Statistics ***************** Done
    Display menu
****************************************************************************/
void showmenu() //menu
{
    cout << "\n               - Student Database Menu -                    \n";
    cout << "---------------------------------------------------------\n";
    cout << "1. Add new student\n";
    cout << "2. Delete student data\n";
    cout << "3. Searching\n";
    cout << "4. Listing\n";
    cout << "5. Write data to file\n";
    cout << "6. Statistics\n";
    cout << "7, Undo Deleted Data\n";
    cout << "8. Show Menu\n";
    cout << "9. Quit\n";
    cout << "----------------------------------------------------------\n";
//automatically written to a disk file
}
/****************************************************** Other related functions ***************************************************/
void displayTitle()
{
    cout << "      +--------------------------------------------------+\n";
    cout << "      |                                                  |\n";
    cout << "      |        Student Database of De Anza College       |\n";
    cout << "      |                                                  |\n";
    cout << "      +--------------------------------------------------+\n";
    showmenu();
}
void myprint(int n,int m,char *p){
    for(int i=0;i<n;cout << ' ',i++);
    cout.write(p,m);
    cout << endl;
}
void function2017() //Hidden option. When chosen, display the name of the developer
{
    char a[]="010110010101101000101001010110101011",
         b[]="0101           1010",
         c[]="010110010       101010101",
         d[]="0101100101011010 101001010110";
    cout << "\n\n\n";
    myprint(39,21,b);
    myprint(36,25,c);
    myprint(34,29,d);
    myprint(32,33,a);
    myprint(31,35,a);
    myprint(31,35,a);
    myprint(32,33,a);
    myprint(33,31,a);
    myprint(34,29,a);
    myprint(36,25,a);
    myprint(38,21,a);
    myprint(41,17,a);
    myprint(43,13,a);
    myprint(45,9,a);
    myprint(47,5,a);
    cout << "+-----------------------------------------------010--------------------+\n"
         << "| Current Verssion: 1.13                         0                     |\n"
         << "| Developed by Yunyi Ren, Thao Nguyen, Zhou Wang, Jakin Huang Wang     |\n"
         << "| 11/07/2017 in CIS 22C Group Project                                  |\n"
         << "+----------------------------------------------------------------------+\n";
}


void chooseMenu(int& menu)
{
    cout << endl << "Enter your menu option: ";
    if (cin >> menu){}
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


void displayIndented(Student*& anItem, int& indent)
{
   cout << setw(indent*7) << indent << ". " << anItem->getStudentID() << " " << anItem->getName() << endl;
}

void display(Student*& Item)
{
    cout << left << setw(11) << Item->getStudentID() <<  setw(20) << Item->getName()  << setw(12) << Item->getEnrollDate()
     << setw(6) << Item->getGpa() << setw (6) << Item->getUnitsCompleted();
     if (Item->getStatus())
        cout << setw(10) << "Full-Time";
     else
        cout << setw(10) << "Part-Time";
     cout << endl;
} // display function to pass to BST and HT traverse functions

bool isPrime(long long number){
    for(int n = 2; n * n < number; n++)
        if(number % n == 0)
            return false;
    return true;
}

int getNextPrime(long long number){
    while(!isPrime(number))
        number++;
    return number;
}


bool checkNameInput(string name)
{
    int space = 0;
    bool lastName = false;
    if (!isalpha(name[0]))
    {
        cout << "Student's name should start with a letter . . .";
        return false;
    }
    for (std::size_t i=1; i< name.size() ;i++)
    {
        if ( !isalpha(name[i]) && !isspace(name[i]) )
        {
            cout << "Please enter correct name format (Only letters and spaces): ";
            return false;
        }
        else if(isspace(name[i]))
        {
            space ++;
        }
        if (space > 0 && lastName == true && isspace(name[i]))
        {
            cout << "Please enter correct name format (First Name + Last Name): ";
            return false;
        }
        if (space>0 && isalpha(name[i]))
            lastName = true;
    }
    return true;
}

bool checkGPAInput(string GPA){
    if(!isdigit(GPA[0]))
        return false;
    else{
      for(char ch : GPA)
        if(!isdigit(ch) && ch != '.')
            return false;
    }
    return true;
}
bool checkEnrollDateInput(string EnrollDate){
    if(!isdigit(EnrollDate[0]))
        return false;
    else{
        for(char ch:EnrollDate)
            if(!isdigit(ch) && ch != '/' )
                return false;
    }
    return true;
}
bool checkUnitsCompleted(string Units) {
    for(char ch : Units)
        if(!isdigit(ch))
            return false;
    return true;
}

void deletePointer (Student*& target)
{
    delete target;
}

/****************************************************** Reach the end of function ***************************************************/
