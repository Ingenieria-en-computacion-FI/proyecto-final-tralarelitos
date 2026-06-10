#include <assert.h>
#include "memory_manager.h"

void test_first_fit() {
     MemoryManager* mm = mm_create(1024);

     int block1 = mm_allocate_first_fit(mm, 100);
     int block2 = mm_allocate_first_fit(mm, 200);

     assert(block1 >= 0);
     assert(block2 >= 0);

     mm_free(mm, block1);

     int block3 = mm_allocate_first_fit(mm, 50);

     assert(block3 == block1);

     mm_destroy(mm);
}
