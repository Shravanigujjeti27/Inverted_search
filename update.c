#include "inverted.h"
// Function to update the database by adding a new file
int update_database(M_node *HT[], F_node **head)
{
    char filename[25];                                  // Array to store filename entered by user
    printf("Enter the filename you want to update : "); // Ask user to enter filename to update database
    scanf("%s", filename);
    char *res = strstr(filename, ".");                  // Check for file extension
    if (res)                                           // If extension exists
    {
        if (strcmp(res, ".txt") == 0)                   // Check if file is a .txt file
        {
            FILE *fptr = fopen(filename, "r");          // Open file in read mode
            if (fptr)                                   // Check if file exists
            {
                fseek(fptr, 0, SEEK_END);               // Move pointer to end of file
                unsigned long int f_tell = ftell(fptr); // Get file size
                rewind(fptr);                           // Reset pointer to beginning
                if (f_tell)                             // Check if file is not empty
                {
                    if (check_duplicates(*head, filename) == FAILURE) // Check if file is already present in file list
                    {
                        if (insert_first(head, filename) == SUCCESS) // Insert filename at beginning of linked list
                            printf(GREEN"\nINFO : Successful : Inserting file name %s into file linked list\n"RESET, filename);
                    }
                    else
                    {
                        printf(YELLOW"\nINFO : %s => This file is repeated, so it will not store into the sll\n"RESET, filename);
                        printf(RED "\nINFO : Database update failed\n" RESET);
                        return FAILURE;
                    }
                }
                else
                {
                    printf(RED"\nINFO : %s => This file is empty\n"RESET, filename);
                    printf(RED "\nINFO : Database update failed\n" RESET);
                    return FAILURE;
                }
                fclose(fptr); // Close the file
            }
            else
            {
                printf(YELLOW"\nINFO : %s => This file does not exist in the current directory\n"RESET, filename);
                printf(RED "\nINFO : Database update failed\n" RESET);
                return FAILURE;
            }
        }
        else
        {
            printf(RED"\nINFO : %s => This file is not .txt\n"RESET, filename);
            printf(RED "\nINFO : Database update failed\n" RESET);
            return FAILURE;
        }
    }
    else
    {
        printf(RED"\nINFO : %s => This file has without extension\n"RESET, filename);
        printf(RED "\nINFO : Database update failed\n" RESET);
        return FAILURE;
    }
    print_filenames(*head);     // Print updated file linked list
    create_database(HT, *head); // Recreate database with updated file list
    printf(GREEN"\nINFO : DATABASE UPDATED SUCCESSFULLY🎉\n"RESET);
}
// Function to insert filename at the beginning of file linked list
int insert_first(F_node **head, char *filename)
{
    F_node *new_node = malloc(sizeof(F_node)); // Allocate memory for new node
    if (new_node == NULL)                      // Check for memory allocation failure
        return FAILURE;
    strcpy(new_node->f_name, filename); // Store filename
    new_node->link = NULL;              // Initialize link
    new_node->link = *head;             // Point new node to current head
    *head = new_node;                   // Update head to new node
    return SUCCESS;                     // Insertion successful
}