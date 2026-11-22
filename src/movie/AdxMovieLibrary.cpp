#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/support/ClassRegistration.h"
#include "dw4/audio/igAdx.h"
#include "dw4/audio/igAdxAfsFileList.h"
#include "dw4/audio/igAdxAudio.h"
#include "dw4/audio/igAdxFile.h"
#include "dw4/movie/igCriMovieCodec.h"
#include "dw4/movie/igCriMovieData.h"
#include "dw4/insight/igInsightPlugin.h"
#include "dw4/movie/igMovieCodec.h"
#include "dw4/movie/igMovieCodecList.h"
#include "dw4/movie/igMovieInfo.h"
#include "dw4/movie/igMovieInfoList.h"
#include "dw4/movie/igMovieManager.h"
#include "dw4/movie/igMoviePlugin.h"
#include "dw4/movie/igMovieRenderer.h"
#include "dw4/movie/igTextureBindAttrList.h"

#pragma push
#pragma readonly_strings on
static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }

class igMemoryPoolView;
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igEnumMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igMetaEnum.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igRawRefMetaField.h"
#include "dw4/core/igShortMetaField.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/core/igStructMetaField.h"
#include "dw4/core/igUnsignedLongMetaField.h"
#include "dw4/audio/igAudioContext.h"
#include "dw4/gfx/igVisualContext.h"
#include "dw4/core/igObject.h"
#include "dw4/gui/igRendererOrderedList.h"

extern "C" void AdxMovieLibrary_MarkRegistered(void);
extern "C" void *igAdx_GetMetaObject(void);
extern "C" int igAdx_GetVTable(void);
#include "dw4/core/igMetaObject.h"
extern "C" void igAdx_EnsureRegistered(void);
extern "C" CallbackArray *igAdx_Register(void);
extern "C" void igAdx_GetMetaObjectFunction(void);
extern "C" void igAdx_InitFields(void);
extern "C" void igAdx_StaticInitCallback(void);
extern "C" void igAdx_ExitCallback(void);
#include "dw4/core/igMemoryPoolContext.h"
extern "C" void *igAdxAfsFileList_GetMetaObject(void);
extern "C" int igAdxAfsFileList_GetVTable(void);
#include "dw4/core/igObjectList.h"
extern "C" CallbackArray *igAdxAfsFileList_Register(void);
extern "C" void igAdxAfsFileList_GetMetaObjectFunction(void);
extern "C" void *igAdxAfsFile_GetMetaObject(void);
#include "dw4/core/StringPool.h"
extern "C" int igAdxAfsFile_GetVTable(void);
extern "C" void igAdxAfsFile_EnsureRegistered(void);
extern "C" CallbackArray *igAdxAfsFile_Register(void);
extern "C" void igAdxAfsFile_GetMetaObjectFunction(void);
extern "C" igMetaObject *igFileName_GetPublishedMetaObject(void);
extern "C" void igAdxAfsFile_InitFields(void);
extern "C" void *igFileNameList_GetMetaObject(void);
extern "C" int igFileNameList_GetVTable(void);
extern "C" void igFileNameList_EnsureRegistered(void);
extern "C" CallbackArray *igFileNameList_Register(void);
extern "C" void igFileNameList_GetMetaObjectFunction(void);
extern "C" void *igFileName_GetMetaObject(void);
extern "C" int igFileName_GetVTable(void);
extern "C" void igFileName_EnsureRegistered(void);
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igFile.h"
extern "C" CallbackArray *igFileName_Register(void);
extern "C" void igFileName_GetMetaObjectFunction(void);
extern "C" void igFileName_InitFields(void);
extern "C" void *igAdxFile_GetMetaObject(void);
extern "C" int igAdxFile_GetVTable(void);
extern "C" void igAdxFile_EnsureRegistered(void);
extern "C" CallbackArray *igAdxFile_Register(void);
extern "C" void igAdxFile_GetMetaObjectFunction(void);
extern "C" void igAdxFile_InitFields(void);
extern "C" void igAdxFile_StaticInitCallback(void);
extern "C" void igAdxFile_ExitCallback(void);
extern "C" void *igAdxAudio_GetMetaObject(void);
extern "C" int igAdxAudio_GetVTable(void);
extern "C" CallbackArray *igAdxAudio_Register(void);
extern "C" void igAdxAudio_GetMetaObjectFunction(void);
extern "C" void igAdxAudio_InitFields(void);
extern "C" igMetaObject *igMovieCodecList_GetOrCreateMetaObject(void);
extern "C" void *igMovieCodecList_GetMetaObject(void);
extern "C" int igMovieCodecList_GetVTable(void);
extern "C" void igMovieCodecList_EnsureRegistered(void);
extern "C" CallbackArray *igMovieCodecList_Register(void);
extern "C" void igMovieCodecList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igMovieCodec_GetOrCreateMetaObject(void);
extern "C" void *igMovieCodec_GetMetaObject(void);
extern "C" int igMovieCodec_GetVTable(void);
extern "C" void igMovieCodec_EnsureRegistered(void);
extern "C" CallbackArray *igMovieCodec_Register(void);
extern "C" void igMovieCodec_GetMetaObjectFunction(void);
extern "C" int igCriMovieCodec_GetVTable(void);
extern "C" void igCriMovieCodec_EnsureRegistered(void);
extern "C" CallbackArray *igCriMovieCodec_Register(void);
extern "C" void igCriMovieCodec_GetMetaObjectFunction(void);
extern "C" igMetaObject *igMovieCodec_GetPublishedMetaObject(void);
extern "C" void igCriMovieCodec_InitFields(void);
extern "C" int igCriMovieData_GetVTable(void);
extern "C" void igCriMovieData_EnsureRegistered(void);
extern "C" CallbackArray *igCriMovieData_Register(void);
extern "C" void igCriMovieData_GetMetaObjectFunction(void);
extern "C" void igCriMovieData_InitFields(void);
extern "C" igMetaObject *igMovieInfoList_GetOrCreateMetaObject(void);
extern "C" int igMovieInfoList_GetVTable(void);
extern "C" void igMovieInfoList_EnsureRegistered(void);
extern "C" CallbackArray *igMovieInfoList_Register(void);
extern "C" void igMovieInfoList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igTextureBindAttrList_GetOrCreateMetaObject(void);
extern "C" int igTextureBindAttrList_GetVTable(void);
extern "C" void igTextureBindAttrList_EnsureRegistered(void);
extern "C" CallbackArray *igTextureBindAttrList_Register(void);
extern "C" void igTextureBindAttrList_GetMetaObjectFunction(void);
extern "C" igMetaEnum *igMovieInfo_GetMovieStateMetaEnum(void);
extern "C" igMetaEnum *igMovieInfo_GetMovieTypeMetaEnum(void);
extern "C" void *igMovieInfo_GetMetaObject(void);
extern "C" int igMovieInfo_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_igTextureBindAttrList_Destruct(igSmartPointer<igObject> *self, short flag);
extern "C" igSmartPointer<igObject> *igSmartPointer_igMovieCodec_Destruct(igSmartPointer<igObject> *self, short flag);
extern "C" void igMovieInfo_EnsureRegistered(void);
extern "C" CallbackArray *igMovieInfo_Register(void);
extern "C" void igMovieInfo_GetMetaObjectFunction(void);
#include "dw4/attrs/igTextureList.h"
#include "dw4/gfx/igImage.h"
#include "dw4/scenegraph/igSceneInfo.h"
#include "dw4/gfx/GfxMetaEnums.h"
extern "C" void igMovieInfo_InitFields(void);
extern "C" igMetaObject *igMovieRenderer_GetOrCreateMetaObject(void);
extern "C" void *igMovieRenderer_GetMetaObject(void);
extern "C" int igMovieRenderer_GetVTable(void);
extern "C" void igMovieRenderer_EnsureRegistered(void);
#include "dw4/gui/igRenderer.h"
extern "C" CallbackArray *igMovieRenderer_Register(void);
extern "C" void igMovieRenderer_GetMetaObjectFunction(void);
extern "C" void igMovieRenderer_InitFields(void);
extern "C" void *igMovieManager_GetMetaObject(void);
#include "dw4/insight/igInfoManager.h"
extern "C" int igMovieManager_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_igMovieCodecList_Destruct(igSmartPointer<igObject> *self, short flag);
extern "C" CallbackArray *igMovieManager_Register(void);
extern "C" void igMovieManager_GetMetaObjectFunction(void);
extern "C" void igMovieManager_InitFields(void);
extern "C" void *igMoviePlugin_GetMetaObject(void);
extern "C" int igMoviePlugin_GetVTable(void);
extern "C" void igMoviePlugin_EnsureRegistered(void);
extern "C" CallbackArray *igMoviePlugin_Register(void);
extern "C" void igMoviePlugin_GetMetaObjectFunction(void);
extern "C" void igMoviePlugin_InitFields(void);
extern "C" int igInsightPlugin_GetMeta(void);
extern "C" igMetaObject *igMovieInfo_GetMeta(void);
extern "C" igMetaObject *igTextureBindAttrList_GetMeta(void);
extern "C" igMetaObject *igTextureBindAttrList_GetElementMeta(void);
extern "C" igMetaObject *igMovieInfoList_GetMeta(void);
extern "C" igMetaObject *igMovieInfoList_GetElementMeta(void);
extern "C" igMetaObject *igMovieCodecList_GetMeta(void);
extern "C" igMetaObject *igMovieCodecList_GetElementMeta(void);
extern "C" igMetaObject *igFileNameList_GetMeta(void);
extern "C" igMetaObject *igFileNameList_GetElementMeta(void);
extern "C" igMetaObject *igAdxAfsFile_GetMeta(void);
extern "C" igMetaObject *igFileName_GetMeta(void);
extern "C" igMetaObject *igAdxAfsFileList_GetMeta(void);
extern "C" igMetaObject *igAdxAfsFileList_GetElementMeta(void);
extern "C" unsigned char g_AdxMovieLibrary_registered;
extern "C" int g_igAdx_vtable[4];
#include "dw4/core/igObjectSystem.h"
struct igMetaObject_334510;
extern "C" igMetaObject *g_igAdxAfsFileList_metaObject;
extern "C" int g_igAdxAfsFileList_vtable[4];
struct igMetaObject_334710;
extern "C" igMetaObject *g_igAdxAfsFile_metaObject;
extern "C" int g_igAdxAfsFile_vtable[4];
extern "C" int g_igFileName_vtable[4];
extern "C" igMetaObject *g_igFileNameList_metaObject;
extern "C" int g_igFileNameList_vtable[4];
extern "C" igMetaObject *g_igFileName_metaObject;
extern "C" int g_igAdxFile_vtable[4];
extern "C" int g_igAdxAudio_vtable[4];
extern "C" igMetaObject *g_igMovieCodecList_metaObject;
extern "C" int g_igMovieCodecList_vtable[4];
extern "C" int g_igMovieCodec_vtable[4];
extern "C" igMovieCodec *igMovieCodec_Destroy(igMovieCodec *self, short flags);
extern "C" igMetaObject *igCriMovieCodec_GetMetaObject(void);
extern "C" int g_igCriMovieCodec_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_igAudioContext_Destruct(igSmartPointer<igObject> *self, short flag);
extern "C" igMetaObject *igCriMovieData_GetMetaObject(void);
extern "C" int g_igCriMovieData_vtable[4];
extern "C" igMetaObject *g_igMovieInfoList_metaObject;
extern "C" igMetaObject *igMovieInfoList_GetMetaObject(void);
extern "C" int g_igMovieInfoList_vtable[4];
extern "C" igMetaObject *g_igTextureBindAttrList_metaObject;
extern "C" igMetaObject *igTextureBindAttrList_GetMetaObject(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
extern "C" int g_igTextureBindAttrList_vtable[4];
extern "C" int g_igMovieInfo_vtable[4];
#include "dw4/core/igInfo.h"
extern "C" int g_igMovieRenderer_vtable[4];
extern "C" int g_igMovieManager_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_igMovieInfoList_Destruct(igSmartPointer<igObject> *self, short flag);
extern "C" igSmartPointer<igObject> *igSmartPointer_igMovieRenderer_Destruct(igSmartPointer<igObject> *self, short flag);
extern "C" int g_igMoviePlugin_vtable[4];
#include "dw4/attrs/igTextureBindAttr.h"
#include "dw4/core/igNamedObjectList.h"

unsigned char g_AdxMovieLibrary_registered;

void AdxMovieLibrary_RegisterClasses(void) {
    igFileName_EnsureRegistered();
    igFileNameList_EnsureRegistered();
    igAdxAfsFile_EnsureRegistered();
    igAdxAfsFileList_EnsureRegistered();
    igAdx_EnsureRegistered();
    igAdxFile_EnsureRegistered();
    igAdxAudio_EnsureRegistered();
    igMovieCodec_EnsureRegistered();
    igMovieCodecList_EnsureRegistered();
    igCriMovieData_EnsureRegistered();
    igCriMovieCodec_EnsureRegistered();
    igMovieInfo_EnsureRegistered();
    igTextureBindAttrList_EnsureRegistered();
    igMovieInfoList_EnsureRegistered();
    igMovieManager_EnsureRegistered();
    igMovieRenderer_EnsureRegistered();
    igMoviePlugin_EnsureRegistered();
}

void AdxMovieLibrary_MarkRegistered(void) {
    if (g_AdxMovieLibrary_registered == 0) {
        g_AdxMovieLibrary_registered = 1;
    }
}

igMetaObject *g_igAdx_metaObject;

void *igAdx_GetMetaObject(void) {
    igMetaObject *g = g_igAdx_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igAdx_EnsureRegistered();
    }
    return g_igAdx_metaObject;
}

