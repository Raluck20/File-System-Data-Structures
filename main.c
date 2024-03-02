/* Movileanu Raluca - 311CB */
#include <stdbool.h>
#include "tree.h"

int main() {
    char *line, *function, *name, *type;
    line = malloc (MAXLENLINE * sizeof(char));
    if (!line) {
        printf("Allocation error!\n");
        return -1; // exit code, eroare de alocare
    }
    /* Initializare director root si curent */
    Dir * root = alocHeadDir(NULL, "root");
    Dir * currentDir = root;
    size_t length;

    do {
        fgets(line, MAXLENLINE, stdin);
        length = strlen(line);
        if (line[length - 1] == '\n') {
            line [length - 1] = '\0';
        }
        function = strtok(line, " ");

        if (strcmp(function, "touch") == 0) {
            name = strtok(NULL, "");
            touch(currentDir, name);
        }
        if (strcmp(function, "mkdir") == 0) {
            name = strtok(NULL, "");
            mkdir(currentDir, name);
        }
        if (strcmp(function, "ls") == 0) {
            ls(currentDir);
        }
        if (strcmp(function, "rm") == 0) {
            name = strtok(NULL, "");
            currentDir->head_children_files = rm(currentDir, name);
        }
        if (strcmp(function, "rmdir") == 0) {
            name = strtok(NULL, "");
            currentDir = rmDir(currentDir, name);
        }
        if (strcmp(function, "cd") == 0) {
            name = strtok(NULL, "");
            cd(&currentDir, name);
        }
        if (strcmp(function, "pwd") == 0) {
            pwd(currentDir);
            printf("\n");
        }
        if (strcmp(function, "find") == 0) {
            bool found = false;
            type = strtok(NULL, " ");
            name = strtok(NULL, "");
            find(root, type, name, &found);
            if (!found) {
                if (strcmp (type, "-d") == 0) {
                    printf("Directory %s not found!\n", name);
                }
                if (strcmp (type, "-f") == 0) {
                    printf("File %s not found!\n", name);
                }
            }
        }
        if (strcmp(function, "quit") == 0) {
            rmAll(root);
            free(line);
            exit(0);
        }
    }
    while (true);

    return 0;
}