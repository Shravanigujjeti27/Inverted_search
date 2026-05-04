#include "inverted.h"
extern int create_flag; // Flag to check if database is already created
extern int update_flag; // Flag to check update operation
// Function to create and initialize a main node
M_node *create_main_node(char *word, char *filename)
{
    M_node *new_main = malloc(sizeof(M_node)); // Allocate memory for main node
    strcpy(new_main->word, word);              // Store the word
    new_main->file_count = 1;                  // Initialize file count as 1
    new_main->main_link = NULL;                // Initialize main node link

    new_main->sub_link = create_sub_node(filename); // Create and link first sub node
    return new_main;                                // Return created main node
}
// Function to create and initialize a sub node
S_node *create_sub_node(char *filename)
{
    S_node *new_sub = malloc(sizeof(S_node)); // Allocate memory for sub node
    new_sub->word_count = 1;                  // Initialize word count
    strcpy(new_sub->filename, filename);      // Store filename
    new_sub->sub_link = NULL;                 // Initialize sub node link
    return new_sub;                           // Return created sub node
}
// Function to create the inverted index database
void create_database(M_node *HT[], F_node *head)
{
    // If database is already created, do not create again
    if (create_flag)
    {
        printf(YELLOW"INFO : Database is already created\n"RESET);
        return;
    }
    // Traverse through each file in the file list
    while (head)
    {
        FILE *fptr = fopen(head->f_name, "r"); // Open file in read mode
        char str[25];                          // Array to store each word
        while (fscanf(fptr, "%s", str) == 1)
        {
            int index = get_index(str); // Get hash index for the word
            // If hash table index is empty
            if (HT[index] == NULL)
            {
                HT[index] = create_main_node(str, head->f_name); // Create new main node
            }
            else
            {
                M_node *temp = HT[index]; // Pointer to traverse main list
                M_node *prev = NULL;
                // Traverse main list to search for the word
                while (temp && strcmp(temp->word, str) != 0)
                {
                    prev = temp;
                    temp = temp->main_link;
                }
                // If word is not found in main list
                if (temp == NULL)
                {
                    prev->main_link = create_main_node(str, head->f_name); // Add new main node
                }
                // If word is found in main list
                else
                {
                    S_node *sub_temp = temp->sub_link; // Pointer to traverse sub list
                    S_node *sub_prev = NULL;
                    // Traverse sub list to search for filename
                    while (sub_temp && strcmp(sub_temp->filename, head->f_name) != 0)
                    {
                        sub_prev = sub_temp;
                        sub_temp = sub_temp->sub_link;
                    }
                    // If filename is not found in sub list
                    if (sub_temp == NULL)
                    {
                        sub_prev->sub_link = create_sub_node(head->f_name); // Add new sub node
                        temp->file_count++;                                 // Increment file count
                    }
                    // If filename is found, increment word count
                    else
                        sub_temp->word_count++;
                }
            }
        }
        fclose(fptr); // Close the file after reading
        // Print success message after processing each file
        printf(BLUE"\nINFO : Successful : Creation of DATABASE for file : %s\n"RESET, head->f_name);
        if (update_flag) // Stop if update operation is done
            break;
        head = head->link; // Move to next file
    }
}
