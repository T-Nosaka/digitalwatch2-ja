#include <pebble.h>
#include "fmvhash.h"

#define FNV_OFFSET_BASIS_32 2166136261U
#define FNV_PRIME_32 16777619U

/*
 * ハッシュ値計算
 */
uint32_t fnv_1_hash_32(uint8_t *bytes, size_t length)
{
    uint32_t hash;
    size_t i;

    hash = FNV_OFFSET_BASIS_32;
    for( i = 0 ; i < length ; ++i) {
        hash = (FNV_PRIME_32 * hash) ^ (bytes[i]);
    }

    return hash;
}
