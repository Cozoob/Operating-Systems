
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int main(){

    struct Array* arr = create_array(4);
    print_array_values(arr);
//    printf("%lu\n", strlen("file1"));
    add_to_array(arr, "file1");
    add_to_array(arr, "file2");
    print_array_values(arr);

    count(arr);
    count(arr);
    count(arr);

    struct Array* results = create_array(2);

    int i, j;
    i = add_result(results);

    struct Array* arr2 = create_array(3);
    add_to_array(arr2, "file2");
    add_to_array(arr2, "file2");
    add_to_array(arr2, "file2");

    count(arr2);
    j = add_result(results);
    print_array_rows(results);


    // usuwanie test
//    remove_block(results, 0);
//    print_array_rows(results);
//
//    count(arr);
//    j = add_result(results);
//    print_array_rows(results);

    printf("i:%d j:%d\n\n", i, j);

    return 0;
}