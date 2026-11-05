/* Messenger class factories and their lazy-registration wrappers, in retail order
 * (beMessengerWork 0x358070, Group 0x3584e0, Delay 0x358950, ArgData 0x358d80).  Each
 * factory makes sure the class is registered, reloads the class handle and creates an
 * instance from the caller's allocator; see docs/engine/object-creation.md.
 * Return and allocator signatures follow the original call/return registers. */

/* Structural ABI view of the static-init callback list the registrars return
 * (see src/engine/igMetaObjectCreation.cpp); never defined here. */
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

/* Published class handles (slot holding each class's igMetaObject pointer), named by the
 * class-handle rule of docs/engine/naming.md; the addresses are the handles listed in
 * include/dw4/reflected.h and the metadata table of docs/engine/object-creation.md. */
extern "C" int g_beMessengerWork_metaObject_00588f88[4];
extern "C" int g_beMessengerGroup_metaObject_00588fc8[4];
extern "C" int g_beMessengerDelay_metaObject_00588ff0[4];
extern "C" int g_beMessengerArgData_metaObject_00589038[4];

extern "C" void *beMessengerWork_Create(void *allocator){beMessengerWork_EnsureRegistered();return igMetaObject_CreateInstance((void *)g_beMessengerWork_metaObject_00588f88[0],allocator);}
extern "C" void beMessengerWork_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerWork_Register);}

extern "C" void *beMessengerGroup_Create(void *allocator){beMessengerGroup_EnsureRegistered();return igMetaObject_CreateInstance((void *)g_beMessengerGroup_metaObject_00588fc8[0],allocator);}
extern "C" void beMessengerGroup_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerGroup_Register);}

extern "C" void *beMessengerDelay_Create(void *allocator){beMessengerDelay_EnsureRegistered();return igMetaObject_CreateInstance((void *)g_beMessengerDelay_metaObject_00588ff0[0],allocator);}
extern "C" void beMessengerDelay_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerDelay_Register);}

extern "C" void *beMessengerArgData_Create(void *allocator){beMessengerArgData_EnsureRegistered();return igMetaObject_CreateInstance((void *)g_beMessengerArgData_metaObject_00589038[0],allocator);}
extern "C" void beMessengerArgData_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerArgData_Register);}
