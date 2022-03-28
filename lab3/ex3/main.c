#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


void write_error();

void search_dirs(char* directory_name, char* string, int depth);

int main(int argc, char* argv[]) {

    if(argc != 4){
        write_error();
    }

    char* directory_name = argv[1];
    char* string = argv[2];
    int depth = atoi(argv[3]);

    search_dirs(directory_name, string, depth);

    return 0;
}

void write_error(){
    perror("There are incorrect arguments!");
    exit(-1);
}

void search_dirs(char* directory_name, char* string, int depth) {
    if (depth == 0) {
        exit(0);
    }

    DIR *dir = opendir(directory_name);
    FILE *file;

    if (dir == NULL) {
        perror("The directory not found.");
        exit(-1);
    }

    int i = chdir(directory_name);

    if (i != 0) {
        write_error();
    }


    struct stat *stats = calloc(1, sizeof(struct stat));

    if (stats == NULL) {
        write_error();
    }

    char *path = calloc(sizeof(char), 256);
    // 0 - FALSE, anything else - TRUE
    int contains = 0;


    struct dirent *ent = readdir(dir);
    do {
        int s = stat(ent->d_name, stats);
        if (s == -1) {
            write_error();
        }

        if (strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0) {
            ent = readdir(dir);
            continue;
        }

        char *new_path = calloc(sizeof(char), strlen(directory_name) + strlen(ent->d_name));
        sprintf(new_path, "%s/%s", directory_name, ent->d_name);
        path = new_path;

        if (ent->d_type == DT_DIR && fork() == 0) {
            search_dirs(path, string, depth - 1);
            exit(0);
        } else if ((stats->st_mode & S_IFMT) == S_IFREG) {
            file = fopen(path, "r");

            char *line = calloc(sizeof(char), 256);

            while (fgets(line, 256 * sizeof(char), file)) {
                if (strstr(line, string)) {
                    contains = 1;
                }
            }

            if (contains) {
                printf("\nPATH: %s\n", path);
                printf("CHILD PID: %d, PARENT PID: %d\n", getpid(), getppid());
                contains = 0;
            }
        }
        wait(NULL);
        free(path);

        ent = readdir(dir);

    } while (ent);
    closedir(dir);

}