int igAdx_GetVTable(void) {
    igObject obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igAdx_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAdx_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAdx_Register);
}

CallbackArray *igAdx_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAdx_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igAdx_GetMetaObjectFunction,
        "igAdx",
        8, /* instance size */
        igAdx_GetVTable,
        igAdx_InitFields,
        igAdx_StaticInitCallback, /* extra callback item */
        0 /* callback list */
    );
}

void igAdx_GetMetaObjectFunction(void)
{
    igAdx_GetMetaObject();
}

void igAdx_InitFields(void)
{
    igMetaObject_AddExitCallback((int)igAdx_ExitCallback);
}

void igAdx_StaticInitCallback(void)
{
    igAdx_CreateScratchString();
}

void igAdx_ExitCallback(void)
{
    igAdx_Shutdown();
}

igMetaObject *g_igAdxAfsFileList_metaObject;

igMetaObject *igAdxAfsFileList_GetOrCreateMetaObject(void) {
    if (g_igAdxAfsFileList_metaObject == 0) {
        g_igAdxAfsFileList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAdxAfsFileList_metaObject;
}

void *igAdxAfsFileList_GetMetaObject(void) {
    bool ok;
    if (g_igAdxAfsFileList_metaObject == 0) goto make;
    ok = !!(g_igAdxAfsFileList_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    igAdxAfsFileList_EnsureRegistered();
done:;
    return g_igAdxAfsFileList_metaObject;
}

int igAdxAfsFileList_GetVTable(void) {
    igAdxAfsFileList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igAdxAfsFileList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAdxAfsFileList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAdxAfsFileList_Register);
}

static igMetaObjectCallback g_igAdxAfsFileList_callbackList[] = { igAdxAfsFile_EnsureRegistered, 0 };

CallbackArray *igAdxAfsFileList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAdxAfsFileList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igAdxAfsFileList_GetMetaObjectFunction,
        "igAdxAfsFileList",
        0x14, /* instance size */
        igAdxAfsFileList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAdxAfsFileList_callbackList /* callback list */
    );
}

void igAdxAfsFileList_GetMetaObjectFunction(void)
{
    igAdxAfsFileList_GetMetaObject();
}

igMetaObject *g_igAdxAfsFile_metaObject;
igMetaField *g_igAdxAfsFile_ptNumberMetaField;
igMetaField *g_igAdxAfsFile_fileNumberMetaField;

void *igAdxAfsFile_GetMetaObject(void) {
    igMetaObject *g = g_igAdxAfsFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igAdxAfsFile_EnsureRegistered();
    }
    return g_igAdxAfsFile_metaObject;
}

