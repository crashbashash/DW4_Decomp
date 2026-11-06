/* Complete forwarding subgroup: two prior matches with corrected signatures and a new 84-byte
 * group-delayed send. */
extern "C" void beMessenger_PrepareDelayedSelection(void *,const char *,const char *,int);
extern "C" void beMessenger_EnqueueSelected(void *,const char *,long long);
extern "C" void beMessenger_SendDelayedNamed(void *self,const char *group,const char *name,int id,const char *message,long long delay){beMessenger_PrepareDelayedSelection(self,group,name,id);beMessenger_EnqueueSelected(self,message,delay);}
extern "C" void beMessenger_SendDelayedGroup(void *self,const char *group,const char *message,long long delay){beMessenger_PrepareDelayedSelection(self,group,0,-1);beMessenger_EnqueueSelected(self,message,delay);}
extern "C" void beMessenger_PrepareDelayedGroup(void *self,const char *group){beMessenger_PrepareDelayedSelection(self,group,0,-1);}
