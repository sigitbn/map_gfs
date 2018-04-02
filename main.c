#include <stdio.h>
#include "menu.h"

/*
 * * Description:
 * 1. Represent map
 * 2. Search path from location to location
 * 3. Hayat, bisa menghadapi perubahan, agile
 * 4.
 *
 * Coverage:
 * - Mandalajati
 * - Antapani
 * - Arcamanik
 * Problem:
 * How to represent a map
 * Which one should be node
 *
 * * TODO :
 * 1. save lat & long
 * 2. GUI
 * 3. ruas jalan, jalan, simpang
 *
 * Struktur bin array
 * | a *b_1 *c_2 _ | b *c_3 _ _| c *_index _ _ |
 *
 * Struktur representasi map (model pengetahuan)
 * 1. a - b --> dago, 1, macet, lat, long, tol/gang/provinsi, dst
 * 2. a - c --> siliwangi, lancar, dst
 * 3. b - c --> dago, 2, padat, dst
 *
 * a = simpang 1
 * b = simpang 2
 * c = simpang 3
 * 1 = index ruas jalan
 *
 */
 // cepat, akurat, hemat, kuat, hayat,

int main() {

    char option;
    do {
        printf("Pilih menu:\n"
                       "1. Tambah jalan\n"
                       "2. Sambungkan jalan\n"
                       "3. Tampilkan jalan\n"
                       "4. Cari rute\n"
                       "0. Keluar\n");

        scanf("\n%c", &option);
        switch (option) {
            case '1':
                menu_add_node();
                break;

            case '2':
                menu_connect_node();
                break;

            case '3':
                menu_show_street();
                break;

            case '4':
                menu_search_route();
                break;

            case '0':
                break;

            default:
                printf("Menu tidak tersedia. Masukkan angka dengan benar\n");
                break;

        }

    } while (option != '0');
    return 0;
}