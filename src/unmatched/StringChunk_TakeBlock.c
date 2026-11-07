typedef struct StringBlockHeader { unsigned short next; unsigned short size; } StringBlockHeader;
typedef struct StringChunkState { char pad[24]; char *free; int largest; } StringChunkState;
char *StringChunk_TakeBlock(StringChunkState *self, unsigned int bytes) {
 unsigned short want;
 unsigned short largest;
 unsigned short sz;
 char *prev;
 char *blk;
 unsigned short next;
 StringBlockHeader *h;
 char *r;
 blk = self->free; want = (bytes >> 2) & 0xFFFF; largest = 0; prev = 0;
 while (blk != 0) {
  h = (StringBlockHeader *)(blk - 4);
  sz = h->size; next = h->next;
  if (sz > largest) { largest = sz; }
  if (!(want > sz)) {
   r = blk - sz * 4;
   if (want == sz) {
    if (prev != 0) {
     h = (StringBlockHeader *)(prev - 4);
     if (next == 0) { h->next = 0; } else { h->next += next; }
    }
    if (blk == self->free) {
     if (next != 0) { self->free = self->free + next * 4; } else { self->free = 0; }
    }
   } else { h->size -= want; }
   self->largest = -1;
   return r;
  }
  prev = blk;
  if (next == 0) { blk = 0; } else { blk = blk + next * 4; }
 }
 self->largest = largest * 4;
 return 0;
}
