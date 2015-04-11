#ifndef LEVENSHTEIN_H_INCLUDED
#define LEVENSHTEIN_H_INCLUDED

int leven1( char *a, unsigned int lena, char *b, unsigned int lenb );
int leven2(const char *s, int ls, const char *t, int lt);
List find_similar_words( char word[], int changes, List_Node *start, List_Node *stop );

#endif // LEVENSHTEIN_H_INCLUDED
