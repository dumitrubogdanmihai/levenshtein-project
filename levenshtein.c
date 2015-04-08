#include"list.h"

int min_val(int a, int b, int c) {
    if(a < b){
        if(a < c)
            return a;
        else
            return c;
    }
    else{
        if(b < c)
            return b;
        else
            return c;
    }
}

int leven1( char *a, unsigned int la, char *b, unsigned int lb ){
    unsigned int m[50][50];
    int i,j;

    for(i=0;i<la;i++)
        m[i][0]=i;
    for(j=0;j<lb;j++)
        m[0][j]=j;

    for(i=0;i<la;i++){
        for(j=0;j<lb;j++){
            if(a[i]==b[j]){
                m[i+1][j+1]=m[i][j];
            }
            else{
                m[i+1][j+1]=min_val(m[i][j], m[i][j+1], m[i+1][j]) + 1;
            }
        }
    }
    return m[la][lb];
}

int leven2(const char *s, int ls, const char *t, int lt)
{
        int a, b, c;

        if (!ls) return lt;
        if (!lt) return ls;

        if (s[ls] == t[ls])
                return leven2(s, ls - 1, t, lt - 1);
        a = leven2(s, ls - 1, t, lt - 1);
        b = leven2(s, ls,     t, lt - 1);
        c = leven2(s, ls - 1, t, lt    );

        if (a > b) a = b;
        if (a > c) a = c;

        return a + 1;
}
