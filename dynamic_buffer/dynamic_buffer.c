#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define DEFAULT_INIT_CAP 16

struct DynamicBuffer_t {
	char *head;
	char *tail;
	size_t max_capicity_bytes;
	size_t type_size;
};

void DynamicBuffer_InitWithCap(struct DynamicBuffer_t *buffer, size_t type_size, size_t cap_elements) {
	buffer->type_size = type_size;	
	buffer->max_capicity_bytes = cap_elements * type_size;
	buffer->head = (char*)malloc(buffer->max_capicity_bytes);
	memset(buffer->head, 0, buffer->max_capicity_bytes);
	buffer->tail = buffer->head;
}

void DynamicBuffer_Init(struct DynamicBuffer_t *buffer, size_t type_size) {
	DynamicBuffer_InitWithCap(buffer, type_size, DEFAULT_INIT_CAP);
}

size_t DynamicBuffer_StoredBytesCount(struct DynamicBuffer_t *buffer) {
	return (unsigned int)(buffer->tail - buffer->head);
}

size_t DynamicBuffer_StoredElementCount(struct DynamicBuffer_t *buffer) {
	return DynamicBuffer_StoredBytesCount(buffer) * buffer->type_size;
}

int DynamicBuffer_Resize(struct DynamicBuffer_t *buffer, size_t size) {
	size_t tail_offset = DynamicBuffer_StoredBytesCount(buffer);
	buffer->head = realloc(buffer->head, size);
	if (!buffer->head) {
		return 1;
	}
	buffer->max_capicity_bytes = size;
	buffer->tail = buffer->head + tail_offset;
	return 0;
}

void DynamicBuffer_AppendUnfixed(struct DynamicBuffer_t *buffer, void *element, size_t size_bytes) {
	char *input = (char*)element;
	for(size_t i = 0; i < size_bytes; i++) {
		*(buffer->tail++) = input[i];
		if (DynamicBuffer_StoredBytesCount(buffer) >= buffer->max_capicity_bytes) {
			DynamicBuffer_Resize(buffer, buffer->max_capicity_bytes * 2);
		}
	}
}

void DynamicBuffer_Append(struct DynamicBuffer_t *buffer, void *element) {
	DynamicBuffer_AppendUnfixed(buffer, element, buffer->type_size);
}

void *DynamicBuffer_GetByteIndex(struct DynamicBuffer_t *buffer, size_t bytes_index) {
	if (bytes_index > buffer->max_capicity_bytes) {
		return 0;
	}
	return &buffer->head[bytes_index];
}

void *DynamicBuffer_GetElementIndex(struct DynamicBuffer_t *buffer, size_t element_index) {
	return DynamicBuffer_GetByteIndex(buffer, buffer->type_size * element_index);
}

void DynamicBuffer_Free(struct DynamicBuffer_t *buffer) {
	free(buffer->head);
	buffer->head = 0;
	buffer->tail = 0;
	buffer->type_size = 0;
	buffer->max_capicity_bytes = 0;
}

