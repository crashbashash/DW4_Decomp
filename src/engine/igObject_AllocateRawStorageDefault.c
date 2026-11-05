void *igObject_AllocateRawStorage(int,int,void *);
void *igObject_AllocateRawStorageDefault(int size,int prefix){return igObject_AllocateRawStorage(size,prefix,0);}
