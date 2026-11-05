/* Interned-string wrapper cleanup identified by GAMERAM's retail unwind table. */
typedef struct StringRefWord { char *value; } StringRefWord;
void StringChunk_ReleaseHeader(void *,int);
void FUN_00100610(void *);
StringRefWord *StringRef_Destruct_00130720(StringRefWord *self,int delete_storage) {
    if(self) {
        char *value=self->value;
        if(value) {
            int *header=(int *)(value-8);
            if(--header[1]==0) StringChunk_ReleaseHeader((void *)header[0], (int)header);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}
