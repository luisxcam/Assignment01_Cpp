/*
//Author: Luis Acevedo
//Purpose: Assignment 01 for C++ class
//Version: July 2015
*/
//Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

//namespace
using namespace std;

//Structs
struct Student{
	string name;
	vector<int> grades;
	float gradeAverage;
	char gradeLetter;
};

//prototypes
void fractionCalculator();
void calculations(int, int, int, int);
void gradingSchema();
void arrayOrganizer();
void calculateAverage(Student&);
char calculateGrade(Student);
void calculateTestAvg(vector<Student>, float&, int, vector<float>&);
void printGrades(vector<Student>, vector<float>, float);

//Main
int main(){
	//variables
	int option;
	bool jobNotDone;

	//Configuration of cout
	cout << setprecision(1) << fixed;

	//Welcome message
	cout << "Welcome to Assignment01" << endl;

	//Loop until user finish his work or selection
	do{
		//Restart variables
		jobNotDone = false;

		//Menu
		cout << "Please pick one of the following options to test" << endl;
		cout << "1)Fraction Calculator" << endl << "2)Grading Schema" << endl << "3)Array Organizer" << endl;

		//Grab option picked
		cin >> option;

		//Go to selected menu
		switch (option){
		case 1:
			fractionCalculator();
			break;
		case 2:
			gradingSchema();
			break;
		case 3:
			arrayOrganizer();
			break;
		default:
			cout << "Option invalid please try again." << endl << endl;
			jobNotDone = true;
			break;
		}
	} while (jobNotDone);//check if the job was done or not

	//End of code
	system("pause");
	return 0;
}//main

/******************************
Fraction calculator: You will start by prompting the user for two fractions in the main. The
inputs should be two strings in the form #/#. You must account for both positive and negative
numerators. Therefor -#/# is also a valid input.
******************************/
void fractionCalculator(){
	//variables
	string userInput;
	string allowedChar = "0123456789/-";
	bool divisorFound, stringNotAllowed, numeratorIsNegative, denominatorIsNegative, negativeFound, valuesCaptured = false;
	const char DIVISOR = '/', NEGATIVE = '-';
	int numerator, denominator, firstNumerator = 0, firstDenominator = 0;

	//Tell user how is this going down
	cout << "Welcome to the Fraction Calculator:" << endl << "We'll ask you to input two (2) fractions, while the format of these is incorrect or the values are not allowed we'll continue asking until the proper data is inserted" << endl;

	//Start asking for both fraction
	do{
		//Loop until the user uses the proper string
		do{
			//Promp to use
			cout << "Please insert a fraction in the following format ##/##" << endl;

			//Grab the user input
			cin >> userInput;

			//Restart all variables
			divisorFound = false;
			numerator = 0;
			denominator = 0;
			numeratorIsNegative = false;
			denominatorIsNegative = false;
			negativeFound = false;

			//Check the string for correct formating
			for (int x = 0; x < userInput.length(); x++){
				//Get ready for next check
				stringNotAllowed = true;

				//Compare the string
				for (int y = 0; y < allowedChar.length(); y++){
					//Compare that the values of the string match those of the allowed ones
					if (userInput[x] == allowedChar[y]){
						//check for divisor
						if (userInput[x] == DIVISOR && divisorFound == false){
							stringNotAllowed = false;
							divisorFound = true;
							negativeFound = false;
						}//if
						//if the divisor was found but there's another one, that's not cool yo
						else if (userInput[x] == DIVISOR && divisorFound == true){
							cout << "More than one divisor (/) symbol was found. ";
							break;
						}//else if
						//Symbol for negative value was found, checking conditions
						else if (userInput[x] == NEGATIVE && negativeFound == false){
							stringNotAllowed = false;
							negativeFound = true;
							//Check if it was the denominator or numerator
							if (divisorFound)
								denominatorIsNegative = true;
							else
								numeratorIsNegative = true;
						}//else if
						else if (userInput[x] == NEGATIVE && negativeFound == true){
							cout << "More than one negative (-) symbol found for the same number. ";
							break;
						}
						//The char is allowed, and is not the divisor, cool beans!
						else{
							//String is ok so far
							stringNotAllowed = false;

							//Calculating the numerator
							if (!divisorFound){
								numerator = (numerator * 10) + (userInput[x] - '0');
							}//if
							//Calculating denominator
							else{
								denominator = (denominator * 10) + (userInput[x] - '0');
							}//else
						}
					}//if
				}//for Y

				//Found a problem with the string, get out of the loop
				if (stringNotAllowed){
					break;
				}
			}//for X

			//Changing the value for the numerator and/or denominator
			if (numeratorIsNegative){
				numerator *= -1;
			}

			if (denominatorIsNegative){
				numerator *= -1;
			}

			//Checking if the input passed the string checking
			if (!stringNotAllowed){
				//if is not on division form
				if (!divisorFound){
					stringNotAllowed = true;
					cout << "Values were correct, but the divisor (/) was not found. Please try again" << endl;
				}//if
				else//The divisor was found, checking that the denom is not zero
				{
					//if the denominator is equal to zero
					if (denominator == 0){
						stringNotAllowed = true;
						cout << "Cannot perfom division by zero. Why? Ask SIRI. Please try again" << endl;
					}//if
				}//else

			}//if
			else{
				cout << "The String you entered is invalid. Please try again." << endl;
			}//else
		} while (stringNotAllowed);//checks that the string is ok

		//Both fractions captured
		if (firstDenominator != 0 && denominator != 0)
			valuesCaptured = true;

		//First fraction captured
		if (firstDenominator == 0){
			firstNumerator = numerator;
			firstDenominator = denominator;
		}

	} while (!valuesCaptured);

	//Perform calculations
	calculations(firstNumerator, firstDenominator, numerator, denominator);

}//fractionCalculator

