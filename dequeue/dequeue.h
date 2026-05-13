
#ifndef DEQUEUE_H
#define DEQUEUE_H

typedef struct Dequeue_t Dequeue_t;

void Dequeue_Reset(struct Dequeue_t *dequeue);

struct DequeueNode_t *DequeueNode_MallocNode(void *stored);

void Dequeue_PushBack(struct Dequeue_t *dequeue, void *data);

void Dequeue_PushFront(struct Dequeue_t *deqeue, void *data);

void *Dequeue_PeekFront(struct Dequeue_t *dequeue);

void *Dequeue_PeekBack(struct Dequeue_t *dequeue);

void *Dequeue_PopFront(struct Dequeue_t *dequeue);

void *Dequeue_PopBack(struct Dequeue_t *dequeue);

int Dequeue_IsEmpty(struct Dequeue_t *dequeue);

void Dequeue_Free(struct Dequeue_t *dequeue);


#endif