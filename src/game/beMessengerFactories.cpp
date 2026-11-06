/* Messenger class factories and their lazy-registration wrappers. Each factory makes sure the
 * class is registered, reloads the class handle and creates an instance from the caller's
 * allocator. */

/* Structural ABI view of the static-init callback list the registrars return; never defined here. */
struct StaticInitCallbacks;
extern "C" void igMetaObject_RunStaticInit(StaticInitCallbacks *(*)());
extern "C" void *igMetaObject_CreateInstance(void *classHandle,void *allocator);

extern "C" StaticInitCallbacks *beMessengerWork_Register();
extern "C" StaticInitCallbacks *beMessengerGroup_Register();
extern "C" StaticInitCallbacks *beMessengerDelay_Register();
extern "C" StaticInitCallbacks *beMessengerArgData_Register();
extern "C" void beMessengerWork_EnsureRegistered();
extern "C" void beMessengerGroup_EnsureRegistered();
extern "C" void beMessengerDelay_EnsureRegistered();
extern "C" void beMessengerArgData_EnsureRegistered();

/* Published class handles (slot holding each class's igMetaObject pointer). */
extern "C" int g_beMessengerWork_metaObject[4];
extern "C" int g_beMessengerGroup_metaObject[4];
extern "C" int g_beMessengerDelay_metaObject[4];
extern "C" int g_beMessengerArgData_metaObject[4];

extern "C" void *beMessengerWork_Create(void *allocator){beMessengerWork_EnsureRegistered();return igMetaObject_CreateInstance((void *)g_beMessengerWork_metaObject[0],allocator);}
extern "C" void beMessengerWork_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerWork_Register);}

extern "C" void *beMessengerGroup_Create(void *allocator){beMessengerGroup_EnsureRegistered();return igMetaObject_CreateInstance((void *)g_beMessengerGroup_metaObject[0],allocator);}
extern "C" void beMessengerGroup_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerGroup_Register);}

extern "C" void *beMessengerDelay_Create(void *allocator){beMessengerDelay_EnsureRegistered();return igMetaObject_CreateInstance((void *)g_beMessengerDelay_metaObject[0],allocator);}
extern "C" void beMessengerDelay_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerDelay_Register);}

extern "C" void *beMessengerArgData_Create(void *allocator){beMessengerArgData_EnsureRegistered();return igMetaObject_CreateInstance((void *)g_beMessengerArgData_metaObject[0],allocator);}
extern "C" void beMessengerArgData_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerArgData_Register);}
