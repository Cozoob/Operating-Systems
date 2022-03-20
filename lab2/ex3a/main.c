// Created by Marcin Kozub using opendir(), readdir(), stat
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

struct res_open_dir{
    unsigned int files;
    unsigned int directories;
    unsigned int char_devs;
    unsigned int blocks;
    unsigned int slinks;
    unsigned int pipes;
    unsigned int socks;
};

struct res_open_dir* count(char* next_directory, unsigned int depth);

void print_data (char* path, struct dirent* dirent, struct stat* stat);

void print_error();

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

    printf("%s\n", core);

    struct res_open_dir* res = count(core, 0);
    printf("Files: %u  "
           "Directories:%u  "
           "CharDevs:%u  "
           "BlockDevs:%u  "
           "SLinks:%u  "
           "Pipes:%u  "
           "Socks:%u\n",
           res->files,
           res->directories,
           res->char_devs,
           res->blocks,
           res->slinks,
           res->pipes,
           res->socks);

    return 0;
}

struct res_open_dir* count(char* next_directory, unsigned int depth){
    DIR* dir = opendir(next_directory);
    if(dir == NULL){
        perror("The directory not found.");
        exit(-1);
    }

    chdir(next_directory);

    struct stat* stats = calloc(1, sizeof (struct stat));

    if(stats == NULL){
        print_error();
    }

    char cwd[PATH_MAX + 1];
    char path[2*PATH_MAX + 1];

    if(getcwd(cwd, sizeof (cwd)) == NULL){
        print_error();
    }

    if(depth == 0){
        printf("%6s   %10s   %15s   %25s   %25s   %s\n", "LINKS", "TYPE", "SIZE", "ACCESS", "MODIFIED", "PATH");
    }

    struct res_open_dir* res = calloc(1, sizeof (struct res_open_dir));
    res->pipes=0;
    res->char_devs=0;
    res->directories=0;
    res->blocks=0;
    res->files=0;
    res->slinks=0;
    res->socks=0;

    struct res_open_dir* change_res;
    struct dirent* ent = readdir(dir);
    while(ent){
        int s = stat(ent->d_name, stats);
        if(s == -1){
            print_error();
        }

        if(strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0){
            ent = readdir(dir);
            continue;
        }

        switch (stats->st_mode & S_IFMT) {
            case S_IFREG:
                res->files++;
                break;
            case S_IFSOCK:
                res->socks++;
                break;
            case S_IFLNK:
                res->slinks++;
                break;
            case S_IFBLK:
                res->blocks++;
                break;
            case S_IFDIR:
                res->directories++;
                break;
            case S_IFIFO:
                res->pipes++;
                break;
            case S_IFCHR:
                res->char_devs++;
                break;
            default:
                break;
        }

        snprintf(path, 2 * PATH_MAX, "%s/%s", cwd, ent->d_name);
        print_data(path, ent, stats);

        if (strcmp(ent->d_name,".")!=0 &&
            strcmp(ent->d_name,"..")!=0 &&
            !(stats->st_mode & S_IFLNK) &&
            stats->st_mode & S_IFDIR){

            change_res = count(ent->d_name, depth + 1);
            res->files+=change_res->files;
            res->blocks+=change_res->blocks;
            res->pipes+=change_res->pipes;
            res->char_devs+=change_res->char_devs;
            res->slinks+=change_res->slinks;
            res->socks+=change_res->socks;
            res->directories+=change_res->directories;

            free(change_res);
            change_res = NULL;
        }

        ent = readdir(dir);
    }

    free(stats);
    free(ent);
    closedir(dir);
    chdir("..");
    return res;
}

void print_data (char* path, struct dirent* dirent, struct stat* stat){
    if(stat == NULL){
        print_error();
    }
    if(dirent == NULL){
        print_error();
    }

    char str[11];

    switch (stat->st_mode & S_IFMT) {
        case S_IFREG:
            strcpy(str, "file");
            break;
        case S_IFSOCK:
            strcpy(str, "sock");
            break;
        case S_IFLNK:
            strcpy(str, "slink");
            break;
        case S_IFBLK:
            strcpy(str, "block dev");
            break;
        case S_IFDIR:
            strcpy(str, "directory");
            break;
        case S_IFIFO:
            strcpy(str, "pipe");
            break;
        case S_IFCHR:
            strcpy(str, "char dev");
            break;
        default:
            strcpy(str, "unknown");
            break;
    }

    char* acces_date = asctime(localtime(&stat->st_atim.tv_sec));
    char* modified_date = asctime(localtime(&stat->st_mtim.tv_sec));

    modified_date[strcspn(modified_date, "\n")] = 0;
    acces_date[strcspn(acces_date, "\n")] = 0;

    printf("%6lu   %10s   %15ld   %25s   %25s   %s\n",
           stat->st_nlink,
           str, stat->st_size,
           acces_date,
           modified_date,
           path);
}

void print_error(){
    perror("Error has occurred!");
    exit(-1);
}