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
const unsigned int INT_MASK = 0xFFFFFFFF;
const int INT_MAX = 0x8FFFFFFF;
const int CHAR_BITS_COUNT = 8;
// Container for route connecting two cities DIRECTLY.
typedef int AdjacencyMatrix[MAX_CITY_COUNT + 1][MAX_CITY_COUNT + 1];

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
    int bit_position = value & (INT_MASK >> (32 - CHAR_BITS_COUNT));
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
    int bit_position = value & (INT_MASK >> (32 - CHAR_BITS_COUNT));
    if (value / CHAR_BITS_COUNT >= set.size)
	return -1;

    // printf("set_has(%d) %x, %x, %x\n", value, byte_position, bit_position, set.bit_array[byte_position] & (1 << bit_position));
    return !!(set.bit_array[byte_position] & (1 << bit_position));
}

void set_free(IntSet set) {
    free(set.bit_array);
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

typedef struct LinkedNode {
    int value;
    struct LinkedNode *next;
} LinkedNode;

/*
 *
 * 2. Dijkstra.
 *
 */
int max_timespan(int timespans[], count) {
    int max = 0;
    for (int i = 1; i <= count; ++city)
	max = timespans[i] > max ? timespans[i] : max;
    return max;
}

// Apply dijkstra algo to all cities.
int minimum_timespan_to_farthest_city(AdjacencyMatrix matrix, size_t cities_count) {
    const int capital_city = 1;

    int min_timespans[MAX_CITY_COUNT + 1];
    memset(min_timespans, 0xFF, MAX_CITY_COUNT + 1);

    min_timespans[1] = 0;

    LinkedNode *cities_visited_head = malloc(sizeof(LinkedNode));
    cities_visited_head->value = capital_city;
    cities_visited_head->next = NULL;
    LinkedNode *cities_visited_tail = cities_visited_head;

    LinkedNode *cities_to_visit_head = malloc(sizeof(LinkedNode));
    cities_to_visit_head->value = 0;
    cities_to_visit_head->next = NULL;

    LinkedNode *current_city_node = cities_to_visit_head;
    for (int city = 2; city <= cities_count; ++city) {
	LinkedNode *new_node = malloc(sizeof(LinkedNode));
	new_node->value = city;
	new_node->next = NULL;
	current_city_node->next = new_node;
	current_city_node = new_node;
    }

    while (1) {
	struct MinTimespan {
	    int city; int timespan; LinkedNode *prev;
	} min_timespan_this_loop = {0, INT_MAX, NULL};

	current_city_node = &cities_visited_head;

	while (current_city_node != NULL) {
	    int current_city = visited_city_node->value;
	    LinkedNode *city_to_visit_node = cities_to_visit_head->next;
	    if (city_to_visit_node == NULL) // All the cities are visited, exit.
		return max_timespan(min_timespans, cities_count);

	    LinkedNode *prev_city_to_visit_node = cities_to_visit_head;
	    while (city_to_visit_node != NULL) {
		int city_to_visit = city_to_visit_node->value;
		int timespan = matrix[current_city][city_to_visit] + min_timespans[current_city];
		if (timespan < min_timespan_this_loop.timespan) {
		    min_timespan_this_loop.city = city_to_visit;
		    min_timespan_this_loop.timespan = timespan;
		    min_timespan_this_loop.prev = prev_city_to_visit_node;
		}
		prev_city_to_visit_node = city_to_visit_node;
		city_to_visit_node = city_to_visit_node->next;
	    }

	    current_city_node = current_city_node->next;
	}

	min_timespans[min_timespan_this_loop.city] = min_timespan_this_loop.timespan;
	cities_visited_tail->next = min_timespan_this_loop.prev->next;
	cities_visited_tail = cities_visited_tail->next;
	min_timespan_this_loop.prev->next = min_timespan_this_loop->next->next;
    }
    return -1;
}

#ifndef UNIT_TEST

int main(int argc, char* argv[]) {

}

#endif
