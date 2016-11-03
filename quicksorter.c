#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linked_list.h"
#include "memcheck.h"


/* Given a pointer to a list of numbers. This function calculates the sorted
 * list and return the sorted list without altering the original list. */
node *quicksort(node *list) {
    node *sorted;
    node *first_n;
    node *smaller;
    node *larger;
    node *temp;
    node *temp2;
    node *larger_sorted;
    node *smaller_sorted;

    smaller = NULL;
    larger = NULL;

    if (list == NULL || list->next == NULL) {
        /* if zero or no node */
        sorted = copy_list(list);
        return sorted;
    }

    else {
        first_n = (node *)malloc(sizeof(node)); /* copy first node */
        first_n->data = list->data;
        first_n->next = NULL;

        for (temp = list->next; temp != NULL; temp = temp->next) {
            /* run to the end of list */
            if (temp->data < first_n->data) {
                /* compare the points and add to appropriate lists */
                smaller = create_node(temp->data, smaller);
            }
            else {
                larger = create_node(temp->data, larger);
            }
        }
        /* recursion */
        larger_sorted = quicksort(larger); 
        smaller_sorted = quicksort(smaller);

        free_list(larger);
        free_list (smaller);


        sorted = append_lists(smaller_sorted, first_n);

        temp2 = append_lists(sorted, larger_sorted);

        free_list(sorted);
        free_list(smaller_sorted);
        free_list(first_n);
        free_list(larger_sorted);

        sorted = temp2;

        assert(is_sorted(sorted) == 1);

        return sorted;
    }
}

/* This is the main function. Given the list of numbers as the command line
 * argument. It prints (unless the option -q is used) the sorted list. */
int main(int argc, char *argv[]) {
    int i;
    int q = 0; /* if there is the optional q. 1 = yes, 0 = no */
    node *list; /* pointer to the list */
    node *sorted; /* pointer to sorted list */
    node *temp;

    if (argc < 2) { /* check usage error */
        fprintf(stderr, "usage: %s [-b] number1 [number2...]\n", \
                 argv[0]);
        exit(1);
    }

    list = NULL; /* creating list from the back */
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i],"-q") == 0) {
            /* if it is optional - q */
            q = 1;
        }
        else {
            list = create_node(atoi(argv[i]), list); /* appending nodes */
        }
    }
    /* reversing the list */
    temp = reverse_list(list); 
    free_list(list);
    list = temp;

    /* begin sorting */

    sorted = quicksort(list);
    free_list(list);
    list = sorted;

    if (q != 1) {
        print_list(list);
    }

    free_list(list);
    print_memory_leaks();
    return 0;
}
