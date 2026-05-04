/*
NAME        : G. Shravani
DATE        : 28 FEB 2026
DESCRIPTION : The purpose of storing an index is to optimize speed and performance in finding relevant documents for a search query.
			  Without an index, the search engine would scan every document in the corpus,
			  which would require considerable time and computing power.
*/
#include "inverted.h"
int update_flag = 0; // Flag to check whether database is updated
int create_flag = 0; // Flag to check whether database is created
int main(int argc, char *argv[])
{
	F_node *head = NULL; // Pointer to the first node of file list
	M_node *HT[27];		 // Hash table array to store database (26 alphabets + 1 for remaining all other characters)
	// Initialize all hash table pointers to NULL
	for (int i = 0; i < 27; i++)
		HT[i] = NULL;
	// Validate_files
	if (argc >= 2)					 // Check whether file names are passed through command line
		validate_files(argv, &head); // Validate input files and create file list
	else
	{
		printf("-------------------------------------------------\n");
		printf(RED"INFO : Insufficient arguments\n");
		printf("Please pass the arguments like ./a.out <txt file>\n"RESET);
		printf("-------------------------------------------------\n");
		return FAILURE;
	}
	// Print validated file names
	if (print_filenames(head) == FAILURE)
	{
		printf(RED "ERROR : No valid files found\n" RESET);
		printf(YELLOW "Database creation is not possible\n-> NULL\n" RESET);
		return FAILURE;
	}
	int option; // Variable to store user choice
	do
	{
		// Display menu options
		printf("\nSelect your choice among following operations:\n1. Create Database\n2. Display Database\n3. Save Database\n4. Search\n5. Update Database\n6. Exit\n\nEnter your choice : ");

		scanf("%d", &option); // Read user choice

		switch (option)
		{
		case 1:
			create_database(HT, head); // Create database from files
			create_flag = 1;		   // Set database created flag
			break;

		case 2:
			if (!create_flag) // Check if database is created or not
			{
				printf(YELLOW"\nDatabase not created yet Nothing to display!!\n"RESET);
				break;
			}
			display_database(HT); // Display database contents
			break;

		case 3:
			char filename[25]; // Variable to store output file name
			printf("Enter the filename to save database : ");
			scanf("%s", filename);		 // Read file name
			save_database(HT, filename); // Save database into file
			break;
		case 4:
			char word[25]; // Variable to store search word
			printf("Enter the word to search : ");
			scanf("%s", word);		   // Read word
			search_database(HT, word); // Search word in database
			break;

		case 5:
			if (!create_flag) // Check if database exists
			{
				printf(YELLOW"\nDatabase not created yet Nothing to update!!\n"RESET);
				break;
			}
			create_flag = 0;			// Reset create flag
			update_flag = 1;			// Set update flag
			update_database(HT, &head); // Update database
			create_flag = 1;			// Set create flag again
			break;

		case 6:
			printf(PURPLE"\nThank you for using Inverted Search🤗\n"RESET);
			break; // Exit the program

		default:
			printf(RED"\nINFO : Please enter the valid option🤷\n"RESET);
		}
	} while (option != 6); // Repeat until user selects Exit

	return 0; // End of program
}
