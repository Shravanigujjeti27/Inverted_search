#include "inverted.h"

void display_database(M_node *HT[])
{
    printf("|----------------------------------------------------------------------|\n");
    printf("|"PURPLE"%-15s%-15s%-15s%-15s%-15s\n","INDEX","WORD","FILECOUNT","FILENAME","WORDCOUNT "RESET"|");
    printf("|----------------------------------------------------------------------|\n");
    // Traverse through all hash table indexes
    for(int i=0;i<27;i++)
    {
        // Check if hash table index is not empty
        if(HT[i] != NULL)
        {
            M_node *main_temp=HT[i];         // Pointer to traverse main list
            // Traverse through main nodes (words)
            while(main_temp)
            {
                S_node *sub_temp=main_temp->sub_link;   // Pointer to traverse sub list
                while(sub_temp)                         // Traverse through sub nodes (files)
                {
                    // For first sub node, print index, word and file count
                    if(sub_temp == main_temp->sub_link)
                    {
                        printf("|"BLUE"%-15d"RESET,i);             // Print index 
                        printf("%-15s"CYAN"%-15d"RESET,main_temp->word,main_temp->file_count);        // Print word and file count
                    }
                    // For remaining sub nodes, leave index and word columns blank
                    else
                    {
                        printf("|%-15s","");                                 // Empty index column
                        printf("%-15s%-15s","","");                         // Empty word and file count columns
                    }
                    printf("%-15s%-10d|\n",sub_temp->filename,sub_temp->word_count);  // Print filename and word count      
                    sub_temp=sub_temp->sub_link;        // Move to next sub node
                }
                main_temp=main_temp->main_link;     // Move to next main node
            }
        }
    }
    printf("|----------------------------------------------------------------------|\n");
}
