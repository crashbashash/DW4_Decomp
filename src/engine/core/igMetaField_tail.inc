void igMetaField_AllocateArray(int *outStatus,igMemoryRefMetaField *field,void *object,int count,AlignedAllocatorView *allocator){
    unsigned int bytes=(unsigned int)count*(unsigned short)((ElementLayoutView *)field->_memType)->Size();
    int alignment=(unsigned short)((ElementLayoutView *)field->_memType)->Alignment();
    void *data=allocator->Allocate(bytes,alignment);
    if(!data){*outStatus=g_resultFailure.v;return;}
    /* Reference-typed elements start zeroed; other element types keep the allocator's contents. */
    if(igObject_IsKindOf((void *)field->_memType, (igMetaObject *)(((int *)g_igRefMetaField_metaObject)[0])))memset(data,0,bytes);
    *(void **)((char *)object+field->_offset)=data;
    *outStatus=g_resultSuccess.v;
}

