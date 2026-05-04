#include "inverted.h"
// Function to search a word in the inverted index database
void search_database(M_node *HT[], char *word)
{
    int index = get_index(word); // Get hash index of the given word
    while (HT[index])            // Traverse through the main list at the calculated index
    {
        if (!strcmp(HT[index]->word, word)) // Check if current main node word matches the search word
        {
            printf("===============================================\n");
            printf(PURPLE"FOUND AT : \n"RESET);
            printf(BLUE"%-10s"RESET" : [%d]\n", "INDEX", index);                      // Print index where word is found
            printf(BLUE"%-10s"RESET" : %-15s\n", "WORD", HT[index]->word);            // Print the word
            printf(BLUE"%-10s"RESET" : %-15d\n", "FILECOUNT", HT[index]->file_count); // Print number of files in which word appears
            S_node *sub_temp = HT[index]->sub_link;                        // Pointer to traverse sub list
            while (sub_temp)                                               // Traverse and print file details
            {
                printf(BLUE"%-10s"RESET" : %-10s || "BLUE"%-10s"RESET" : %-15d\n", "FILENAME", sub_temp->filename, "WORDCOUNT", sub_temp->word_count);
                sub_temp = sub_temp->sub_link; // Move to next sub node
            }
            printf("===============================================\n");
            return; // Exit function once word is found
        }
        HT[index] = HT[index]->main_link; // Move to next main node if word does not match
    }
    // If word is not found in database
    printf(CYAN"\nINFO : WORD IS NOT FOUND IN THE DATABASE😑\n"RESET);
}
