#ifndef LEVENSHTEIN_H_INCLUDED
#define LEVENSHTEIN_H_INCLUDED

int min_val(int a, int b, int c);

List find_similar_words( char word[], int changes, List_Node *start, List_Node *stop );

#endif // LEVENSHTEIN_H_INCLUDED
