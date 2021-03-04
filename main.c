#include "tlv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

void test_assert(bool res)
{
    if (!res)
    {
        printf("Error\n");
        exit(1);
    }
}

void test_add()
{
    tlv_t tlv;
    tlv_init(&tlv, TLV_BUF, TLV_SIZE);

    tlv_elem_t elem;

    elem.type = TYPE_U8;
    elem.length = sizeof(U8);
    *(uint8_t *)elem.value = U8;
    test_assert(tlv_add(&tlv, &elem));

    elem.type = TYPE_U8;
    elem.length = sizeof(U8_2);
    *(uint8_t *)elem.value = U8_2;
    test_assert(tlv_add(&tlv, &elem));

    elem.type = TYPE_U16;
    elem.length = sizeof(U16);
    *(uint8_t *)elem.value = U16;
    test_assert(tlv_add(&tlv, &elem));

    elem.type = TYPE_U32;
    elem.length = sizeof(U32);
    *(uint8_t *)elem.value = U32;
    test_assert(tlv_add(&tlv, &elem));
}

/*void test_add_and_read_different_sizes(const utest_stats_t *stats, void *user_ctx)
{
    tlv_t tlv;
    ushort_t size =
        TLV_HEADER_SIZE + 1 +
        TLV_HEADER_SIZE + 2 +
        TLV_HEADER_SIZE + 4;
    tlv_elem_t *elem = NULL;

    tlv_init(&tlv, TLV_BUF, size);

    elem = tlv_add(&tlv, TYPE_U8, sizeof(U8));
    UTEST_ASSERT(elem != NULL);
    *(uint8_t *)tlv_get_value(elem) = U8;

    elem = tlv_add(&tlv, TYPE_U16, sizeof(U16));
    UTEST_ASSERT(elem != NULL);
    *(uint16_t *)tlv_get_value(elem) = U16;

    elem = tlv_add(&tlv, TYPE_U32, sizeof(U32));
    UTEST_ASSERT(elem != NULL);
    *(uint32_t *)tlv_get_value(elem) = U32;

    elem = tlv_begin(&tlv);
    UTEST_ASSERT(elem < tlv_end(&tlv));
    UTEST_ASSERT(TEST_TLV_ELEM(elem, U8));

    elem = tlv_next(elem);
    UTEST_ASSERT(elem < tlv_end(&tlv));
    UTEST_ASSERT(TEST_TLV_ELEM(elem, U16));

    elem = tlv_next(elem);
    UTEST_ASSERT(elem < tlv_end(&tlv));
    UTEST_ASSERT(TEST_TLV_ELEM(elem, U32));

    elem = tlv_next(elem);
    UTEST_ASSERT(elem >= tlv_end(&tlv));
}*/

/*void test_same_type_different_size(const utest_stats_t *stats, void *user_ctx)
{
    tlv_t tlv;
    ushort_t size =
        TLV_HEADER_SIZE + 1 +
        TLV_HEADER_SIZE + 2;
    tlv_elem_t *elem = NULL;

    bool success = tlv_init(&tlv, TLV_BUF, size);
    UTEST_ASSERT(success);

    elem = tlv_add(&tlv, TYPE_U8, sizeof(U8));
    UTEST_ASSERT(elem != NULL);
    *(uint8_t *)tlv_get_value(elem) = U8;

    elem = tlv_add(&tlv, TYPE_U8, sizeof(U16));
    UTEST_ASSERT(elem != NULL);
    *(uint16_t *)tlv_get_value(elem) = U16;

    elem = tlv_begin(&tlv);
    UTEST_ASSERT(elem < tlv_end(&tlv));
    UTEST_ASSERT(TEST_TLV_ELEM(elem, U8));

    elem = tlv_next(elem);
    UTEST_ASSERT(elem < tlv_end(&tlv));
    UTEST_ASSERT(test_tlv_elem(elem, TYPE_U8, sizeof(U16), &U16));
}*/

/*void test_different_type_same_size(const utest_stats_t *stats, void *user_ctx)
{
    tlv_t tlv;
    ushort_t size =
        TLV_HEADER_SIZE + 1 +
        TLV_HEADER_SIZE + 1;
    tlv_elem_t *elem = NULL;

    bool success = tlv_init(&tlv, TLV_BUF, size);
    UTEST_ASSERT(success);

    elem = tlv_add(&tlv, TYPE_U8, sizeof(U8));
    UTEST_ASSERT(elem != NULL);
    *(uint8_t *)tlv_get_value(elem) = U8;

    elem = tlv_add(&tlv, TYPE_U16, sizeof(U8_2));
    UTEST_ASSERT(elem != NULL);
    *(uint8_t *)tlv_get_value(elem) = U8_2;

    elem = tlv_begin(&tlv);
    UTEST_ASSERT(elem < tlv_end(&tlv));
    UTEST_ASSERT(TEST_TLV_ELEM(elem, U8));

    elem = tlv_next(elem);
    UTEST_ASSERT(elem < tlv_end(&tlv));
    UTEST_ASSERT(test_tlv_elem(elem, TYPE_U16, sizeof(U8_2), &U8_2));
}*/

/*void test_add_no_mem(const utest_stats_t *stats, void *user_ctx)
{
    tlv_t tlv;
    ushort_t size = TLV_HEADER_SIZE + 1;
    tlv_elem_t *elem = NULL;

    bool success = tlv_init(&tlv, TLV_BUF, size);
    UTEST_ASSERT(success);
    UTEST_ASSERT(tlv_begin(&tlv) == tlv_end(&tlv));

    elem = tlv_add(&tlv, TYPE_U16, sizeof(U16));
    UTEST_ASSERT(elem == NULL);
    UTEST_ASSERT(tlv_begin(&tlv) == tlv_end(&tlv));
}*/

/*void test_add_in_the_middle_of_iteration(const utest_stats_t *stats, void *user_ctx)
{
    tlv_t tlv;
    ushort_t size =
        TLV_HEADER_SIZE + 1 +
        TLV_HEADER_SIZE + 2;
    tlv_elem_t *first = NULL;
    tlv_elem_t *elem = NULL;

    bool success = tlv_init(&tlv, TLV_BUF, size);
    UTEST_ASSERT(success);

    elem = tlv_add(&tlv, TYPE_U8, sizeof(U8));
    UTEST_ASSERT(elem != NULL);
    *(uint8_t *)tlv_get_value(elem) = U8;

    first = tlv_begin(&tlv);
    UTEST_ASSERT(TEST_TLV_ELEM(first, U8));

    elem = tlv_add(&tlv, TYPE_U16, sizeof(U16));
    UTEST_ASSERT(elem != NULL);
    *(uint16_t *)tlv_get_value(elem) = U16;

    UTEST_ASSERT(TEST_TLV_ELEM(first, U8));
    elem = tlv_next(first);
    UTEST_ASSERT(TEST_TLV_ELEM(elem, U16));
}*/

int main()
{
    test_add();

    return 0;
}
