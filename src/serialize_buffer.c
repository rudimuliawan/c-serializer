//
// Created by rudi on 26/10/21.
//

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <serialize_buffer.h>


void serialize_buffer_init(SerializeBuffer **buffer)
{
    SerializeBuffer *buff = (SerializeBuffer *)calloc(1, sizeof(SerializeBuffer));
    buff->start = calloc(1, SERIALIZE_BUFFER_DEFAULT_SIZE);
    buff->size = SERIALIZE_BUFFER_DEFAULT_SIZE;
    buff->next = 0;

    *buffer = buff;
}


void serialize_buffer_serialize(SerializeBuffer *buffer, char *data, int nbytes)
{
    int available_size = buffer->size - buffer->next;
    bool is_resize = false;

    while (available_size < nbytes) {
        buffer->size = buffer->size * 2;
        available_size = buffer->size - buffer->next;
        is_resize = true;
    }

    if (!is_resize) {
        memcpy((char *)buffer->start + buffer->next, data, nbytes);
        buffer->next += nbytes;
        return;
    }

    buffer->start = realloc(buffer->start, buffer->size);
    memcpy((char *) buffer->start + buffer->next, data, nbytes);
    buffer->next += nbytes;
}


void serialize_buffer_deserialize(SerializeBuffer *buffer, char *dest, int size)
{
    memcpy(dest, buffer->start + buffer->next, size);
    buffer->next += size;
}


void serialize_buffer_skip(SerializeBuffer *buffer, int skip_size)
{
    if (buffer->next + skip_size > 0 &&
        buffer->next + skip_size < buffer->size)
    {
        buffer->next += skip_size;
    }
}


void serialize_buffer_reset(SerializeBuffer *buffer)
{
	buffer->next = 0;
}

void serialize_buffer_free(SerializeBuffer *buffer)
{
    buffer->start = NULL;
    buffer->next = 0;
    buffer->size = 0;
}
