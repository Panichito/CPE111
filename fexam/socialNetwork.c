/* social.c
 *
 * Created by Panithi Suwanno (Big) 63070503426
 * For Final Exam CPE111 (Thu. 13/06/2021)
 *
 * I have decided to use Tree data structure.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListUtil.h"

typedef struct _person
{
	char username[64];
	char firstname[64];
	char lastname[64];
	char date[32];

	LIST_HANDLE *friend;
	struct _person *left;
	struct _person *right;
} PEOPLE_T;

void usage() 
{
	printf("Usage:   ./socialNetwork [inputfile]\n\n");
	exit(0);
}

PEOPLE_T* findUser(char *username, PEOPLE_T* root)
{
	PEOPLE_T* found = NULL;
	if(root != NULL)
	{
		if(strcmp(username, root->username) == 0)
			found = root;
		else if(strcmp(username, root->username) < 0)
			found = findUser(username, root->left);
		else
			found = findUser(username, root->right);
	}
	return found;
}

void makeFriend(PEOPLE_T* f1, PEOPLE_T* f2)
{
	/* too make it short - f stand for friend */
	if(f1->friend == NULL) {
		f1->friend = newList();
	}
	if(f2->friend == NULL) {
		f2->friend = newList();
	}
	if(listInsertEnd(f1->friend, f2) && listInsertEnd(f2->friend, f1)) {
		printf("\t'%s' and '%s' is now friends\n", f1->username, f2->username);
	}
	else {
		printf("Linked list error!\n");
	}
}

void insertNode(PEOPLE_T* root, PEOPLE_T* person)
{
	if(strcmp(person->username, root->username) < 0)   /* go left */
	{
		if(root->left == NULL)
		{
			root->left = person;
			printf("Succussfully added user '%s' to the social network\n", person->username);
			printf(" -- Adding '%s' as a left child of '%s'\n", person->username, root->username);
		}
		else
			insertNode(root->left, person);
	}
	else  /* go right */
	{
		if(root->right == NULL)
		{
			root->right = person;
			printf("Succussfully added user '%s' to the social network\n", person->username);
			printf(" -- Adding '%s' as a right child of '%s'\n", person->username, root->username);
		}
		else 
			insertNode(root->right, person);
	}
}


/* my intention is to making main function shorter */
void buildNetwork(PEOPLE_T** rootNode, FILE* pIn)
{
	char input[256];
	char username[64];
	char firstname[64];
	char lastname[64];
	char date[64];
	PEOPLE_T* person = NULL;
	PEOPLE_T* friend1 = NULL;
	PEOPLE_T* friend2 = NULL;
	PEOPLE_T* root = NULL;
	while(fgets(input, sizeof(input), pIn) != NULL)
	{
		sscanf(input, "%s %s %s %s", username, firstname, lastname, date);

		person = (PEOPLE_T*) calloc(1, sizeof(PEOPLE_T));
		if(person == NULL)
		{
			printf("Memory allocation error!\n");
			exit(2);
		}

		/* FRIEND - this case firstname = firstusername, lastname = secondusername */
		if(strcmp(username, "FRIEND") == 0) 
		{
			friend1 = findUser(firstname, root);
			friend2 = findUser(lastname, root);
			if(friend1 == NULL)
			{
				printf("Skipping %s not exist\n", firstname);
				continue;
			} if(friend2 == NULL) {
				printf("Skipping %s not exist\n", lastname);
				continue;
			}
			makeFriend(friend1, friend2);
			continue;
		}
		
		if(findUser(username, root) != NULL)  /* found this username in data structure */
		{
			printf("Username '%s' is already taken - skipping!\n", username);
			continue;
		}

		strcpy(person->username, username);
		strcpy(person->firstname, firstname);
		strcpy(person->lastname, lastname);
		strcpy(person->date, date);
		if(root == NULL)
		{
			root = person;
			printf("Succussfully added user '%s' to the social network\n", root->username);
			printf(" -- Adding '%s' as a root node\n", root->username);
		}
		else 
			insertNode(root, person);
	}
	*rootNode = root;
	/* I separate the file reading from the main function. 
	 * So I have to set root node in order to recall it in my main function */
}

