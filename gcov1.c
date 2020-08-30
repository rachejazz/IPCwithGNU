#include <stdio.h>
int hcf(int n1, int n2);
int main() {
	printf("HELLO STUPID WORLD");
    int n1, n2;
    printf("Enter two positive integers: ");
    n1=14;n2=20;
    printf("G.C.D of %d and %d is %d.", n1, n2, hcf(n1, n2));
    return 0;
}

int hcf(int n1, int n2) {
    if (n2 != 0)
        return hcf(n2, n1 % n2);
    else
        return n1;
}


