struct StaticInitCallbacks { void (**functions)(); int count; };
extern "C" void igArray_Destruct(StaticInitCallbacks *,short);
extern "C" void igMetaObject_RunStaticInit(StaticInitCallbacks *(*initialize)()){
    StaticInitCallbacks *list=initialize();
    int count; int i;
    if(list){count=list->count;for(i=0;i<count;i++)list->functions[i]();igArray_Destruct(list,1);}
}
