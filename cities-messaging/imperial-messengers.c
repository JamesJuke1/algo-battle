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
const int INT_MAX = 0x7FFFFFFF;
const int UNREACHABLE = INT_MAX;
const int CHAR_BITS_COUNT = 8;
// Container for route connecting two cities DIRECTLY.
typedef int AdjacencyMatrix[MAX_CITY_COUNT + 1][MAX_CITY_COUNT + 1];

typedef struct LinkedNode {
    int value;
    struct LinkedNode *next;
} LinkedNode;

void free_linkednode(LinkedNode *head) {
    while(head) {
	LinkedNode *p = head->next;
	free(head);
	head = p;
    }
}

/*
 *
 * 2. Dijkstra.
 *
 */
int max_timespan(int timespans[], int count) {
    int max = 0;
    for (int i = 1; i <= count; ++i)
	max = timespans[i] > max ? timespans[i] : max;
    return max;
}

// Apply dijkstra algo to all cities.
int minimum_timespan_to_farthest_city(AdjacencyMatrix matrix, size_t cities_count) {
    const int capital_city = 1;

    // Mininal timespan from capital to cities.
    int min_timespans[MAX_CITY_COUNT + 1];
    memset(min_timespans, 0xFF, MAX_CITY_COUNT + 1);

    min_timespans[1] = 0;

    // Visited cities, whose min_timespan is known.
    LinkedNode *cities_visited_head = malloc(sizeof(LinkedNode));
    cities_visited_head->value = capital_city;
    cities_visited_head->next = NULL;
    LinkedNode *cities_visited_tail = cities_visited_head;

    // unvisited cities.
    LinkedNode *cities_to_visit_head = malloc(sizeof(LinkedNode));
    cities_to_visit_head->value = 0;
    cities_to_visit_head->next = NULL;

    // All cities except capital are unvisited at beginning.
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

	current_city_node = cities_visited_head;

	// Loop all unvisited cities, select the most nearest one into cities_visited list.
	while (current_city_node != NULL) {
	    const int current_city = current_city_node->value;
	    LinkedNode *city_to_visit_node = cities_to_visit_head->next;

	    // All the cities are visited, exit.
	    if (city_to_visit_node == NULL)
	    {
		int r = max_timespan(min_timespans, cities_count);

		// Cleanup resources.
		free_linkednode(cities_visited_head);
		free_linkednode(cities_to_visit_head);
		return r;
	    }

	    // Loop all nearby cities of current city, update their min_timespans.
	    LinkedNode *prev_city_to_visit_node = cities_to_visit_head;
	    while (city_to_visit_node != NULL) {
		const int city_to_visit = city_to_visit_node->value;

		// Unreachable, then skip
		if (matrix[current_city][city_to_visit] == UNREACHABLE) {
		    prev_city_to_visit_node = city_to_visit_node;
		    city_to_visit_node = city_to_visit_node->next;
		    continue;
		}

		int timespan = matrix[current_city][city_to_visit] + min_timespans[current_city];

		// Update min_timespan_this_loop if required.
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

	// Moved selected city node from "to_visit" list to "visited" list.
	cities_visited_tail->next = min_timespan_this_loop.prev->next;
	cities_visited_tail = cities_visited_tail->next;
	cities_visited_tail->next = NULL;

	min_timespan_this_loop.prev->next = min_timespan_this_loop.prev->next->next;
    }

    // Cleanup resources.
    free_linkednode(cities_visited_head);
    free_linkednode(cities_to_visit_head);
    return UNREACHABLE;
}

int read_int() {
    char input[30];
    int number;
    for (int i = 0; i < sizeof(input) - 1; i++)
    {
	char c = (char)getc(stdin);
	if (c == 'x' || c == 'X')
	    return UNREACHABLE;

	if (c < '0' || '9' < c)
	{
	    if (i == 0) continue;
	    input[i] = 0;
	    return atoi(input);
	}
	input[i] = c;
    }

    input[29] = 0;
    return atoi(input);
}

int main(int argc, char* argv[]) {
    int cities_count = read_int();

    AdjacencyMatrix matrix;

    // Input adjacency matrix.
    for (int source_city = 2; source_city <= cities_count; ++source_city) {
	for (int dest_city = 1; dest_city < source_city; ++dest_city) {
	    int timespan = read_int();
	    matrix[source_city][dest_city] = timespan;
	    matrix[dest_city][source_city] = timespan;
	}
    }

    int min_timespan = minimum_timespan_to_farthest_city(matrix, cities_count);

    printf("%d\n", min_timespan);
}
