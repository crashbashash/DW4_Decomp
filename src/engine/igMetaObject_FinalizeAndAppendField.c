void igMetaField_FinalizeDescriptor(void *);
void igMetaObject_AppendField(void *,void *);
void igMetaObject_FinalizeAndAppendField(void *meta,void *field){
    igMetaField_FinalizeDescriptor(field);igMetaObject_AppendField(meta,field);
}
