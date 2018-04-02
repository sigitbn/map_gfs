//
// Created by sigitbn on 3/26/18.
//

#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

unsigned char *get_char_array_from_file(char *file_name) {

    FILE *file = fopen(file_name, "rb");
    unsigned char *char_array = calloc(10, 1);
    for (int i = 0; i < 10; i++) {
        char_array[i] = 0;
    }
    int latest_free_memory;
    if (file) {
        fread(char_array, sizeof(char), 10, file);
        latest_free_memory = get_address(char_array, 0) + 15;

        unsigned char *new_char_array = realloc(char_array, (size_t) latest_free_memory);

        fseek(file, 0, SEEK_SET);
        latest_free_memory = get_address(new_char_array, 0) + 15;
        fread(new_char_array, sizeof(unsigned char), (size_t) latest_free_memory, file);

        fclose(file);
        return new_char_array;
    }

    return char_array;
}

void save_char_array_to_file(char *file_name, unsigned char *char_array, int latest_free_memory) {

    FILE *file = fopen(file_name, "wb");

    if (file) {
        write_integer_to_array(char_array, 0, latest_free_memory);
        int new_size = latest_free_memory + 1;
        fwrite(char_array, sizeof(unsigned char), (size_t) new_size, file);
        fclose(file);
    }
}

void write_integer_to_array(unsigned char *array, int array_address, int integer) {
    array[array_address] = get_first_digit(integer);
    array[array_address + 1] = get_second_digit(integer);
    array[array_address + 2] = get_third_digit(integer);
}

//get address for give first digit pointer (read 3 digit and count the address)
int get_address(const unsigned char *array, int i) {
    int address = array[i] * 256 * 256
                  + array[i + 1] * 256
                  + array[i + 2];

    if (address == 0 && i == 0) address = 3;
    return address;
}

//convert address to 3 digit array [first digit]
unsigned char get_first_digit(int address) {
    int digit = address / (256 * 256);
    return (unsigned char) digit;
}

//convert address to 3 digit array [second digit]
unsigned char get_second_digit(int address) {
    int digit = (address % (256 * 256)) / 256;
    return (unsigned char) digit;

}

//convert address to 3 digit array [third digit]
unsigned char get_third_digit(int address) {
    int digit = (address % (256 * 256 * 256));
    return (unsigned char) digit;
}

char *get_street_info(int selected_line, int selected_info) {
    FILE *file = (FILE *) fopen("street_info.txt", "rb");
    char INFO[30];

    char *result = calloc(30, sizeof(char));

    for (int i = 0; i < 20; i++) {
        result[i] = (char) 0;
    }
    result[0] = '-';

    int line_number = 0;
    char line[100];

    //fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file)) {
        if (line_number == selected_line) {
            char *token = strtok(line, ",\n\0");
            int i = 0;
            //printf("%s", token);
            while (token != NULL) {
                if (i == selected_info) {
                    strcpy(result, token);
                }
                i++;
                //printf("token : %s\n", token);
                token = strtok(NULL, ",\n\0");
            }
        }
        line_number++;
    }
    return result;
}

int insert_street_name(char *street_name) {
    FILE *file = (FILE *) fopen("street_info.txt", "r");
    int i = 0;
    char line[200];

    //get jumlah line
    while (fgets(line, sizeof(line), file)) {
        i++;
    }

    fclose(file);

    file = fopen("street_info.txt", "a");
    fprintf(file, "%d,%s\n", i, street_name);

    fclose(file);

    return i;
}