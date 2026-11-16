#include "dw4/reflected.h"
#include "dw4/igVec3f.h"
#include "dw4/igMath.h"
#include "dw4/igLightAttrDispatchView.h"
#include "dw4/beLightCtrl.h"
#include "dw4/beLightCtrlInfo.h"
#include "dw4/beMessenger.h"
#include "dw4/igDataLists.h"
#include "dw4/igNamedObject.h"

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
    igVec3f ambient;
    igLightAttrDispatchView *light;
    igLightAttrDispatchView **lights;
    igVec3f diffuse;
    igVec3f specular;
    int name;
    igLightSet *lightSet;
    igVec4f colour;
    info = (beLightCtrlInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beLightCtrl_GetMsgActionEnum(), message)) {
    case 0:
        name = (int)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
        beMessenger_GetVec3((float *)&ambient, (beMessenger *)self->_messenger, 0);
        beMessenger_GetVec3((float *)&diffuse, (beMessenger *)self->_messenger, 1);
        beMessenger_GetVec3((float *)&specular, (beMessenger *)self->_messenger, 2);
        lightSet = (igLightSet *)igProperty_FindByName((igObjectList *)info->_lightSetList, g_propertyNameField, (const char *)name);
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

igMetaObject *beLightCtrl_GetMeta(void)
{
    return g_beLightCtrl_metaObject;
}
