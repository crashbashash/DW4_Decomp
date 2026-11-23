#ifndef DW4_IGOBJECTSYSTEM_H
#define DW4_IGOBJECTSYSTEM_H

/* Starting and stopping the Alchemy object system; `headerVersion` is the version of the headers the
 * caller was built with (0xC80). g_objectSystem is the running object system: its `active` flag,
 * metadata registry, pools, configuration registry and the vtable probe offset every class's
 * GetVTable reads. */
#ifdef __cplusplus
#include "dw4/core/igStringRef.h"
#endif

struct igMemoryPoolView;
struct igRegistry;
struct igDriverDatabase;
namespace Gap { namespace Core { class igResource; } }
struct igPluginHelper;
struct igSymbolTable;
struct igEventTrackerView;
struct igStringTableView;
struct igObject;

/* The object system behind &g_objectSystem: the activity flags, the metadata registry and the
 * counts it held at boot, the callbacks run for every registered meta object, the configuration
 * registry and the event formats are used here. */
struct ObjectSystemView {
    unsigned char active;
    char unknown1[3];
    int bootMetaObjectCount;      /* metaRegistry count when the boot registration finished */
    int bootMetaFieldCount;       /* meta-field registry count at the same point */
    int metaObjectCount;          /* metaRegistry count when igObjectSystem_Initialize finished */
    int metaFieldCount;           /* meta-field registry count at the same point */
    unsigned char started;        /* set first at start-up, cleared last at shut-down */
    unsigned char preExitDone;    /* the "exitPre" marker has been sent */
    unsigned char exitDone;       /* set once igObjectSystem_Exit has run, before the exit callbacks */
    char unknown23[1];
    void *metaRegistry;
    char unknown28[4];
    int f32;
    void *metaEnumList;           /* igMetaEnum objects registered through igObjectSystem_AppendMetaEnum */
    void *exitCallbacks;          /* igObjectSystem_AddExitCallback appends here */
    void *registrationCallbacks;
    struct igMemoryPoolView *bootstrapPool; /* the allocator of record 0 (Bootstrap) */
    struct igMemoryPoolView *systemPool;    /* the allocator of record 4 (System) */
    struct igRegistry *configRegistry;
    struct igDriverDatabase *driverDatabase;
    Gap::Core::igResource *resource;     /* the resource manager: named directories and objects */
    struct igMemoryPoolView *resourceTempPool;   /* the resource manager's temporary pool over a raw buffer */
    unsigned int resourceTempPoolSize;    /* "resourceTempMemoryPoolSize": no temporary pool when zero */
    struct igPluginHelper *pluginHelper;
    struct igSymbolTable *symbolTable;   /* loaded from symbolsFileName at memory set-up */
    struct igEventTrackerView *globalEventTracker; /* useGlobalEventTracker's tracker; receives the "exitPre" and "exitIn" markers */
    struct igMemoryPoolView *driverDataPool; /* the allocator of record 20 (DriverData) when it is its own pool */
    unsigned char f92;
    char unknown93[3];
    struct igMemoryPoolView *fastPool;       /* the allocator of record 7 (Fast) when it is its own pool */
    int copyVTables;              /* copy the vtables of the classes listed in CLASSES_TO_VTABLE_CACHE into fastPool */
    struct igStringTableView *vtableClassNames; /* the class names of that section */
    int f108;
    struct igObject *retainedObject;     /* released at shut-down */
    unsigned char useGlobalEventTracker;
    unsigned char saveEventTrackerOnExit;     /* MemoryContext::vfunc_56 runs at exit */
    unsigned char showLeaksOnExit;
    unsigned char showMemoryStatisticsOnExit;
    unsigned char showObjectStatisticsOnExit;
    unsigned char reportHeaderVersionMismatch; /* igObjectSystem_CheckHeaderVersion reports a mismatch only when 1 */
    unsigned char warnOnDllDateMismatch;
    char unknown123[1];
    void *eventTrackerInitialCapacity;
    int eventTrackerEventTypeFilter;
    int eventTrackerMarkerTypeFilter;
    int eventTrackerNotificationTypeFilter;
    int eventTrackerNotificationCodeFilter;
    char memoryEventFormat[128];
    char markerEventFormat[128];
    char notificationEventFormat[128];
    char eventTrackerFileName[128];
    char systemPoolEventTrackerFileName[128];
    char symbolsFileName[128];
    int stringPoolStatisticsLevel;
    int vtableProbeOffset;        /* zero: the EnsureRegistered probes read the vtable word through it */
#ifdef __cplusplus
    igStringRef rootPath;         /* "IG_ROOT" from the environment */
    igStringRef basePath;
#else
    char *rootPath;               /* "IG_ROOT" from the environment (an igStringRef in C++) */
    char *basePath;
#endif
#ifdef __cplusplus
    /* igMemoryPoolContextInfo_ConfigureEventTracking reads these two through calls: as plain member reads their locals take other saved registers. */
    struct igMemoryPoolView *getSystemPool() { return systemPool; }
    int getConfigRegistry() { return (int)configRegistry; }
#endif
};

#ifdef __cplusplus
extern "C" {
#endif

extern struct ObjectSystemView *g_objectSystem;

void igObjectSystem_Acquire(int headerVersion);
void igObjectSystem_Release(void);
void igObjectSystem_SetIniText(const char *text);

#ifdef __cplusplus
}
#endif

#endif
