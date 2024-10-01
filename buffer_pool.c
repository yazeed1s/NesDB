
#include <stdint.h>

/*
 * This is the implementation of the buffer pool manager subsystem or "bufmgr".
 *
 * The bufmgr is used to access a database disk file.  It implements
 * atomic commit and rollback through the use of a journal file that
 * is separate from the database file.  The bufmgr also implements file
 * locking to prevent two processes from writing the same database
 * file simultaneously, or one process from reading the database while
 * another is writing.
 */

typedef struct memory_page_t memory_page_t;

// pager is basically the buffer pool manager
struct memory_page_t {
  //  sqlite3_pcache_page *pPage; /* Pcache object page handle */
  void *page_data; /* Page data */
  //  PCache *pCache;             /* PRIVATE: Cache that owns this page */
  memory_page_t *pDirty; /* Transient list of dirty sorted by pgno */
  //   Pager *pPager;         /* The pager this page is part of */
  //   Pgno pgno;             /* Page number for this page */
  uint64_t page_hash;        /* Hash of page content */
  memory_page_t *pDirtyNext; /* Next element in list of dirty pages */
  memory_page_t *pDirtyPrev; /* Previous element in list of dirty pages */
};

typedef struct buffer_pool_manager_t buffer_pool_manager_t;

// pager is basically the buffer pool manager
struct buffer_pool_manager_t {
 
};