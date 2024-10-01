#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int read_date(int page_id, char *page_data);
int write_data(int page_id, const char *page_data);

typedef struct disk_manager_t disk_manager_t;
struct disk_manager_t {
  // file descriptor
  int fd;
  // flags for io ops (O_RDONLY | O_WRONLY | O_RDWR | O_APPEND)
  int32_t flags;
  // total number of flushes
  uint32_t num_flushes;
  // total number of writes
  uint32_t num_writes;
  // total number of pages in the file
  uint32_t num_pages;
  // read a page from the database file.
  // takes the page id (int), and a pointer to data holder (out)
  int (*read_date)(int, char *);
  // writes a page to the database file.
  // takes the page id (int), and data to hold
  int (*write_data)(int, const char *);
};

int read_date(int page_id, char *page_data) { return 0; }
int write_data(int page_id, const char *page_data) { return 0; }

disk_manager_t *create_disk_manager(const char *file) {
  int fd;
  int flags = O_RDWR;
  if ((fd = open(file, flags)) == -1)
    return NULL;

  disk_manager_t *dmgr = (disk_manager_t *)malloc(sizeof(disk_manager_t));
  if (dmgr == NULL)
    return NULL;

  dmgr->fd = fd;
  dmgr->flags = flags;
  dmgr->num_flushes = dmgr->num_pages = dmgr->num_writes = 0;
  dmgr->read_date = read_date;
  dmgr->write_data = write_data;

  return dmgr;
}