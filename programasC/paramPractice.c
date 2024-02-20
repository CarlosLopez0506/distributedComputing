#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <parameter1> <parameter2> ... <parametern>\n", argv[0]);
        return 1;
    }

    printf("You provided %d parameter(s). They are:\n", argc - 1);

    for (int i = 1; i < argc; i++) {
        printf("Parameter %d: %s\n", i, argv[i]);
    }

    return 0;
}
