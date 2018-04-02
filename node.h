// Save name of the street and pointer address
// Used when search pointer address given name
// Created by sigitbn on 3/25/18.
//

#ifndef MAP_GFS_NODE_LIST_H
#define MAP_GFS_NODE_LIST_H

/*
 * Buat jalan
 * Tambah jalan
 *
 *
 */

int add_node(int node_index);

int connect_street(int node_start, int node_finnish, char* street_name);

int get_node_address(int node_index);

struct Stack1D * search_route(int node_start, int node_finnish);


#endif //MAP_GFS_NODE_LIST_H