/******************************
In a separate function create a program that will
calculate the following.Addition, Subtraction, Multiplication and Division of the two fractions.Then
display the results in a formatted table.All outputted fractions must be in lowest terms or whole
numbers if possible.
******************************/
void calculations(int numerator, int denominator, int numerator2, int denominator2){
	//variables
	int numeratorCarrier, denominatorCarrier, limitGCF, gcf;

	//Table header
	cout << "Calculations table:" << endl;

	//ADDITION + + + ADDITION + + + ADDITION + + + ADDITION + + + ADDITION + + + 
	//Proceed with addition
	numeratorCarrier = (numerator*denominator2) + (numerator2*denominator);
	denominatorCarrier = denominator * denominator2;

	//Start GCF
	gcf = 1;

	//Start decreasing fraction
	do{
		//Find the GCF limit
		if (abs(numeratorCarrier) > abs(denominatorCarrier))
			limitGCF = abs(denominatorCarrier);
		else
			limitGCF = abs(numeratorCarrier);

		//Find all values
		for (int x = 1; x <= limitGCF; x++){
			if (numeratorCarrier%x == 0 && denominatorCarrier%x == 0)
				gcf = x;
		}

		//Decrease value
		numeratorCarrier /= gcf;
		denominatorCarrier /= gcf;
	} while (gcf != 1);

	//Display result
	cout << setfill(' ') << setw(18) << left << "Addition" << left << numeratorCarrier << "/" << denominatorCarrier << endl;

	//SUBTRACTION - - - SUBTRACTION - - - SUBTRACTION - - - SUBTRACTION - - - 
	//Proceed with addition
	numeratorCarrier = (numerator*denominator2) - (numerator2*denominator);
	denominatorCarrier = denominator * denominator2;

	//Start GCF
	gcf = 1;

	//Start decreasing fraction
	do{
		//Find the GCF limit
		if (abs(numeratorCarrier) > abs(denominatorCarrier))
			limitGCF = abs(denominatorCarrier);
		else
			limitGCF = abs(numeratorCarrier);

		//Find all values
		for (int x = 1; x <= limitGCF; x++){
			if (numeratorCarrier%x == 0 && denominatorCarrier%x == 0)
				gcf = x;
		}

		//Decrease value
		numeratorCarrier /= gcf;
		denominatorCarrier /= gcf;
	} while (gcf != 1);

	//Display result
	cout << setfill(' ') << setw(18) << left << "Subtraction" << left << numeratorCarrier << "/" << denominatorCarrier << endl;

	//MULTIPLICATION * * * MULTIPLICATION * * * MULTIPLICATION * * * MULTIPLICATION * * * 
	//Proceed with addition
	numeratorCarrier = numerator * numerator2;
	denominatorCarrier = denominator * denominator2;

	//Start GCF
	gcf = 1;

	//Start decreasing fraction
	do{
		//Find the GCF limit
		if (abs(numeratorCarrier) > abs(denominatorCarrier))
			limitGCF = abs(denominatorCarrier);
		else
			limitGCF = abs(numeratorCarrier);

		//Find all values
		for (int x = 1; x <= limitGCF; x++){
			if (numeratorCarrier%x == 0 && denominatorCarrier%x == 0)
				gcf = x;
		}

		//Decrease value
		numeratorCarrier /= gcf;
		denominatorCarrier /= gcf;
	} while (gcf != 1);

	//Display result
	cout << setfill(' ') << setw(18) << left << "Multiplication" << left << numeratorCarrier << "/" << denominatorCarrier << endl;

	//DIVISION / / / DIVISION / / / DIVISION / / / DIVISION / / / 
	//Proceed with addition
	numeratorCarrier = numerator * denominator2;
	denominatorCarrier = denominator * numerator2;

	//Start GCF
	gcf = 1;

	//Start decreasing fraction
	do{
		//Find the GCF limit
		if (abs(numeratorCarrier) > abs(denominatorCarrier))
			limitGCF = abs(denominatorCarrier);
		else
			limitGCF = abs(numeratorCarrier);

		//Find all values
		for (int x = 1; x <= limitGCF; x++){
			if (numeratorCarrier%x == 0 && denominatorCarrier%x == 0)
				gcf = x;
		}

		//Decrease value
		numeratorCarrier /= gcf;
		denominatorCarrier /= gcf;
	} while (gcf != 1);

	//Display result
	cout << setfill(' ') << setw(18) << left << "Division" << left << numeratorCarrier << "/" << denominatorCarrier << endl;

}//calculations

