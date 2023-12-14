#include <stdio.h>

int isEven (int n);
int gdc(int a, int b);

int main() {
    int a, b, divisore;

    printf("Inserire due numeri interi:");
    scanf("%d %d", &a, &b);
    divisore = gdc(a, b);
    printf("Il massimo comune divisore di %d e %d e' %d.", a, b, divisore);
    return 0;
}

int isEven (int n) {
    return !(n%2);
}

int gdc(int a, int b) {
    int temp;
    if (a==b)
        return a;
    if (b>a) {
        temp = a;
        a = b;
        b = temp;
    }
    if (isEven(a) && isEven(b))
        return 2* gdc(a/2, b/2);
    else if (!isEven(a) && isEven(b))
        return gdc(a, b/2);
    else if (!isEven(a) && !isEven(b))
        return gdc((a-b)/2, b);
    else
        return gdc(a/2, b);

}