int getMenuOption()
{
	char input[16];
	int option = -1;
	while(option < 0)
	{
		printf("Availble actions:\n");
		printf("\t 1 - Create a new user\n");
		printf("\t 2 - Show a user's friends\n");
		printf("\t 3 - Suggest new friends\n");
		printf("\t 4 - Add new friends\n");
		printf("\t 5 - Exit the program\n");
		printf("What action? ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%d", &option);
		if((option > 5) || (option < 1))
		{
			printf("Invalid selection - choose 1 to 5\n");
			option = -1;
		}
	}
	printf("\n");
	return option;
}

void createNewUser(PEOPLE_T* root)
{
	char input[64];
	char username[64];
	char firstname[64];
	char lastname[64];
	char date[64];
	PEOPLE_T* check = NULL;

	printf("Enter new username: ");
	fgets(input, sizeof(input), stdin);
	sscanf(input, "%s", username);
	check = findUser(username, root);
	if(check != NULL)
	{
		printf("\tSorry, that username is already in use!\n\n");
		return;
	}

	if(strcmp(username, "DONE") == 0)  /* prevent repeated with DONE in addFriend() function */
	{
		printf("\tSorry, 'DONE' is reserved word!\n\n");
		return;
	}

	printf("\nCreating a new user profile for '%s'\n", username);
	printf("\tWhat is your first name? ");
	fgets(input, sizeof(input), stdin);
	sscanf(input, "%s", firstname);
	printf("\tWhat is your last name? ");
	fgets(input, sizeof(input), stdin);
	sscanf(input, "%s", lastname);
	printf("\tWhat is your birthday (dd-mm-yyyy)? ");
	fgets(input, sizeof(input), stdin);
	sscanf(input, "%s", date);

	check = (PEOPLE_T*) calloc(1, sizeof(PEOPLE_T));
	if(check == NULL)
	{
		printf("Memory allocation error!\n");
		exit(2);
	}
	else 
	{
		strcpy(check->username, username);
		strcpy(check->firstname, firstname);
		strcpy(check->lastname, lastname);
		strcpy(check->date, date);
		insertNode(root, check);
		printf("\n");
	}
}

int isFriend(PEOPLE_T* person1, PEOPLE_T* person2)
{
	LIST_HANDLE list = NULL;
	list = person1->friend;
	if(list == NULL)
	{
		printf("\tNo friends for '%s'\n", person1->username);
	}
	else 
	{
		listReset(list);
		person1 = listGetNext(list);
		while(person1 != NULL)
		{
			if(strcmp(person1->username, person2->username) == 0)
				return 1;
			person1 = listGetNext(list);
		}
	}
	return 0;
}

void printAllFriend(char* name, PEOPLE_T* root, int *count)
{
	PEOPLE_T* find = findUser(name, root);
	LIST_HANDLE list = find->friend;
	if(list == NULL) {
		printf("\tNo friends for '%s'\n", find->username);
	}
	else {
		listReset(list);
		find = listGetNext(list);
		while(find != NULL) {
			printf("\t%s %s (%s) - Brithday %s\n", find->firstname, find->lastname, find->username, find->date);
			find = listGetNext(list);
			*count = *count + 1;  /* count for printing  format */
		}
	}
}

