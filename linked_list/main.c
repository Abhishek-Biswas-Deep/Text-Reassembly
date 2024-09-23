#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "linked_list.h"

static void clean_list(linked_list_t *list) {
    for (ll_node_t *n = list->head; n; n = n->next) {
        free(n->item);
    }
}

static int compare(void *s1, void *s2) {
    return strcmp(s1, s2);
}


int main() {
    unsigned int num_lists;
    int rc = scanf("%u", &num_lists);
    assert(rc == 1);

    linked_list_t **lists = calloc(num_lists, sizeof(linked_list_t *));
    assert(lists);

    char buffer[100];
    ll_node_t *curr = NULL;
    unsigned int overlap = 0;

    while (scanf("%s", buffer) == 1 && !strcmp(buffer, "list")) {
        unsigned int list_idx;
        rc = scanf("%u", &list_idx);
        assert(rc == 1);
        assert(list_idx < num_lists);
        linked_list_t *list = lists[list_idx];
        printf("List %u: ", list_idx);

        rc = scanf("%s", buffer);
        assert(rc == 1);

        if (!strcmp(buffer, "new")) {
            if (list) {
                clean_list(list);
                ll_destroy(list);
            }
            list = ll_new();
            assert(list);
            lists[list_idx] = list;
            printf( "new list\n");
        } else if (!strcmp(buffer, "append")) {
            assert(list);
            scanf("%s", buffer);
            char * string = strdup(buffer);
            int success = ll_add_back(list, string);
            if (!success) {
                printf("Failed to append \"%s\" to list\n", string);
                free(string);
            }
        } else if (!strcmp(buffer, "prepend")) {
            assert(list);
            scanf("%s", buffer);
            char * string = strdup(buffer);
            int success = ll_add_front(list, string);
            if (!success) {
                printf("Failed to prepend \"%s\" to list\n", string);
                free(string);
            }
        } else if (!strcmp(buffer, "front")) {
            assert(list);
            char *string = ll_get_front(list);
            if (!string) {
                printf("Failed to get front of list\n");
            } else {
                printf("'%s' is at front of list\n", string);
            }
        } else if (!strcmp(buffer, "back")) {
            assert(list);
            char *string = ll_get_back(list);
            if (!string) {
                printf("Failed to get back of list\n");
            } else {
                printf("'%s' is at back of list\n", string);
            }
        } else if (!strcmp(buffer, "remove_front")) {
            assert(list);
            char *string = ll_remove_front(list);
            if (!string) {
                printf("Failed to remove from front of list\n");
            } else {
                free(string);
            }
        } else if (!strcmp(buffer, "remove_back")) {
            assert(list);
            char *string = ll_remove_back(list);
            if (!string) {
                printf("Failed to remove from back of list\n");
            } else {
                free(string);
            }
        } else if (!strcmp(buffer, "destroy")) {
            for (ll_node_t *n = list->head; n; n = n->next) {
                free(n->item);
            }
            ll_destroy(list);
            list = NULL;
            lists[list_idx] = list;
        } else if (!strcmp(buffer, "size")) {
            printf("List has %d items\n", ll_size(list));
            continue;
        } else if (!strcmp(buffer, "empty")) {
            if (ll_is_empty(list)) {
                printf("List is empty\n");
            } else {
                printf("List is not empty\n");
            }
        } else if (!strcmp(buffer, "find")) {
            curr = NULL;
            scanf("%s", buffer);
            for (ll_node_t *n = list->head; n; n = n->next) {
                if(!strcmp(buffer, n->item)) {
                    curr = n;
                    break;
                }
            }

            if (!curr) {
                printf("'%s' not found in list\n", buffer);
            } else {
                printf("'%s' found in list\n", buffer);
            }
        } else if (!strcmp(buffer, "insert")) {
            scanf("%s", buffer);
            if (curr) {
                char *string = strdup(buffer);
                int success = ll_insert(list, curr, string);
                if (!success) {
                    printf("Failed to insert '%s' after '%s' in list", string,
                           (char *)curr->item);
                    free(string);
                }
            } else {
                printf("No node to insert after.\n");
            }
        } else if (!strcmp(buffer, "remove")) {
            if (curr) {
                char *string = ll_remove(list, curr);
                if (!string) {
                    printf("Failed to remove '%s' in list", (char *)curr->item);
                } else {
                    free(string);
                }
            } else {
                printf("No node to remove.\n");
            }
        } else if (!strcmp(buffer, "build")) {
            assert(list);
            int list_size;

            rc = scanf("%u", &list_size);
            assert(rc == 1);

            for (int i = 0; i < list_size; i++) {
                rc = scanf("%s", buffer);
                assert(rc == 1);
                char * string = strdup(buffer);
                assert(string);
                int success = ll_add_back(list, string);
                if (!success) {
                    printf("Failed to append \"%s\" to list\n", string);
                    free(string);
                }
            }
            printf("build\n");
        } else if (!strcmp(buffer, "overlap")) {
            unsigned int list2;
            rc = scanf("%u", &list2);
            assert(rc == 1);
            assert(list2 < num_lists);
            overlap = ll_overlap(list, lists[list2], &compare);
            printf("Overlap between lists %u and %u is %u\n", list_idx, list2, overlap);
            continue;
        } else if (!strcmp(buffer, "splice")) {
            unsigned int list2;
            rc = scanf("%u", &list2);
            assert(rc == 1);
            assert(list2 < num_lists);
            ll_splice(list, lists[list2], overlap);
            printf("List %u spliced to the end of list %u\n", list2, list_idx);
        } else if (!strcmp(buffer, "print")) {
            printf("print\n");
        } else {
            break;
        }

        if (list) {
            printf(" [");
            for (ll_node_t *n = list->head; n; n = n->next) {
                printf(" %s", (char *)n->item);
            }
            printf(" ] (%d items)\n", ll_size(list));
        } else {
            printf("No list!\n");
        }
    }

    free(lists);
    return 0;
}
