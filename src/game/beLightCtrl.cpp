#include "dw4/reflected.h"
#include "dw4/igVec3f.h"
#include "dw4/igMath.h"
#include "dw4/igLightAttrDispatchView.h"

extern "C" void beLightCtrl_Prepare(void);
extern "C" int beLightCtrl_GetInfoMeta(void);
extern "C" void beLightCtrl_UpdateRam(void);
extern "C" int beLightCtrl_GetMeta(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" int beLightCtrl_GetMsgActionEnum(...);
extern "C" int beMessenger_GetString(int, int);
extern "C" void beMessenger_GetVec3(void *, int, int);
extern "C" int beMessenger_ResolveEnumValue(int messenger, int values, const char *name);
extern "C" void *igProperty_FindByName(int, int, int);
extern "C" int g_beLightCtrlInfo_metaObject[4];
extern "C" int g_beLightCtrl_metaObject[4];
extern "C" char LIGHTCTRL[];
extern "C" void beLightCtrl_OnAddRam(beLightCtrl * p0, int p1, char * p2);
extern "C" int g_propertyNameField[4];
extern "C" int beLightCtrl_OnMessageText(beLightCtrl *self, beBaseInfoRam *ram, const char *message);

void beLightCtrl_Prepare(void)
{
}

int beLightCtrl_GetInfoMeta(void)
{
    return g_beLightCtrlInfo_metaObject[0];
}

void beLightCtrl_OnAddRam(beLightCtrl * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, LIGHTCTRL);
}

void beLightCtrl_UpdateRam(void)
{
}

int beLightCtrl_OnMessageText(beLightCtrl *self, beBaseInfoRam *ram, const char *message) {
    beLightCtrlInfo *info;
    igVec3f ambient;
    igLightAttrDispatchView *light;
    igLightAttrDispatchView **lights;
    igVec3f diffuse;
    igVec3f specular;
    int name;
    igLightSet *lightSet;
    igVec4f colour;
    info = (beLightCtrlInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue(self->_messenger, beLightCtrl_GetMsgActionEnum(), message)) {
    case 0:
        name = beMessenger_GetString(self->_messenger, 0);
        beMessenger_GetVec3(&ambient, self->_messenger, 0);
        beMessenger_GetVec3(&diffuse, self->_messenger, 1);
        beMessenger_GetVec3(&specular, self->_messenger, 2);
        lightSet = (igLightSet *)igProperty_FindByName(info->_lightSetList, g_propertyNameField[0], name);
        if (lightSet != 0) {
            lights = (igLightAttrDispatchView **)((igLightList *)lightSet->_lights)->_data;
            light = *lights;
            colour.w = 1.0f;
            colour.x = ambient.x; colour.y = ambient.y; colour.z = ambient.z;
            light->setAmbient(&colour.x);
            colour.x = diffuse.x; colour.y = diffuse.y; colour.z = diffuse.z;
            light->setDiffuse(&colour.x);
            colour.x = specular.x; colour.y = specular.y; colour.z = specular.z;
            light->setSpecular(&colour.x);
        }
        return 1;
    default:
        return 0;
    }
}

int beLightCtrl_GetMeta(void)
{
    return g_beLightCtrl_metaObject[0];
}
