#ifndef ZDB_PAGE_H
#define ZDB_PAGE_H

// 4KB is the maximum page size
#include <cstdint>
#define PAGE_SIZE 4096

typedef char byte_tt;
typedef uint8_t byte_t;

// The slot array maps "slots" to the tuples' starting position offsets.
// The header keeps track of:
// → The # of used slots
// → The offset of the starting location of the last slot used.
typedef struct {
  uint16_t free_space_start; /* offset to start of free space */
  uint16_t free_space_end;   /* offset to end of free space */
  uint16_t total_slots;      /* total number of slots */
  uint16_t free_slots;       /* number of free slots */
  uint16_t free_space;       /* amount of free space in this page */
  uint16_t padding;          /* padding to align struct size, if necessary */
} page_header_t;

typedef struct {
  page_header_t header; /* the page's header */
  int32_t page_id;      /* unique page id for this page */
  byte_t *data;         /* pointer to the content located in this page*/
  /* pin_count: tracks the number of threads that are currently
   * accessing this page (either reading or modifying it).
   * A thread has to increment the counter before it access the page.
   * If a page’s count is greater than zero, then the storage
   * manager is not allowed to evict this page from memory.
   */
  int32_t pin_count;
  /* 'is_dirty': true if the page is dirty, i.e. it is different
   * from its corresponding page on disk.
   */
  bool is_dirty;
  int32_t size; /* total page size, that is PAGE_SIZE */
} page_t;


/* pub struct BufferPoolManager { */
/*     pool: Vec<Arc<RwLock<Page>>>, */
/*     // LRU-K置换算法 */
/*     pub replacer: Arc<RwLock<LRUKReplacer>>, */
/*     pub disk_manager: Arc<DiskManager>, */
/*     // 缓冲池中的页号与frame号的映射 */
/*     page_table: Arc<DashMap<PageId, FrameId>>, */
/*     // 缓冲池中空闲的frame */
/*     free_list: Arc<RwLock<VecDeque<FrameId>>>, */
/* } */

/* #[derive(Debug)] */
/* pub struct DiskManager { */
/*     next_page_id: AtomicU32, */
/*     db_file: Mutex<File>, */
/*     pub meta: RwLock<MetaPage>, */
/* } */

/* sql statement --> buffer pool manager --> disk manager */
#endif
