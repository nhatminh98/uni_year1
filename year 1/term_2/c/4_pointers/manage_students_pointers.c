#include <stdio.h>
#include <stdlib.h>
#include<string.h>


// structure for student details
struct student_details
	{
		char student_name[50];
		int student_number;
		int number_of_courses;
		int student_marks[30];
	};

void newStudent(int *num_students, struct student_details *database);
void addMarks(int *num_students, struct student_details *database);
void printAllStudents(int num_students, struct student_details *database);



int main(void)
{
	int what_do;
	int num_students=0, exit = 0;
	
	struct student_details database[100];
	
	
	// continous while loop that runs until user exits (dependent on exit flag).
	while(exit == 0)
	{
		fpurge(stdin); //purge input incase user tried to input invalid characters, e.g. arrow key up in cmd
		what_do = 0;   // reset what_do (again in case user input invalid characters)
		printf("Type your option:\n1: Introduce new student\n2: Introduce mark\n3: Print report of all students\n4: Exit\n");
		scanf("%d",&what_do);
		
		// switch for each of the 4 options + default switch in case invalid characters are inputted
		switch(what_do)
		{
			case 1:
			newStudent(&num_students,database); //calls newStudent function and passes num_students as a pointer and database
			break;
			
			
			case 2:
			addMarks(&num_students,database);  //calls addMarks function and passes num_students as a pointer and database
			break;

			
			case 3:
			printAllStudents(num_students,database);  //calls printAllStudents function and passes num_students and database
			break;

			
			case 4:
			exit = 1;
			break;
		
			default:
			printf("Input not recognised\n\n");
			break;	
		}
	}
	return 0;
}




// adds new student to database. Takes two arguments, num_students and the database to which it has to add the student.
// database should be in form of array of structs and num_students should be one more than the last number in the array. Num_students is incremented at the end of the function.
void newStudent(int *num_students, struct student_details *database)
{
	int i;
	fpurge(stdin); // purges stdin as last character in stdin will be a newline character (which would interfere with the scanf below)
	
	printf("Please input the student's name\n");
	scanf("%[^\n]",&database[*num_students].student_name);  // %[^\n] makes scanf run until it encounters a newline character - thus allowing it to accept spaces
	
	printf("Please input the student number\n");
	scanf("%d",&database[*num_students].student_number); 
	
	printf("Please input the number of courses the student is enrolled in\n");
	scanf("%d",&database[*num_students].number_of_courses);
	
	for(i=0;i<database[*num_students].number_of_courses;i++)    // for loop for adding marks, loops through number_of_courses in database for that student until value is reached
	{
		printf("please input the marks for course number %d\n",i+1);  // i + 1 for aesthetics as we would have a course 0 otherwise
		scanf("%d",&database[*num_students].student_marks[i]);
	}
						
	*num_students = *num_students + 1;  // increments num_students by 1, so that it will remain up to date
}




// displays all students in the order in which they were added to the system. Then allows user to choose a student to add marks to.
void addMarks(int *num_students, struct student_details *database)
{
	int i, number, new_number_of_courses;
	if(*num_students == 0) // checks if there are students in the system, if not then complains to user
	{
		printf("Please add a student first!\n\n");
	}
	else
	{
		for(i=0;i<*num_students;i++) // for loop that prints all students in the order they were added to the system
		{
			printf("\n");
			printf("%d -> student name: %s\n",(i+1),database[i].student_name); // i+1 for aesthetic reasons, to avoid student 0
		}
		
		
		// asks user for selection, and once selection is made, asks for number of courses.
		printf("\n");
		printf("please choose your student: \n");
		scanf("%d",&number);
		number = number - 1;
		
		// asks for marks based on the number of courses the user previously input
		printf("Please input the number of courses\n");
		scanf("%d",&new_number_of_courses);
			
		for(i=0; i<new_number_of_courses; i++)
		{
			printf("please input the marks for course number %d\n", (i + 1 + database[number].number_of_courses)); // i+1 for aesthetic reasons, to avoid student 0
			scanf("%d",&database[number].student_marks[(i + database[number].number_of_courses)]);
		}
		
		database[number].number_of_courses = database[number].number_of_courses + new_number_of_courses; // increases the stored values of number of courses by the number of new courses
	}
}
	
	
	
// loops through all values in the array of structs and prints them all.
// uses num_students value to find where to end the loop (does not take it as a pointer as no changes are made to num_students).
void printAllStudents(int num_students, struct student_details *database)
{
	int i, c;
	for(i=0;i<num_students;i++)
			{
				printf("\n");
				printf("student name: %s\n",database[i].student_name);
				printf("student number: %d\n",database[i].student_number);
				printf("student marks: ");
				for(c=0;c<database[i].number_of_courses;c++)
				{
					printf("%d ",database[i].student_marks[c]);
				}
				printf("\n");
			}
			printf("\n");
}