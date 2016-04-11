#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

//Typedef for boolean values
typedef int bool;
#define true 1
#define false 0

struct survey
{
	int ppsNumber;
	char firstName[15];
	char lastName[15];
	char address[30];
	char email[30];
	
	int ageBracket;
	int incomeBracket;
	int exercisePerWeek;
	int alcoholPerWeek;
	int smokePerWeek;

	struct survey* next;
};

typedef struct
{
	char user[10];
	char pass[10];
} login_t;

void addSurvey(struct survey** head_ptr);
void sortSurvey(struct survey** head_ptr);
void displayAll(struct survey* head_ptr);
void displaySurveyDetails(struct survey* head_ptr);
void updateSurvey(struct survey** head_ptr);
void deleteFirst(struct survey** head_ptr);
void deleteSurvey(struct survey** head_ptr);
void generateStats(struct survey* head_ptr);
void printReportFile(struct survey* head_ptr);
void saveList(struct survey* head_ptr);
void loadList(struct survey** head_ptr);

void main()
{
	FILE *fptr;
	login_t login[3];
	bool successful = false;
	struct survey* top;
	int choice;
	char userlogin[10];
	char userpass[10];
	char ch;
	int i;

	//Initially set top to NULL
	top = NULL;

	//Login
	fptr = fopen("login.txt", "r");

	if (fptr == NULL)
	{
		printf("Error Opening File.");
		exit(1);
	}
	else
	{
		//Populate login details array
		for (i = 0; i < 3; i++)
		{
			fscanf(fptr, "%s", &login[i].user);
			fscanf(fptr, "%s", &login[i].pass);

			//printf("%s\n%s\n", login[i].user, login[i].pass);
		}

		fclose(fptr);
	}

	while (successful == false)
	{
		//Get username
		printf("\nEnter Username: ");
		scanf("%s", userlogin);

		//Get password
		printf("Enter Password <any 6 characters>: ");

		//Mask password with ******
		for (i = 0; i < 6; i++)
		{
			//Get 6 individual characters from the user put them into the character array one after another while changing the value of ch to '*' and printing it
			ch = _getch();
			userpass[i] = ch;
			ch = '*';
			printf("%c", ch);
		}

		//Put null terminator at the end of the string
		userpass[i] = '\0';

		for (i = 0; i < 3; i++)
		{
			if (strcmp(login[i].user, userlogin) == 0 && strcmp(login[i].pass, userpass) == 0)
			{
				successful = true;
			}
		}
	}
	
	//Load existing list
	loadList(&top);

	//Print menu
	printf("\n\n====Menu====");

	printf("\nAdd Survey (1)");
	printf("\nDisplay All Surveys (2)");
	printf("\nDisplay Survey Details (3)");
	printf("\nUpdate Survey (4)");
	printf("\nDelete Survey (5)");
	printf("\nGenerate Statistics (6)");
	printf("\nPrint Report File (7)");

	//Initial Read
	printf("\n\nEnter Choice (-1 to exit): ");
	scanf("%d", &choice);
	
	while (choice != -1)
	{
		switch (choice)
		{
			case 1:
				addSurvey(&top);
				break;
			case 2:
				displayAll(top);
				break;
			case 3:
				displaySurveyDetails(top);
				break;
			case 4:
				updateSurvey(&top);
				break;
			case 5:
				deleteSurvey(&top);
				break;
			case 6:
				generateStats(top);
				break;
			case 7:
				printReportFile(top);
				break;
		} //end switch

		//Print menu
		printf("\n\n====Menu====");

		printf("\nAdd Survey (1)");
		printf("\nDisplay All Surveys (2)");
		printf("\nDisplay Survey Details (3)");
		printf("\nUpdate Survey (4)");
		printf("\nDelete Survey (5)");
		printf("\nGenerate Stats (6)");
		printf("\nPrint Report File (7)");

		//Subsequent Read
		printf("\n\nEnter Choice (-1 to exit): ");
		scanf("%d", &choice);
		
	} //end while
	
	saveList(top);

	_getch();
}

