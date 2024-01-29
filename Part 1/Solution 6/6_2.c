#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* the trie node data structure */
struct s_trie_node
{
    char *translation; /* NULL if node not a word */

    /* pointer array to child nodes */
    struct s_trie_node *children[UCHAR_MAX + 1];
};

/* pointer to the root node of the trie structure */
static struct s_trie_node *proot = NULL;

/* helper functions for trie structure */

/* allocate new node on the heap
   output: pointer to new node (must be freed) */
struct s_trie_node *new_node(void);

/* delete node and all its children
   input: pointer to node to delete
   postcondition: node and children are freed */
void delete_node(struct s_trie_node *pnode);

/* add word to trie, with translation
   input: word and translation
   output: non-zero if new node added, zero otherwise
   postcondition: word exists in trie */
int add_word(const char *word, char *translation);

/* read dictionary file into trie structure */
unsigned int load_dictionary(const char *filename);

/* search trie structure for word and return translations
   input: word to search
   output: translation, or NULL if not found */
char *lookup_word(const char *word);

/* maximum number of characters for word to search */
#define WORD_MAX 256

/* maximum number of characters in line */
#ifndef LINE_MAX
#define LINE_MAX 2048
#endif

// main function ============================================================================================================
int main(int argc, char *argv[])
{
    char word[WORD_MAX], *translation;
    int len;

    if (argc <= 1)
        return 0; /* no dictionary specified */

    /* load dictionary */
    proot = new_node();
    load_dictionary(argv[1]);

    do
    {
        printf("Enter word to translate: ");
        fflush(stdout);
        if (!fgets(word, WORD_MAX, stdin))
            abort();

        /* strip trailing newline */
        len = strlen(word);
        if (len > 0 && word[len - 1] == '\n')
        {
            word[len - 1] = '\0';
            --len;
        }

        /* exit on empty string */
        if (len == 0)
            break;

        /* lookup word */
        translation = lookup_word(word);

        if (translation)
            printf("%s -> %s\n", word, translation);
        else
            printf("\"%s\" not found\n", word);
    } while (1);

    /* clean up trie structure */
    delete_node(proot);

    return 0;
}
// ==========================================================================================================================

/* allocate new node on the heap
   output: pointer to new node (must be freed) */

struct s_trie_node *new_node(void)
{
    /* TODO: allocate a new node on the heap, and
      initialize all fields to default values */
    struct s_trie_node *newNode = (struct s_trie_node *)malloc(sizeof(struct s_trie_node));
    if (newNode)
    {
        newNode->translation = NULL;
        for (int i = 0; i < UCHAR_MAX + 1; i++)
        {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

/* delete node and all its children
   input: pointer to node to delete
   postcondition: node and children are freed */

void delete_node(struct s_trie_node *pnode)
{
    /* TODO: delete node and all its children
     Be sure to free non-null translations!
     Hint: use recursion
   */
    if (!pnode)
    {
        return;
    }
    for (int i = 0; i < UCHAR_MAX + 1; i++)
    {
        delete_node(pnode->children[i]);
    }
    if (pnode->translation)
    {
        free(pnode->translation);
        pnode->translation = NULL;
    }
    free(pnode);
}

/* add word to trie, with translation
   input: word and translation
   output: non-zero if new node added, zero otherwise
   postcondition: word exists in trie */

int add_word(const char *word, char *translation)
{
    /* TODO: add word to trie structure
       If word exists, append translation to existing
       string
       Be sure to store a copy of translation, since
       the string is reused by load_dictionary()
     */
    struct s_trie_node *current = proot;
    for (int i = 0; word[i] != '\0'; i++)
    {
        unsigned char index = (unsigned char)word[i];
        if (!current->children[index])
        {
            current->children[index] = new_node();
            if (!current->children[index])
            {
                return 0; // Allocation failure
            }
        }
        current = current->children[index];
    }
    if (current->translation)
    {
        // Word already exists, append translation
        size_t len = strlen(current->translation);
        current->translation = (char *)realloc(current->translation, len + strlen(translation) + 1);
        strcat(current->translation, translation);
    }
    else
    {
        // New word, allocate memory for translation
        current->translation = strdup(translation);
    }
    return 1;
}

/* delimiter for dictionary */
#define DELIMS "\t"

/* read dictionary file into trie structure */
unsigned int load_dictionary(const char *filename)
{
    FILE *pfile;
    char line[LINE_MAX], *word, *translation;
    unsigned int icount = 0;

    /* ensure file can be opened */
    if (!(pfile = fopen(filename, "r")))
        return icount;

    /* read lines */
    while ((fgets(line, LINE_MAX, pfile)))
    {
        /* strip trailing newline */
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
            --len;
        }

        if (len == 0 || line[0] == '#')
            continue; /* ignore comment/empty lines */

        /* separate word and translation */
        word = line + strspn(line, DELIMS);
        if (!word[0])
            continue; /* no word in line */
        translation = word + strcspn(word, DELIMS);
        *translation++ = '\0';
        translation += strspn(translation, DELIMS);

        /* add word to trie */
        if (add_word(word, translation))
            icount++;
    }

    /* finish */
    fclose(pfile);
    return icount;
}

/* search trie structure for word and return translations
   input: word to search
   output: translation, or NULL if not found */
char *lookup_word(const char *word)
{
    struct s_trie_node *current = proot;
    for (int i = 0; word[i] != '\0'; i++)
    {
        unsigned char index = (unsigned char)word[i];
        if (!current->children[index])
        {
            return NULL;
        }
        current = current->children[index];
    }
    return current->translation;
}
