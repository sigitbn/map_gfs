//
// Created by sigitbn on 3/26/18.
//

#ifndef MAP_GFS_FILE_H
#define MAP_GFS_FILE_H

unsigned char *get_char_array_from_file(char *file_name);

int get_address(const unsigned char *array, int i);

void save_char_array_to_file(char *filename, unsigned char *char_array, int latest_free_memory);

void write_integer_to_array(unsigned char *array, int array_address, int integer);

unsigned char get_first_digit(int address);

unsigned char get_second_digit(int address);

unsigned char get_third_digit(int address);

char *get_street_info(int selected_line, int selected_info);

int insert_street_name(char *street_name);

#endif //MAP_GFS_FILE_H
