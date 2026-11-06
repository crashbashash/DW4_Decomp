extern "C" void beMessenger_SelectGroupRam(void *,const char *,int);
extern "C" void beMessenger_SelectGroup(void *,const char *);
extern "C" void beMessenger_SelectReceivers(void *,const char *,const char *,int);
extern "C" void beMessenger_DispatchSelected(void *,const char *);
extern "C" void beMessenger_SelectGroupRam(void *self,const char *category,int id){beMessenger_SelectReceivers(self,category,0,id);}
extern "C" void beMessenger_SelectGroup(void *self,const char *category){beMessenger_SelectReceivers(self,category,0,-1);}
extern "C" void beMessenger_SendNamed(void *self,const char *category,const char *name,int id,const char *key){beMessenger_SelectReceivers(self,category,name,id);beMessenger_DispatchSelected(self,key);}
extern "C" void beMessenger_SendRam(void *self,const char *category,int id,const char *key){beMessenger_SelectGroupRam(self,category,id);beMessenger_DispatchSelected(self,key);}
extern "C" void beMessenger_SendGroup(void *self,const char *category,const char *key){beMessenger_SelectGroup(self,category);beMessenger_DispatchSelected(self,key);}
