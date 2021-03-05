#include "tlv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TYPE_U8  0x12
#define TYPE_U16 0x22
#define TYPE_U32 0x33

/* One buffer for all the tests */
#define TLV_SIZE 1024
uint8_t TLV_BUF[TLV_SIZE];
const uint8_t  U8   = 0xFA;
const uint8_t  U8_2 = 0xCE;
const uint16_t U16  = 0xFACE;
const uint32_t U32  = 0xFACEC0DE;

/*#define TEST_TLV_ELEM(elem, val) \
    test_tlv_elem(elem, TYPE_##val, sizeof(val), &val)*/

void test_add_same_type_different_size()
{
    tlv_t tlv;
    tlv_init(&tlv, TLV_BUF, TLV_SIZE);

    assert(tlv_add(&tlv, TYPE_U8, sizeof(U8), (uint8_t *)&U8) == true);
    assert(tlv_add(&tlv, TYPE_U8, sizeof(U8_2), (uint8_t *)&U8_2) == true);
    assert(tlv_add(&tlv, TYPE_U8, sizeof(U16), (uint8_t *)&U16) == true);
    assert(tlv_add(&tlv, TYPE_U8, sizeof(U32), (uint8_t *)&U32) == true);

    tlv_elem_t *elem = tlv_begin(&tlv);

    assert(elem->type == TYPE_U8);
    assert(elem->length == sizeof(U8));
    assert((uint8_t)*(uint8_t *)elem->value == U8);
    elem = tlv_next(elem);

    assert(elem->type == TYPE_U8);
    assert(elem->length == sizeof(U8_2));
    assert((uint8_t)*(uint8_t *)elem->value == U8_2);
    elem = tlv_next(elem);

    assert(elem->type == TYPE_U8);
    assert(elem->length == sizeof(U16));
    assert((uint16_t)*(uint16_t *)elem->value == U16);
    elem = tlv_next(elem);

    assert(elem->type == TYPE_U8);
    assert(elem->length == sizeof(U32));
    assert((uint32_t)*(uint32_t *)elem->value == U32);
    elem = tlv_next(elem);

    assert(elem == tlv_end(&tlv));
}

void test_add_same_size_different_type()
{
    tlv_t tlv;
    tlv_init(&tlv, TLV_BUF, TLV_SIZE);

    assert(tlv_add(&tlv, TYPE_U8, sizeof(U8), (uint8_t *)&U8) == true);
    assert(tlv_add(&tlv, TYPE_U16, sizeof(U8), (uint8_t *)&U8) == true);
    assert(tlv_add(&tlv, TYPE_U32, sizeof(U8), (uint8_t *)&U8) == true);

    tlv_elem_t *elem = tlv_begin(&tlv);

    assert(elem->type == TYPE_U8);
    assert(elem->length == sizeof(U8));
    assert((uint8_t)*(uint8_t *)elem->value == U8);
    elem = tlv_next(elem);

    assert(elem->type == TYPE_U16);
    assert(elem->length == sizeof(U8));
    assert((uint8_t)*(uint8_t *)elem->value == U8);
    elem = tlv_next(elem);

    assert(elem->type == TYPE_U32);
    assert(elem->length == sizeof(U8));
    assert((uint8_t)*(uint8_t *)elem->value == U8);
    elem = tlv_next(elem);

    assert(elem == tlv_end(&tlv));
}

void test_add_no_memory()
{
    tlv_t tlv;
    uint8_t tlv_size = 4;
    tlv_init(&tlv, TLV_BUF, tlv_size);

    assert(tlv_add(&tlv, TYPE_U8, sizeof(U8), (uint8_t *)&U8) == false);
}

void test_add_in_middle()
{
    tlv_t tlv;
    tlv_init(&tlv, TLV_BUF, TLV_SIZE);

    tlv_add(&tlv, TYPE_U8, sizeof(U8), (uint8_t *)&U8);

    tlv_elem_t *first = tlv_begin(&tlv);
    assert(first->type == TYPE_U8);
    assert(first->length == sizeof(U8));
    assert((uint8_t)*(uint8_t *)first->value == U8);

    tlv_add(&tlv, TYPE_U16, sizeof(U16), (uint8_t *)&U16);
    tlv_elem_t *second = tlv_next(first);

    assert(second->type == TYPE_U16);
    assert(second->length == sizeof(U16));
    assert((uint16_t)*(uint16_t *)second->value == U16);

    assert(tlv_next(second) == tlv_end(&tlv));
}

int main()
{
    test_add_same_type_different_size();
    test_add_same_size_different_type();
    test_add_no_memory();
    test_add_in_middle();

    return 0;
}
