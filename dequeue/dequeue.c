#include <assert.h>
#include <stdlib.h>

struct DequeueNode_t {
    void *stored;
    struct DequeueNode_t *next;
    struct DequeueNode_t *prev;
};

struct Dequeue_t {
    struct DequeueNode_t *head;
    struct DequeueNode_t *tail;
};

void Dequeue_Reset(struct Dequeue_t *dequeue) {
    dequeue->head = 0;
    dequeue->tail = 0;
}

struct DequeueNode_t *DequeueNode_MallocNode(void *stored) {
    struct DequeueNode_t *node = malloc(sizeof(struct Dequeue_t));
    node->next = 0;
    node->prev = 0;
    node->stored = stored;
    return node;
}

void Dequeue_PushBack(struct Dequeue_t *dequeue, void *data) {
    struct DequeueNode_t *node = DequeueNode_MallocNode(data);
    if(!dequeue->head) {
        dequeue->head = node;
        dequeue->tail = dequeue->head;
    }
    else {
        dequeue->tail->next = node;
        node->prev = dequeue->tail;
        dequeue->tail = node;
    }
}

void Dequeue_PushFront(struct Dequeue_t *deqeue, void *data) {
    struct DequeueNode_t *node = DequeueNode_MallocNode(data);
    if(!deqeue->head) {
        deqeue->head = node;
        deqeue->tail = deqeue->head;
    }
    else {
        deqeue->head->prev = node;
        node->next = deqeue->head;
        deqeue->head = node;
    }
}

void *Dequeue_PeekFront(struct Dequeue_t *dequeue) {
    if(!dequeue->head) {
        return 0;
    }
    return dequeue->head->stored;
}

void *Dequeue_PeekBack(struct Dequeue_t *dequeue) {
    if(!dequeue->tail) {
        return 0;
    }
    return dequeue->tail->stored;
}

void *Dequeue_PopFront(struct Dequeue_t *dequeue) {
    if(!dequeue->head) {
        return 0;
    }
    void *front = DequeuePeekFront(dequeue);
    if(dequeue->head == dequeue->tail) {
        free(dequeue->head);
        dequeue->head = 0;
        dequeue->tail = 0;
    }
    else {
        assert(dequeue->head->next->prev == dequeue->head);
        dequeue->head = dequeue->head->next;
        free(dequeue->head->prev);
        dequeue->head->prev = 0;
    }
    return front;
}

void *Dequeue_PopBack(struct Dequeue_t *dequeue) {
    if(!dequeue->tail) {
        return 0;
    }
    assert(!dequeue->tail->next);
    void *back = DequeuePeekBack(dequeue);
    if(dequeue->tail == dequeue->head) {
        free(dequeue->head);
        dequeue->head = 0;
        dequeue->tail = 0;
    }
    else {
        assert(dequeue->tail->prev->next == dequeue->tail);
        dequeue->tail = dequeue->tail->prev;
        free(dequeue->tail->next);
        dequeue->tail->next = 0;
    }

    return back;
}

int Dequeue_IsEmpty(struct Dequeue_t *dequeue) {
    return !dequeue->head;
}

void Dequeue_Free(struct Dequeue_t *dequeue) {
    struct DequeueNode_t *node = dequeue->head;
    while (node) {
        struct DequeueNode_t *next = node->next;
        free(node);
        node = next;
    }
}
