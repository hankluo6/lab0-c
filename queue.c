#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    char *news = malloc(strlen(s) * sizeof(char) + 1);
    if (!q || !newh || !news) {
        free(newh);
        free(news);
        return false;
    }
    strncpy(news, s, strlen(s) + 1);
    newh->value = news;
    newh->next = q->head;
    q->head = newh;
    if (!q->tail)
        q->tail = newh;
    ++q->size;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    char *news = malloc(strlen(s) * sizeof(char) + 1);
    if (!q || !newh || !news) {
        free(newh);
        free(news);
        return false;
    }
    strncpy(news, s, strlen(s) + 1);
    newh->value = news;
    newh->next = NULL;
    if (q->tail)
        q->tail->next = newh;
    else
        q->head = newh;
    q->tail = newh;
    ++q->size;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head)
        return false;
    list_ele_t *del = q->head;
    q->head = q->head->next;
    if (sp) {
        strncpy(sp, del->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
    free(del->value);
    free(del);
    --q->size;
    if (!q->size)
        q->tail = NULL;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q ? q->size : 0;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || q->size < 2) {
        return;
    }
    list_ele_t *rear = q->head->next->next;
    q->tail->next = q->head;

    while (q->head->next != q->tail) {
        q->head->next->next = q->tail->next;
        q->tail->next = q->head->next;
        q->head->next = rear;
        rear = rear->next;
    }
    q->tail = q->head;
    q->head = q->head->next;
    q->tail->next = NULL;
}

void merge_sort(list_ele_t **head)
{
    if (!(*head) || !(*head)->next)
        return;
    list_ele_t *fast = (*head)->next;
    list_ele_t *slow = *head;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    fast = slow->next;
    slow->next = NULL;

    list_ele_t **front = head;
    list_ele_t **back = &fast;

    merge_sort(front);
    merge_sort(back);

    list_ele_t *newh = NULL;
    list_ele_t **tmp = &newh;
    while (*front && *back) {
        if (strcmp((*front)->value, (*back)->value) < 0) {
            *tmp = *front;
            *front = (*front)->next;
        } else {
            *tmp = *back;
            *back = (*back)->next;
        }
        tmp = &((*tmp)->next);
    }
    if (*front)
        *tmp = *front;
    else if (*back)
        *tmp = *back;
    *head = newh;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q || q->size < 2)
        return;
    merge_sort(&q->head);
    list_ele_t *tmp = q->tail;
    while (tmp->next)
        tmp = tmp->next;
    q->tail = tmp;
}