int igAdxAfsFile_GetVTable(void) {
    igAdxAfsFile obj;
    int vtable;
    int *pathListRef;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igFileName_vtable[0];
    pathListRef = &obj._pathList;
    *pathListRef = 0;
    *(int **)&obj._vtable = &g_igAdxAfsFile_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igFileName_vtable[0];
    if (pathListRef != 0) {
        igObject::release((igObject *)*pathListRef);
    }
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void igAdxAfsFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAdxAfsFile_Register);
}

CallbackArray *igAdxAfsFile_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAdxAfsFile_metaObject,
        igFileName_Register,
        igFileName_GetPublishedMetaObject,
        igAdxAfsFile_GetMetaObjectFunction,
        "igAdxAfsFile",
        0x14, /* instance size */
        igAdxAfsFile_GetVTable,
        igAdxAfsFile_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igAdxAfsFile_GetMetaObjectFunction(void)
{
    igAdxAfsFile_GetMetaObject();
}

igMetaObject *igFileName_GetPublishedMetaObject(void) {
    return g_igFileName_metaObject;
}

static FieldFactory g_igAdxAfsFile_ctorTable[] = {
    igShortMetaField_Create,
    igShortMetaField_Create,
};
static const char *g_igAdxAfsFile_fieldTable[] = {
    "_ptNumber",
    "_fileNumber",
};
static igMetaField **g_igAdxAfsFile_fieldHandles[] = {
    &g_igAdxAfsFile_ptNumberMetaField,
    &g_igAdxAfsFile_fileNumberMetaField,
};
static int g_igAdxAfsFile_fieldOffsets[] = {
    16,
    18,
};

void igAdxAfsFile_InitFields(void) {
    int firstField;
    void *meta;

    meta = g_igAdxAfsFile_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAdxAfsFile_ctorTable, 2);
    igMetaObject_NameFields((igMetaObject *)meta, g_igAdxAfsFile_fieldTable, g_igAdxAfsFile_fieldHandles, g_igAdxAfsFile_fieldOffsets, firstField);
}

igMetaObject *g_igFileNameList_metaObject;

void *igFileNameList_GetMetaObject(void) {
    unsigned char b;
    if (g_igFileNameList_metaObject != 0) {
        b = (g_igFileNameList_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    igFileNameList_EnsureRegistered();
done:
    return g_igFileNameList_metaObject;
}

int igFileNameList_GetVTable(void) {
    igFileNameList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igFileNameList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igFileNameList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFileNameList_Register);
}

static igMetaObjectCallback g_igFileNameList_callbackList[] = { igFileName_EnsureRegistered, 0 };

CallbackArray *igFileNameList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFileNameList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igFileNameList_GetMetaObjectFunction,
        "igFileNameList",
        0x14, /* instance size */
        igFileNameList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFileNameList_callbackList /* callback list */
    );
}

void igFileNameList_GetMetaObjectFunction(void)
{
    igFileNameList_GetMetaObject();
}

igMetaObject *g_igFileName_metaObject;
igMetaField *g_igFileName_pathListMetaField;

void *igFileName_GetMetaObject(void) {
    igMetaObject *g = g_igFileName_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igFileName_EnsureRegistered();
    }
    return g_igFileName_metaObject;
}

int igFileName_GetVTable(void) {
    igFileName obj;
    int vtable;
    int *nameRef;
    int *pathListRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igFileName_vtable[0];
    pathListRef = &obj._pathList;
    *pathListRef = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igFileName_vtable[0];
    if (pathListRef != 0) {
        igObject::release((igObject *)*pathListRef);
    }
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void igFileName_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFileName_Register);
}

static igMetaObjectCallback g_igFileName_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

CallbackArray *igFileName_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFileName_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        igFileName_GetMetaObjectFunction,
        "igFileName",
        0x10, /* instance size */
        igFileName_GetVTable,
        igFileName_InitFields,
        0, /* extra callback item */
        g_igFileName_callbackList /* callback list */
    );
}

void igFileName_GetMetaObjectFunction(void)
{
    igFileName_GetMetaObject();
}

static FieldFactory g_igFileName_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igFileName_fieldTable[] = {
    "_pathList",
};
static igMetaField **g_igFileName_fieldHandles[] = {
    &g_igFileName_pathListMetaField,
};
static int g_igFileName_fieldOffsets[] = {
    12,
};

void igFileName_InitFields(void) {
    int firstField;
    void *pathListField;
    void *meta;

    meta = g_igFileName_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igFileName_ctorTable, 1);
    pathListField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField));
    ((igObjectRefMetaField *)pathListField)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igFileName_fieldTable, g_igFileName_fieldHandles, g_igFileName_fieldOffsets, firstField);
}

igMetaObject *g_igAdxFile_metaObject;
igMetaField *g_igAdxFile_bIsOpenMetaField;
igMetaField *g_igAdxFile_pBufferMetaField;
igMetaField *g_igAdxFile_pBufferPtrMetaField;
igMetaField *g_igAdxFile_pTmpBufferMetaField;
igMetaField *g_igAdxFile_bUseAsyncMetaField;
igMetaField *g_igAdxFile_bUseAlchemyAsyncMetaField;
igMetaField *g_igAdxFile_bUseBufferMetaField;
igMetaField *g_igAdxFile_bBufferFilledMetaField;
igMetaField *g_igAdxFile_iBufferSizeMetaField;
igMetaField *g_igAdxFile_iBufferPosMetaField;
igMetaField *g_igAdxFile_iSeekPositionMetaField;
igMetaField *g_igAdxFile_iFileSizeMetaField;
igMetaField *g_igAdxFile_iSectorSizeMetaField;
igMetaField *g_igAdxFile_lSleepTimeMetaField;

igAdxFile *igAdxFile_Create(int allocator) {
    igAdxFile_EnsureRegistered();
    return (igAdxFile *)igMetaObject_CreateInstance(g_igAdxFile_metaObject, (igMemoryPoolView *)allocator);
}

void *igAdxFile_GetMetaObject(void) {
    igMetaObject *g = g_igAdxFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igAdxFile_EnsureRegistered();
    }
    return g_igAdxFile_metaObject;
}

int igAdxFile_GetVTable(void) {
    igAdxFile obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._fileName = 0;
    obj._completeFilename = 0;
    *(int **)&obj._vtable = &g_igAdxFile_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igAdxFile_vtable[0];
    igFile_Destroy((igFile *)&obj, 0);
    return vtable;
}

void igAdxFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAdxFile_Register);
}

CallbackArray *igAdxFile_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAdxFile_metaObject,
        Gap::Core::igFile::arkRegisterInternal,
        Gap::Core::igFile::getClassMeta,
        igAdxFile_GetMetaObjectFunction,
        "igAdxFile",
        0x68, /* instance size */
        igAdxFile_GetVTable,
        igAdxFile_InitFields,
        igAdxFile_StaticInitCallback, /* extra callback item */
        0 /* callback list */
    );
}

void igAdxFile_GetMetaObjectFunction(void)
{
    igAdxFile_GetMetaObject();
}

static FieldFactory g_igAdxFile_ctorTable[] = {
    igBoolMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igRawRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igUnsignedLongMetaField_Create,
};
static const char *g_igAdxFile_fieldTable[] = {
    "_bIsOpen",
    "_pBuffer",
    "_pBufferPtr",
    "_pTmpBuffer",
    "_bUseAsync",
    "_bUseAlchemyAsync",
    "_bUseBuffer",
    "_bBufferFilled",
    "_iBufferSize",
    "_iBufferPos",
    "_iSeekPosition",
    "_iFileSize",
    "_iSectorSize",
    "_lSleepTime",
};
static igMetaField **g_igAdxFile_fieldHandles[] = {
    &g_igAdxFile_bIsOpenMetaField,
    &g_igAdxFile_pBufferMetaField,
    &g_igAdxFile_pBufferPtrMetaField,
    &g_igAdxFile_pTmpBufferMetaField,
    &g_igAdxFile_bUseAsyncMetaField,
    &g_igAdxFile_bUseAlchemyAsyncMetaField,
    &g_igAdxFile_bUseBufferMetaField,
    &g_igAdxFile_bBufferFilledMetaField,
    &g_igAdxFile_iBufferSizeMetaField,
    &g_igAdxFile_iBufferPosMetaField,
    &g_igAdxFile_iSeekPositionMetaField,
    &g_igAdxFile_iFileSizeMetaField,
    &g_igAdxFile_iSectorSizeMetaField,
    &g_igAdxFile_lSleepTimeMetaField,
};
static int g_igAdxFile_fieldOffsets[] = {
    44,
    48,
    52,
    56,
    60,
    61,
    62,
    63,
    64,
    68,
    72,
    76,
    80,
    88,
};

