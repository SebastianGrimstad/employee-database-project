#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv[]) {
    printf("Usage %s -n -f <database file>\n", argv[0]);
    printf("\t -n   -   create new database\n");
    printf("\t -f   -   (required) path to database file\n");
    return;
}

int main(int argc, char *argv[]) {
    int c = 0;
    bool newfile = false;
    char *filepath = NULL;

    while ((c = getopt(argc, argv, "nf:")) != -1) {
        switch (c) {
            case 'n':

                newfile = true;
                break;

            case 'f':

                filepath = optarg;
                break;

            case '?':
                printf("Unknown flag -%c\n", c);
                break;

            default:
                return -1;
        }
    }

    if (filepath == NULL) {
        printf("Filepath is a required argument\n");
        print_usage(argv);
        return 0;
    }

    printf("Newfile: %d\n", newfile);
    printf("filepath: %s\n", filepath);

    return 0;
}
