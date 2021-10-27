//
// Created by rudi on 26/10/21.
//

#ifndef SERIALIZE_BUFFER_H
#define SERIALIZE_BUFFER_H

#define SENTINEL_VALUE 0xFFFFFFFF
#define SERIALIZE_BUFFER_DEFAULT_SIZE 100


typedef struct serialize_buffer {
    char *start;
    int next;
    int size;
} SerializeBuffer;


void serialize_buffer_init(SerializeBuffer **buffer);
void serialize_buffer_serialize(SerializeBuffer *buffer, char *data, int nbytes);
void serialize_buffer_deserialize(SerializeBuffer *buffer, char *dest, int size);
void serialize_buffer_reset(SerializeBuffer *buffer);
void serialize_buffer_skip(SerializeBuffer *buffer, int skip_size);
void serialize_buffer_free(SerializeBuffer *buffer);

#endif // SERIALIZE_BUFFER_H