void igAdxFile_InitFields(void) {
    int firstField;
    void *meta;

    meta = g_igAdxFile_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAdxFile_ctorTable, 0xE);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 4)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 5)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 6)))->setDefault(1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 8)))->setDefault(0x20000);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0xC)))->setDefault(0x800);
    ((Gap::Core::igUnsignedLongMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0xD)))->setDefault(0xFE502A);
    igMetaObject_NameFields((igMetaObject *)meta, g_igAdxFile_fieldTable, g_igAdxFile_fieldHandles, g_igAdxFile_fieldOffsets, firstField);
    g_igAdxFile_metaObject->_writeProxy = (int)(&Gap::Core::igFile::getClassMetaSafe);
    igMetaObject_AddExitCallback((int)&igAdxFile_ExitCallback);
}

void igAdxFile_StaticInitCallback(void)
{
    igAdxFile_StaticInitialize();
}

void igAdxFile_ExitCallback(void)
{
    igAdxFile_StaticFinalize();
}

igMetaObject *g_igAdxAudio_metaObject;
igMetaField *g_igAdxAudio_pWorkAreaMetaField;
igMetaField *g_igAdxAudio_iWorkSizeMetaField;
igMetaField *g_igAdxAudio_iMaxHandlesMetaField;
igMetaField *g_igAdxAudio_iMaxChannelsMetaField;
igMetaField *g_igAdxAudio_iTypeMetaField;
igMetaField *g_igAdxAudio_iMaxStreamsMetaField;
igMetaField *g_igAdxAudio_iMaxFrequencyMetaField;
igMetaField *g_igAdxAudio_bIsInitializedMetaField;
igMetaField *g_igAdxAudio_filenameMetaField;

igAdxAudio *igAdxAudio_Create(int allocator) {
    igAdxAudio_EnsureRegistered();
    return (igAdxAudio *)igMetaObject_CreateInstance(g_igAdxAudio_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igAdxAudio_GetOrCreateMetaObject(void) {
    if (g_igAdxAudio_metaObject == 0) {
        g_igAdxAudio_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAdxAudio_metaObject;
}

void *igAdxAudio_GetMetaObject(void) {
    igMetaObject *g = g_igAdxAudio_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igAdxAudio_EnsureRegistered();
    }
    return g_igAdxAudio_metaObject;
}

int igAdxAudio_GetVTable(void) {
    igAdxAudio obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igAdxAudio_vtable[0];
    obj._filename = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igAdxAudio_vtable[0];
    if (&obj._filename != 0) {
        releaseString((const char *)obj._filename);
    }
    return vtable;
}

void igAdxAudio_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAdxAudio_Register);
}

CallbackArray *igAdxAudio_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAdxAudio_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igAdxAudio_GetMetaObjectFunction,
        "igAdxAudio",
        0x30, /* instance size */
        igAdxAudio_GetVTable,
        igAdxAudio_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igAdxAudio_GetMetaObjectFunction(void)
{
    igAdxAudio_GetMetaObject();
}

static FieldFactory g_igAdxAudio_ctorTable[] = {
    igRawRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_igAdxAudio_fieldTable[] = {
    "_pWorkArea",
    "_iWorkSize",
    "_iMaxHandles",
    "_iMaxChannels",
    "_iType",
    "_iMaxStreams",
    "_iMaxFrequency",
    "_bIsInitialized",
    "_filename",
};
static igMetaField **g_igAdxAudio_fieldHandles[] = {
    &g_igAdxAudio_pWorkAreaMetaField,
    &g_igAdxAudio_iWorkSizeMetaField,
    &g_igAdxAudio_iMaxHandlesMetaField,
    &g_igAdxAudio_iMaxChannelsMetaField,
    &g_igAdxAudio_iTypeMetaField,
    &g_igAdxAudio_iMaxStreamsMetaField,
    &g_igAdxAudio_iMaxFrequencyMetaField,
    &g_igAdxAudio_bIsInitializedMetaField,
    &g_igAdxAudio_filenameMetaField,
};
static int g_igAdxAudio_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

void igAdxAudio_InitFields(void) {
    int firstField;
    void *meta;

    meta = g_igAdxAudio_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAdxAudio_ctorTable, 9);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 2)))->setDefault(4);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 3)))->setDefault(2);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 5)))->setDefault(4);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 6)))->setDefault(0xBB80);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 8)))->setDefault(0);
    igMetaObject_NameFields((igMetaObject *)meta, g_igAdxAudio_fieldTable, g_igAdxAudio_fieldHandles, g_igAdxAudio_fieldOffsets, firstField);
}

igMetaObject *g_igMovieCodecList_metaObject;

igMovieCodecList *igMovieCodecList_Create(int allocator) {
    igMovieCodecList_EnsureRegistered();
    return (igMovieCodecList *)igMetaObject_CreateInstance(g_igMovieCodecList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igMovieCodecList_GetOrCreateMetaObject(void) {
    if (g_igMovieCodecList_metaObject == 0) {
        g_igMovieCodecList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMovieCodecList_metaObject;
}

void *igMovieCodecList_GetMetaObject(void) {
    igMetaObject *g = g_igMovieCodecList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igMovieCodecList_EnsureRegistered();
    }
    return g_igMovieCodecList_metaObject;
}

int igMovieCodecList_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader((igObject *)tmp);
    tmp[0] = (int)&g_igMovieCodecList_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igMovieCodecList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMovieCodecList_Register);
}

static igMetaObjectCallback g_igMovieCodecList_callbackList[] = { igMovieCodec_EnsureRegistered, 0 };

CallbackArray *igMovieCodecList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieCodecList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igMovieCodecList_GetMetaObjectFunction,
        "igMovieCodecList",
        0x14, /* instance size */
        igMovieCodecList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMovieCodecList_callbackList /* callback list */
    );
}

void igMovieCodecList_GetMetaObjectFunction(void)
{
    igMovieCodecList_GetMetaObject();
}

igMetaObject *g_igMovieCodec_metaObject;

igMetaObject *igMovieCodec_GetOrCreateMetaObject(void) {
    if (g_igMovieCodec_metaObject == 0) {
        g_igMovieCodec_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMovieCodec_metaObject;
}

void *igMovieCodec_GetMetaObject(void) {
    igMetaObject *g = g_igMovieCodec_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igMovieCodec_EnsureRegistered();
    }
    return g_igMovieCodec_metaObject;
}

int igMovieCodec_GetVTable(void) {
    igMovieCodec obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_igMovieCodec_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

igMovieCodec *igMovieCodec_Destroy(igMovieCodec *self, short flags) {
    if (self != 0) {
        *(int **)&self->_vtable = &g_igMovieCodec_vtable[0];
        if (self != 0) {
            *(int **)&self->_vtable = &g_igNamedObject_vtable[0];
            if (&self->_name != 0) {
                releaseString((const char *)self->_name);
            }
        }
        if (flags > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void igMovieCodec_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMovieCodec_Register);
}

CallbackArray *igMovieCodec_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieCodec_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        igMovieCodec_GetMetaObjectFunction,
        "igMovieCodec",
        0xc, /* instance size */
        igMovieCodec_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMovieCodec_GetMetaObjectFunction(void)
{
    igMovieCodec_GetMetaObject();
}

igMetaObject *g_igCriMovieCodec_metaObject;
igMetaField *g_igCriMovieCodec_initializedMetaField;
igMetaField *g_igCriMovieCodec_visualContextMetaField;
igMetaField *g_igCriMovieCodec_audioContextMetaField;

igMetaObject *igCriMovieCodec_GetMetaObject(void)
{
    igMetaObject *g = g_igCriMovieCodec_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        igCriMovieCodec_EnsureRegistered();
    return g_igCriMovieCodec_metaObject;
}

int igCriMovieCodec_GetVTable(void) {
    igCriMovieCodec obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    *(int **)&obj._vtable = &g_igCriMovieCodec_vtable[0];
    obj._visualContext = 0;
    obj._audioContext = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igCriMovieCodec_vtable[0];
    igSmartPointer_igAudioContext_Destruct((igSmartPointer<igObject> *)&obj._audioContext, (short)(-1));
    igSmartPointer_igVisualContext_Destruct((igSmartPointer<igObject> *)&obj._visualContext, -1);
    igMovieCodec_Destroy((igMovieCodec *)&obj, (long long)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igAudioContext_Destruct(igSmartPointer<igObject> *self, short flag) {
    if (self != 0) {
        igObject *object = self->p;
        igObject::release(object);
        if (flag > 0) operator delete(self);
    }
    return self;
}

void igCriMovieCodec_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCriMovieCodec_Register);
}

static igMetaObjectCallback g_igCriMovieCodec_callbackList[] = { igVisualContext_EnsureRegistered, igAudioContext_EnsureRegistered, 0 };

CallbackArray *igCriMovieCodec_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCriMovieCodec_metaObject,
        igMovieCodec_Register,
        igMovieCodec_GetPublishedMetaObject,
        igCriMovieCodec_GetMetaObjectFunction,
        "igCriMovieCodec",
        0x18, /* instance size */
        igCriMovieCodec_GetVTable,
        igCriMovieCodec_InitFields,
        0, /* extra callback item */
        g_igCriMovieCodec_callbackList /* callback list */
    );
}