void generateStats(struct survey* head_ptr)
{
	//Array for each bracket - 5 age brackets + 7 income brackets
	int brackets[12] = { 0 };

	//Arrays for each category storing values for each of the 12 brackets
	//Smokers
	int nonSmokers[12] = { 0 };
	int smoke20[12] = { 0 };
	int smoke40[12] = { 0 };
	int smoke40Plus[12] = { 0 };
	//Exercise
	int nonExercisers[12] = { 0 };
	int exercise3[12] = { 0 };
	int exercise5[12] = { 0 };
	int exercise5Plus[12] = { 0 };
	//Alcohol
	int nonDrinker[12] = { 0 };
	int drink2[12] = { 0 };
	int drink4[12] = { 0 };
	int drink4Plus[12] = { 0 };

	int i, j;
	struct survey *temp;
	temp = head_ptr;

	//loop through list to find total numPeople in each AgeBracket and each IncomeBracket
	while (temp != NULL)
	{
		//Count stats based on age
		for (i = 1; i <= 5; i++)
		{
			if (temp->ageBracket == i)
			{
				//Gets total number of people per age bracket
				switch (i)
				{
					case 1:
						brackets[0]++;
						break;
					case 2:
						brackets[1]++;
						break;
					case 3:
						brackets[2]++;
						break;
					case 4:
						brackets[3]++;
						break;
					case 5:
						brackets[4]++;
						break;
				} //end switch

				//Get number of people in each catagory    
				for (j = 1; j <= 4; j++)
				{
					//Cigarettes
					if (temp->smokePerWeek == j)
					{
						switch (j)
						{
							case 1:
								nonSmokers[i - 1]++;
								break;
							case 2:
								smoke20[i - 1]++;
								break;
							case 3:
								smoke40[i - 1]++;
								break;
							case 4:
								smoke40Plus[i - 1]++;
								break;
						} //end switch
					} //end if

					//Exercise
					if (temp->exercisePerWeek == j)
					{
						switch (j)
						{
							case 1:
								nonExercisers[i - 1]++;
								break;
							case 2:
								exercise3[i - 1]++;
								break;
							case 3:
								exercise5[i - 1]++;
								break;
							case 4:
								exercise5Plus[i - 1]++;
								break;
						} //end switch
					} //end if

					//Alcohol
					if (temp->alcoholPerWeek == j)
					{
						switch (j)
						{
							case 1:
								nonDrinker[i - 1]++;
								break;
							case 2:
								drink2[i - 1]++;
								break;
							case 3:
								drink4[i - 1]++;
								break;
							case 4:
								drink4Plus[i - 1]++;
								break;
						} //end switch
					} //end if
				} //end for (j)

			} //end if (age == i)

		} //end for (i)

		// Count Stats based on Income
		for (i = 1; i <= 7; i++)
		{
			if (temp->incomeBracket == i)
			{
				switch (i)
				{
					case 1:
						brackets[5]++;
						break;
					case 2:
						brackets[6]++;
						break;
					case 3:
						brackets[7]++;
						break;
					case 4:
						brackets[8]++;
						break;
					case 5:
						brackets[9]++;
						break;
					case 6:
						brackets[10]++;
						break;
					case 7:
						brackets[11]++;
						break;
				} //end switch
				
				//Get number of people in each category
				for (j = 1; j <= 4; j++)
				{
					//Cigarettes
					if (temp->smokePerWeek == j)
					{
						switch (j)
						{
						case 1:
							nonSmokers[i + 4]++;
							break;
						case 2:
							smoke20[i + 4]++;
							break;
						case 3:
							smoke40[i + 4]++;
							break;
						case 4:
							smoke40Plus[i + 4]++;
							break;
						} //end switch
					} //end if

					//Exercise
					if (temp->exercisePerWeek == j)
					{
						switch (j)
						{
						case 1:
							nonExercisers[i + 4]++;
							break;
						case 2:
							exercise3[i + 4]++;
							break;
						case 3:
							exercise5[i + 4]++;
							break;
						case 4:
							exercise5Plus[i + 4]++;
							break;
						} //end switch
					} //end if

					//Alcohol
					if (temp->alcoholPerWeek == j)
					{
						switch (j)
						{
						case 1:
							nonDrinker[i + 4]++;
							break;
						case 2:
							drink2[i + 4]++;
							break;
						case 3:
							drink4[i + 4]++;
							break;
						case 4:
							drink4Plus[i + 4]++;
							break;
						} //end switch
					} //end if

				} //end for (j)

			} //end if (income == i)

		} // end for (i)
		
		//increment to next list position
		temp = temp->next;
	} //end while

	printf("=====Statistics=====");
	printf("\nBrackets are as follows:");
	printf("\n\tBracket 1: Ages 18 - 20\n\tBracket 2: Ages 20 - 30\n\tBracket 3: Ages 30 - 50\n\tBracket 4: Ages 50 - 65\n\tBracket 5: Ages 65+");
	printf("\n\tBracket 6: No income\n\tBracket 7: Less than 20,000 Income\n\tBracket 8: Less than 40,000 Income\n\tBracket 9: Less than 60,000 Income");
	printf("\n\tBracket 10: Less than 80,000 Income\n\tBracket 11: Less than 100,000 Income\n\tBracket 12: Greater than 100,000 Income\n\n");

	//Only prints results that can be calculated therefore avoids printing irrelevant/empty results fields
	for (i = 0; i < 12; i++)
	{
		//Check if result is greater than 0 otherwise console prints -NaN
		if ((float)nonSmokers[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d are Non Smokers", ((float)nonSmokers[i] / brackets[i] * 100), (i + 1));

		if ((float)smoke20[i] / brackets[i] * 100 > 0)	
			printf("\n%.2f percent of people in Bracket %d smoke less than 20 Cigarettes per week", ((float)smoke20[i] / brackets[i] * 100), (i + 1));	

		if ((float)smoke40[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d smoke less than 40 Cigarettes per week", ((float)smoke40[i] / brackets[i] * 100), (i + 1));

		if ((float)smoke40Plus[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d smoke greater than 40 Cigarettes per week", ((float)smoke40Plus[i] / brackets[i] * 100), (i + 1));

		if ((float)nonExercisers[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d never exercise", ((float)nonExercisers[i] / brackets[i] * 100), (i + 1));

		if ((float)exercise3[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d exercise 3 times per week", ((float)exercise3[i] / brackets[i] * 100), (i + 1));

		if ((float)exercise5[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d exercise 5 times per week", ((float)exercise5[i] / brackets[i] * 100), (i + 1));

		if ((float)exercise5Plus[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d exercise more than 5 times per week", ((float)exercise5Plus[i] / brackets[i] * 100), (i + 1));

		if ((float)nonDrinker[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d are Non Drinkers", ((float)nonDrinker[i] / brackets[i] * 100), (i + 1));

		if ((float)drink2[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d drink less than 2 units per week", ((float)drink2[i] / brackets[i] * 100), (i + 1));

		if ((float)drink4[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d drink less than 4 units per week", ((float)drink4[i] / brackets[i] * 100), (i + 1));

		if ((float)drink4Plus[i] / brackets[i] * 100 > 0)
			printf("\n%.2f percent of people in Bracket %d drink more than 4 units per week", ((float)drink4Plus[i] / brackets[i] * 100), (i + 1));
	}

} //end stats

void addSurvey(struct survey** head_ptr)
{
	//Pointer to new survey
	struct survey *newNode;
	char emailval[5] = ".com";

	//Allocate space for new survey
	newNode = (struct survey*)malloc(sizeof(struct survey));

	//Get survey info
	printf("\nEnter PPS Number: ");
	scanf("%d", &newNode->ppsNumber);

	printf("\nEnter First Name: ");
	scanf("%s", newNode->firstName);

	printf("\nEnter Last Name: ");
	scanf("%s", newNode->lastName);

	printf("\nEnter Address: ");
	scanf("%s", newNode->address);

	do
	{
		//Validate email address
		//Keep asking for email while strchr() and strstr() functions are returning NULL
		printf("\nEnter Email Address: ");
		scanf("%s", newNode->email);
	} while ((strchr(newNode->email, '@') == NULL) || (strchr(newNode->email, '.') == NULL) || (strstr(newNode->email, emailval) == NULL));

	printf("\nAge Bracket: ");
	printf("\n\t18-20 yrs (1)");
	printf("\n\t20-30 yrs (2)");
	printf("\n\t30-50 yrs (3)");
	printf("\n\t50-65 yrs (4)");
	printf("\n\t65+ yrs (5)");
	printf("\nEnter option (1-5): ");
	scanf("%d", &newNode->ageBracket);

	printf("\nIncome Bracket: ");
	printf("\n\tNo Income (1)");
	printf("\n\tLess Than 20,000 (2)");
	printf("\n\tLess Than 40,000 (3)");
	printf("\n\tLess Than 60,000 (4)");
	printf("\n\tLess Than 80,000 (5)");
	printf("\n\tLess Than 100,000 (6)");
	printf("\n\tGreater Than 100,000 (7)");
	printf("\nEnter option (1-7): ");
	scanf("%d", &newNode->incomeBracket);

	printf("\nHow often do you exercise: ");
	printf("\n\tNever (1)");
	printf("\n\tLess Than 3 Times/week (2)");
	printf("\n\tLess Than 5 Times/week (3)");
	printf("\n\tMore Than 5 Times/week (4)");
	printf("\nEnter option (1-4): ");
	scanf("%d", &newNode->exercisePerWeek);

	printf("\nHow much alcohol do you consume per week: ");
	printf("\n\tNone (1)");
	printf("\n\tLess Than 2 Units (2)");
	printf("\n\tLess Than 4 Units (3)");
	printf("\n\tMore Than 4 Units (4)");
	printf("\nEnter option (1-4): ");
	scanf("%d", &newNode->alcoholPerWeek);

	printf("\nHow many cigarettes do you smoke per week: ");
	printf("\n\tNone (1)");
	printf("\n\tLess Than 20 Cigarettes (2)");
	printf("\n\tLess Than 40 Cigarettes (3)");
	printf("\n\tMore Than 40 Cigarettes (4)");
	printf("\nEnter option (1-4): ");
	scanf("%d", &newNode->smokePerWeek);

	//Take existing value of head_ptr (null or other node) and put it as the 'next' for the newNode
	//So that the new node's 'next' value points either to the original first node or null
	newNode->next = *head_ptr;

	//Now transfer the existing address of the newNode to be the new head_ptr
	*head_ptr = newNode;

	sortSurvey(head_ptr);
}

void sortSurvey(struct survey** head_ptr)
{
	int i, j;
	struct survey *temp;
	struct survey *temp2;
	int tempPPS;
	char tempFirstName[15];
	char tempLastName[15];
	char tempAddress[30];
	char tempEmail[30];
	int tempAgeBracket;
	int tempIncomeBracket;
	int tempExercisePerWeek;
	int tempAlcoholPerWeek;
	int tempSmokePerWeek;

	temp = *head_ptr;
	temp2 = temp->next;

	do
	{
		//Set j to 0
		j = 0;

		while (temp2 != NULL)
		{

			if (temp->ppsNumber > 0)
			{
				//Compare the PPS values of the current next elements
				if (temp->ppsNumber > temp2->ppsNumber)
				{
					//Set j to 1 to continue loop
					j = 1;

					//swap all survey struct values
					tempPPS = temp->ppsNumber;
					temp->ppsNumber = temp2->ppsNumber;
					temp2->ppsNumber = tempPPS;

					strcpy(tempFirstName, temp->firstName);
					strcpy(temp->firstName, temp2->firstName);
					strcpy(temp2->firstName, tempFirstName);

					strcpy(tempLastName, temp->lastName);
					strcpy(temp->lastName, temp2->lastName);
					strcpy(temp2->lastName, tempLastName);

					strcpy(tempAddress, temp->address);
					strcpy(temp->address, temp2->address);
					strcpy(temp2->address, tempAddress);

					strcpy(tempEmail, temp->email);
					strcpy(temp->email, temp2->email);
					strcpy(temp2->email, tempEmail);

					tempAgeBracket = temp->ageBracket;
					temp->ageBracket = temp2->ageBracket;
					temp2->ageBracket = tempAgeBracket;

					tempIncomeBracket = temp->incomeBracket;
					temp->incomeBracket = temp2->incomeBracket;
					temp2->incomeBracket = tempIncomeBracket;

					tempExercisePerWeek = temp->exercisePerWeek;
					temp->exercisePerWeek = temp2->exercisePerWeek;
					temp2->exercisePerWeek = tempExercisePerWeek;

					tempAlcoholPerWeek = temp->alcoholPerWeek;
					temp->alcoholPerWeek = temp2->alcoholPerWeek;
					temp2->alcoholPerWeek = tempAlcoholPerWeek;

					tempSmokePerWeek = temp->smokePerWeek;
					temp->smokePerWeek = temp2->smokePerWeek;
					temp2->smokePerWeek = tempSmokePerWeek;
				}
			}

			//increment
			temp = temp->next;
			temp2 = temp->next;
		} //end while

	} while (j == 1);
}

void displayAll(struct survey* head_ptr)
{
	struct survey *temp;

	temp = head_ptr;

	while (temp != NULL)
	{
		printf("\n\nPPS Number: %d", temp->ppsNumber);
		printf("\nFirst Name: %s", temp->firstName);
		printf("\nLast Name: %s", temp->lastName);
		printf("\nAddress: %s", temp->address);
		printf("\nEmail: %s", temp->email);

		switch (temp->ageBracket)
		{
			case 1:
				printf("\nAge Bracket: 18 - 20 yrs");
				break;
			case 2:
				printf("\nAge Bracket: 20 - 30 yrs");
				break;
			case 3:
				printf("\nAge Bracket: 30 - 50 yrs");
				break;
			case 4:
				printf("\nAge Bracket: 50 - 65 yrs");
				break;
			case 5:
				printf("\nAge Bracket: 65+ yrs");
				break;
		}

		switch (temp->incomeBracket)
		{
			case 1:
				printf("\nIncome Bracket: No income");
				break;
			case 2:
				printf("\nIncome Bracket: Less Than 20,000");
				break;
			case 3:
				printf("\nIncome Bracket: Less Than 40,000");
				break;
			case 4:
				printf("\nIncome Bracket: Less Than 60,000");
				break;
			case 5:
				printf("\nIncome Bracket: Less Than 80,000");
				break;
			case 6:
				printf("\nIncome Bracket: Less Than 100,000");
				break;
			case 7:
				printf("\nIncome Bracket: Greater Than 100,000");
				break;
		}

		switch (temp->exercisePerWeek)
		{
			case 1:
				printf("\nExercise PerWeek: Never");
				break;
			case 2:
				printf("\nExercise PerWeek: Less Than 3 Times");
				break;
			case 3:
				printf("\nExercise PerWeek: Less Than 5 Times");
				break;
			case 4:
				printf("\nExercise PerWeek: More Than 5 Times");
				break;
		}

		switch (temp->alcoholPerWeek)
		{
		case 1:
			printf("\nAlcohol PerWeek: None");
			break;
		case 2:
			printf("\nAlcohol PerWeek: Less Than 2 Units");
			break;
		case 3:
			printf("\nAlcohol PerWeek: Less Than 4 Units");
			break;
		case 4:
			printf("\nAlcohol PerWeek: More Than 4 Units");
			break;
		}

		switch (temp->smokePerWeek)
		{
		case 1:
			printf("\nCigarettes PerWeek: None");
			break;
		case 2:
			printf("\nCigarettes PerWeek: Less Than 20");
			break;
		case 3:
			printf("\nCigarettes PerWeek: Less Than 40");
			break;
		case 4:
			printf("\nCigarettes PerWeek: More Than 40");
			break;
		}
		
		//increment
		temp = temp->next;
	}
}

void displaySurveyDetails(struct survey* head_ptr)
{
	struct survey *temp;
	int pps;

	temp = head_ptr;

	//Enter pps number
	printf("\nEnter Survey PPS Number: ");
	scanf("%d", &pps);

	//loop through list
	while (temp != NULL)
	{
		if (pps == temp->ppsNumber)
		{
			//Print Survey Details
			printf("\n\nPPS Number: %d", temp->ppsNumber);
			printf("\nFirst Name: %s", temp->firstName);
			printf("\nLast Name: %s", temp->lastName);
			printf("\nAddress: %s", temp->address);
			printf("\nEmail: %s", temp->email);

			switch (temp->ageBracket)
			{
			case 1:
				printf("\nAge Bracket: 18 - 20 yrs");
				break;
			case 2:
				printf("\nAge Bracket: 20 - 30 yrs");
				break;
			case 3:
				printf("\nAge Bracket: 30 - 50 yrs");
				break;
			case 4:
				printf("\nAge Bracket: 50 - 65 yrs");
				break;
			case 5:
				printf("\nAge Bracket: 65+ yrs");
				break;
			}

			switch (temp->incomeBracket)
			{
			case 1:
				printf("\nIncome Bracket: No income");
				break;
			case 2:
				printf("\nIncome Bracket: Less Than 20,000");
				break;
			case 3:
				printf("\nIncome Bracket: Less Than 40,000");
				break;
			case 4:
				printf("\nIncome Bracket: Less Than 60,000");
				break;
			case 5:
				printf("\nIncome Bracket: Less Than 80,000");
				break;
			case 6:
				printf("\nIncome Bracket: Less Than 100,000");
				break;
			case 7:
				printf("\nIncome Bracket: Greater Than 100,000");
				break;
			}

			switch (temp->exercisePerWeek)
			{
			case 1:
				printf("\nExercise PerWeek: Never");
				break;
			case 2:
				printf("\nExercise PerWeek: Less Than 3 Times");
				break;
			case 3:
				printf("\nExercise PerWeek: Less Than 5 Times");
				break;
			case 4:
				printf("\nExercise PerWeek: More Than 5 Times");
				break;
			}

			switch (temp->alcoholPerWeek)
			{
			case 1:
				printf("\nAlcohol PerWeek: None");
				break;
			case 2:
				printf("\nAlcohol PerWeek: Less Than 2 Units");
				break;
			case 3:
				printf("\nAlcohol PerWeek: Less Than 4 Units");
				break;
			case 4:
				printf("\nAlcohol PerWeek: More Than 4 Units");
				break;
			}

			switch (temp->smokePerWeek)
			{
			case 1:
				printf("\nCigarettes PerWeek: None");
				break;
			case 2:
				printf("\nCigarettes PerWeek: Less Than 20");
				break;
			case 3:
				printf("\nCigarettes PerWeek: Less Than 40");
				break;
			case 4:
				printf("\nCigarettes PerWeek: More Than 40");
				break;
			}

			//return from function
			return;
		}
		else
		{
			//increment to next list element
			temp = temp->next;
		}
	} //end while

	printf("Survey Not Found");

}

void updateSurvey(struct survey** head_ptr)
{
	struct survey *temp;
	int pps;
	char emailval[5] = ".com";

	temp = *head_ptr;

	//Enter pps number
	printf("\nEnter Survey PPS Number: ");
	scanf("%d", &pps);

	//loop through list
	while (temp != NULL)
	{
		if (pps == temp->ppsNumber)
		{
			//Enter new details
			printf("\nEnter new PPS Number: ");
			scanf("%d", &temp->ppsNumber);

			//enter new name..etc
			printf("\nEnter First Name: ");
			scanf("%s", temp->firstName);

			printf("\nEnter Last Name: ");
			scanf("%s", temp->lastName);

			printf("\nEnter Address: ");
			scanf("%s", temp->address);

			do
			{
				//Validate email address
				//Keep asking for email while strchr() and strstr() functions are returning NULL
				printf("\nEnter Email Address: ");
				scanf("%s", temp->email);
			} while ((strchr(temp->email, '@') == NULL) || (strchr(temp->email, '.') == NULL) || (strstr(temp->email, emailval) == NULL));

			printf("\nAge Bracket: ");
			printf("\n\t18-20 yrs (1)");
			printf("\n\t20-30 yrs (2)");
			printf("\n\t30-50 yrs (3)");
			printf("\n\t50-65 yrs (4)");
			printf("\n\t65+ yrs (5)");
			printf("\nEnter option (1-5): ");
			scanf("%d", &temp->ageBracket);

			printf("\nIncome Bracket: ");
			printf("\n\tNo Income (1)");
			printf("\n\tLess Than 20,000 (2)");
			printf("\n\tLess Than 40,000 (3)");
			printf("\n\tLess Than 60,000 (4)");
			printf("\n\tLess Than 80,000 (5)");
			printf("\n\tLess Than 100,000 (6)");
			printf("\n\tGreater Than 100,000 (7)");
			printf("\nEnter option (1-7): ");
			scanf("%d", &temp->incomeBracket);

			printf("\nHow often do you exercise: ");
			printf("\n\tNever (1)");
			printf("\n\tLess Than 3 Times/week (2)");
			printf("\n\tLess Than 5 Times/week (3)");
			printf("\n\tMore Than 5 Times/week (4)");
			printf("\nEnter option (1-4): ");
			scanf("%d", &temp->exercisePerWeek);

			printf("\nHow much alcohol do you consume per week: ");
			printf("\n\tNone (1)");
			printf("\n\tLess Than 2 Units (2)");
			printf("\n\tLess Than 4 Units (3)");
			printf("\n\tMore Than 4 Units (4)");
			printf("\nEnter option (1-4): ");
			scanf("%d", &temp->alcoholPerWeek);

			printf("\nHow many cigarettes do you smoke per week: ");
			printf("\n\tNone (1)");
			printf("\n\tLess Than 20 Cigarettes (2)");
			printf("\n\tLess Than 40 Cigarettes (3)");
			printf("\n\tMore Than 40 Cigarettes (4)");
			printf("\nEnter option (1-4): ");
			scanf("%d", &temp->smokePerWeek);

			//re-sort the list
			sortSurvey(head_ptr);

			//return from function
			return;
		}
		else
		{
			//increment to next list element
			temp = temp->next;
		}
	} //end while

	printf("Survey Not Found");
}

void deleteFirst(struct survey** head_ptr)
{
	//Take the next item that the head points to and save it
	//Free the head item
	//Set the head to be the next item that we've stored on the side
	struct survey *next_node = NULL;
	//struct survey *temp;

	if (*head_ptr == NULL)
	{
		printf("Nothing to delete");
	}
	else
	{
		//assign the 2nd student to next_node
		next_node = (*head_ptr)->next;

		//free
		free(*head_ptr);

		//set the head of the list to what used to be the 2nd
		*head_ptr = next_node;
	}
}

void deleteSurvey(struct survey** head_ptr)
{
	//Take PPS from user
	//Find the index
	//Iterate to the node before the node we wish to delete
	//Save the node to delete in temp
	//Set the previous node's next pointer to point to the node after the node to delete
	//Delete the node using free(temp)

	int i;
	int pps;
	int index = 0;
	struct survey *current = *head_ptr;
	struct survey *temp = NULL;

	//Take PPS from user
	printf("\nEnter PPS Number of Survey to Delete: ");
	scanf("%d", &pps);

	//Find the index
	while (current != NULL)
	{
		if (current->ppsNumber == pps)
		{
			break;
		}

		//increment index
		index++;
		//increment node
		current = current->next;
	}

	if (current == NULL)
	{
		printf("Survey does not exist");
		return; //return to exit function
	}

	if (index == 0)
	{
		deleteFirst(head_ptr);
		printf("\nDeleted survey with PPS Number: %d", pps);

		return;
	}

	//reset current to head_ptr
	current = *head_ptr;

	for (i = 0; i < index - 1; i++)
	{
		if (current->next == NULL)
		{
			printf("\nNode does not exist");
			return; //return to exit function
		}

		//increment
		current = current->next;
	}

	temp = current->next;
	current->next = temp->next;
	
	free(temp);
	printf("\nDeleted survey with PPS Number: %d", pps);
}

void printReportFile(struct survey* head_ptr)
{
	FILE *fptr;
	struct survey *temp;
	
	temp = head_ptr;

	fptr = fopen("surveyReport.txt", "w");

	if (fptr == NULL)
	{
		printf("Error printing to file - surveyReport.txt");
		return;
	}
	else
	{
		while (temp != NULL)
		{
			fprintf(fptr, "\n======= SURVEY REPORT =======");

			fprintf(fptr, "\nPPS Number: %d", temp->ppsNumber);
			fprintf(fptr, "\nFirst Name: %s", temp->firstName);
			fprintf(fptr, "\nLast Name: %s", temp->lastName);
			fprintf(fptr, "\nAddress: %s", temp->address);
			fprintf(fptr, "\nEmail: %s", temp->email);

			switch (temp->ageBracket)
			{
			case 1:
				fprintf(fptr, "\nAge Bracket: 18 - 20 yrs");
				break;
			case 2:
				fprintf(fptr, "\nAge Bracket: 20 - 30 yrs");
				break;
			case 3:
				fprintf(fptr, "\nAge Bracket: 30 - 50 yrs");
				break;
			case 4:
				fprintf(fptr, "\nAge Bracket: 50 - 65 yrs");
				break;
			case 5:
				fprintf(fptr, "\nAge Bracket: 65+ yrs");
				break;
			}

			switch (temp->incomeBracket)
			{
			case 1:
				fprintf(fptr, "\nIncome Bracket: No income");
				break;
			case 2:
				fprintf(fptr, "\nIncome Bracket: Less Than 20,000");
				break;
			case 3:
				fprintf(fptr, "\nIncome Bracket: Less Than 40,000");
				break;
			case 4:
				fprintf(fptr, "\nIncome Bracket: Less Than 60,000");
				break;
			case 5:
				fprintf(fptr, "\nIncome Bracket: Less Than 80,000");
				break;
			case 6:
				fprintf(fptr, "\nIncome Bracket: Less Than 100,000");
				break;
			case 7:
				fprintf(fptr, "\nIncome Bracket: Greater Than 100,000");
				break;
			}

			switch (temp->exercisePerWeek)
			{
			case 1:
				fprintf(fptr, "\nExercise PerWeek: Never");
				break;
			case 2:
				fprintf(fptr, "\nExercise PerWeek: Less Than 3 Times");
				break;
			case 3:
				fprintf(fptr, "\nExercise PerWeek: Less Than 5 Times");
				break;
			case 4:
				fprintf(fptr, "\nExercise PerWeek: More Than 5 Times");
				break;
			}

			switch (temp->alcoholPerWeek)
			{
			case 1:
				fprintf(fptr, "\nAlcohol PerWeek: None");
				break;
			case 2:
				fprintf(fptr, "\nAlcohol PerWeek: Less Than 2 Units");
				break;
			case 3:
				fprintf(fptr, "\nAlcohol PerWeek: Less Than 4 Units");
				break;
			case 4:
				fprintf(fptr, "\nAlcohol PerWeek: More Than 4 Units");
				break;
			}

			switch (temp->smokePerWeek)
			{
			case 1:
				fprintf(fptr, "\nCigarettes PerWeek: None");
				break;
			case 2:
				fprintf(fptr, "\nCigarettes PerWeek: Less Than 20");
				break;
			case 3:
				fprintf(fptr, "\nCigarettes PerWeek: Less Than 40");
				break;
			case 4:
				fprintf(fptr, "\nCigarettes PerWeek: More Than 40");
				break;
			}
			//increment
			temp = temp->next;
		}

		printf("\nSurvey Report File Successful.\n");
		fclose(fptr);
	}
	
}

void saveList(struct survey* head_ptr)
{
	FILE *fptr;
	struct survey *temp;

	//Open file in write mode
	fptr = fopen("survey.txt", "w");

	if (fptr == NULL)
	{
		printf("\n\nError Saving to file Survey.txt");
		return;
	}
	else
	{
		temp = head_ptr;

		while (temp != NULL)
		{
			fprintf(fptr, "\n%d", temp->ppsNumber);
			fprintf(fptr, "\n%s", temp->firstName);
			fprintf(fptr, "\n%s", temp->lastName);
			fprintf(fptr, "\n%s", temp->address);
			fprintf(fptr, "\n%s", temp->email);
			fprintf(fptr, "\n%d", temp->ageBracket);
			fprintf(fptr, "\n%d", temp->incomeBracket);
			fprintf(fptr, "\n%d", temp->exercisePerWeek);
			fprintf(fptr, "\n%d", temp->alcoholPerWeek);
			fprintf(fptr, "\n%d", temp->smokePerWeek);

			//increment to next list element
			temp = temp->next;
		}

		printf("\n\nSurvey Information saved to file - \"survey.txt\"");
		fclose(fptr);
	}
}

void loadList(struct survey** head_ptr)
{
	FILE *fptr;
	struct survey *newNode, *current;

	current = NULL;

	//Open File
	fptr = fopen("survey.txt", "r");

	if (fptr == NULL)
	{
		printf("\n\nError Opening File Survey.txt");
		return;
	}
	else
	{
		while (!feof(fptr))
		{
			//Allocate space for newNode
			newNode = (struct survey*)malloc(sizeof(struct survey));

			//Scan the survey information
			fscanf(fptr, "%d %s %s %s %s %d %d %d %d %d", &newNode->ppsNumber, newNode->firstName, newNode->lastName, newNode->address, newNode->email, &newNode->ageBracket, &newNode->incomeBracket, &newNode->exercisePerWeek, &newNode->alcoholPerWeek, &newNode->smokePerWeek);

			//Set newNode's next value to - (NULL)
			newNode->next = NULL;

			//if the head_ptr is NULL
			if (*head_ptr == NULL)
			{
				//Set the head_ptr and current to newNode
				current = *head_ptr = newNode;
			}
			else
			{
				//Otherwise set current and current->next to newNode
				current = current->next = newNode;
			}
		} //end while

		fclose(fptr);
	}
}