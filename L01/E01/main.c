#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXDIM 51

char *cercaRegexp (char *src, char *regexp);

int main() {
    char stringa[MAXDIM], regexp[MAXDIM];
    char *c;

    printf("Inserire regexp: ");
    scanf("%s", regexp);
    printf("Inserire stringa: ");
    scanf("%s", stringa);
    c = cercaRegexp(stringa, regexp);
    if (c == NULL)
        printf("Regexp non trovata.\n");
    else
        printf("Regexp trovata: %p  %c", c, *c);


}

char *cercaRegexp (char *src, char *regexp) {
    int i, j, k, t;
    int found = 0, flag;

    for (i=0; i<strlen(src) && !found; i++) {
        found = 1;
        k = 0;
        for (j=0; j<strlen(regexp) && found && src[i+k] != '\0'; j++ && k++) {
            if (regexp[j] == '[') {
                if (regexp[j+1] != '^') {
                    flag = 0;
                    for (t = j+1; regexp[t] != ']'; t++) {
                        if (src[i+k] == regexp[t])
                            flag = 1;
                    }
                    if (flag == 1)
                        j = t;
                    else
                        found = 0;
                }
                else {
                    flag = 0;
                    for (t = j+2; regexp[t] != ']' && !flag; t++) {
                        if (src[i+k] == regexp[t])
                            flag = 1;
                    }
                    if (flag == 1)
                        found = 0;
                    else
                        j = t;
                }
            }
            else if (regexp[j] == '\\') {
                if (regexp[j+1] == 'a') {
                    if (!islower(src[i+k]))
                        found = 0;
                }
                else if (regexp[j+1] == 'A') {
                    if (!isupper(src[i+k]))
                        found = 0;
                }
            }
            else if (regexp[j] != '.') {
                if (src[i+k] != regexp[j])
                    found = 0;
            }
        }
        if (src[i] == '\0' && regexp[j] != '\0')
            found = 0;
    }
    if (!found || j!=strlen(regexp))
        return NULL;
    return src+i-1;
}