void igCriMovieCodec_GetMetaObjectFunction(void)
{
    igCriMovieCodec_GetMetaObject();
}

igMetaObject *igMovieCodec_GetPublishedMetaObject(void) {
    return g_igMovieCodec_metaObject;
}

static FieldFactory g_igCriMovieCodec_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igCriMovieCodec_fieldTable[] = {
    "_initialized",
    "_visualContext",
    "_audioContext",
};
static igMetaField **g_igCriMovieCodec_fieldHandles[] = {
    &g_igCriMovieCodec_initializedMetaField,
    &g_igCriMovieCodec_visualContextMetaField,
    &g_igCriMovieCodec_audioContextMetaField,
};
static int g_igCriMovieCodec_fieldOffsets[] = {
    12,
    16,
    20,
};

void igCriMovieCodec_InitFields(void) {
    int firstField;
    igObjectRefMetaField *visualContextField;
    igObjectRefMetaField *audioContextField;
    void *meta;
    igMetaField *initializedField;

    meta = g_igCriMovieCodec_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igCriMovieCodec_ctorTable, 3);
    initializedField = (igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField);
    initializedField->_persistent = 0;
    visualContextField = (igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 1);
    visualContextField->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    visualContextField->_persistent = 0;
    audioContextField = (igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 2);
    audioContextField->_metaObject = (int)igAudioContext_GetOrCreateMetaObject();
    audioContextField->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igCriMovieCodec_fieldTable, g_igCriMovieCodec_fieldHandles, g_igCriMovieCodec_fieldOffsets, firstField);
}

igMetaObject *g_igCriMovieData_metaObject;
igMetaField *g_igCriMovieData_mwplyMetaField;
igMetaField *g_igCriMovieData_cprmbufMetaField;
igMetaField *g_igCriMovieData_adxtMetaField;
igMetaField *g_igCriMovieData_adxworkMetaField;
igMetaField *g_igCriMovieData_macroFunctionMetaField;

igCriMovieData *igCriMovieData_Create(int allocator) {
    igCriMovieData_EnsureRegistered();
    return (igCriMovieData *)igMetaObject_CreateInstance(g_igCriMovieData_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igCriMovieData_GetMetaObject(void) {
    igMetaObject *g = g_igCriMovieData_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        igCriMovieData_EnsureRegistered();
    return g_igCriMovieData_metaObject;
}

int igCriMovieData_GetVTable(void) {
    igCriMovieData obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igCriMovieData_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igCriMovieData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCriMovieData_Register);
}

CallbackArray *igCriMovieData_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCriMovieData_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igCriMovieData_GetMetaObjectFunction,
        "igCriMovieData",
        0x1c, /* instance size */
        igCriMovieData_GetVTable,
        igCriMovieData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igCriMovieData_GetMetaObjectFunction(void)
{
    igCriMovieData_GetMetaObject();
}

static FieldFactory g_igCriMovieData_ctorTable[] = {
    igStructMetaField_Create,
    igRawRefMetaField_Create,
    igStructMetaField_Create,
    igRawRefMetaField_Create,
    igStructMetaField_Create,
};
static const char *g_igCriMovieData_fieldTable[] = {
    "_mwply",
    "_cprmbuf",
    "_adxt",
    "_adxwork",
    "_macroFunction",
};
static igMetaField **g_igCriMovieData_fieldHandles[] = {
    &g_igCriMovieData_mwplyMetaField,
    &g_igCriMovieData_cprmbufMetaField,
    &g_igCriMovieData_adxtMetaField,
    &g_igCriMovieData_adxworkMetaField,
    &g_igCriMovieData_macroFunctionMetaField,
};
static int g_igCriMovieData_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
};

void igCriMovieData_InitFields(void) {
    int firstField;
    void *mwplyField;
    void *adxtField;
    void *macroFunctionField;
    void *meta;

    meta = g_igCriMovieData_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igCriMovieData_ctorTable, 5);
    mwplyField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField));
    ((igMetaField *)mwplyField)->_size = 4;
    ((igMetaField *)mwplyField)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 1))->_persistent = 0;
    adxtField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 2));
    ((igMetaField *)adxtField)->_size = 4;
    ((igMetaField *)adxtField)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 3))->_persistent = 0;
    macroFunctionField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 4));
    ((igMetaField *)macroFunctionField)->_size = 4;
    ((igMetaField *)macroFunctionField)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igCriMovieData_fieldTable, g_igCriMovieData_fieldHandles, g_igCriMovieData_fieldOffsets, firstField);
}

igMetaObject *g_igMovieInfoList_metaObject;

igMovieInfoList *igMovieInfoList_Create(int allocator) {
    igMovieInfoList_EnsureRegistered();
    return (igMovieInfoList *)igMetaObject_CreateInstance(g_igMovieInfoList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igMovieInfoList_GetOrCreateMetaObject(void) {
    if (g_igMovieInfoList_metaObject == 0) {
        g_igMovieInfoList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMovieInfoList_metaObject;
}

igMetaObject *igMovieInfoList_GetMetaObject(void) {
    igMetaObject *g = g_igMovieInfoList_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    igMovieInfoList_EnsureRegistered();
done:
    return g_igMovieInfoList_metaObject;
}

int igMovieInfoList_GetVTable(void) {
    igMovieInfoList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igMovieInfoList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igMovieInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMovieInfoList_Register);
}

static igMetaObjectCallback g_igMovieInfoList_callbackList[] = { igMovieInfo_EnsureRegistered, 0 };

CallbackArray *igMovieInfoList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieInfoList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igMovieInfoList_GetMetaObjectFunction,
        "igMovieInfoList",
        0x14, /* instance size */
        igMovieInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMovieInfoList_callbackList /* callback list */
    );
}

void igMovieInfoList_GetMetaObjectFunction(void)
{
    igMovieInfoList_GetMetaObject();
}

igMetaObject *g_igTextureBindAttrList_metaObject;

igTextureBindAttrList *igTextureBindAttrList_Create(int allocator) {
    igTextureBindAttrList_EnsureRegistered();
    return (igTextureBindAttrList *)igMetaObject_CreateInstance(g_igTextureBindAttrList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igTextureBindAttrList_GetOrCreateMetaObject(void) {
    if (g_igTextureBindAttrList_metaObject == 0) {
        g_igTextureBindAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureBindAttrList_metaObject;
}

igMetaObject *igTextureBindAttrList_GetMetaObject(void) {
    if (g_igTextureBindAttrList_metaObject == 0 || !isValid(g_igTextureBindAttrList_metaObject)) igTextureBindAttrList_EnsureRegistered();
    return g_igTextureBindAttrList_metaObject;
}

int igTextureBindAttrList_GetVTable(void) {
    igTextureBindAttrList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igTextureBindAttrList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureBindAttrList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureBindAttrList_Register);
}

static igMetaObjectCallback g_igTextureBindAttrList_callbackList[] = { Gap::Attrs::igTextureBindAttr::arkRegister, 0 };

CallbackArray *igTextureBindAttrList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureBindAttrList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igTextureBindAttrList_GetMetaObjectFunction,
        "igTextureBindAttrList",
        0x14, /* instance size */
        igTextureBindAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igTextureBindAttrList_callbackList /* callback list */
    );
}