/******************************
Grading Schema: In a separate function you will implement a grading schema. Write a
program that reads a student’s name together with his or her test score from a file given by the user.
The first two values in the file will represent the number of students followed by the number of tests.
The program should then compute the average test score for each student and assign the appropriate
grade (A, B, C, D, E or F) as well as the average of each test. Your program must perform the following
functions.
a) A void function calculateAverage, to determine the average of the test scores for each student.[x]
b) A value-returning function, calculateGrade, to determine and return each student’s grade letter.[x]
c) A void function calculateTestAvg that calculates the average of all tests and overall average of
students.
d) A void function printGrades that prints the grades values, average marks and grade letter
followed by the average of all tests and students.
******************************/
void gradingSchema(){
	//variables
	ifstream file;
	string fileInput;
	int numberOfStudents, numberOfTest;
	vector<Student> studentList;
	Student studentCarrier;
	vector<float> gradesAverage;
	float totalGradeAverage;

	//Open the file
	file.open("../grades.txt");

	//grab the amount of students and the amount of test
	file >> fileInput;
	numberOfStudents = stoi(fileInput);
	file >> fileInput;
	numberOfTest = stoi(fileInput);

	//Read the data
	for (int x = 0; x < numberOfStudents; x++){
		//Grab the name
		file >> studentCarrier.name;

		//Grab the grades
		for (int y = 0; y < numberOfTest; y++){
			file >> fileInput;
			studentCarrier.grades.push_back(stoi(fileInput));
		}//for

		//Add to the main array
		studentList.push_back(studentCarrier);

		//Clean the grade vector
		studentCarrier.grades.clear();

		//Calculate the averages
		calculateAverage(studentList[x]);

		//Get the letters
		studentList[x].gradeLetter = calculateGrade(studentList[x]);
	}//for

	//Calculate tests average
	calculateTestAvg(studentList, totalGradeAverage, numberOfTest, gradesAverage);

	//Print the table
	printGrades(studentList,gradesAverage,totalGradeAverage);
}//gradingSchema

void calculateAverage(Student& student){
	//variables
	int gradeCarrier = 0;

	//Get the total
	for (int x = 0; x < student.grades.size(); x++){
		gradeCarrier += student.grades[x];
	}//for

	//Calculate average
	student.gradeAverage = (float)gradeCarrier / student.grades.size();
}//calculateAverage

char calculateGrade(Student student){
	//Check the range
	if (student.gradeAverage < 60.0)
		return 'F';
	else if (student.gradeAverage >= 60.0 && student.gradeAverage < 70.0)
		return 'D';
	else if (student.gradeAverage >= 70.0 && student.gradeAverage < 80.0)
		return 'C';
	else if (student.gradeAverage >= 80.0 && student.gradeAverage < 90.0)
		return 'B';
	else if (student.gradeAverage >= 90.0)
		return 'A';

	return NULL;
}//calculateGrade

void calculateTestAvg(vector<Student> students, float& totalGradeAverage, int amountOfGrades, vector<float>& gradesAverage){
	//variables
	int gradeCarrier = 0;

	//Go through each test
	for (int x = 0; x < amountOfGrades; x++){
		//Go through each student
		for (int y = 0; y < students.size(); y++){
			gradeCarrier += students[y].grades[x];
		}//for

		//Calculate and store
		gradesAverage.push_back((float)gradeCarrier/students.size());

		//Clean
		gradeCarrier = 0;
	}//for

	//Start variable
	totalGradeAverage = 0.0;

	//Calculate the total average
	for (int x = 0; x < gradesAverage.size(); x++){
		totalGradeAverage += (float)gradesAverage[x];
	}
	totalGradeAverage /= (float) gradesAverage.size();
}//calculateTestAvg

