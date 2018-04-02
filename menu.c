//
// Created by sigitbn on 3/27/18.
//
#include <stdio.h>
#include <stdlib.h>
#include "stack1D.h"
#include "stack.h"
#include "file.h"
#include "node.h"
#include "menu.h"

void menu_add_node() {
    char repeat;
    do {
        int node_index = 0;

        printf("Masukkan nomor simpul:\n");
        scanf("%d", &node_index);
        int status = add_node(node_index);
        if (status != -1) {
            printf("Simpul %d berhasil ditambahkan\n", node_index);
        } else {
            printf("Simpul tidak berhasil ditambahkan\n");
        }
        printf("Apakah Anda ingin mengulangi?(y/n)\n");
        scanf("\n%c", &repeat);

    } while (repeat == 'y');
}

void menu_connect_node() {
    char *street_name = malloc(80);
    int source = 0;
    int destination = 0;
    int address_source;
    int address_destination;

    do {
        printf("Masukkan nomor simpul asal:\n");
        scanf("\n%d", &source);
        address_source = get_node_address(source);

        if (address_source == -1) {
            printf("Simpul tidak ditemukan, apakah anda ingin menambakan simpul? (y/n)\n");
            char add;
            scanf("\n%c", &add);
            if (add == 'y') {
                address_source = add_node(source);
                printf("Simpul %d berhasil ditambahkan\n", source);
            }
        }
    } while (address_source == -1);

    do {
        printf("Masukkan nomor simpul tujuan:\n");
        scanf("\n%d", &destination);
        address_destination = get_node_address(destination);

        if (address_destination == -1) {
            printf("Simpul tidak ditemukan, apakah anda ingin menambakan simpul? (y/n)\n");
            char add;
            scanf("\n%c", &add);
            if (add == 'y') {
                address_destination = add_node(destination);
                printf("Jalan %d berhasil ditambahkan\n", destination);
            }
        }
    } while (address_destination == -1);

    printf("Masukkan nama jalan:\n");
    scanf("\n%s", street_name);

    connect_street(address_source, address_destination, street_name);
    free(street_name);

}

void menu_show_street() {

}

void menu_search_route() {
    int source = 0;
    int destination = 0;
    int address_source;
    int address_destination;

    do {
        printf("Masukkan node asal:\n");
        scanf("\n%d", &source);
        address_source = get_node_address(source);

        if (address_source == -1) {
            printf("Node tidak ditemukan, apakah anda ingin mengganti node asal? (y/n)\n");
            char change;
            scanf("\n%c", &change);
            if (change != 'y') {
                return;
            }
        }
    } while (address_source == -1);

    do {
        printf("Masukkan node tujuan:\n");
        scanf("\n%d", &destination);
        address_destination = get_node_address(destination);

        if (address_destination == -1) {
            printf("Node tidak ditemukan, apakah anda ingin mengganti node tujuan? (y/n)\n");
            char change;
            scanf("\n%c", &change);
            if (change != 'y') {
                return;
            }
        }
    } while (address_destination == -1);

    struct Stack1D *solution = search_route(address_source, address_destination);
    unsigned char *node_network = get_char_array_from_file("node_network.bin");
    //printf("s%d", node_network[stack1DPop(solution)]);
    struct Stack1D *street_index = createStack1D(100);

    int next = stack1DPop(solution);
    while (!isStack1DEmpty(solution)) {

        int current = stack1DPop(solution);
        if (current != -1) {
            for (int i = 0; i < 5; i++) {
                int neighbour = current + (i * 6) + 3;
                int current_neighbour = get_address(node_network, neighbour);
                if (current_neighbour == next) {
                    stack1DPush(street_index, get_address(node_network, neighbour + 3));
                    next = current;
                    break;
                }
            }
        }
    }

    while (!isStack1DEmpty(street_index)) {
        int index = stack1DPop(street_index);
        printf("%s, ", get_street_info(index, 1));
    }

    printf("\n");
    free(solution);
}
