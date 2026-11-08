/* newlib mallocr.c pieces. */
#include "dw4/newlib_mallocr.h"

typedef unsigned int size_t;
#define RARG Reent *reent_ptr,
#define RONEARG Reent *reent_ptr
#define RCALL reent_ptr,
#define RONECALL reent_ptr
#define MALLOC_LOCK FUN_00127310(reent_ptr)
#define MALLOC_UNLOCK FUN_00127390(reent_ptr)
#define malloc_getpagesize 4096
#define check_chunk(P)
#define check_malloc_state()
#define check_inuse_chunk(P)
#define check_free_chunk(P)
#define check_malloced_chunk(P, N)
#define Void_t void
typedef struct __sFILE FILE;
struct ReentStderr { char pad[12]; FILE *_stderr; };
#define _stderr_r(ptr) (((struct ReentStderr *)(ptr))->_stderr)
int FUN_001251c8(FILE *, const char *, ...);
#define fiprintf FUN_001251c8
void FUN_00126180(void);
#define malloc_update_mallinfo FUN_00126180
extern const char D_004d3ec8[], D_004d3ee8[], D_004d3f08[];
void FUN_00126df8(RONEARG)
{
  unsigned long local_max_total_mem;
  int local_sbrked_mem;
  struct mallinfo local_mallinfo;
  FILE *fp;

  MALLOC_LOCK;
  malloc_update_mallinfo();
  local_max_total_mem = max_total_mem;
  local_sbrked_mem = sbrked_mem;
  local_mallinfo = current_mallinfo;
  MALLOC_UNLOCK;

  fp = _stderr_r(reent_ptr);
  fiprintf(fp, D_004d3ec8,
	  (unsigned int)(local_max_total_mem));
  fiprintf(fp, D_004d3ee8,
	  (unsigned int)local_sbrked_mem);
  fiprintf(fp, D_004d3f08,
	  (unsigned int)local_mallinfo.uordblks);
}