void igTextureBindAttrList_GetMetaObjectFunction(void)
{
    igTextureBindAttrList_GetMetaObject();
}

static const char *g_igMovieInfo_movieStateNames[] = {
    "IG_MOVIE_PLAY",
    "IG_MOVIE_PAUSE",
    "IG_MOVIE_ENDED",
};
static int g_igMovieInfo_movieStateValues[] = {
    0,
    1,
    2,
};
igMetaEnum *g_igMovieInfo_movieStateMetaEnum;

igMetaEnum *igMovieInfo_GetMovieStateMetaEnum(void) {
    if (g_igMovieInfo_movieStateMetaEnum == 0) {
        g_igMovieInfo_movieStateMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_MOVIE_STATE", g_igMovieInfo_movieStateNames, g_igMovieInfo_movieStateValues, 3);
    }
    return g_igMovieInfo_movieStateMetaEnum;
}

static const char *g_igMovieInfo_movieTypeNames[] = {
    "IG_MOVIE_TYPE_DEFAULT",
    "IG_MOVIE_TYPE_VIDEO",
    "IG_MOVIE_TYPE_AUDIO",
    "IG_MOVIE_TYPE_BOTH",
};
static int g_igMovieInfo_movieTypeValues[] = {
    0,
    1,
    2,
    3,
};
igMetaEnum *g_igMovieInfo_movieTypeMetaEnum;

igMetaEnum *igMovieInfo_GetMovieTypeMetaEnum(void) {
    if (g_igMovieInfo_movieTypeMetaEnum == 0) {
        g_igMovieInfo_movieTypeMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_MOVIE_TYPE", g_igMovieInfo_movieTypeNames, g_igMovieInfo_movieTypeValues, 4);
    }
    return g_igMovieInfo_movieTypeMetaEnum;
}

igMetaObject *g_igMovieInfo_metaObject;
igMetaField *g_igMovieInfo_pathMetaField;
igMetaField *g_igMovieInfo_typeMetaField;
igMetaField *g_igMovieInfo_loopMetaField;
igMetaField *g_igMovieInfo_widthMetaField;
igMetaField *g_igMovieInfo_heightMetaField;
igMetaField *g_igMovieInfo_audioChannelMetaField;
igMetaField *g_igMovieInfo_audioVolumeMetaField;
igMetaField *g_igMovieInfo_videoTexturesMetaField;
igMetaField *g_igMovieInfo_minificationFilterMetaField;
igMetaField *g_igMovieInfo_magnificationFilterMetaField;
igMetaField *g_igMovieInfo_tileWidthMetaField;
igMetaField *g_igMovieInfo_tileHeightMetaField;
igMetaField *g_igMovieInfo_codecTypeMetaField;
igMetaField *g_igMovieInfo_codecMetaField;
igMetaField *g_igMovieInfo_stateMetaField;
igMetaField *g_igMovieInfo_sceneInfoMetaField;
igMetaField *g_igMovieInfo_runtimeImageMetaField;
igMetaField *g_igMovieInfo_runtimeTexturesMetaField;
igMetaField *g_igMovieInfo_imageFormatMetaField;
igMetaField *g_igMovieInfo_userdataMetaField;
igMetaField *g_igMovieInfo_bitrateMetaField;

igMovieInfo *igMovieInfo_Create(int allocator) {
    igMovieInfo_EnsureRegistered();
    return (igMovieInfo *)igMetaObject_CreateInstance(g_igMovieInfo_metaObject, (igMemoryPoolView *)allocator);
}

void *igMovieInfo_GetMetaObject(void) {
    igMetaObject *g = g_igMovieInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igMovieInfo_EnsureRegistered();
    }
    return g_igMovieInfo_metaObject;
}

int igMovieInfo_GetVTable(void) {
    igMovieInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    *(int **)&obj._vtable = &g_igMovieInfo_vtable[0];
    obj._path = 0;
    obj._videoTextures = 0;
    obj._codecType = 0;
    obj._codec = 0;
    obj._sceneInfo = 0;
    obj._runtimeImage = 0;
    obj._runtimeTextures = 0;
    obj._userdata = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igMovieInfo_vtable[0];
    igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj._userdata, -1);
    igSmartPointer_igTextureList_Destruct((igSmartPointer<igObject> *)&obj._runtimeTextures, -1);
    igSmartPointer_igImage_Destruct((igSmartPointer<igObject> *)&obj._runtimeImage, -1);
    igSmartPointer_igSceneInfo_Destruct((igSmartPointer<igObject> *)&obj._sceneInfo, -1);
    igSmartPointer_igMovieCodec_Destruct((igSmartPointer<igObject> *)&obj._codec, -1);
    igStringRef_Destruct((igStringRef *)&obj._codecType, -1);
    igSmartPointer_igTextureBindAttrList_Destruct((igSmartPointer<igObject> *)&obj._videoTextures, -1);
    igStringRef_Destruct((igStringRef *)&obj._path, -1);
    igInfo_Destroy((igInfo *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igTextureBindAttrList_Destruct(igSmartPointer<igObject> *self, short flag) {
    if (self != 0) {
        igObject *object = self->p;
        igObject::release(object);
        if (flag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igMovieCodec_Destruct(igSmartPointer<igObject> *self, short flag) {
    if (self != 0) {
        igObject *object = self->p;
        igObject::release(object);
        if (flag > 0) operator delete(self);
    }
    return self;
}

void igMovieInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMovieInfo_Register);
}

static igMetaObjectCallback g_igMovieInfo_callbackList[] = { igTextureBindAttrList_EnsureRegistered, igMovieCodec_EnsureRegistered, igSceneInfo_EnsureRegistered, Gap::Gfx::igImage::arkRegister, Gap::Attrs::igTextureList::arkRegister, Gap::Core::igObject::arkRegister, 0 };

CallbackArray *igMovieInfo_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieInfo_metaObject,
        Gap::Core::igInfo::arkRegisterInternal,
        igInfo_GetPublishedMetaObject,
        igMovieInfo_GetMetaObjectFunction,
        "igMovieInfo",
        0x68, /* instance size */
        igMovieInfo_GetVTable,
        igMovieInfo_InitFields,
        0, /* extra callback item */
        g_igMovieInfo_callbackList /* callback list */
    );
}

void igMovieInfo_GetMetaObjectFunction(void)
{
    igMovieInfo_GetMetaObject();
}

static FieldFactory g_igMovieInfo_ctorTable[] = {
    igStringMetaField_Create,
    igEnumMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igMovieInfo_fieldTable[] = {
    "_path",
    "_type",
    "_loop",
    "_width",
    "_height",
    "_audioChannel",
    "_audioVolume",
    "_videoTextures",
    "_minificationFilter",
    "_magnificationFilter",
    "_tileWidth",
    "_tileHeight",
    "_codecType",
    "_codec",
    "_state",
    "_sceneInfo",
    "_runtimeImage",
    "_runtimeTextures",
    "_imageFormat",
    "_userdata",
    "_bitrate",
};
static igMetaField **g_igMovieInfo_fieldHandles[] = {
    &g_igMovieInfo_pathMetaField,
    &g_igMovieInfo_typeMetaField,
    &g_igMovieInfo_loopMetaField,
    &g_igMovieInfo_widthMetaField,
    &g_igMovieInfo_heightMetaField,
    &g_igMovieInfo_audioChannelMetaField,
    &g_igMovieInfo_audioVolumeMetaField,
    &g_igMovieInfo_videoTexturesMetaField,
    &g_igMovieInfo_minificationFilterMetaField,
    &g_igMovieInfo_magnificationFilterMetaField,
    &g_igMovieInfo_tileWidthMetaField,
    &g_igMovieInfo_tileHeightMetaField,
    &g_igMovieInfo_codecTypeMetaField,
    &g_igMovieInfo_codecMetaField,
    &g_igMovieInfo_stateMetaField,
    &g_igMovieInfo_sceneInfoMetaField,
    &g_igMovieInfo_runtimeImageMetaField,
    &g_igMovieInfo_runtimeTexturesMetaField,
    &g_igMovieInfo_imageFormatMetaField,
    &g_igMovieInfo_userdataMetaField,
    &g_igMovieInfo_bitrateMetaField,
};
static int g_igMovieInfo_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
    96,
    100,
};

void igMovieInfo_InitFields(void) {
    int firstField;
    void *meta;
    igObjectRefMetaField *videoTexturesField;
    igObjectRefMetaField *codecField;
    igObjectRefMetaField *sceneInfoField;
    igObjectRefMetaField *runtimeImageField;
    igObjectRefMetaField *runtimeTexturesField;
    igEnumMetaField *typeField;
    igEnumMetaField *minificationFilterField;
    igEnumMetaField *magnificationFilterField;
    igEnumMetaField *stateField;
    igEnumMetaField *imageFormatField;
    igObjectRefMetaField *userdataField;

    meta = g_igMovieInfo_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMovieInfo_ctorTable, 0x15);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField)))->setDefault(0);
    typeField = (igEnumMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 1);
    ((Gap::Core::igEnumMetaField *)typeField)->setDefault(0);
    typeField->_getMetaEnumFunction = (int)igMovieInfo_GetMovieTypeMetaEnum;
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 3)))->setDefault(-1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 4)))->setDefault(-1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 5)))->setDefault(-1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 6)))->setDefault(-1);
    videoTexturesField = (igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 7);
    videoTexturesField->_metaObject = (int)igTextureBindAttrList_GetOrCreateMetaObject();
    minificationFilterField = (igEnumMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 8);
    ((Gap::Core::igEnumMetaField *)minificationFilterField)->setDefault(0);
    /* matching construct: a function-pointer store; an int store pools the getter addresses in .data */
    *(void (**)(void))&minificationFilterField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    magnificationFilterField = (igEnumMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 9);
    ((Gap::Core::igEnumMetaField *)magnificationFilterField)->setDefault(0);
    *(void (**)(void))&magnificationFilterField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0xA)))->setDefault(-1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0xB)))->setDefault(-1);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0xC)))->setDefault(0);
    codecField = (igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0xD);
    codecField->_metaObject = (int)igMovieCodec_GetOrCreateMetaObject();
    codecField->_persistent = 0;
    stateField = (igEnumMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0xE);
    ((Gap::Core::igEnumMetaField *)stateField)->setDefault(1);
    stateField->_getMetaEnumFunction = (int)igMovieInfo_GetMovieStateMetaEnum;
    sceneInfoField = (igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0xF);
    sceneInfoField->_metaObject = (int)igSceneInfo_GetOrCreateMetaObject();
    sceneInfoField->_persistent = 0;
    runtimeImageField = (igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0x10);
    runtimeImageField->_metaObject = (int)Gap::Gfx::igImage::getClassTypeLazy();
    runtimeImageField->_persistent = 0;
    runtimeTexturesField = (igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0x11);
    runtimeTexturesField->_metaObject = (int)Gap::Attrs::igTextureList::getClassTypeLazy();
    runtimeTexturesField->_persistent = 0;
    imageFormatField = (igEnumMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0x12);
    ((Gap::Core::igEnumMetaField *)imageFormatField)->setDefault(7);
    imageFormatField->_persistent = 0;
    imageFormatField->_getMetaEnumFunction = (int)IG_GFX_TEXTURE_FORMAT_GetMetaEnum;
    userdataField = (igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0x13);
    userdataField->_metaObject = (int)Gap::Core::igObject::getClassMeta();
    userdataField->_persistent = 0;
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField + 0x14)))->setDefault(-1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igMovieInfo_fieldTable, g_igMovieInfo_fieldHandles, g_igMovieInfo_fieldOffsets, firstField);
}

