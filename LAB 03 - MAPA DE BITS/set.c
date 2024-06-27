#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "set.h"

#define MAX_MEMBERS 32

struct set {
    int n;
    unsigned int members;
};

static int set_member_valid(int i) {
    if ((i < 0) || (i >= MAX_MEMBERS)) return 0;
    return 1;
}

Set* set_create(void) {
    Set* set;
    set = (Set*)malloc(sizeof(Set));
    if (set != NULL) {
        set->n = MAX_MEMBERS;
        set->members = 0;
    }
    return set;
}

void set_destroy(Set* set) {
    if (set) free(set);
}

void set_show(char* title, Set* set) {
    int i, first = 1;
    printf("%s = {", title);
    for (i = 0; i < MAX_MEMBERS; i++) {
        if (set_is_member(set, i)) {
            if (first) {
                printf("%d", i);
                first = 0;
            }
            else
                printf(",%d", i);
        }
    }
    printf("}\n\n");
}

void set_insert(Set* set, int i) {
    if (set == NULL || !set_member_valid(i)) return;
    set->members |= (1u << i);
}

void set_remove(Set* set, int i) {
    if (set == NULL || !set_member_valid(i)) return;
    set->members &= ~(1u << i);
}

Set* set_copy(Set* set) {
    Set* new_set = set_create();
    if (new_set != NULL && set != NULL) {
        new_set->members = set->members;
    }
    return new_set;
}

Set* set_union(Set* set1, Set* set2) {
    Set* union_set = set_create();
    if (union_set != NULL) {
        union_set->members = set1->members | set2->members;
    }
    return union_set;
}

Set* set_intersection(Set* set1, Set* set2) {
    Set* intersection_set = set_create();
    if (intersection_set != NULL) {
        intersection_set->members = set1->members & set2->members;
    }
    return intersection_set;
}

Set* set_difference(Set* set1, Set* set2) {
    Set* difference_set = set_create();
    if (difference_set != NULL) {
        difference_set->members = set1->members & ~(set2->members);
    }
    return difference_set;
}

int set_is_member(Set* set, int i) {
    if (set == NULL || !set_member_valid(i)) return 0;
    return ((set->members >> i) & 1);
}

int set_is_subset(Set* set1, Set* set2) {
    if (set1 == NULL || set2 == NULL) return 0;
    return (set1->members & set2->members) == set2->members;
}

int set_is_equal(Set* set1, Set* set2) {
    if (set1 == NULL || set2 == NULL) return 0;
    return set1->members == set2->members;
}

int set_number_of_elements(Set* set) {
    int count = 0;
    if (set == NULL) return 0;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (set_is_member(set, i)) count++;
    }
    return count;
}

Set* set_complement(Set* set) {
    Set* complement_set = set_create();
    if (complement_set != NULL) {
        complement_set->members = ~(set->members);
    }
    return complement_set;
}
