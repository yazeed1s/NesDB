#ifndef ZDB_PAGE_H
#define ZDB_PAGE_H

// 4KB is the maximum page size
#include <cstdint>
#define PAGE_SIZE 4096

typedef char byte_t;

// The slot array maps "slots" to the tuples' starting position offsets.
// The header keeps track of:
// → The # of used slots
// → The offset of the starting location of the last slot used.
typedef struct {
  uint16_t free_space_start; /* offset to start of free space */
  uint16_t free_space_end;   /* offset to end of free space */
} page_header_t;

typedef struct {
  int32_t page_id;
  byte_t *data;
  /* pin_count: tracks the number of threads that are currently
   * accessing this page (either reading or modifying it).
   * A thread has to increment the counter before it access the page.
   * If a page’s count is greater than zero, then the storage
   * manager is not allowed to evict this page from memory.
   */
  int pin_count;
  /* 'is_dirty': true if the page is dirty, i.e. it is different
   * from its corresponding page on disk.
   */
  bool is_dirty;
} page_t;

// page data layout: *tuple-oriented*
// data inside the page is represneted as **tuples**
// the data layout scheme is **slotted pages**;
#endif