///\file dictionary.c
///\brief Biblioteca C pentru implementarea dictionarul de cuvinte.
///
/// Autori: Dumitru Bogdan,Enache Ionut in 25/06/2015.
/**
    *S-a implementat:
* -salvarea dictionarului intr-un fisier
* -eliberarea memoriei listei ce contine dictionarul
* -incarcarea dictionarului
*/
#include "list.h" ///> index_lex(),index_len(),sort_list_len(),sort_list_lex(),list_insert(),list_remove(),save_list(),print_list()
#include "dictionary.h" ///>free_list(),load_dictionaries(),save_dictionary()
#include <stdlib.h> ///> malloc()
#include <stdio.h> ///> printf()
#include <assert.h> ///> assert()
#include <string.h> ///> strlen()

void free_list(List * list){

    ///\fn void free_dict(List * dict)
    ///\brief Elibereaza memoria alocata dictionarului.
    ///\param dict Pointer de tip List
    ///
    ///Implemntarea eliberarii de momorie alocata unei liste.

    List_Node *i=list->head;
    List_Node *next;

    while (i != NULL) {
        next = i->next;

        free(i->word);
        free(i);

        i = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

void load_dictionaries(){

    ///\fn void load_dictionaries()
    ///\brief Incarcarea dictionarelor in memorie.
    ///
    /// Implementarea memorarii dictionarelor din fisierele wordsEnLex.txt si wordsEnLen.txt in listele aferente si indexarea acestora

    dict_lex = load_dictionary("dictionary/wordsEnLex.txt",false);
    index_lex(&dict_lex, ind_lex);

    dict_len = load_dictionary("dictionary/wordsEnLen.txt",false);
    index_len(&dict_len, ind_len, &max_len);
}

List load_dictionary(char file_name[], bool eliminate_duplicates ){ // doar pt limba romana

    ///\fn List load_dictionary(char file_name[], bool eliminate_duplicates )
    ///\brief Incarca dictionarul.
    ///\param file_name Variabila de tip char ce memoreaza numele fisierului
    ///\param eliminate_duplicates Variabila de tip bool precizeaza eliminarea duplicatelor
    ///
    ///Implemntarea memorarii unui dictionar intr-o lista.


    List l;
    l.head =NULL;
    List_Node *n = NULL;

    char buffer[255]; //in buffer se va salva fiecare linie din fisier
    char* p;    // p va reprezenta un pointer la fiecare element din buffer

    FILE* f=fopen(file_name,"r");
    assert(f!=NULL);

    while(fgets(buffer,255,f)){
        if(buffer[ strlen(buffer)-1] == '\n')
           buffer[strlen(buffer)-1] = '\0';

        n = (List_Node*) malloc( sizeof(List_Node) );

        p=strtok(buffer," \t\n");
        if(p!=NULL){
            n->word = (char *) malloc( sizeof(char)*strlen(p)+1 );
            strcpy( n->word, p);
        }

        p=strtok(NULL," \t\n");
        if(p!=NULL){
            n->app = atoi(p);
        }
        list_insert(&l,n);
    }
    fclose(f);
    return l;
}

void save_dictionary(List* l, char file_name[]) {

    ///\fn void save_dictionary(List* l, char file_name[])
    ///\brief Salveaza lista.
    ///\param l Variabila de tip List
    ///\param file_name Variabila de tip char ce memoreaza numele fisierului
    ///
    ///Implemntarea salvarii intr-un fisier a unui dictionar (cuvant si numar de aparitii).


    List_Node *i=l->head;
    char file_path[100]="\dictionary\\";
    strcat(file_path,file_name);
    FILE* f=fopen(file_name, "w");
    assert(f!=NULL);

    while (i != NULL) {
        fprintf(f,"%s\t\t %d\n", i->word, i->app);
        i = i->next;
    }
    fclose(f);
}
