#ifndef DYNAMIC_BUFFER_H
#define DYNAMIC_BUFFER_H

#include <stddef.h>

struct DynamicBuffer_t {
	char *head;
	char *tail;
	size_t max_capicity_bytes;
	size_t type_size;
};


extern void DynamicBuffer_Init(struct DynamicBuffer_t *buffer, size_t type_size);

extern void DynamicBuffer_InitWithCap(struct DynamicBuffer_t *buffer, size_t type_size, size_t cap_elements);

extern size_t DynamicBuffer_StoredBytesCount(struct DynamicBuffer_t *buffer);

extern size_t DynamicBuffer_StoredElementCount(struct DynamicBuffer_t *buffer);

extern int DynamicBuffer_Resize(struct DynamicBuffer_t *buffer, size_t size);

extern void DynamicBuffer_AppendUnfixed(struct DynamicBuffer_t *buffer, void *element, size_t size_bytes);

extern void DynamicBuffer_Append(struct DynamicBuffer_t *buffer, void *element);



extern void *DynamicBuffer_GetByteIndex(struct DynamicBuffer_t *buffer, size_t bytes_index);

extern void *DynamicBuffer_GetElementIndex(struct DynamicBuffer_t *buffer, size_t element_index);

extern void DynamicBuffer_Free(struct DynamicBuffer_t *buffer);

#endif

