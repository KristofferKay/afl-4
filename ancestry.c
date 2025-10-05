#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ancestry.h"

struct person_t *make_person(char *first_name, char *last_name, int year_born) {
    // TODO: Allokér plads til en `struct person_t`.
    struct person_t *person = malloc(sizeof(struct person_t));

    // TODO: Allokér også plads til kopier af `first_name` og `last_name`.
    person->first_name = malloc(strlen(first_name) +1 );
    person->last_name = malloc(strlen(last_name) +1 );

    // TODO: Kopiér indholdet fra `first_name` og `last_name` over i kopierne.
    strcpy(person->first_name,first_name);
    strcpy(person->last_name,last_name);

    person->year_born = year_born;
    // TODO: Husk at gøre plads til både alle tegnene i navnene + 1 NUL-byte.

    return person;
}

void free_person(struct person_t *person) {
    // TODO: Der skal være et free()-kald for hver malloc() i make_person().
    free(person->first_name);
    free(person->last_name);
    // TODO: Du må gerne sætte `first_name` og `last_name` til NULL *EFTER* de er free()'et.
    person->first_name = NULL;
    person->last_name = NULL;

    free(person);
}

struct ancestry_node_t *make_tree(struct person_t *person) {
    // TODO: Allokér plads til en `struct ancestry_node_t`.
    struct ancestry_node_t *ancestry_node = malloc(sizeof(struct ancestry_node_t));
    // TODO: Sæt `person` til input-personen.
    ancestry_node->person = person;

    // TODO: Sæt `mom` og `dad` til NULL.
    ancestry_node->dad = NULL;
    ancestry_node->mom = NULL;

    return ancestry_node;
}

bool add_mom(struct ancestry_node_t *child_node, struct person_t *mom_person) {
    // TODO: Hvis der allerede er en mor-stamtavle, skal funktionen fejle.
    if (child_node == NULL || mom_person == NULL) {
        return true;
    }

    if (child_node->mom != NULL) {
        return true;
    }
    // TODO: Hvis ikke, skal `mom_person` indsættes i en `mom_node` som først skal allokeres.
    struct ancestry_node_t *mom_node = malloc(sizeof(struct ancestry_node_t));
    mom_node->person = mom_person;
    child_node->mom = mom_node;

    return mom_node;
}

bool add_dad(struct ancestry_node_t *child_node, struct person_t *dad_person) {
    // TODO: Hvis der allerede er en far-stamtavle, skal funktionen fejle.
    if (child_node == NULL || dad_person == NULL) {
        return true;
    }

    // TODO: Hvis ikke, skal `dad_person` indsættes i en `dad_node` som først skal allokeres.
    struct ancestry_node_t *dad_node = malloc(sizeof(struct ancestry_node_t));
    dad_node->person = dad_person;
    child_node->dad = dad_node;

    return dad_node;
}

void free_tree(struct ancestry_node_t *node) {
    // TODO: Kald `free_person()` på personen i noden.
    // TODO: Kald `free_tree()` på begge forældre-stamtræer.
    // TODO: Sæt pointerne til NULL efter de er free()'et.
    if (node == NULL) {
        return;
    }
    free_person(node->person);
    free_tree(node->mom);
    free_tree(node->dad);
    node->dad = NULL;
    node->mom = NULL;

    free(node);
}

void print_tree_recursive(struct ancestry_node_t *node, char *prefix, bool is_last) {
    if (node == NULL) {
        return;
    }

    printf("%s", prefix);
    printf("%s", is_last ? "└── " : "├── ");
    printf("%s %s\n", node->person->first_name, node->person->last_name);

    char new_prefix[1000];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

    if (node->mom != NULL && node->dad != NULL) {
        print_tree_recursive(node->mom, new_prefix, false);
        print_tree_recursive(node->dad, new_prefix, true);
    } else if (node->mom != NULL) {
        print_tree_recursive(node->mom, new_prefix, true);
    } else if (node->dad != NULL) {
        print_tree_recursive(node->dad, new_prefix, true);
    }
}

void print_tree(struct ancestry_node_t *node) {
    print_tree_recursive(node, "", true);
}