void printGrades(vector<Student> students, vector<float> gradesAverage, float totalGradesAverage){
	//Print header
	cout << setfill(' ') << setw(10) << right << "Name" << setw(10) << right << "test1" << setw(10) << right << "test2" << setw(10) << right << "test3" << setw(10) << right << "test4" << setw(10) << right << "test5" << setw(10) << right << "AVG" << setw(10) << right << "Grade" << endl << endl;	 

	//Print values
	
	for (int x = 0; x < students.size(); x++){
		//Name
		cout << setfill(' ') << setw(10) << right << students[x].name;

		//Grades
		for (int y = 0; y < students[x].grades.size(); y++){
			cout << setw(10) << right << students[x].grades[y];
		}

		//Grade Avg
		cout << setw(10) << right << students[x].gradeAverage;

		//Grade Letter
		cout << setw(10) << right << students[x].gradeLetter;
	}//for

	//Print averages
	cout << setfill(' ') << setw(10) << right << "test avg";
	for (int x = 0; x < gradesAverage.size(); x++)
		cout << setw(10) << right << gradesAverage[x];

	//Print the total average
	cout << setw(10) << right << totalGradesAverage;
	cout << endl;
}//printGrades

/******************************
Write a function that given a list of non-negative integers in the range of 1-99 from the
user, arranges them such that they form the largest possible number. For example, given [50, 2, 1, 9],
the largest formed number is 95021. You may assume that you will not receive more than 10 numbers.
You must use vectors throughout the program without any uses of arrays.
******************************/
void arrayOrganizer(){
	//variables
	vector<int> list, organizedList;
	string userInput;
	string allowedChar = "0123456789,";
	const char COMMA = ',';
	int number = NULL;
	bool listNotCompleted, valueNotAllowed;
	int maxIndex;

	//Welcome message
	cout << "Welcome to the Array Organizer." << endl;

	//Start gathering the values
	do{
		//Asume is wrong
		listNotCompleted = true;

		//Ask user
		cout << "Please insert a list of numerical values separated by commas" << endl;

		//Grab value
		cin >> userInput;

		//Check the format of the string
		for (int x = 0; x < userInput.length(); x++){
			//Asume the value being entered is not allowed
			valueNotAllowed = true;

			//Check with the list of allowed values
			for (int y = 0; y < allowedChar.length(); y++){
				if (userInput[x] == allowedChar[y]){

					//Check if it was a blank space or not
					if (userInput[x] == COMMA){
						if (number != NULL){
							list.push_back(number);
							number = NULL;
						}
					}//if
					else{
						//First start the carrier
						if (number == NULL)
							number = 0;

						//Proceed to build the number
						number = (number * 10) + (userInput[x] - '0');

						//Check that the number is only 2 digits long
						if (number >= 100){
							cout << "The value entered is greater than 2 digits long." << endl;
							number = NULL;
							break;
						}
					}//else

					//Value is Ok!
					valueNotAllowed = false;
				}//if
			}//for y

			//if a value wasn't allowed restart the operation
			if (valueNotAllowed){
				cout << "Value not allowed. Please try again" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}

			//If the last value was checked and no errors, add to the vector
			if (x + 1 == userInput.length() && number != NULL){
				list.push_back(number);
				number = NULL;
			}
		}//for x

		//The list was ok
		if (!valueNotAllowed)
			listNotCompleted = false;

	} while (listNotCompleted);//Checking that the user did the list

	//Fill the organized array
	do{
		//Restart for next value
		maxIndex = 0;

		//Iterate through the vector
		for (int x = 0; x < list.size(); x++){
			//Both are double digits
			if (list[x] > 9 && list[maxIndex] > 9 && list[x] > list[maxIndex]){
				maxIndex = x;
			}
			//Both are single digits
			else if (list[x] <= 9 && list[maxIndex] <= 9 && list[x] > list[maxIndex]){
				maxIndex = x;
			}
			//List is single and Max is double
			else if (list[x] <= 9 && list[maxIndex] > 9 && list[x] >= list[maxIndex] / 10){
				if (list[x] >= list[maxIndex] % 10)
					maxIndex = x;
			}
			//List is double and Max is single
			else if (list[x] > 9 && list[maxIndex] <= 9 && list[x] / 10 >= list[maxIndex]){
				if (list[x] % 10 > list[maxIndex])
					maxIndex = x;
			}
		}//for

		//Add to other vector
		organizedList.push_back(list[maxIndex]);

		//Delete the value used
		list.erase(list.begin() + maxIndex);

	} while (list.size() != 0);//do

	//Display result of your madness
	cout << "The biggest number you can get with those number is :" << endl;
	for (int x = 0; x < organizedList.size(); x++){
		cout << organizedList[x] << " ";
	}
	cout << endl;

}//arrayOrganizer