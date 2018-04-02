//
// Created by sigitbn on 3/25/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "file.h"
#include "stack.h"

int CHILD_DISTANCE = 3;
int NEXT_DISTANCE = 6;
int SIZE_OF_STREET_IN_ARRAY = 9;
int SIZE_OF_STREET_IN_NETWORK = 35;
int FAILED = -1;

/*
 * Struktur bin array
 * | a *b_1 *c_2 _ | b *c_3 _ _| index jalan _ _, *_index _ _ |
 */
int add_node(int node_index) {
    unsigned char *node_array = get_char_array_from_file("node_array.bin");
    unsigned char *node_network = get_char_array_from_file("node_network.bin");

    int current_street_array_address = get_address(node_array, 0);
    int current_street_network_address = get_address(node_network, 0);

    write_integer_to_array(node_array, current_street_array_address, node_index);

    write_integer_to_array(node_array, current_street_array_address + CHILD_DISTANCE,
                           current_street_network_address); // save index street network in street array <child>

    write_integer_to_array(node_array, current_street_array_address + NEXT_DISTANCE,
                           current_street_array_address +
                           SIZE_OF_STREET_IN_ARRAY); // save next street address <next>

    write_integer_to_array(node_network, current_street_network_address, node_index);

    int new_size_network = (current_street_network_address + SIZE_OF_STREET_IN_NETWORK + 10) * sizeof(unsigned char);
    unsigned char *new_network = realloc(node_network, (size_t) new_size_network);
    for (int i = current_street_network_address + 3; i < new_size_network; i++) {
        node_network[i] = 0;//s for street
    }

    int new_size_array = (current_street_array_address + SIZE_OF_STREET_IN_ARRAY + 10);
    unsigned char *new_array = realloc(node_array, (size_t) new_size_array);

    new_array[current_street_array_address + SIZE_OF_STREET_IN_ARRAY] = '-'; // mark for end of street array

    save_char_array_to_file("node_array.bin", new_array,
                            current_street_array_address + SIZE_OF_STREET_IN_ARRAY);

    save_char_array_to_file("node_network.bin", new_network,
                            current_street_network_address + SIZE_OF_STREET_IN_NETWORK);

    free(new_array);
    free(new_network);
    return current_street_network_address;
}

int connect_street(int node_start, int node_finnish, char *street_name) {
    unsigned char *node_network = get_char_array_from_file("node_network.bin");
    int current_node_network_address = get_address(node_network, 0);

    for (int i = 0; i < 5; i++) {
        int neighbour = node_start + (i * 6) + 3;
        int current_neighbour = get_address(node_network, neighbour);
        if (current_neighbour == 0) {
            int street_info_index = insert_street_name(street_name);

            write_integer_to_array(node_network, neighbour, node_finnish);
            write_integer_to_array(node_network, neighbour + 3, street_info_index);
            save_char_array_to_file("node_network.bin", node_network, current_node_network_address);
            free(node_network);
            printf("%d added\n", i);
            return 1;
        } else if (current_neighbour == node_finnish) {
            free(node_network);
            printf("%d exist\n", i);
            return 2;
        }
    }
    free(node_network);
    printf("failed\n");
    return FAILED;
}

int get_node_address(int node_index) {
    unsigned char *node_array = get_char_array_from_file("node_array.bin");

    int current_node_array_address = get_address(node_array, 0);
    int address = FAILED;
    if (current_node_array_address == 3) { address = FAILED; }
    else {
        int check = 3;
        do {
            int current_node_index = get_address(node_array, check);
            if (current_node_index == node_index) {
                address = get_address(node_array, check + CHILD_DISTANCE);
                break;
            } else {
                check = get_address(node_array, check + NEXT_DISTANCE);
            }
        } while (check < current_node_array_address);
    }

    free(node_array);
    return address;
}

/*
 * push node asal ke stack 1D, s1
 * push s1 ke stack2D, s2
 * while(!isEmpty(s2))
 * {
 *      pop s2, simpan nilainya di temp stack1D, temp1D
 *      pop temp1D, simpan nilainya ke kandidat
 *
 *      push nilai kandidat ke stack 1D, solution1D
 *
 *      if(!isEmpty(temp1)) {push lagi temp1 ke s2}
 *
 *
 *      if(kandidat == node tujuan)
 *          berhenti
 *      else
 *          if(punya tetangga)
 *             push semua nilainya ke s2
 *          else
 *             pop solution1D
 *
 * }*/
struct Stack1D *search_route(int node_start, int node_finnish) {
    unsigned char *node_network = get_char_array_from_file("node_network.bin");
    struct Stack *stack = createStack(100);
    struct Stack1D *stack1D = createStack1D(100);
    struct Stack1D *solution = createStack1D(100);
    int *visited = calloc((size_t) get_address(node_network, 0), sizeof(int));

    stack1DPush(solution, -1);

    stack1DPush(stack1D, node_start);
    push(stack, stack1D);

    while (!isEmpty(stack)) {
        struct Stack1D *temp = pop(stack);

        int candidate = stack1DPop(temp);

        if (!isStack1DEmpty(temp))
            push(stack, temp);

        stack1DPush(solution, candidate);
        visited[candidate] = 1;
        if (candidate == node_finnish) {
            break;
        } else {
            struct Stack1D *neighbourStack = createStack1D(100);
            for (int i = 0; i < 5; i++) {
                int neighbour = candidate + (i * 6) + 3;
                int current_neighbour = get_address(node_network, neighbour);
                if (current_neighbour > 3 && visited[current_neighbour] != 1) {
                    stack1DPush(neighbourStack, current_neighbour);
                }
            }
            if (!isStack1DEmpty(neighbourStack)) { push(stack, neighbourStack); }
            else { stack1DPop(solution); };
        }
    }
    //free(stack);
    return solution;
}