igMetaObject *g_igMovieRenderer_metaObject;
igMetaField *g_igMovieRenderer_movieManagerMetaField;

igMetaObject *igMovieRenderer_GetOrCreateMetaObject(void) {
    if (g_igMovieRenderer_metaObject == 0) {
        g_igMovieRenderer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMovieRenderer_metaObject;
}

void *igMovieRenderer_GetMetaObject(void) {
    igMetaObject *g = g_igMovieRenderer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igMovieRenderer_EnsureRegistered();
    }
    return g_igMovieRenderer_metaObject;
}

int igMovieRenderer_GetVTable(void) {
    igMovieRenderer obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._visualContext = 0;
    *(int **)&obj._vtable = &g_igMovieRenderer_vtable[0];
    obj._movieManager = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igMovieRenderer_vtable[0];
    if (&obj._movieManager != 0) {
        igObject::release((igObject *)obj._movieManager);
    }
    *(int **)&obj._vtable = &g_igRenderer_vtable[0];
    if (&obj._visualContext != 0) {
        igObject::release((igObject *)obj._visualContext);
    }
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igMovieManager_Destruct(igSmartPointer<igObject> *self, short flag) {
    if (self != 0) {
        igObject *object = self->p;
        igObject::release(object);
        if (flag > 0) operator delete(self);
    }
    return self;
}

void igMovieRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMovieRenderer_Register);
}

static igMetaObjectCallback g_igMovieRenderer_callbackList[] = { igMovieManager_EnsureRegistered, 0 };

CallbackArray *igMovieRenderer_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieRenderer_metaObject,
        Gap::Gui::igRenderer::arkRegisterInternal,
        Gap::Gui::igRenderer::getClassMeta,
        igMovieRenderer_GetMetaObjectFunction,
        "igMovieRenderer",
        0x10, /* instance size */
        igMovieRenderer_GetVTable,
        igMovieRenderer_InitFields,
        0, /* extra callback item */
        g_igMovieRenderer_callbackList /* callback list */
    );
}

void igMovieRenderer_GetMetaObjectFunction(void)
{
    igMovieRenderer_GetMetaObject();
}

static FieldFactory g_igMovieRenderer_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igMovieRenderer_fieldTable[] = {
    "_movieManager",
};
static igMetaField **g_igMovieRenderer_fieldHandles[] = {
    &g_igMovieRenderer_movieManagerMetaField,
};
static int g_igMovieRenderer_fieldOffsets[] = {
    12,
};

void igMovieRenderer_InitFields(void) {
    int firstField;
    void *movieManagerField;
    void *meta;

    meta = g_igMovieRenderer_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMovieRenderer_ctorTable, 1);
    movieManagerField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField));
    ((igObjectRefMetaField *)movieManagerField)->_metaObject = (int)igMovieManager_GetOrCreateMetaObject();
    ((igMetaField *)movieManagerField)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igMovieRenderer_fieldTable, g_igMovieRenderer_fieldHandles, g_igMovieRenderer_fieldOffsets, firstField);
}

igMetaObject *g_igMovieManager_metaObject;
igMetaField *g_igMovieManager_movieListMetaField;
igMetaField *g_igMovieManager_audioDisabledMetaField;
igMetaField *g_igMovieManager_audioMetaField;
igMetaField *g_igMovieManager_codecListMetaField;
igMetaField *g_igMovieManager_movieRendererMetaField;
igMetaField *g_igMovieManager_rendererListMetaField;

