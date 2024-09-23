#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "linked_list.h"

#define EOT "EOS"

static int compare(void *s1, void *s2) {
    return strcmp(s1, s2);
}

static void print_seg(linked_list_t *list) {
    for (ll_node_t *node = list->head; node; node = node->next) {
        printf("%s ", (char *)node->item);
    }
    printf("\n");
}


int main() {
    linked_list_t *segments = ll_new();
    char buffer[20];

    for(int rc = scanf("%s", buffer); rc == 1 && strcmp(buffer, EOT) != 0; rc = scanf("%s", buffer)) {
        linked_list_t *seg = ll_new();
        ll_add_back(segments, seg);
        for ( ; rc == 1 && strcmp(buffer, EOT) != 0; rc = scanf("%s", buffer)) {
            char *word = strdup(buffer);
            assert(word);
            ll_add_back(seg, word);
        }
    }

    linked_list_t *text = ll_remove_front(segments);
    if (!text) {
        return 0;
    }

    while (!ll_is_empty(segments)) {
        unsigned int max_overlay = 0;
        ll_node_t *max_node = NULL;
        int direction = 0;

        for (ll_node_t *node = segments->head; node; node = node->next) {
            unsigned int overlay = ll_overlap(text, node->item, compare);
            if (overlay > max_overlay) {
                max_overlay = overlay;
                max_node = node;
                direction = 0;
            }
            overlay = ll_overlap(node->item, text, compare);
            if (overlay > max_overlay) {
                max_overlay = overlay;
                max_node = node;
                direction = 1;
            }
        }

        if (!max_overlay) {
            printf("OOPS:\n");
            for (ll_node_t *seg = segments->head; seg; seg = seg->next) {
                print_seg(seg->item);
            }
            return 1;
        }

        linked_list_t * seg = ll_remove(segments, max_node);
        if (direction) {
            linked_list_t *tmp = seg;
            seg = text;
            text = tmp;
        }

        ll_splice(text, seg, max_overlay);

        for (char * word = ll_remove_front(seg); word; word = ll_remove_front(seg)) {
            free(word);
        }
        ll_destroy(seg);
    }

    unsigned int line = 0;
    for (char * word = ll_remove_front(text); word; word = ll_remove_front(text)) {
        line += strlen(word) + 1;
        printf("%s ", word);
        if (line > 30) {
            line = 0;
            printf("\n");
        }
        free(word);
    }

    if (line) {
        printf("\n");
    }

    ll_destroy(text);

    return 0;
}