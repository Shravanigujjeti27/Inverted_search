#include "inverted.h"
// Function to save the inverted index database into a file
void save_database(M_node *HT[], char *filename)
{
    char *res = strstr(filename, ".txt"); // Check whether filename has .txt extension
    FILE *fptr = NULL;                    // File pointer initialization
    if (res && !strcmp(res, ".txt"))      // Validate filename extension and open file in write mode
        fptr = fopen(filename, "w");      // Create or overwrite the file
    else
    {
        printf(RED"\nINFO : %s => Please use .txt extension\n"RESET, filename);
        return;
    }
    if (fptr == NULL) // Check if file creation/opening failed
    {
        printf(RED"\nERROR : Unable to create file\n"RESET);
        return;
    }
    for (int i = 0; i < 27; i++) // Traverse through all hash table indexes
    {
        if (HT[i] != NULL) // Check if index contains data
        {
            M_node *main_temp = HT[i]; // Pointer to traverse main list
            while (main_temp)          // Traverse through main nodes
            {
                // Write index, word, and file count to file
                fprintf(fptr, "#%d;", i);
                fprintf(fptr, "%s;", main_temp->word);
                fprintf(fptr, "%d;", main_temp->file_count);
                S_node *sub_temp = main_temp->sub_link; // Pointer to traverse sub list
                                                        // Write sub node details (filename and word count)
                while (sub_temp)
                {
                    fprintf(fptr, "%s;%d;", sub_temp->filename, sub_temp->word_count);
                    sub_temp = sub_temp->sub_link; // Move to next sub node
                }
                fprintf(fptr, "#\n");             // Mark end of one word entry
                main_temp = main_temp->main_link; // Move to next main node
            }
        }
    }
    fclose(fptr); // Close the file after writing
    printf(BLUE"\nINFO : Database saved successfully😍\n"RESET);
}
