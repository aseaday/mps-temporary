/* 
TEST_HEADER
 id = $Id$
 summary = free though not allocated
 language = c
 link = testlib.o
OUTPUT_SPEC
 assert = true
 assertfile P= tract.c
 assertcond = found
END_HEADER
*/

#include "testlib.h"
#include "mpscmv.h"

static void test(void)
{
 mps_arena_t arena;
 mps_pool_t pool;
 size_t extendBy;
 size_t avgSize;
 size_t maxSize;

 mps_addr_t obj = (mps_addr_t)1;

 extendBy = (size_t) 4096;
 avgSize  = (size_t) 32;
 maxSize  = (size_t) 65536;

 cdie(mps_arena_create(&arena, mps_arena_class_vm(), mmqaArenaSIZE), "create arena");

 cdie(
  mps_pool_create(&pool, arena, mps_class_mv(),
   extendBy, avgSize, maxSize),
  "create pool");
/*
 cdie(mps_alloc(&obj, pool, 152), "allocate");
*/
 mps_free(pool, obj, 512);
 comment("Freed.");

 mps_pool_destroy(pool);
 comment("Destroyed pool");

 mps_arena_destroy(arena);
 comment("Destroyed arena.");
}

int main(void)
{
 easy_tramp(test);
 return 0;
}
