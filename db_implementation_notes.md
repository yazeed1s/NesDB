# The big goal
- Implement index-orgnized storage for disk-oriented db
- it's gonna be row-oriented storage
# Problems to take care of
1- How the DBMS represents the database in files on disk?
	- db data will be stored in pages, but i won't follow how PG scatter db data into multiple files. Instead i will follow what sqlite does, all of the db is stored in single file. 
		- Since the whole db is in a single file, there is no need for page directory, the logic for accesing a specific page within the db file will be page_offset = page# * page_size.
		- the api for page related tasks is Create/Get/Write/Delete page
2- How the DBMS manages its memory and moves data back-and-forth from disk?
	- for this, buffer pool is needed, no mmap.

# Database page architicture
## 1. Page architicture
- page size will be **4KB**  (lower overhead for write heavy workload since the disk access is sequential), may be confgiurable?
### Page Header
- every page contain a **header**, that stores 
  - Page size
  - Checksum
  - DBMS version
  - Transaction visibility
### page Data Layout
- data inside the page will be represneted as **tuples**
- the data layout scheme will be **slotted pages**
- a page essentially looks like the following
```ini
|----------------|
|  page header   |
|----------------|
|                |
|  page data     |
|                |
|----------------|

```
# Components:
1. Disk manager
	- read, write data on disk, when buffer pool instructs
	- create db file
2. Buffer pool
	- Move data between disk and RAM, also caches frequently used pages in RAM
3. 

# Resources:
1. https://docs.oracle.com/cd/E11882_01/server.112/e40540/indexiot.htm#CBBJEBIH
2. https://www.sqlite.org/arch.html
3. https://www.vldb.org/conf/2000/P285.pdf
4. https://www.sqlite.org/howitworks.html