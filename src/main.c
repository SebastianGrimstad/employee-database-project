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

    int dbfd = 0;  // database
    struct dbheader_t *dbhdr = NULL;

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

    if (newfile) {
        dbfd = create_db_file(filepath);
        if (dbfd == STATUS_ERROR) {
            printf("Unable to create database\n");
            return -1;
        }
        if (create_db_header(&dbhdr) == STATUS_ERROR) {
            printf("Failed to create db header!\n");
            return -1;
        }
    } else {
        dbfd = open_db_file(filepath);
        if (dbfd == STATUS_ERROR) {
            printf("Unable to opne datebase\nb");
            return -1;
        }

        if (validate_db_header(dbfd, &dbhdr) == STATUS_ERROR) {
            printf("Failed to validate database header\n");
            return -1;
        }
    }

    output_file(dbfd, dbhdr, NULL);

    return 0;
}