void suggestFriend(char* name, PEOPLE_T* root)
{
	PEOPLE_T* find = findUser(name, root);
	LIST_HANDLE list = find->friend;
	if(list == NULL) {
		printf("\tNo friends for '%s'\n", find->username);
	}
	else {
		listReset(list);
		find = listGetNext(list);
		while(find != NULL) {
			int count = 0;
			PEOPLE_T* check = findUser(find->username, root);
			LIST_HANDLE listChk = check->friend;
			listReset(listChk);
			check = listGetNext(listChk);

			printf("\tFriend of '%s' whom you might like:\n", find->username);
			while(check != NULL)
			{
				if(strcmp(name, check->username) != 0 && !isFriend(check, findUser(name, root))) {
					printf("\t\t%s %s (%s) - Brithday %s\n", check->firstname, check->lastname, check->username, check->date);
					++count;
				}
				check = listGetNext(listChk);
			}
			if(!count) {
				printf("\t\tNo friends suggestion\n");
			}
			find = listGetNext(list);
		}
	}
}

void addFriend(PEOPLE_T* root)
{
	char input[64];
	char friend[64];
	PEOPLE_T* check1 = NULL;
	PEOPLE_T* check2 = NULL;

	printf("Add friends for what user? ");
	fgets(input, sizeof(input), stdin);
	sscanf(input, "%s", input);
	check1 = findUser(input, root);
	if(check1 == NULL)
	{
		printf("\tSorry, this username is not exist!\n\n");
		return;
	}
	
	while(1)
	{
		printf("Adding friends for user '%s %s (%s)'\n", check1->firstname, check1->lastname, check1->username);
		printf("\tWho do you want to add (username)? (DONE to stop) ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%s", friend);
		if(strcmp(friend, "DONE") == 0)
			break;
		else if(strcmp(friend, check1->username) == 0)
		{
			printf("\tSorry, you are entering your own name - try again\n");
			continue;
		}
		check2 = findUser(friend, root);
		if(check2 == NULL)
		{
			printf("\tSorry, username '%s' is not exist!\n\n", friend);
			continue;
		}

		if(isFriend(check1, check2))
		{
			printf("\t>> This user is alredy your friend!\n");
			continue;
		}
		printf("\t>> User '%s' is now your friend!\n", check2->username);
		makeFriend(check1, check2);
	}
}

int main(int argc, char* argv[])
{
	/* for program initialize */
	char input[256];
	FILE* pIn = NULL; 
	/* for data structure */
	PEOPLE_T* root = NULL;  /* tree always start from root node */
	PEOPLE_T* person = NULL;
	/* for run program */
	int option = -1;
	int count = 0;

	if(argc < 2)
		usage();
	pIn = fopen(argv[1], "r");
	if(pIn == NULL)
	{
		printf("Error cannot open '%s' for reading!\n", argv[0]);
		exit(1);
	}
	
	/* read file */
	buildNetwork(&root, pIn);
	fclose(pIn);
	printf("\n");
	/* finished file reading process */

	/* start program */
	option = getMenuOption();
	while(option != 5)
	{
		switch(option)
		{
			case 1:
				createNewUser(root);
				break;
			case 2:
				count = 0;
				printf("Print friends for what user? ");
				fgets(input, sizeof(input), stdin);
				sscanf(input, "%s", input);
				person = findUser(input, root);
				if(person == NULL)
				{
					printf("\tSorry, username '%s' is not exist!\n\n", input);
					break;
				}
				printf("Here is a list of your current friends:\n");
				printAllFriend(input, root, &count);
				if(count == 0) 
					printf("\tSorry, we cannot find any friend of '%s'!\n", input);
				break;
			case 3:
				count = 0;
				printf("Suggest friends for what user? ");
				fgets(input, sizeof(input), stdin);
				sscanf(input, "%s", input);
				person = findUser(input, root);
				if(person == NULL)
				{
					printf("\tSorry, username '%s' is not exist!\n\n", input);
					break;
				}
				printf("Here is a list of your current friends:\n");
				printAllFriend(input, root, &count);
				if(count == 0) 
				{
					printf("\t'%s' has no friends!\n", input);
					break;
				}
				printf("-- Here are some people you might to know -- \n");
				suggestFriend(input, root);
				break;
			case 4:
				addFriend(root);
				break;
			default:
				printf("Invalid option - we should never get here!\n");
		}
		option = getMenuOption();
	}

	printf("\tGood bye!\n\n");
	return 0;
}

