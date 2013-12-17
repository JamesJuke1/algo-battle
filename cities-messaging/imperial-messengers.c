/*
Author: Zhou Chong
Email: xorcererzc@gmail.com

Problem: Imperial Messengers


Sections:

1. Base data structure.
2. Dijkstra.
3. Input handling.

*/

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


/*
 *
 * 1. Base Data Structures.
 *
 */
const int MAX_CITY_COUNT = 100;

const int CHAR_BITS_COUNT = 8;
// Container for route connecting two cities DIRECTLY.
typedef int AdjacencyMatrix[5][5];

// Set, actually a bit array for integers.
// CPU is fast enough for a small array.
typedef struct IntSet {
    char *bit_array;
    size_t size;
} IntSet;

// Return 0 for success, otherwise failure.
int set_init(IntSet* set, int max_int_value) {
    set->size = max_int_value / CHAR_BITS_COUNT + 1;
    set->bit_array = malloc(sizeof(char) * set->size);

    if (set->bit_array == 0)
	return -1;

    memset(set->bit_array, 0, set->size);
    return 0;
}

// Return 0 for added, otherwise failure or already existed.
int set_add(IntSet set, int value) {
    int byte_position = value >> CHAR_BITS_COUNT;
    int bit_position = value & (0xFFFFFFFF >> (32 - CHAR_BITS_COUNT));
    if (value / CHAR_BITS_COUNT >= set.size)
	return -1;

    // printf("set_add(%d) %x, %x, %x\n", value, byte_position, bit_position, set.bit_array[byte_position] & (1 << bit_position));
    int has_value = set.bit_array[byte_position] & (1 << bit_position);
    set.bit_array[byte_position] |= 1 << bit_position;
    return !!has_value;
}

// Return 1 for yes, 0 for no, otherwise error.
int set_has(IntSet set, int value) {
    int byte_position = value >> CHAR_BITS_COUNT;
    int bit_position = value & (0xFFFFFFFF >> (32 - CHAR_BITS_COUNT));
    if (value / CHAR_BITS_COUNT >= set.size)
	return -1;

    // printf("set_has(%d) %x, %x, %x\n", value, byte_position, bit_position, set.bit_array[byte_position] & (1 << bit_position));
    return !!(set.bit_array[byte_position] & (1 << bit_position));
}

#ifdef UNIT_TEST

int main(int argc, char* argv[]) {
    IntSet set;
    assert(set_init(&set, 100) == 0);
    assert(set_add(set, 1) == 0);
    assert(set_add(set, 2) == 0);
    assert(set_add(set, 100) == 0);

    // Added again;
    assert(set_add(set, 100) > 0);

    assert(set_has(set, 1) == 1);
    assert(set_has(set, 2) == 1);
    assert(set_has(set, 3) == 0);

    assert(set_has(set, 100) == 1);
    assert(set_has(set, 99) == 0);

    assert(set_has(set, 55) == 0);
    return 0;
}

#endif

/*
 *
 * 2. Dijkstra.
 *
 */


// dijkstra algo to all cities.
int minimum_time_to_farthest_city(AdjacencyMatrix matrix, size_t cities_count) {
    int min_times[MAX_CITY_COUNT];
    IntSet cities_visited;
    set_init(&cities_visited, cities_count);


    return 0;
}

#ifndef UNIT_TEST

int main(int argc, char* argv[]) {


}

#endif
