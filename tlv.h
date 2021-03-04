#ifndef TLV_H_
#define TLV_H_

#include <stdint.h>
#include <stdbool.h>

typedef uint16_t tlv_type_t;
typedef uint16_t tlv_len_t;

typedef struct tlv_elem_s
{
    tlv_type_t type;
    tlv_len_t length;
    uint8_t value[]; /* Value placed in memory from this variable and farther */
}
tlv_elem_t;

typedef struct tlv_s
{
    int size;
    uint8_t *begin;
    uint8_t *end;
}
tlv_t;

void tlv_init(tlv_t* tlv, uint8_t *buf, int size);
bool tlv_add(tlv_t* tlv, const tlv_elem_t *elem);
tlv_elem_t* tlv_begin(const tlv_t* tlv);
tlv_elem_t* tlv_next(const tlv_elem_t* elem);
tlv_elem_t* tlv_end(const tlv_t* tlv);
void* tlv_get_value(tlv_elem_t* elem);

#endif /*TLV_H_*/
