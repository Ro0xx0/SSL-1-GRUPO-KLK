#include <stdio.h>
#include "scanner.h"

int main(void) {
    TOKEN t;
    while ((t = Scanner()) != 13) {
        printf("%d->%s\n", t, Buffer());
    }
}
