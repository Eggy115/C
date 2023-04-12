#include <stdio.h>
#include <stdlib.h>

int interpreter(FILE *src);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: bf <file>\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");

    if (!fp) {
        fprintf(stderr, "Could not open brainfuck file %s :(\n", argv[1]);
        exit(2);
    }

    return interpreter(fp);
}

int interpreter(FILE *src) {
    char c;
    int mem = 0, code = 0;
    char memory[3001];

    fseek(src, 0, SEEK_END);

    int src_len = ftell(src);
    char *source = (char*)malloc(src_len);
    rewind(src);

    for (int i = 0; i < src_len; i++) {
        source[i] = fgetc(src);
    }

    while (code >= 0 && code < src_len) {
        char ch = source[code];

        if (ch == '.') {
            printf("%c", memory[mem]);
        }

        if (ch == ',') {
            memory[mem] = fgetc(stdin);
        }

        if (ch == '+') {
            memory[mem]++;
        }

        if (ch == '-') {
            memory[mem]--;
        }

        if (ch == '>') {
            mem++;
        }

        if (ch == '<') {
            mem--;
        }
    }

    return 0;
}
