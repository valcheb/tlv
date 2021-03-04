#include "tlv.h"
#include <stddef.h>
#include <string.h>

void* tlv_get_value(tlv_elem_t* elem)
{
    return (void *)elem->value;
}

void tlv_init(tlv_t* tlv, uint8_t *buf, int size)
{
    tlv->size  = size;
    tlv->begin = buf;
    tlv->end   = buf;
}

bool tlv_add(tlv_t* tlv, const tlv_elem_t *elem)
{
    int tsize = sizeof(elem->type) + sizeof(elem->length) + elem->length;
    if ( tsize > tlv->size - (tlv->end - tlv->begin))
    {
        return false;
    }

    memcpy((tlv_elem_t *)tlv->end, elem, tsize);

    tlv->end += tsize;

    return true;
}

tlv_elem_t* tlv_begin(const tlv_t* tlv)
{
    return (tlv_elem_t *)tlv->begin;
}

tlv_elem_t* tlv_end(const tlv_t* tlv)
{
    return (tlv_elem_t *)tlv->end;
}

tlv_elem_t* tlv_next(const tlv_elem_t* elem)
{
    int tsize = sizeof(elem->type) + sizeof(elem->length) + elem->length;
    return (tlv_elem_t *) (elem + tsize);
}
