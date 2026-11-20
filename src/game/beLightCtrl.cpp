#include "dw4/support/reflected.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/maths/igMath.h"
#include "dw4/attrs/igLightAttrDispatchView.h"
#include "dw4/game/beLightCtrl.h"
#include "dw4/game/beLightCtrlInfo.h"
#include "dw4/game/beMessenger.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/igNamedObject.h"

extern "C" void beLightCtrl_Prepare(void);
extern "C" igMetaObject *beLightCtrl_GetInfoMeta(void);
extern "C" void beLightCtrl_UpdateRam(void);
extern "C" igMetaObject *beLightCtrl_GetMeta(void);
extern "C" char LIGHTCTRL[];
extern "C" void beLightCtrl_OnAddRam(beLightCtrl * p0, int p1, char * p2);
extern "C" int beLightCtrl_OnMessageText(beLightCtrl *self, beBaseInfoRam *ram, const char *message);

void beLightCtrl_Prepare(void)
{
}

igMetaObject *beLightCtrl_GetInfoMeta(void)
{
    return g_beLightCtrlInfo_metaObject;
}

void beLightCtrl_OnAddRam(beLightCtrl * p0, int p1, char * p2)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)p0->_messenger, (beBaseInfoRam *)p1, LIGHTCTRL);
}

void beLightCtrl_UpdateRam(void)
{
}

int beLightCtrl_OnMessageText(beLightCtrl *self, beBaseInfoRam *ram, const char *message) {
    beLightCtrlInfo *info;
    igLightAttrDispatchView *light;
    igLightAttrDispatchView **lights;
    int name;
    igLightSet *lightSet;
    info = (beLightCtrlInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beLightCtrl_GetMsgActionEnum(), message)) {
    case 0: {
        name = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
        igVec3f ambient = beMessenger_GetVec3((beMessenger *)self->_messenger, 0);
        igVec3f diffuse = beMessenger_GetVec3((beMessenger *)self->_messenger, 1);
        igVec3f specular = beMessenger_GetVec3((beMessenger *)self->_messenger, 2);
        igVec4f colour;
        lightSet = (igLightSet *)igProperty_FindByName((igObjectList *)info->_lightSetList, g_propertyNameField, (const char *)name);
        if (lightSet != 0) {
            lights = (igLightAttrDispatchView **)((igLightList *)lightSet->_lights)->_data;
            light = *lights;
            colour.w = 1.0f;
            colour.x = ambient[0]; colour.y = ambient[1]; colour.z = ambient[2];
            light->setAmbient(&colour.x);
            colour.x = diffuse[0]; colour.y = diffuse[1]; colour.z = diffuse[2];
            light->setDiffuse(&colour.x);
            colour.x = specular[0]; colour.y = specular[1]; colour.z = specular[2];
            light->setSpecular(&colour.x);
        }
        return 1;
    }
    default:
        return 0;
    }
}

igMetaObject *beLightCtrl_GetMeta(void)
{
    return g_beLightCtrl_metaObject;
}
