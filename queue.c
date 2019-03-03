/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"
#define min(a, b) (((a) < (b)) ? (a) : (b))

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q) {
        return NULL;
    }
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}


/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;

    if (!q->head) {
        free(q);
        return;
    }

    while (q->head) {
        list_ele_t *remove_ele = q->head;
        q->head = q->head->next;
        free(remove_ele->value);
        free(remove_ele);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    size_t size;
    if (!q)
        return false;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!newh)
        return false;
    size = (size_t) strlen(s) + 1;
    newh->value = (char *) malloc(size);
    if (!newh->value) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    if (!q->head) {
        newh->next = NULL;
        q->head = newh;
        q->tail = newh;
    } else {
        newh->next = q->head;
        q->head = newh;
    }
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh;
    size_t size;
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    size = (size_t) strlen(s) + 1;
    newh->value = (char *) malloc(size);
    if (!newh->value) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    newh->next = NULL;
    if (!q->head) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = newh;
    }
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/

bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head)
        return false;
    list_ele_t *head = q->head;
    if (sp && head->value) {
        size_t len = min(strlen(head->value), bufsize - 1);
        memcpy(sp, head->value, len);
        sp[len] = '\0';
    }
    q->head = q->head->next;
    free(head->value);
    free(head);
    q->size--;
    return true;
}

/*
  Return number of elements in queueㄎ
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q && q->head) {
        list_ele_t *pre = q->head;
        list_ele_t *current = q->head->next;
        list_ele_t *next;
        list_ele_t *temp;
        while (current) {
            next = current->next;
            current->next = pre;
            pre = current;
            current = next;
        }
        q->head->next = NULL;
        temp = q->head;
        q->head = q->tail;
        q->tail = temp;
    }
    /* You need to write the code for this function */
}

void print_list(list_ele_t *head)
{
    while (head) {
        printf("%s ", head->value);
        head = head->next;
    }
    printf("\n");
}
/**
 * get_mid - get mid element of link list
 * @head: pointer to queue first element
 *
 * @Return: pointer to mid of link list
 */
list_ele_t *get_mid(list_ele_t *head)
{
    int i = 0;
    list_ele_t *des = head;
    while (head) {
        head = head->next;
        i++;
    }
    for (int j = 0; j < i / 2 - 1; j++)
        des = des->next;
    return des;
}
/**
 * insert_tail - insert node_2 in tail of node_1
 * @node_1: pointer element
 * @node_1: pointer element
 *
 */
void insert_tail(list_ele_t *node_1, list_ele_t *node_2)
{
    if (node_1 && node_2) {
        list_ele_t *temp = node_1->next;
        node_1->next = node_2;
        node_2->next = temp;
    }
}
/**
 * sort_merge - merge two sorted link list
 * @head1: pointer to first sorted link list
 * @head2: pointer to second sorted link list
 *
 * @Return: pointer to merged link list head
 */
list_ele_t *sort_merge(list_ele_t *head1, list_ele_t *head2)
{
    if (head1 && head2) {
        if (*(head1->value) > *(head2->value)) {
            list_ele_t *tmp = head2;
            head2 = head1;
            head1 = tmp;
        }
    } else {
        return head1 ? head1 : head2;
    }
    list_ele_t *org_head = head1;
    while (head2) {
        if (head1) {
            if (head1->next == NULL) {
                head1->next = head2;
                break;
            } else if (*(head1->value) < *(head2->value) &&
                       *(head1->next->value) > *(head2->value)) {
                list_ele_t *item = head2;
                head2 = head2->next;
                insert_tail(head1, item);
            } else {
                head1 = head1->next;
            }
        }
    }
    return org_head;
}
/**
 * spice_half - cut link list into half
 * @head: pointer to queue first element
 *
 * @Return: half of remaining link list
 * e.g. a->b->c->d splice into a->b,c->d and return pointer to c
 */
list_ele_t *spice_half(list_ele_t *head)
{
    if (head) {
        list_ele_t *mid = get_mid(head);
        list_ele_t *next_start = mid->next;
        mid->next = NULL;
        return next_start;
    } else
        return head;
}
/**
 * merge_sort - using merge sort to sort queue
 * @head: pointer to queue first element
 *
 * queue element must be a single char
 * @Return :pointer to sorted link list head;
 */
list_ele_t *merge_sort(list_ele_t *head)
{
    if (head && head->next) {
        list_ele_t *mid = spice_half(head);
        head = merge_sort(head);
        mid = merge_sort(mid);
        list_ele_t *result = sort_merge(head, mid);
        return result;
    } else {
        return head;
    }
}

void my_merge_sort(queue_t *q)
{
    q->head = merge_sort(q->head);
}