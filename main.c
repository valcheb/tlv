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
    while(elem != tlv_end(&tlv))
    {
        assert(elem->type == TYPE_U8);
        elem = tlv_next(elem);
    }
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
    while(elem != tlv_end(&tlv))
    {
        assert((uint8_t)*elem->value == U8);
        assert(elem->length == sizeof(U8));
        elem = tlv_next(elem);
    }
    assert(elem == tlv_end(&tlv));
}

int main()
{
    test_add_same_type_different_size();
    test_add_same_size_different_type();

    return 0;
}
