/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(!q) {
      return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->cnt = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if(!q) {
      return;
    }
    /* How about freeing the list elements? */
    list_ele_t *next;
    for(list_ele_t *ele = q->head; ele; ele = next) {
      next = ele->next;
      free(ele);
    }
    
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if(!q) {
      return false;
    }
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    /* What if malloc returned NULL? */
    if (!newh) {
      return false;
    }
    newh->value = v;
    newh->next = q->head;

    // newh is the very first element
    if(!q->head) {
      q->tail = newh;
    }
    q->head = newh;
    q->cnt++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q) {
      return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
      return false;
    }
    newh->value = v;
    newh->next = NULL;
    
    q->tail->next = newh;
    q->tail = newh;
    q->cnt++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    /* You need to fix up this code. */
    if (!q || !q->head) {
      return false;
    }
    list_ele_t *ele = q->head;
    q->head = q->head->next;
    if (vp) {
      *vp = ele->value;
    }
    free(ele);
    q->cnt--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q && q->head ? q->cnt : 0;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (!q || !q->head) {
      return;
    }
    list_ele_t *cur = q->head;
    list_ele_t *next = q->head->next;
    list_ele_t *new_next;
    for(; next; cur = next, next = new_next) {
      new_next = next->next;
      next->next = cur;
    }
    q->head->next = NULL;
    q->tail = q->head;
    q->head = cur;
}

