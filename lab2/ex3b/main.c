// Created by Marcin Kozub using nftw()
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

struct res_open_dir{
    unsigned int files;
    unsigned int directories;
    unsigned int char_devs;
    unsigned int blocks;
    unsigned int slinks;
    unsigned int pipes;
    unsigned int socks;
};

int *print_data (const char* path, const struct stat *stats, int type_flag, struct FTW *ftw);

struct res_open_dir* res;
bool is_relative_path;
char cwd[PATH_MAX];

int main(int argc, char* argv[]) {

    if(argc < 2){
        perror("There are not enough arguments!");
        exit(-1);
    } else if (argc > 2){
        perror("There are too many arguments!");
        exit(-1);
    }

    char* core = calloc(strlen(argv[1] + 1), sizeof (char));
    strcpy(core, argv[1]);


    char* i = getcwd(cwd, PATH_MAX);
    if(i == NULL){
        perror("Error occurred!");
        exit(-1);
    }

    res = calloc(1, sizeof(struct res_open_dir));
    res->files = 0;
    res->directories = 0;
    res->char_devs = 0;
    res->blocks = 0;
    res->slinks = 0;
    res->pipes = 0;
    res->socks = 0;

    printf("%6s   %10s   %15s   %25s   %25s   %s\n",
           "LINKS",
           "TYPE",
           "SIZE",
           "ACCESS",
           "MODIFIED",
           "PATH");
    nftw(core, (__nftw_func_t) print_data, 1, 0);
    printf("Files: %u  Dirs:%u  CharDevs:%u  BlockDevs:%u  SLinks:%u  FIFOs:%u  Socks:%u\n",
           res->files,
           res->directories,
           res->char_devs,
           res->blocks,
           res->slinks,
           res->pipes,
           res->socks);


    free(res);

    return 0;
}

int *print_data (const char* path, const struct stat *stats, int type_flag, struct FTW *ftw){

    if(!type_flag || !ftw){
        // do nothing... it is ok.
    }

    char type[10];
    switch (stats->st_mode & S_IFMT) {
        case S_IFSOCK:
            res->socks++;
            strcpy(type, "sock");
            break;
        case S_IFLNK:
            res->slinks++;
            strcpy(type, "slink");
            break;
        case S_IFREG:
            res->files++;
            strcpy(type, "file");
            break;
        case S_IFBLK:
            res->blocks++;
            strcpy(type, "block dev");
            break;
        case S_IFDIR:
            res->directories++;
            strcpy(type, "dirs");
            break;
        case S_IFCHR:
            res->char_devs++;
            strcpy(type, "char dev");
            break;
        case S_IFIFO:
            res->pipes++;
            strcpy(type, "pipes");
            break;
        default:
            strcpy(type, "unknown");
            break;
    }

    char* acces_date = ctime(&stats->st_atime);
    char* modified_date = ctime(&stats->st_mtime);

    modified_date[strcspn(modified_date, "\n")] = 0;
    acces_date[strcspn(acces_date, "\n")] = 0;


    if (is_relative_path)
        printf("%6lu   %10s   %15ld   %25s   %25s   %s/%s\n",
               stats->st_nlink,
               type, stats->st_size,
               acces_date,
               modified_date,
               cwd,
               path);
    else
        printf("%6lu   %10s   %15ld   %25s   %25s   %s\n",
               stats->st_nlink,
               type,
               stats->st_size,
               acces_date,
               modified_date,
               path);

    return 0;
}