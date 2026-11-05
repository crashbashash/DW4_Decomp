void *igObject_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void igObject_EnsureRegistered(void){igMetaObject_RunStaticInit(igObject_Register);}