igMovieManager *igMovieManager_CreateInstance(int allocator) {
    igMovieManager_EnsureRegistered();
    return (igMovieManager *)igMetaObject_CreateInstance(g_igMovieManager_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igMovieManager_GetOrCreateMetaObject(void) {
    if (g_igMovieManager_metaObject == 0) {
        g_igMovieManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMovieManager_metaObject;
}

void *igMovieManager_GetMetaObject(void) {
    bool ok;
    if (g_igMovieManager_metaObject == 0) goto make;
    ok = !!(g_igMovieManager_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    igMovieManager_EnsureRegistered();
done:;
    return g_igMovieManager_metaObject;
}

int igMovieManager_GetVTable(void) {
    igMovieManager obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    *(int **)&obj._vtable = &g_igMovieManager_vtable[0];
    obj._movieList = 0;
    obj._audio = 0;
    obj._codecList = 0;
    obj._movieRenderer = 0;
    obj._rendererList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igMovieManager_vtable[0];
    igSmartPointer_igRendererOrderedList_Destruct((igSmartPointer<igObject> *)&obj._rendererList, -1);
    igSmartPointer_igMovieRenderer_Destruct((igSmartPointer<igObject> *)&obj._movieRenderer, (short)(-1));
    igSmartPointer_igMovieCodecList_Destruct((igSmartPointer<igObject> *)&obj._codecList, (long long)(-1));
    igSmartPointer_igAudioContext_Destruct((igSmartPointer<igObject> *)&obj._audio, (short)(-1));
    igSmartPointer_igMovieInfoList_Destruct((igSmartPointer<igObject> *)&obj._movieList, (short)(-1));
    igInfoManager_Destroy((igInfoManager *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igMovieInfoList_Destruct(igSmartPointer<igObject> *self, short flag) {
    if (self != 0) {
        igObject *object = self->p;
        igObject::release(object);
        if (flag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igMovieCodecList_Destruct(igSmartPointer<igObject> *self, short flag) {
    if (self != 0) {
        igObject *object = self->p;
        igObject::release(object);
        if (flag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igMovieRenderer_Destruct(igSmartPointer<igObject> *self, short flag) {
    if (self != 0) {
        igObject *object = self->p;
        igObject::release(object);
        if (flag > 0) operator delete(self);
    }
    return self;
}

void igMovieManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMovieManager_Register);
}

static igMetaObjectCallback g_igMovieManager_callbackList[] = { igMovieInfoList_EnsureRegistered, igAudioContext_EnsureRegistered, igMovieCodecList_EnsureRegistered, igMovieRenderer_EnsureRegistered, igRendererOrderedList_EnsureRegistered, 0 };

CallbackArray *igMovieManager_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMovieManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        igMovieManager_GetMetaObjectFunction,
        "igMovieManager",
        0x28, /* instance size */
        igMovieManager_GetVTable,
        igMovieManager_InitFields,
        0, /* extra callback item */
        g_igMovieManager_callbackList /* callback list */
    );
}

void igMovieManager_GetMetaObjectFunction(void)
{
    igMovieManager_GetMetaObject();
}

static FieldFactory g_igMovieManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igMovieManager_fieldTable[] = {
    "_movieList",
    "_audioDisabled",
    "_audio",
    "_codecList",
    "_movieRenderer",
    "_rendererList",
};
static igMetaField **g_igMovieManager_fieldHandles[] = {
    &g_igMovieManager_movieListMetaField,
    &g_igMovieManager_audioDisabledMetaField,
    &g_igMovieManager_audioMetaField,
    &g_igMovieManager_codecListMetaField,
    &g_igMovieManager_movieRendererMetaField,
    &g_igMovieManager_rendererListMetaField,
};
static int g_igMovieManager_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
};

void igMovieManager_InitFields(void) {
    igObjectRefMetaField *movieListField;
    igObjectRefMetaField *audioField;
    igObjectRefMetaField *codecListField;
    igObjectRefMetaField *movieRendererField;
    igObjectRefMetaField *rendererListField;
    void *meta;
    int startIndex;

    meta = g_igMovieManager_metaObject;
    startIndex = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMovieManager_ctorTable, 6);
    movieListField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, startIndex));
    movieListField->_metaObject = (int)igMovieInfoList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, startIndex + 1))->_persistent = 0;
    audioField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, startIndex + 2));
    audioField->_metaObject = (int)igAudioContext_GetOrCreateMetaObject();
    audioField->_persistent = 0;
    codecListField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, startIndex + 3));
    codecListField->_metaObject = (int)igMovieCodecList_GetOrCreateMetaObject();
    codecListField->_persistent = 0;
    movieRendererField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, startIndex + 4));
    movieRendererField->_metaObject = (int)igMovieRenderer_GetOrCreateMetaObject();
    movieRendererField->_construct = 1;
    movieRendererField->_persistent = 0;
    rendererListField = ((igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, startIndex + 5));
    rendererListField->_metaObject = (int)igRendererOrderedList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igMovieManager_fieldTable, g_igMovieManager_fieldHandles, g_igMovieManager_fieldOffsets, startIndex);
}

igMetaObject *g_igMoviePlugin_metaObject;
igMetaField *g_igMoviePlugin_movieManagerMetaField;

void *igMoviePlugin_GetMetaObject(void) {
    igMetaObject *g = g_igMoviePlugin_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igMoviePlugin_EnsureRegistered();
    }
    return g_igMoviePlugin_metaObject;
}

int igMoviePlugin_GetVTable(void) {
    igMoviePlugin obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igMoviePlugin_vtable[0];
    obj._movieManager = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igMoviePlugin_vtable[0];
    if (&obj._movieManager != 0) {
        igObject::release((igObject *)obj._movieManager);
    }
    return vtable;
}

void igMoviePlugin_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMoviePlugin_Register);
}

static igMetaObjectCallback g_igMoviePlugin_callbackList[] = { igMovieManager_EnsureRegistered, 0 };

CallbackArray *igMoviePlugin_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMoviePlugin_metaObject,
        igInsightPlugin_Register,
        igInsightPlugin_GetPublishedMetaObject,
        igMoviePlugin_GetMetaObjectFunction,
        "igMoviePlugin",
        0xc, /* instance size */
        igMoviePlugin_GetVTable,
        igMoviePlugin_InitFields,
        0, /* extra callback item */
        g_igMoviePlugin_callbackList /* callback list */
    );
}

void igMoviePlugin_GetMetaObjectFunction(void)
{
    igMoviePlugin_GetMetaObject();
}

igMetaObject *igInsightPlugin_GetPublishedMetaObject(void) {
    return g_igInsightPlugin_metaObject;
}

static FieldFactory g_igMoviePlugin_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igMoviePlugin_fieldTable[] = {
    "_movieManager",
};
static igMetaField **g_igMoviePlugin_fieldHandles[] = {
    &g_igMoviePlugin_movieManagerMetaField,
};
static int g_igMoviePlugin_fieldOffsets[] = {
    8,
};

void igMoviePlugin_InitFields(void) {
    int firstField;
    void *movieManagerField;
    void *meta;

    meta = g_igMoviePlugin_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMoviePlugin_ctorTable, 1);
    movieManagerField = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField));
    ((igObjectRefMetaField *)movieManagerField)->_metaObject = (int)igMovieManager_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igMoviePlugin_fieldTable, g_igMoviePlugin_fieldHandles, g_igMoviePlugin_fieldOffsets, firstField);
}

int igInsightPlugin_GetMeta(void)
{
    return (int)g_igInsightPlugin_metaObject;
}

igMetaObject *igMovieInfo_GetMeta(void)
{
    return g_igMovieInfo_metaObject;
}

igMetaObject *igTextureBindAttrList_GetMeta(void)
{
    return g_igTextureBindAttrList_metaObject;
}

igMetaObject *igMovieInfoList_GetMeta(void)
{
    return g_igMovieInfoList_metaObject;
}

igMetaObject *igMovieCodecList_GetMeta(void)
{
    return g_igMovieCodecList_metaObject;
}

igMetaObject *igFileNameList_GetMeta(void)
{
    return g_igFileNameList_metaObject;
}

igMetaObject *igAdxAfsFile_GetMeta(void)
{
    return g_igAdxAfsFile_metaObject;
}

igMetaObject *igFileName_GetMeta(void)
{
    return g_igFileName_metaObject;
}

igMetaObject *igAdxAfsFileList_GetMeta(void)
{
    return g_igAdxAfsFileList_metaObject;
}

igMetaObject *igMovieCodecList_GetElementMeta(void)
{
    return g_igMovieCodec_metaObject;
}

igMetaObject *igMovieInfoList_GetElementMeta(void)
{
    return g_igMovieInfo_metaObject;
}

igMetaObject *igTextureBindAttrList_GetElementMeta(void)
{
    return Gap::Attrs::igTextureBindAttr::getClassMeta();
}

igMetaObject *igAdxAfsFileList_GetElementMeta(void)
{
    return g_igAdxAfsFile_metaObject;
}

igMetaObject *igFileNameList_GetElementMeta(void)
{
    return g_igFileName_metaObject;
}

#pragma pop
