int FUN_00177010(igPsx2VisualContext *vc, int *arg1, int *arg2, int arg3, int arg4) {
    int i;
    VertexArray177 *prev;
    int j; /* matching construct: declaration-order sweep — second loop counter gets a1, count a0 */
    int limit;
    int count;
    bool enabled = false;
    int result = 0;
    int levels = 0;
    VertexArray177 *va;

    if (vc->_bVertexBlendingEnabled) {
        if (arg3 > -1) {
            levels = p2GetDisplayListBlendWeightCount((p2DisplayList *)arg3);
            limit = p2GetDisplayListBlendMatrixCount((p2DisplayList *)arg3);
            if (levels != 0) {
                enabled = true;
                if (levels > 0 && levels < 5 && vc->_blendMatricesCount < 121 && !g_igPsx2DisableExt_ext10Enabled
                    && limit >= vc->_blendMatricesCount) {
                    result = 2;
                } else {
                    result = 3;
                }
            }
        } else {
            va = (VertexArray177 *)vc->_pVertexArray;
            levels = (unsigned char)(((unsigned int)*((VertexFormat177 *)va)->format() & 0xf0) >> 4);
            if (levels > 0) {
                enabled = true;
                if (levels > 0 && levels < 5 && vc->_blendMatricesCount < 121 && !g_igPsx2DisableExt_ext10Enabled) {
                    result = 2;
                    p2SetBlendIndexArray((void *)va->f36);
                    p2SetBlendWeightArray((void *)va->f32);
                } else {
                    result = 1;
                    if (vc->_currentDListHandle >= 0) {
                        vc->_dlistErrors = 1;
                    }
                }
            }
        }
    }
    if ((VertexArray177 *)vc->_pVertexArray != 0 && vc->_currentDListHandle != -1) {
        ((VertexArray177 *)vc->_pVertexArray)->f72[0] = vc->_texCoordIndex[0];
        if (vc->_pixelPipelineMode == 3) {
            for (i = 1; i < vc->_bMultiPassNum; i++) {
                ((VertexArray177 *)vc->_pVertexArray)->f72[i] = vc->_texCoordIndex[i];
            }
            ((VertexArray177 *)vc->_pVertexArray)->f136 = vc->_bMultiPassNum;
        } else {
            ((VertexArray177 *)vc->_pVertexArray)->f136 = 0;
        }
        ((DLists177 *)vc->_pDLists)->entries[vc->_currentDListHandle]->va = (VertexArray177 *)vc->_pVertexArray;
    }
    if (arg4 == -1) {
        *arg1 = ((VertexArray177 *)vc->_pVertexArray)->f8[0] ? ((VertexArray177 *)vc->_pVertexArray)->f8[0] : 0;
        *arg2 = ((VertexArray177 *)vc->_pVertexArray)->f8[1] ? ((VertexArray177 *)vc->_pVertexArray)->f8[1] : 0;
    } else {
        prev = ((DLists177 *)vc->_pDLists)->entries[arg4]->va;
        if (prev != 0) {
            if (vc->_texEnable[0] && vc->_texCoordIndex[0] != prev->f72[0]) {
                result = 3;
            }
            if (vc->_pixelPipelineMode == 3) {
                count = vc->_bMultiPassNum;
                if (count != prev->f136) {
                    result = 3;
                } else {
                    for (j = 1; j < count; j++) {
                        if (vc->_texEnable[j] && vc->_texCoordIndex[j] != prev->f72[j]) {
                            result = 3;
                        }
                    }
                }
            } else if (prev->f136 != 0) {
                result = 3;
            }
        }
    }
    if (enabled) {
        if (result == 2) {
            p2SetBlendWeightCount(levels, levels);
            if (!p2IsCapabilityEnabled(9)) {
                p2EnableCapability(9);
            }
        } else if (result == 1) {
            if (p2IsCapabilityEnabled(9)) {
                p2DisableCapability(9);
            }
            if (vc->_bLightingEnabled || vc->_texCoordSource[0] == 2) {
                if (vc->_inverseTransposeNeedValidation) {
                    FUN_00180060((O_180060 *)vc);
                }
                FUN_00180170(vc->_pVertexArray, vc->_blendIndex, vc->_blendMatrices, vc->_inverseTranspose, arg1, arg2, vc->_blendMatricesCount);
            } else {
                FUN_00180170(vc->_pVertexArray, vc->_blendIndex, vc->_blendMatrices, 0, arg1, arg2, vc->_blendMatricesCount);
            }
        }
    } else if (p2IsCapabilityEnabled(9)) {
        p2DisableCapability(9);
    }
    if (p2IsCapabilityEnabled(27)) {
        p2DisableCapability(27);
        p2SetComponentLayout(0, 0, 0, 0);
        p2SetComponentLayout(1, 0, 0, 0);
        p2SetComponentLayout(2, 0, 0, 0);
        p2SetComponentLayout(3, 0, 0, 0);
        p2SetComponentLayout(4, 0, 0, 0);
    }
    return result;
}

int FUN_001774c0(igPsx2VisualContext *vc, Geometry1774 *geom, bool *useTexture) {
    int j;
    int limit;
    AttrNode1774 *node;
    AttrValue1774 *value;
    int attrs;
    int levels = 0; /* matching construct: declaration-order sweep — levels in s4, texture in s3 */
    int matrices;
    int texture;
    int prebuilt;
    int result = 0;

    prebuilt = geom->f128;
    *useTexture = false;
    if (vc->_bVertexBlendingEnabled) {
        matrices = 0;
        texture = 0;
        if (prebuilt) {
            levels = geom->f120;
            limit = geom->f116;
        } else {
            attrs = geom->attrs;
            node = (AttrNode1774 *)FUN_0015f4a0((S_15f430 *)attrs, 6, 0);
            int m1 = (int)Gap::Core::igUnsignedCharList::getClassMeta(); /* matching construct: spelling sweep — the compared metas are locals, spilled with sw */
            if (m1 == node->obj->meta()) {
                matrices = node->obj->f16;
                levels = node->f24;
            } else {
                int m2 = (int)g_igVec3ucList_metaObject;
                if (m2 == node->obj->meta()) {
                    matrices = node->obj->f16;
                    levels = 3;
                } else {
                    int m3 = (int)g_igVec4ucList_metaObject;
                    if (m3 == node->obj->meta()) {
                        levels = 3;
                        matrices = node->obj->f16;
                    }
                }
            }
            node = (AttrNode1774 *)FUN_0015f4a0((S_15f430 *)attrs, 5, 0);
            if (node != 0) {
                value = node->obj;
                if ((int)Gap::Core::igCharList::getClassMeta() == value->meta()) {
                    int a = node->f32;
                    p2SetComponentLayout(3, 1, 7 - a, a);
                    texture = value->f16;
                    *useTexture = true;
                } else if ((int)Gap::Core::igUnsignedCharList::getClassMeta() == node->obj->meta()) {
                    int a = node->f32;
                    p2SetComponentLayout(3, 0, 8 - a, a);
                    texture = value->f16;
                    *useTexture = true;
                } else if ((int)Gap::Core::igShortList::getClassMeta() == node->obj->meta()) {
                    int a = node->f32;
                    p2SetComponentLayout(3, 1, 0xF - a, a);
                    texture = value->f16;
                    *useTexture = true;
                } else if ((int)Gap::Core::igUnsignedShortList::getClassMeta() == node->obj->meta()) {
                    int a = node->f32;
                    p2SetComponentLayout(3, 0, 0x10 - a, a);
                    texture = value->f16;
                    *useTexture = true;
                } else {
                    texture = node->obj->f16;
                }
            }
            limit = vc->_blendMatricesCount;
        }
        if (levels > 0 && levels < 5 && vc->_blendMatricesCount < 121 && !g_igPsx2DisableExt_ext10Enabled && limit >= vc->_blendMatricesCount) {
            result = 2;
            if (!prebuilt) {
                p2SetBlendIndexArray((void *)matrices);
                p2SetBlendWeightArray((void *)texture);
            }
        } else {
            result = 1;
        }
        if (result == 2) {
            p2SetBlendWeightCount(levels, levels);
            if (!p2IsCapabilityEnabled(9)) {
                p2EnableCapability(9);
            }
        } else if (result == 1) {
            if (p2IsCapabilityEnabled(9)) {
                p2DisableCapability(9);
            }
        }
    } else if (p2IsCapabilityEnabled(9)) {
        p2DisableCapability(9);
    }
    if (prebuilt) {
        if (vc->_texEnable[0] && vc->_texCoordIndex[0] != geom->f48[0]) {
            result = 3;
        }
        if (vc->_pixelPipelineMode == 3) {
            if (vc->_bMultiPassNum != geom->f112) {
                result = 3;
            } else {
                for (j = 1; j < vc->_bMultiPassNum; j++) {
                    if (vc->_texEnable[j] && vc->_texCoordIndex[j] != geom->f48[j]) {
                        result = 3;
                    }
                }
            }
        } else if (geom->f112 != 0) {
            result = 3;
        }
    }
    return result;
}

namespace Gap {
namespace Gfx {

bool igPsx2VisualContext::getStatistic(unsigned int stat)
{
    return getStatisticCapability(stat);
}

bool igPsx2VisualContext::getStatisticCapability(unsigned int stat) {
    bool supported = false;
    switch (stat) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 16:
    case 17:
    case 20:
    case 23:
    case 24:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
    case 71:
    case 72:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    case 79:
    case 80:
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
    case 86:
    case 87:
    case 88:
    case 89:
    case 90:
    case 91:
    case 92:
    case 93:
    case 94:
    case 95:
    case 96:
    case 97:
    case 98:
    case 99:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 109:
    case 110:
    case 111:
    case 112:
    case 113:
    case 114:
    case 115:
    case 116:
    case 117:
    case 118:
    case 119:
    case 120:
    case 121:
    case 122:
    case 123:
    case 124:
    case 125:
    case 126:
    case 127:
    case 128:
    case 129:
    case 130:
    case 131:
    case 132:
    case 133:
    case 134:
    case 135:
    case 136:
    case 137:
    case 138:
    case 139:
    case 140:
    case 141:
    case 142:
    case 143:
    case 144:
    case 145:
    case 146:
    case 147:
    case 148:
    case 149:
    case 150:
    case 151:
    case 152:
    case 153:
    case 154:
    case 155:
    case 156:
    case 157:
    case 158:
    case 159:
    case 160:
    case 161:
    case 162:
    case 163:
    case 164:
    case 165:
    case 166:
    case 167:
    case 168:
    case 169:
    case 170:
    case 171:
    case 172:
    case 173:
    case 174:
    case 175:
    case 176:
    case 177:
    case 178:
    case 179:
    case 180:
    case 181:
    case 182:
    case 183:
    case 184:
    case 185:
    case 186:
    case 187:
    case 188:
    case 190:
        supported = true;
        break;
    }
    return supported;
}
}
}

unsigned char g_igPsx2VisualContext_capability31Enabled;

unsigned char g_igPsx2VisualContext_capability34Enabled;

namespace Gap {
namespace Gfx {

bool igPsx2VisualContext::setStatistic(unsigned int stat, bool enb)
{
    StatisticsCapture *node;

    bool supported = ((Gap::Gfx::igVisualContext *)this)->getStatisticCapability(stat);
    if (supported) {
        if (stat == 31) {
            g_igPsx2VisualContext_capability31Enabled = enb;
        }
        if (stat == 34) {
            g_igPsx2VisualContext_capability34Enabled = enb;
        }
        if (stat == 31) {
        } else if (stat == 34) {
        } else if (stat == 57) {
            for (node = (StatisticsCapture *)_statisticCaptures; node != 0; node = node->next) {
                node->active = 1;
                node->startCapture = 0;
            }
        }
    }
    return supported;
}

void igPsx2VisualContext::getStatistic() {
    if (DAT_0048ac30[0] != 0) {
        memset(&g_gsStatCurrent, 0, 0x1C8);
        DAT_00560ee8[0] = 0;
        DAT_0048ac30[0] = 0;
    }
    DAT_00560ef0[0] = DAT_00560ee8[0];
    g_gsStatPrevious.c[0] = g_gsStatCurrent.c[0];
    DAT_00560b58[0] = DAT_00560d28[0];
    DAT_00560b60[0] = DAT_00560d30[0];
    DAT_00560b68[0] = DAT_00560d38[0];
    DAT_00560b70[0] = DAT_00560d40[0];
    DAT_00560b78[0] = DAT_00560d48[0];
    DAT_00560b80[0] = DAT_00560d50[0];
    DAT_00560b88[0] = DAT_00560d58[0];
    DAT_00560b90[0] = DAT_00560d60[0];
    DAT_00560b98[0] = DAT_00560d68[0];
    DAT_00560ba0[0] = DAT_00560d70[0];
    DAT_00560ba8[0] = DAT_00560d78[0];
    DAT_00560bb0[0] = DAT_00560d80[0];
    DAT_00560bb8[0] = DAT_00560d88[0];
    DAT_00560bc0[0] = DAT_00560d90[0];
    DAT_00560bc8[0] = DAT_00560d98[0];
    DAT_00560bd0[0] = DAT_00560da0[0];
    DAT_00560bd8[0] = DAT_00560da8[0];
    DAT_00560be0[0] = DAT_00560db0[0];
    DAT_00560be8[0] = DAT_00560db8[0];
    DAT_00560bf0[0] = DAT_00560dc0[0];
    DAT_00560bf8[0] = DAT_00560dc8[0];
    DAT_00560c00[0] = DAT_00560dd0[0];
    DAT_00560c08[0] = DAT_00560dd8[0];
    DAT_00560c10[0] = DAT_00560de0[0];
    DAT_00560c18[0] = DAT_00560de8[0];
    DAT_00560c20[0] = DAT_00560df0[0];
    DAT_00560c28[0] = DAT_00560df8[0];
    DAT_00560c30[0] = DAT_00560e00[0];
    DAT_00560c38[0] = DAT_00560e08[0];
    DAT_00560c40[0] = DAT_00560e10[0];
    DAT_00560c48[0] = DAT_00560e18[0];
    DAT_00560c50[0] = DAT_00560e20[0];
    DAT_00560c58[0] = DAT_00560e28[0];
    DAT_00560c60[0] = DAT_00560e30[0];
    DAT_00560c68[0] = DAT_00560e38[0];
    DAT_00560c70[0] = DAT_00560e40[0];
    DAT_00560c78[0] = DAT_00560e48[0];
    DAT_00560c80[0] = DAT_00560e50[0];
    DAT_00560c88[0] = DAT_00560e58[0];
    DAT_00560c90[0] = DAT_00560e60[0];
    DAT_00560c98[0] = DAT_00560e68[0];
    DAT_00560ca0[0] = DAT_00560e70[0];
    DAT_00560ca8[0] = DAT_00560e78[0];
    DAT_00560cb0[0] = DAT_00560e80[0];
    DAT_00560cb8[0] = DAT_00560e88[0];
    DAT_00560cc0[0] = DAT_00560e90[0];
    DAT_00560cc8[0] = DAT_00560e98[0];
    DAT_00560cd0[0] = DAT_00560ea0[0];
    DAT_00560cd8[0] = DAT_00560ea8[0];
    DAT_00560ce0[0] = DAT_00560eb0[0];
    DAT_00560ce8[0] = DAT_00560eb8[0];
    DAT_00560cf0[0] = DAT_00560ec0[0];
    DAT_00560cf8[0] = DAT_00560ec8[0];
    DAT_00560d00[0] = DAT_00560ed0[0];
    DAT_00560d08[0] = DAT_00560ed8[0];
    DAT_00560d10[0] = DAT_00560ee0[0];
    p2GetStatistics(&g_gsStatCurrent);
}

float igPsx2VisualContext::getStatisticValue(int stat) {
    float result = -1.0f;
    float elapsed = DELTA(5);
    if (!(elapsed <= 0.0f)) {
        switch (stat) {
        case 4: result = elapsed; break;
        case 5: result = DELTA(6); break;
        case 0: result = DELTA(0) / elapsed; break;
        case 1: result = DELTA(1) / elapsed; break;
        case 6: result = (1000.0f * (DELTA(36) / (float)TICKS_PER_SECOND)) / elapsed; break;
        case 7: result = 1000.0f * ((float)CUR[37] / (float)TICKS_PER_SECOND); break;
        case 8: result = 1000.0f * ((float)CUR[38] / (float)TICKS_PER_SECOND); break;
        case 2: result = DELTA(2) / elapsed; break;
        case 36: result = DELTA(26) / elapsed; break;
        case 37: result = DELTA(25) / elapsed; break;
        case 3: result = (float)g_gsRawCounter[0]; break;
        case 30: result = (1000.0f * (DELTA(30) / (float)TICKS_PER_SECOND)) / elapsed; break;
        case 31: result = (16.0f * DELTA(29)) / elapsed; break;
        case 32: result = DELTA(27) / elapsed; break;
        case 33: result = (1000.0f * (DELTA(34) / (float)TICKS_PER_SECOND)) / elapsed; break;
        case 34: result = (16.0f * DELTA(33)) / elapsed; break;
        case 35: result = DELTA(31) / elapsed; break;
        case 39: result = 1000.0f * ((DELTA(43) / elapsed) / (float)TICKS_PER_SECOND); break;
        case 38: {
            float sum = DELTA(39) / elapsed;
            sum = sum + DELTA(40) / elapsed;
            sum = sum + DELTA(41) / elapsed;
            sum = sum + DELTA(42) / elapsed;
            sum = sum + DELTA(44) / elapsed;
            sum = sum + DELTA(45) / elapsed;
            sum = sum + DELTA(46) / elapsed;
            result = 1000.0f * (sum / (float)TICKS_PER_SECOND);
            break;
        }
        case 40: result = DELTA(24) / elapsed; break;
        case 41: result = DELTA(7) / elapsed; break;
        case 44: result = (float)p2GetPoolAllocated(3); break;
        case 45: result = (float)p2GetPoolAllocated(7); break;
        case 46: result = (float)p2GetPoolAllocated(8); break;
        case 47: result = (float)p2GetPoolAllocated(9); break;
        case 48: result = (float)p2GetPoolAllocated(10); break;
        case 49: result = (float)p2GetPoolAllocated(0); break;
        case 50: result = (float)p2GetPoolAllocated(1); break;
        case 51: result = (float)p2GetPoolAllocated(2); break;
        case 52: result = (float)p2GetPoolAllocated(4); break;
        case 53: result = (float)p2GetPoolAllocated(5); break;
        case 54: result = (float)p2GetPoolAllocated(6); break;
        case 55: result = (float)p2GetPoolAllocated(11); break;
        case 56: result = (float)p2GetPoolAllocated(12); break;
        case 58: result = (float)g_gsAccumulator_00560668[0] / elapsed; g_gsAccumulator_00560668[0] = 0; break;
        case 59: result = (float)g_gsAccumulator_00560660[0] / elapsed; g_gsAccumulator_00560660[0] = 0; break;
        case 16: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 17: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 20: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 24: result = (float)g_gsAccumulator_005608a0[0] / elapsed; g_gsAccumulator_005608a0[0] = 0; break;
        case 187: result = DELTA(48) / elapsed; break;
        case 188: result = DELTA(49) / elapsed; break;
        case 190: result = DELTA(56) / elapsed; break;
        }
        if (stat >= 60 && stat < 187) {
            result = (float)g_gsEventCount[stat] / elapsed;
            g_gsEventCount[stat] = 0;
        }
    }
    if (result == -1.0f) {
        if (stat == 42) {
            GsStatBlock snapshot;
            p2GetStatistics(&snapshot);
            result = (float)snapshot.c[3];
        } else if (stat == 43) {
            GsStatBlock snapshot;
            p2GetStatistics(&snapshot);
            result = (float)snapshot.c[4];
        }
    }
    return result;
}
}
}

void FUN_001788a0(void *arg0) {
    int i;
    *(int *)((char *)(arg0) + 1552) = 0;
    i = 0;
    do {
        DAT_005608c0[i] = 0;
    } while (++i < 0x7E);
}

void FUN_001788e0(StatContext88 *arg0, int arg1) {
    StatNode88 *temp_s1;
    StatNode88 *temp_s0;
    StatRefObject *temp_a0;

    temp_s1 = arg0->f610;
    if (temp_s1 != 0) {
        do {
            temp_a0 = temp_s1->f0c;
            temp_s0 = temp_s1->f3b8;
            temp_a0->refs = temp_a0->refs - 1;
            if ((temp_a0->refs & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
            ((StatAllocator *)((Gap::Gfx::igVisualContext *)arg0)->getStatisticsMemoryPool())->vX(temp_s1);
        } while (temp_s0 != 0);
    }
    arg0->f610 = 0;
}

#define REPORT(args) { igReport_Printf args; igReport_Flush(); }
#define PER_FRAME(field) ((int)((capture->end.field - capture->start.field) / frameCount))
#define DMA_MS(field) (1000.0f * (__floatdisf(capture->end.field - capture->start.field) / (float)9216000) / frameCount)
#define PERCENT(part, whole) (100.0f * ((float)(part) / (float)(whole)))

void FUN_00178970(igPsx2VisualContext *self, StatisticsCapture *capture) {
    int frameCount;
    int internalFrames;
    int vsyncs;
    int vertices;
    int polygons;
    float strip;
    float vu1Time;
    float gifTime;
    float totalTime;
    float dmaCount;
    float listedVertices;
    float listedPolygons;
    int fastPath;
    int litPath;
    int fastLitPath;
    int vu0Blend;
    int vu1Blend;
    int multipass;
    float ratio;
    int programSize;
    int heapSize;
    int stackSize;
    int stateCount;
    int validations;
    int path;
    int prePath;
    int lighting;
    int giftag;
    int state;
    int blending;
    int gsRegister;
    int memoryLayout;
    int multipassState;
    int lightingState;
    int material;
    int materialMode;
    int light;
    int lightState;
    int byGlobalColor;
    int byPrimitive;

    {
        int text = (int)capture->name->_buffer;
        if (text == 0) text = (int)g_stringObjEmptyText;
        REPORT(("\nCapture report for %d (%s)\n--------------------------------\n", capture->index, text))
    }
    frameCount = capture->frameCount;
    internalFrames = (int)(capture->end.framesTimed - capture->start.framesTimed);
    vsyncs = (int)(capture->end.vsyncs - capture->start.vsyncs);
    REPORT(("Frame Count : %d (internal frame count %d)\n", frameCount, internalFrames))
    REPORT(("Frame Rate : %2.02f ( vsync %d approx.)\n", (double)(60.0f * (float)internalFrames / (float)vsyncs), vsyncs))
    REPORT(("\n"))
    vertices = PER_FRAME(vertices);
    polygons = PER_FRAME(primitives);
    if (polygons == 0) polygons = 1;
    strip = (float)vertices / (float)polygons;
    if (vertices == 0) vertices = 1;
    REPORT(("1. Geometry\n"))
    REPORT(("   Average Polygon Count %d\n", polygons))
    REPORT(("   Average Vertex Count %d\n", vertices))
    REPORT(("   Strip Coefficient %2.04f %%", (double)strip))
    if (strip >= 2.9f) {
        REPORT(("(%s)\n", "Extremely poor strip efficiency"))
    } else if (strip >= 2.3f) {
        REPORT(("(%s)\n", "Bad strip efficiency"))
    } else if (strip >= 1.5f) {
        REPORT(("(%s)\n", "Average strip efficiency"))
    } else {
        REPORT(("(%s)\n", "Good strip efficiency"))
    }
    REPORT(("\n"))
    vu1Time = DMA_MS(vif1DmaTime);
    gifTime = DMA_MS(gifDmaTime);
    totalTime = DMA_MS(dmaOverlapTime);
    dmaCount = __floatdisf(capture->end.vif1DmaCount - capture->start.vif1DmaCount) / (float)frameCount;
    REPORT(("2. DMAs\n"))
    REPORT(("   Average VU1 Dma time %2.04f ms\n", (double)vu1Time))
    REPORT(("   Average VU1 Dma count %f \n", (double)dmaCount))
    REPORT(("   Average GIF Dma time %2.04f ms", (double)gifTime))
    if (gifTime <= 0.000001f) {
        REPORT(("(%s)\n", "No texture is being paged"))
    } else {
        REPORT(("(%s)\n", "Texture is being paged"))
        REPORT(("   Average GIF Dma count %f \n", (double)dmaCount))
    }
    REPORT(("   Average VU1+GIF Dma time %2.04f ms\n", (double)totalTime))
    REPORT(("\n"))
    listedVertices = PERCENT(PER_FRAME(displayListVertices), vertices);
    listedPolygons = PERCENT(PER_FRAME(displayListPrimitives), polygons);
    REPORT(("3. percentage render list-ed %0.02f %%(based on vertices)\n", (double)listedVertices))
    REPORT(("   percentage render list-ed %0.02f %%(based on polys)\n", (double)listedPolygons))
    if (listedVertices > 70.0f) {
        REPORT(("   %s\n", "Good use of render lists."))
    } else if (listedVertices > 40.0f) {
        REPORT(("   %s\n", "Use more render list for your geometry."))
    } else {
        REPORT(("   %s\n", "You need to use render list for your geometry."))
    }
    REPORT(("\n"))
    fastPath = PER_FRAME(fastPathVertices);
    litPath = PER_FRAME(litPathVertices);
    fastLitPath = PER_FRAME(fastLitPathVertices);
    vu0Blend = PER_FRAME(vu0BlendVertices);
    vu1Blend = PER_FRAME(vu1BlendVertices);
    multipass = PER_FRAME(vu1MultiPassVertices);
    REPORT(("4. Path usage\n"))
    REPORT(("   Fast path percentage %0.02f %%( vertex count %d )\n", (double)PERCENT(fastPath, vertices), fastPath))
    REPORT(("   Lit path percentage %0.02f %%( vertex count %d )\n", (double)PERCENT(litPath, vertices), litPath))
    REPORT(("   Fast lit path percentage %0.02f %%( vertex count %d )\n", (double)PERCENT(fastLitPath, vertices), fastLitPath))
    REPORT(("   VU0 vertex blending percentage %0.02f %%( vertex count %d )\n", (double)PERCENT(vu0Blend, vertices), vu0Blend))
    REPORT(("   VU1 vertex blending percentage %0.02f %%( vertex count %d )\n", (double)PERCENT(vu1Blend, vertices), vu1Blend))
    REPORT(("   VU1 MultiPass percentage %0.02f %%( vertex count %d )\n", (double)PERCENT(multipass, vertices), multipass))
    if (vu0Blend + vu1Blend != 0) {
        ratio = PERCENT(vu0Blend, vu0Blend + vu1Blend);
        REPORT(("   VU0 / VU1 percentage %0.02f %%", (double)ratio))
        if (ratio < 50.0f) {
            REPORT(("(Vertex blending runs more on VU1 than VU0)\n"))
        } else {
            REPORT(("(Vertex blending runs more on VU0 than VU1)\n"))
        }
    }
    if (litPath != 0) {
        ratio = PERCENT(fastLitPath, litPath);
        REPORT(("   Fast / Lit percentage %0.02f %%", (double)ratio))
        if (ratio < 50.0f) {
            REPORT(("(Lighting is run mostly in slow mode)\n"))
        } else {
            REPORT(("(Lighting is run mostly in fast mode)\n"))
        }
    }
    REPORT(("\n"))
    struct mallinfo mi = mallinfo();
    heapSize = (int)_heap_size;
    programSize = (int)_end;
    stackSize = (int)_stack_size;
    if (heapSize == -1) {
        int used = mi.uordblks + (programSize + stackSize);
        int probeSize = 0x2000400 - used;
        if (used <= 0) {
            heapSize = 0x8000000;
        } else {
            void *probe = Memory_SystemAllocate(probeSize);
            if (probe == 0) {
                heapSize = 0x2000000;
            } else {
                heapSize = 0x8000000;
                Memory_SystemFree(probe);
            }
        }
    }
    heapSize = heapSize - programSize - stackSize;
    REPORT(("5. Memory usage\n"))
    REPORT(("   Program size %.2f Mb\n", (double)((float)programSize * (1.0f / 1048576.0f))))
    REPORT(("   Stack size %.2f Mb\n", (double)((float)stackSize * (1.0f / 1048576.0f))))
    REPORT(("   Heap size %.2f Mb\n", (double)((float)heapSize * (1.0f / 1048576.0f))))
    REPORT(("   Total size %.0f Mb\n", (double)((float)(heapSize + (programSize + stackSize)) * (1.0f / 1048576.0f))))
    REPORT(("   Heap used %.0f bytes (%.0f bytes)\n", (double)(float)mi.uordblks, (double)(float)mi.arena))
    REPORT(("   Heap available %.0f bytes\n", (double)(float)(heapSize - mi.uordblks)))
    REPORT(("\n"))
    stateCount = PER_FRAME(capabilityChanges);
    validations = PER_FRAME(stateSends);
    path = PER_FRAME(functionTablesSent);
    prePath = PER_FRAME(lightingFunctionsSent);
    lighting = PER_FRAME(lightsSent);
    giftag = PER_FRAME(gifTagsSent);
    state = PER_FRAME(vertexFormatsSent);
    blending = PER_FRAME(blendMatricesSent);
    gsRegister = PER_FRAME(gsRegistersSent);
    memoryLayout = PER_FRAME(vuBufferLayoutsSent);
    multipassState = PER_FRAME(passSetupsSent);
    lightingState = PER_FRAME(lightingSwitches);
    material = PER_FRAME(materialSets);
    materialMode = PER_FRAME(lightingModeSets);
    light = PER_FRAME(lightSets);
    lightState = PER_FRAME(lightSwitches);
    byGlobalColor = PER_FRAME(colourModeChanges);
    byPrimitive = PER_FRAME(primitiveChanges);
    REPORT(("6. State management\n"))
    REPORT(("   Average vertex per state change %.04f (count %d)\n", (double)((float)vertices / (float)stateCount), stateCount))
    REPORT(("   State validation per frame %d\n", validations))
    if (validations != 0) {
        REPORT(("      Path         %d (%3.1f %%)\n", path, (double)PERCENT(path, validations)))
        REPORT(("         By global color       %d\n", byGlobalColor))
        REPORT(("         By changing primitive %d\n", byPrimitive))
        REPORT(("      PrePath      %d (%3.1f %%)\n", prePath, (double)PERCENT(prePath, validations)))
        REPORT(("      Giftag       %d (%3.1f %%)\n", giftag, (double)PERCENT(giftag, validations)))
        REPORT(("      State        %d (%3.1f %%)\n", state, (double)PERCENT(state, validations)))
        REPORT(("      Blending     %d (%3.1f %%)\n", blending, (double)PERCENT(blending, validations)))
        REPORT(("      GSRegister   %d (%3.1f %%)\n", gsRegister, (double)PERCENT(gsRegister, validations)))
        REPORT(("      MemoryLayout %d (%3.1f %%)\n", memoryLayout, (double)PERCENT(memoryLayout, validations)))
        REPORT(("      Multipass    %d (%3.1f %%)\n", multipassState, (double)PERCENT(multipassState, validations)))
        REPORT(("      Lighting     %d (%3.1f %%)\n", lighting, (double)PERCENT(lighting, validations)))
        REPORT(("         Lighting State %d\n", lightingState))
        REPORT(("         Material       %d\n", material))
        REPORT(("         MaterialMode   %d\n", materialMode))
        REPORT(("         Light          %d\n", light))
        REPORT(("         Light State    %d\n", lightState))
    }
    REPORT(("\n"))
    REPORT(("7. Internal struct size\n"))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_CLUT_PSX2 %d\n", p2GetPoolAllocated(3)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_DMAPREDICATE_PSX2 %d\n", p2GetPoolAllocated(7)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_DMACOMPLETION_PSX2 %d\n", p2GetPoolAllocated(8)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_FINISH_PSX2 %d\n", p2GetPoolAllocated(9)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_TEXTURE_PSX2 %d\n", p2GetPoolAllocated(10)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF0_PSX2 %d\n", p2GetPoolAllocated(0)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF1_PSX2 %d\n", p2GetPoolAllocated(1)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_DMABUFFER_GIF_PSX2 %d\n", p2GetPoolAllocated(2)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF0_SIZE_PSX2 %d\n", p2GetPoolAllocated(4)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF1_SIZE_PSX2 %d\n", p2GetPoolAllocated(5)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_DMABUFFER_GIF_SIZE_PSX2 %d\n", p2GetPoolAllocated(6)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_STATE_CACHE_PSX2 %d\n", p2GetPoolAllocated(11)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_MULTIPASS_PSX2 %d\n", p2GetPoolAllocated(12)))
    REPORT(("   IG_GFX_INTERNAL_STRUCT_RENDERLIST_PSX2 %d\n", p2GetPoolAllocated(13)))
    REPORT(("\n"))
}
#undef REPORT
#undef PER_FRAME
#undef DMA_MS
#undef PERCENT

void FUN_00179e00(StatContext *arg0) {
    int s3;
    int s2;
    int idx;
    StatNode *n;
    int a1;
    Ref_1778e0 sectionName((O_1778e0 *)igStringObj_Create((int)((Gap::Gfx::igVisualContext *)arg0)->getStatisticsMemoryPool()));
    Ref_1778e0 indexText((O_1778e0 *)igStringObj_Create((int)((Gap::Gfx::igVisualContext *)arg0)->getStatisticsMemoryPool()));
    s3 = ((G_1778e0 *)g_objectSystem)->f56;
    s2 = 0;
    igStringObj_Set((igStringObj *)(O_1778e0 *)sectionName, "STATISTICS_CAPTURE_");
    igStringObj_SetInt((int)(O_1778e0 *)indexText, 0, "%d");
    { int y = indexText->f12; int x = sectionName->f12;
    a1 = indexText->f8;
    if (a1 == 0) a1 = (int)g_stringObjEmptyText;
    igStringObj_Insert((igStringObj *)(O_1778e0 *)sectionName, (char *)a1, x, y); }
    while ((idx = ((Gap::Core::igRegistry *)s3)->findSection((char *)(sectionName->f8 == 0 ? (int)g_stringObjEmptyText : sectionName->f8), 0)) != -1) {
        n = (StatNode *)((StatAllocator *)((Gap::Gfx::igVisualContext *)arg0)->getStatisticsMemoryPool())->v52(960);
        if (n == 0) break;
        n->f16 = 1;
        n->f0 = s2;
        igGetRegistryValue_Int((igRegistry *)s3, idx, "numCapture", &n->f4, 1, 0);
        igGetRegistryValue_Int((igRegistry *)s3, idx, "startCapture", &n->f8, -1 - n->f4, 0);
        n->f12 = (O_1778e0 *)((O_1778e0 *)igStringObj_Create((int)((Gap::Gfx::igVisualContext *)arg0)->getStatisticsMemoryPool()));
        igGetRegistryValue_StringObj((igRegistry *)s3, idx, "stringCapture", (igStringObj **)&n->f12, "", 0);
        s2 += 1;
        n->f952 = arg0->f1552;
        arg0->f1552 = n;
        igStringObj_SetInt((int)(O_1778e0 *)indexText, s2, "%d");
        igStringObj_Set((igStringObj *)(O_1778e0 *)sectionName, "STATISTICS_CAPTURE_");
        { int y = indexText->f12; int x = sectionName->f12;
        a1 = indexText->f8;
        if (a1 == 0) a1 = (int)g_stringObjEmptyText;
        igStringObj_Insert((igStringObj *)(O_1778e0 *)sectionName, (char *)a1, x, y); }
    }
}

void FUN_0017a070(int *a) {
    igObject *temp_a0;
    igObject *temp_a0_2;

    a[0] = 7;
    a[1] = 1;
    a[2] = 1;
    a[3] = 1;
    a[4] = 1;
    a[21] = 0;
    a[22] = 0x20;
    a[23] = 0;
    a[24] = 0x20;
    a[5] = 0;
    a[8] = -1;
    a[9] = -1;
    a[10] = -1;
    temp_a0 = (igObject *)(a[12]);
    igObject::release(temp_a0);
    a[12] = 0;
    temp_a0_2 = (igObject *)(a[13]);
    igObject::release(temp_a0_2);
    a[13] = 0;
    a[14] = 0;
    a[15] = 0;
    a[25] = -1;
    a[27] = 0;
    a[26] = -1;
    a[18] = 0;
    a[19] = 0;
    a[33] = 0;
    *(char *)((char *)a + 80) = 1;
    *(char *)((char *)a + 81) = 1;
    a[7] = -1;
}

void FUN_0017a180(void *self) {
    int r;
    BufferEntryRef *o;
    BufferEntryRef **slot;
    BufferSetView *arg0;
    unsigned int i;
    arg0 = (BufferSetView *)self;
    o = arg0->f52;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)o);
        }
    }
    arg0->f52 = 0;
    o = arg0->f48;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)o);
        }
    }
    arg0->f48 = 0;
    i = 0;
    if (arg0->f56 != 0) {
        for (; i < arg0->f60; i++) {
            slot = arg0->f56 + i;
            o = *slot;
            if (o != 0) {
                r = o->references - 1;
                o->references = r;
                r = o->references;
                if (((unsigned long long)((long long)r << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)o);
                }
            }
            *slot = 0;
        }
        Memory_FreeBuffer(arg0->f56);
    }
    if (arg0->f72 != 0) {
        Memory_FreeBuffer(arg0->f72);
    }
    arg0->f60 = 0;
}

int FUN_0017a2b0(int arg0) {
    if (arg0 & 0x10000) {
        return DAT_0048acb0[arg0 & 0xFFFF];
    }
    return DAT_0048ac40[arg0];
}

void FUN_0017a300(Self_17a070 *self) {
    int textureArraySize;
    int bi;
    Buf_17a070 *b;
    T *o;
    int i;
    textureArraySize = 0x40;
    igGetRegistryValue_Int((igRegistry *)(*(int *)((char *)g_objectSystem + 56)), 4, "IG_GFX_VC_TEXTURE_ARRAY_SIZE", &textureArraySize, 0x40, 0);
    Buf_17a070 *r = (Buf_17a070 *)Memory_AllocateBufferDirect(0x14, (igMemoryPoolView *)((Gap::Gfx::igVisualContext *)self)->getListMemoryPool());
    if (r != 0) {
        bi = (int)r;
        b = (Buf_17a070 *)bi;
        int n = textureArraySize;
        Owner_17a070 *ow;
        int k;
        int *old;
        int *tok;
        b->f8 = 0;
        if (g_stringPool == 0) {
            int pool = (int)StringPool_Allocate(0x10);
            if (pool != 0) pool = (int)StringPool_Construct((StringPool *)pool);
            g_stringPool = (StringPool *)pool;
        }
        tok = (int *)StringPool_Intern(g_stringPool, "IG_GFX_VC_TEXTURE_ARRAY_SIZE");
        old = (int *)b->f8;
        if (old != 0) {
            int *h = old - 2;
            int c = old[-1] - 1;
            old[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
        }
        b->f8 = (int)tok;
        if (n == 0) n = 1;
        ow = (Owner_17a070 *)Memory_FindBufferOwner(b);
        b->f16 = ow->v228(n, 0x88, 0x10);
        b->f12 = (short *)ow->v224(n, 2);
        b->s2 = n;
        b->s0 = n;
        b->s4 = n;
        for (k = 0; k < n; k++) b->f12[k] = (short)k;
        r = (Buf_17a070 *)bi;
    }
    self->f324 = r;
    self->f336 = -1;
    self->f340 = 1;
    i = 0;
    do {
        self->a564[i] = 0;
        i++;
    } while (i < 16);
    o = (T *)igIntList_Create((int)((Gap::Gfx::igVisualContext *)self)->getListMemoryPool());
    if (o != 0) o->references = o->references + 1;
    {
        T *old2 = self->f332;
        if (old2 != 0) {
            --old2->references;
            if (((unsigned long long)(long long)old2->references & 0x7fffffULL) == 0) igObject_Destroy((igObject *)old2);
        }
    }
    self->f332 = o;
    {
        T *c = self->f332;
        --c->references;
        if (((unsigned long long)(long long)c->references & 0x7fffffULL) == 0) igObject_Destroy((igObject *)c);
    }
}

void FUN_0017a540(igPsx2VisualContext *vc, int keepLists) {
    int index, s3, v, old;
    int *hd;
    T9f0 *t;
    index = ((T9f0 *)vc->_pTexList)->f0 - 1;
    for (; index > -1; index--) {
        if (((T9f0 *)vc->_pTexList)->Chk(index)) {
            ((TexContext *)vc)->vfunc_131(index);
        }
    }
    if (keepLists != 0) {
        igDataList *loaded = (igDataList *)vc->_pTexLoadedList;
        loaded->_count = 0;
        loaded = (igDataList *)vc->_pTexLoadedList;
        if ((loaded->_count > 0) == false) {
            ((Gap::Core::igDataList *)loaded)->setCapacity(0, 4);
        }
    } else {
        t = (T9f0 *)vc->_pTexList;
        if (t != 0) {
            if (g_stringPool == 0) {
                v = (int)StringPool_Allocate(16);
                if (v != 0) {
                    v = (int)StringPool_Construct((StringPool *)v);
                }
                g_stringPool = (StringPool *)v;
            }
            s3 = (int)StringPool_Intern(g_stringPool, 0);
            old = t->f8;
            if (old != 0) {
                hd = (int *)(old - 8);
                v = *(int *)(old - 4) - 1;
                *(int *)(old - 4) = v;
                if (v == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
                }
            }
            t->f8 = s3;
            Memory_FreeBuffer((void *)t->f16);
            Memory_FreeBuffer((void *)t->f12);
            if (&t->f8 != 0) {
                old = t->f8;
                if (old != 0) {
                    hd = (int *)(old - 8);
                    v = *(int *)(old - 4) - 1;
                    *(int *)(old - 4) = v;
                    if (v == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
                    }
                }
            }
            Memory_FreeBufferAliasB(t);
        }
        vc->_pTexList = 0;
        igObject::release((igObject *)vc->_pTexLoadedList);
        vc->_pTexLoadedList = 0;
    }
    if (vc->_iCLUT_A8 != -1) FUN_0016ab80((Oab80 *)vc, vc->_iCLUT_A8);
    if (vc->_iCLUT_I8 != -1) FUN_0016ab80((Oab80 *)vc, vc->_iCLUT_I8);
    if (vc->_iCLUT_IA16 != -1) FUN_0016ab80((Oab80 *)vc, vc->_iCLUT_IA16);
    if (vc->_pCLUT_I8 != 0) {
        Memory_FreeBuffer((void *)vc->_pCLUT_I8);
        vc->_pCLUT_I8 = 0;
    }
    if (vc->_pCLUT_A8 != 0) {
        Memory_FreeBuffer((void *)vc->_pCLUT_A8);
        vc->_pCLUT_A8 = 0;
    }
    if (vc->_pCLUT_IA16 != 0) {
        Memory_FreeBuffer((void *)vc->_pCLUT_IA16);
        vc->_pCLUT_IA16 = 0;
    }
    FUN_0017a870((S0_17a070 *)vc, keepLists);
}

void FUN_0017a7e0(S0_17a070 *arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int displayWidth;
    int displayHeight;
    int colorFormat;
    int depthFormat;

    FUN_0017a870(arg0, 0);
    p2GetDisplaySize(&displayWidth, &displayHeight, &colorFormat, &depthFormat);
    *(int *)((char *)(arg0) + 1524) = (int)p2LoadTexture(0, displayWidth, displayHeight, colorFormat, 1);
    *(int *)((char *)(arg0) + 1528) = (int)p2LoadTexture(0, displayWidth, displayHeight, colorFormat, 2);
    *(int *)((char *)(arg0) + 1532) = (int)p2LoadTexture(0, displayWidth, displayHeight, depthFormat, 3);
}

void FUN_0017a870(S0_17a070 *arg0, int arg1) {
    int temp_a0;
    int temp_a0_2;
    int temp_a0_3;

    if (arg1 == 0) {
        temp_a0 = arg0->f5F4;
        if (temp_a0 != 0) {
            p2FreeTexture((P2Texture *)temp_a0);
            arg0->f5F4 = 0;
        }
        temp_a0_2 = arg0->f5F8;
        if (temp_a0_2 != 0) {
            p2FreeTexture((P2Texture *)temp_a0_2);
            arg0->f5F8 = 0;
        }
        temp_a0_3 = arg0->f5FC;
        if (temp_a0_3 != 0) {
            p2FreeTexture((P2Texture *)temp_a0_3);
            arg0->f5FC = 0;
        }
    }
}

namespace Gap {
namespace Gfx {

int igPsx2VisualContext::getAvailableTextureMemory(int which) const {
    return 0;
}

void igPsx2VisualContext::setTextureStageState(int stage, bool enable) {
    struct TextureStateView117 *arg0 = (struct TextureStateView117 *)this;
    int n;
    int j;
    if (stage < 15) {
        n = stage;
    } else {
        n = 15;
    }
    if (n < 8) {
        if (arg0->a[n] == enable) {
            DAT_00560a08[n] += 1;
        }
    }
    arg0->a[n] = enable;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    p2CurrentProgram = n;
    p2CurrentGsRegisters = &p2GsRegisterSets[j];
    if (enable) {
        p2EnableCapability(1);
    } else {
        p2DisableCapability(1);
    }
    p2CurrentProgram = 0;
    p2CurrentGsRegisters = p2GsRegisterSets;
}

bool igPsx2VisualContext::getTextureStageState(int stage) const {
    return _texEnable[stage < 15 ? stage : 15];
}

int igPsx2VisualContext::createTexture(int width, int height, IG_GFX_TEXTURE_FORMAT format, IG_GFX_TEXTURE_SOURCE source, unsigned int textureMode) {
    return igPsx2VisualContext_CreateTexture((TexContext *)this, width, height, format, source, textureMode, 1);
}

int igPsx2VisualContext::createTexture(int width, int height, IG_GFX_TEXTURE_FORMAT format, IG_GFX_TEXTURE_SOURCE source, unsigned int textureMode, unsigned int imageCount)
{
    return igPsx2VisualContext_CreateTexture((TexContext *)this, width, height, format, source, textureMode, imageCount);
}
}
}

inline void adoptNewImage(MipImage *&image, AdoptReference)
{
    igVirtualObject::release(image);
    image = (MipImage *)Gap::Gfx::igImage::_instantiateFromPool(0);
}

int igPsx2VisualContext_CreateTexture(TexContext *context, int width, int height, int format, int kind, unsigned int flags,
                                       unsigned int levels)
{
    TexList *list = context->texList;
    int index;
    unsigned int mipLevels;
    TexEntry *entry;
    int i;

    if (list->freeCount <= 0) {
        list->data = (TexEntry *)(Memory_ReallocateAlignedAlias(list->data, (list->count + 4) * sizeof(TexEntry), 16));
        memset(&list->data[list->count], 0, 4 * sizeof(TexEntry));
        if (list->freeCapacity < 4) {
            list->freeIndices = ((ListAllocator *)Memory_FindBufferOwner(list))->reallocate(list->freeIndices, 8);
            list->freeCapacity = 4;
        }
        for (i = 0; i < 4; i++) {
            list->freeIndices[i] = list->count + i;
        }
        list->freeCount = 4;
        list->count += 4;
    }
    index = list->freeIndices[list->freeCount - 1];
    list->freeCount--;
    if (levels == 0) {
        levels = 1;
    }
    entry = &context->texList->data[index];
    mipLevels = levels - 1;
    FUN_0017a070((int *)entry);
    entry->width = width;
    entry->height = height;
    entry->format = format;
    entry->kind = kind;
    entry->flags = flags;
    igObject::release(entry->palette);
    entry->palette = 0;
    igVirtualObject::release(entry->image);
    entry->image = 0;
    entry->depth = -1;
    entry->mipCount = mipLevels > 6 ? 6 : mipLevels;
    entry->mipImages = 0;
    entry->buffers = ((TexMemoryPool *)((Gap::Gfx::igVisualContext *)context)->getInternalMemoryPool())->allocate(32);
    for (i = 0; i < 8; i++) {
        entry->buffers[i] = 0;
    }
    if (format < 0x10000) {
        g_gsRawCounter[0] += (unsigned int)(DAT_0048ac70[format] * (width * height));
    }
    if (format >= 0x10000) {
        g_gsRawCounter[0] += (DAT_0048aca0[format - 0x10000] * (width * height)) >> 1;
    }
    if (entry->kind == 2) {
        adoptNewImage(entry->image, AdoptReference());
        entry->image->setWidth(entry->width);
        entry->image->setHeight(entry->height);
        entry->image->setFormat(entry->format);
        entry->image->allocate(0, 0);
    }
    if (flags == 1 && mipLevels == 0) {
        int size = width < height ? width : height;
        int count = 0;

        while (size >>= 1) {
            count++;
        }
        entry->mipCount = count < 6 ? count : 6;
    }
    if (entry->mipCount != 0) {
        unsigned int mip;

        entry->mipImages = ((TexMemoryPool *)((Gap::Gfx::igVisualContext *)context)->getInternalMemoryPool())->allocateArray(4, 6);
        for (mip = 0; mip < 6; mip++) {
            entry->mipImages[mip].clear();
        }
    }
    entry->altClut = FUN_0017cb80((ClutContextCB80 *)context, format, (int *)entry);
    if (entry->width < 128 && entry->width < entry->height) {
        if ((unsigned int)entry->format <= 2 || entry->format == 4 || entry->format == 6 || entry->format == 0x10000 ||
            entry->format == 0x10001) {
            entry->width = 128;
        }
    }
    return index;
}

namespace Gap {
namespace Gfx {

bool igPsx2VisualContext::setTextureComponentSizeIntensityAlpha(int handle, int intensityBits, int alphaBits) {
    return 0;
}
}
}

struct TexBits { char pad0[112]; int pixelFormat; int redBits; int greenBits; int blueBits; int alphaBits; char pad132[4]; };
struct TexBitsList { char pad0[16]; TexBits *data; };
static inline unsigned int colourBits(unsigned int r, unsigned int g, unsigned int b) {
    if (r != 0) return r;
    if (g != 0) return g;
    return b;
}
namespace Gap {
namespace Gfx {

bool igPsx2VisualContext::setTextureComponentSize(int handle, unsigned int redBits, unsigned int greenBits, unsigned int blueBits, unsigned int alphaBits) {
    TexBits *entry = &((TexBitsList *)_pTexList)->data[handle];
    int kind;
    unsigned int bits;

    entry->redBits = redBits;
    entry->greenBits = greenBits;
    entry->blueBits = blueBits;
    entry->alphaBits = alphaBits;
    if (redBits == 0 && greenBits == 0 && blueBits == 0 && alphaBits != 0) {
        kind = 16;
        bits = alphaBits;
    } else if (alphaBits == 0) {
        if (redBits == 0 || greenBits == 0 || blueBits == 0) {
            kind = 4;
            bits = colourBits(redBits, greenBits, blueBits);
        } else {
            kind = 2;
            bits = redBits + greenBits + blueBits;
        }
    } else {
        if (redBits == 0 || greenBits == 0 || blueBits == 0) {
            kind = 8;
            bits = colourBits(redBits, greenBits, blueBits);
            bits += alphaBits;
        } else {
            kind = 1;
            bits = redBits + greenBits + blueBits + alphaBits;
        }
    }
    switch (kind) {
    case 1:
        if (bits < 9) {
            entry->pixelFormat = 6;
        } else if (bits < 17 && alphaBits < 2) {
            entry->pixelFormat = 7;
        }
        break;
    case 2:
        if (bits == 8) {
            entry->pixelFormat = 5;
        } else if (bits == 32) {
            entry->pixelFormat = 8;
        }
        break;
    case 8:
        if (bits == 8) {
            if (alphaBits == 4) {
                entry->pixelFormat = 2;
            } else if (alphaBits == 2) {
                entry->pixelFormat = 3;
            } else if (alphaBits == 1) {
                entry->pixelFormat = 4;
            }
        }
        break;
    case 4:
        if (bits == 8) {
            entry->pixelFormat = 1;
        } else if (bits == 4) {
            entry->pixelFormat = 0;
        }
        break;
    case 16:
        if (bits == 8) {
            entry->pixelFormat = 10;
        } else if (bits == 4) {
            entry->pixelFormat = 9;
        }
        break;
    default:
        return 0;
    }
    return 1;
}

void igPsx2VisualContext::getTextureComponentSizeIntensityAlpha(int handle, int &intensityBits, int &alphaBits, bool &palletized) const {

}

void igPsx2VisualContext::getTextureComponentSize(int handle, int &redBits, int &greenBits, int &blueBits, int &alphaBits, bool &palletized) const {
    TexBits *entry = &((TexBitsList *)_pTexList)->data[handle];

    redBits = entry->redBits;
    greenBits = entry->greenBits;
    blueBits = entry->blueBits;
    alphaBits = entry->alphaBits;
    palletized = 0;
}

bool igPsx2VisualContext::loadTexture(int texHandle)
{
    return setTexture(texHandle, 0);
}

bool igPsx2VisualContext::setTexture(int texHandle, int stage)
{
    bool result;
    bool clutDirty;
    ClutEntry *clut;
    int clutIndex = -1;
    TexEntry *entry;
    bool enabled;
    bool reload;
    int isTarget;

    if (texHandle == -1) {
        p2MarkTextureStage(stage);
        return false;
    }
    entry = &((TexList *)_pTexList)->data[texHandle];
    result = true;
    clutDirty = false;
    clut = 0;
    enabled = result;
    if (g_igPsx2DisableExt_ext0Enabled) {
        enabled = false;
    }
    if (!enabled) {
        return true;
    }
    if (entry->buffers[0] == 0) {
        FUN_0017b5f0((TexContext *)this, entry);
    }
    if (entry->clut >= 0 || entry->altClut >= 0) {
        if (entry->clut >= 0) {
            clut = &((ClutList *)_pClutList)->data[entry->clut];
            clutIndex = entry->clut;
        } else if (entry->altClut >= 0) {
            clut = &((ClutList *)_pClutList)->data[entry->altClut];
            clutIndex = entry->altClut;
        }
        if (clut->data->dirty) {
            clutDirty = true;
        }
    }
    isTarget = entry != 0;
    if (isTarget) {
        isTarget = entry->kind == 2;
    }
    reload = false;
    if (isTarget && entry->reload) {
        reload = true;
    }
    if (_currentTex != texHandle || entry->stage != stage || clutDirty || reload) {
        if (reload) {
            entry->reload = false;
            p2SetTextureImage((P2Texture *)entry->buffers[0], (void *)entry->image->pixels);
        }
        FUN_0017b400((TexContext *)this, entry, stage, clut, clutIndex);
        entry->stage = stage;
        _currentTex = texHandle;
        result = FUN_0020bb20((P2Texture **)entry->buffers, stage, (unsigned char)!_texPageEnable) != 0;
    }
    return result;
}
}
}

void FUN_0017b5f0(TexContext *context, TexEntry *entry)
{
    int level = 0;
    int format;
    int count;

    if (Gap::Gfx::igImage::isIndexed((IG_GFX_TEXTURE_FORMAT)entry->format)) {
        format = DAT_0048acb0[entry->format - 0x10000];
    } else {
        format = DAT_0048ac40[entry->format];
    }
    entry->buffers[0] = (int)p2LoadTexture((void *)(entry->image ? entry->image->pixels : 0), entry->width, entry->height, format, 0);
    level++;
    count = entry->mipCount;
    if (count != 0) {
        if (entry->flags & 1) {
            int width = entry->width;
            int height = entry->height;
            igSmartPointer<MipImage> previous(entry->image, kRetainReference);
            int i;

            for (i = 0; i < count; i++) {
                igSmartPointer<MipImage> mip((MipImage *)Gap::Gfx::igImage::_instantiateFromPool((igMemoryPoolView *)((Gap::Gfx::igVisualContext *)context)->getImageMemoryPool()));
                int mipFormat;

                mip->reduceFrom(previous);
                entry->mipImages[i] = mip;
                if (Gap::Gfx::igImage::isIndexed((IG_GFX_TEXTURE_FORMAT)entry->format)) {
                    mipFormat = DAT_0048acb0[entry->format - 0x10000];
                } else {
                    mipFormat = DAT_0048ac40[entry->format];
                }
                entry->buffers[level] = (int)p2LoadTexture((void *)mip->pixels, mip->width, mip->height, mipFormat, 0);
                p2ChainTexture((P2Texture *)entry->buffers[0], (P2Texture *)entry->buffers[level]);
                level++;
                width >>= 1;
                height >>= 1;
                previous = mip;
                if (width <= 0) {
                    width = 1;
                }
                if (height <= 0) {
                    height = 1;
                }
            }
            entry->flags &= ~1;
        } else {
            unsigned int i;

            for (i = 0; i < entry->mipCount; i++) {
                int mipFormat;
                MipImage *mip;

                if (Gap::Gfx::igImage::isIndexed((IG_GFX_TEXTURE_FORMAT)entry->format)) {
                    mipFormat = DAT_0048acb0[entry->format - 0x10000];
                } else {
                    mipFormat = DAT_0048ac40[entry->format];
                }
                mip = entry->mipImages[i];
                entry->buffers[level] = (int)p2LoadTexture((void *)mip->pixels, mip->width, mip->height, mipFormat, 0);
                p2ChainTexture((P2Texture *)entry->buffers[0], (P2Texture *)entry->buffers[level]);
                level++;
            }
        }
    }
    if (entry->clut >= 0 || entry->altClut >= 0) {
        entry->bufferIndex = level;
    }
}

namespace Gap {
namespace Gfx {

int igPsx2VisualContext::getCurrentTexture(int stage) const {
    return _currentTex;
}

void igPsx2VisualContext::unloadTexture(int texHandle) {
    UCodeContextView *context = (UCodeContextView *)this;
    UCodeSlot *slot = &context->slots->_data[texHandle];
    int i;

    context->current = -1;
    if (slot->handle >= 0) {
        if (slot->program->resident != 0) {
            FUN_0016b1d0((OB1d0 *)context, slot->handle);
        }
        slot->buffers[slot->bufferIndex] = 0;
    } else if (slot->altHandle >= 0) {
        FUN_0016b1d0((OB1d0 *)context, slot->altHandle);
        slot->buffers[slot->bufferIndex] = 0;
    }
    if (slot->kind == 3) {
        if (slot->buffers[0] != 0) {
            p2FenceUsedTexture((P2Texture *)slot->buffers[0]);
            if (slot->buffer != 0) {
                p2FenceUsedTexture((P2Texture *)slot->buffer);
            }
        }
    } else if (slot->buffers != 0) {
        for (i = 0; i < 8; i++) {
            if (slot->buffers[i] != 0) {
                p2WaitDmaSequence(2, p2GetTextureUploadSequence((P2Texture *)slot->buffers[i]));
                p2FreeTexture((P2Texture *)slot->buffers[i]);
                slot->buffers[i] = 0;
            }
        }
    }
}

void igPsx2VisualContext::deleteTexture(int texHandle)
{
    TexEntry *entry = &((TexList *)_pTexList)->data[texHandle];
    TexList *list;

    ((Gap::Gfx::igVisualContext *)this)->unloadTexture(texHandle);
    if (entry->clut >= 0) {
        ClutObject *clut = entry->image->clut;
        if (clut != 0 && clut->locked == 0) {
            FUN_0016ab80((Oab80 *)this, entry->clut);
            clut->handle = -1;
        }
    }
    if (entry->kind == 3 && entry->buffers[0] != 0) {
        p2FreeTexture((P2Texture *)entry->buffers[0]);
        if (entry->buffer != 0) {
            p2FreeTexture((P2Texture *)entry->buffer);
        }
    }
    if (entry->format < 0x10000) {
        g_gsRawCounter[0] += -(DAT_0048ac70[entry->format] * (entry->width * entry->height));
    }
    if (entry->format >= 0x10000) {
        g_gsRawCounter[0] += (int)-((DAT_0048aca0[entry->format - 0x10000] * (entry->width * entry->height)) >> 1);
    }
    FUN_0017a180(entry);
    list = (TexList *)_pTexList;
    if (texHandle < list->count && texHandle >= 0) {
        if (list->freeCount >= list->freeCapacity) {
            ListAllocator *allocator = (ListAllocator *)Memory_FindBufferOwner(list);
            list->freeCapacity += 8;
            list->freeIndices = allocator->reallocate(list->freeIndices, list->freeCapacity * 2);
        }
        list->freeIndices[list->freeCount] = texHandle;
        list->freeCount++;
    }
}

bool igPsx2VisualContext::setTextureSource(int handle, igImage *image)
{
    return setTextureSource(handle, image, 0);
}

bool igPsx2VisualContext::setTextureSource(int handle, void *buffer) {
    int a0;
    int var_a3;
    int var_a4;
    char *s0;

    s0 = (char *)(*(int *)((char *)(_pTexList) + 16) + (handle * 0x88));
    if (*(int *)(s0 + 20) != 2 || *(int *)(s0 + 72) == 0) {
        return 0;
    }
    a0 = *(int *)(s0 + 0);
    var_a4 = 1;
    var_a3 = 1;
    if (a0 < 0x10000) {
        var_a4 = DAT_0048ac70[a0];
    } else if (a0 == 0x10001) {
        var_a3 = 2;
    }
    TextureImageView260 *c = *(TextureImageView260 **)(s0 + 52);
    c->vX((int)buffer, (var_a4 * (*(int *)(s0 + 32) * *(int *)(s0 + 36))) / var_a3, var_a3, var_a4);
    *(char *)(s0 + 81) = 1;
    return 1;
}

igImage *igPsx2VisualContext::getTextureImage(int handle) const {
    return (igImage *)*(int *)((char *)((*(int *)((char *)(_pTexList) + 16) + (handle * 0x88))) + 48);
}

bool igPsx2VisualContext::setTextureSource(int handle, int srcHandle) {
    return 0;
}

void igPsx2VisualContext::setTextureMinificationFilter(int handle, IG_GFX_TEXTURE_FILTER filter) {
    int temp_a3;

    temp_a3 = handle * 0x88;
    if (filter == *(int *)((char *)((TextureList138 *)_pTexList)->f16 + temp_a3 + 4)) {
        DAT_00560a28[0] += 1;
    }
    *(int *)((char *)((TextureList138 *)_pTexList)->f16 + temp_a3 + 4) = filter;
    *(char *)((char *)((TextureList138 *)_pTexList)->f16 + temp_a3 + 80) = 1;
}

void igPsx2VisualContext::setTextureMagnificationFilter(int handle, IG_GFX_TEXTURE_FILTER filter) {
    struct TextureEntry140 *e = ((struct TextureList140 *)_pTexList)->arr + handle; if (filter == e->v) { DAT_00560a2c[0] += 1; } e = ((struct TextureList140 *)_pTexList)->arr + handle; e->v = filter; e = ((struct TextureList140 *)_pTexList)->arr + handle; e->flag = 1;
}

IG_GFX_TEXTURE_FILTER igPsx2VisualContext::getTextureMinificationFilter(int handle) const {
    return (IG_GFX_TEXTURE_FILTER)*(int *)((char *)((*(int *)((char *)(_pTexList) + 16) + (handle * 0x88))) + 4);
}

IG_GFX_TEXTURE_FILTER igPsx2VisualContext::getTextureMagnificationFilter(int handle) const {
    return (IG_GFX_TEXTURE_FILTER)*(int *)((char *)((*(int *)((char *)(_pTexList) + 16) + (handle * 0x88))) + 8);
}

void igPsx2VisualContext::setTextureAddressingMode(int handle, IG_GFX_TEXTURE_WRAP wrapU, IG_GFX_TEXTURE_WRAP wrapV) {
    int temp_v1;
    temp_v1 = handle * 0x88;
    if (wrapU == *(int *)(((struct TextureList136 *)_pTexList)->e + temp_v1 + 12)) {
        DAT_00560a34[0] += 1;
    }
    if (wrapV == *(int *)(((struct TextureList136 *)_pTexList)->e + temp_v1 + 16)) {
        DAT_00560a38[0] += 1;
    }
    *(int *)(((struct TextureList136 *)_pTexList)->e + temp_v1 + 12) = wrapU;
    *(int *)(((struct TextureList136 *)_pTexList)->e + temp_v1 + 16) = wrapV;
    *(char *)(((struct TextureList136 *)_pTexList)->e + temp_v1 + 80) = 1;
}

void igPsx2VisualContext::getTextureAddressingMode(int handle, IG_GFX_TEXTURE_WRAP &wrapU, IG_GFX_TEXTURE_WRAP &wrapV) const {
    int temp_a1;

    temp_a1 = handle * 0x88;
    wrapU = (IG_GFX_TEXTURE_WRAP) *(int *)((char *)((*(int *)((char *)(_pTexList) + 16) + temp_a1)) + 12);
    wrapV = (IG_GFX_TEXTURE_WRAP) *(int *)((char *)((*(int *)((char *)(_pTexList) + 16) + temp_a1)) + 16);
}
}
}

void FUN_0017c6e0(int arg0) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_a3;
    void *temp_a2;

    var_a3 = 0;
    do {
        temp_a2 = (void *)(arg0 + (var_a3 * 4));
        var_a3 += 1;
        *(int *)((char *)(temp_a2) + 580) = 1;
        *(int *)((char *)(temp_a2) + 644) = 0;
    } while (var_a3 < 0x10);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setTextureMatrixProjectiveState(int stage, unsigned char enable) {
    if (stage < 8) {
        if (_currentTextureProjectiveState[stage] == enable) {
            DAT_00560a3c[stage] = DAT_00560a3c[stage] + 1;
        }
    }
    _currentTextureProjectiveState[stage] = enable;
    if (stage == 0) {
        if (enable) {
            p2EnableCapability(0x1A);
            return;
        }
        p2DisableCapability(0x1A);
    }
}

unsigned char igPsx2VisualContext::getTextureMatrixProjectiveState(int stage) {
    return _currentTextureProjectiveState[stage];
}

void igPsx2VisualContext::setTextureStageFunc(int stage, int func) {
    VisualContextSlots *arg0 = (VisualContextSlots *)this;
    int a3;
    stage = stage < 15 ? stage : 15;
    if (stage < 8) {
        if (arg0->slot[stage] == func) {
            DAT_00560a5c[stage] += 1;
        }
    }
    arg0->slot[stage] = func;
    a3 = stage > 1 ? stage - 1 : 0;
p2CurrentProgram = stage; p2CurrentGsRegisters = &p2GsRegisterSets[a3]; p2SetTextureFunction(DAT_0048acf0[func]);
    p2CurrentProgram = 0;
    p2CurrentGsRegisters = p2GsRegisterSets;
}
}
}

void FUN_0017c880(igPsx2VisualContext *arg0, int arg1, unsigned char arg2) {
    FUN_0017c8a0(arg0, 0, arg1, arg2);
}

void FUN_0017c8a0(igPsx2VisualContext *context, int stage, int function, unsigned char colorComponent) {
    int n;
    int j;

    if (stage < 15) {
        n = stage;
    } else {
        n = 15;
    }
    if (n < 8) {
        if (context->_texStageFunc[n] == function) {
            DAT_00560a5c[n] += 1;
        }
    }
    context->_texStageFunc[n] = function;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    p2CurrentProgram = n;
    p2CurrentGsRegisters = &p2GsRegisterSets[j];
    context->_bTextureColorComponent = colorComponent;
    p2SetTextureFunctionAndAlpha(DAT_0048acf0[function], colorComponent);
    p2CurrentProgram = 0;
    p2CurrentGsRegisters = p2GsRegisterSets;
}

namespace Gap {
namespace Gfx {

int igPsx2VisualContext::getTextureStageFunc(int stage) const {
    int arg0 = (int)(::igPsx2VisualContext *)this;
 int i = stage < 15 ? stage : 15; int off = i * 4; int *p = (int *)(off + (int)arg0); return p[145];
}

void igPsx2VisualContext::setTextureStageCoordSource(int stage, IG_GFX_TEXTURE_COORD_SOURCE source, int coordIndex) {
    struct TextureStageView150 *p = (struct TextureStageView150 *)this;
    int i;
    stage = stage < 15 ? stage : 15;
    if (stage < 8) {
        if (p->a[stage] == source) {
            DAT_00560a7c[stage] += 1;
        }
        if (p->b[stage] == coordIndex) {
            DAT_00560a9c[stage] += 1;
        }
    }
    p->a[stage] = source;
    p->b[stage] = coordIndex;
    if (stage > 1) {
        i = stage - 1;
    } else {
        i = 0;
    }
    p2CurrentProgram = stage;
    p2CurrentGsRegisters = &p2GsRegisterSets[i];
    switch (source) {
    case 0:
        p2DisableCapability(10);
        break;
    case 2:
        p2EnableCapability(10);
        p2SetTextureCombineMode(1);
        break;
    case 1:
        p2EnableCapability(10);
        p2SetTextureCombineMode(0);
        break;
    case 3:
        p2EnableCapability(10);
        p2SetTextureCombineMode(3);
        break;
    case 5:
        p2EnableCapability(10);
        p2SetTextureCombineMode(2);
        break;
    }
    p2CurrentProgram = 0;
    p2CurrentGsRegisters = &p2GsRegisterSets[0];
}

/* The base is kept in its own local rather than written back into the parameter; otherwise the add
 * is emitted with the operands swapped. */
void igPsx2VisualContext::getTextureStageCoordSource(int stage, IG_GFX_TEXTURE_COORD_SOURCE &source, int &coordIndex) const {
    int arg0 = (int)(::igPsx2VisualContext *)this;
    int i = stage < 15 ? stage : 15;
    int off = i * 4;
    int p = off + arg0;
    source = (IG_GFX_TEXTURE_COORD_SOURCE) *(int *)(p + 644);
    coordIndex = *(int *)(p + 708);
}
}
}

int FUN_0017cb80(struct ClutContextCB80 *arg0, int arg1, int *arg2) {
    int result = 0;
    int r = -1;
    switch (arg1) {
    case 0:
        if (arg0->f836 == -1) {
            arg0->f836 = FUN_0017ccb0(arg0, 0, 8, &result);
            arg0->f852 = result;
        }
        r = arg0->f836;
        *arg2 = 0x10000;
        break;
    case 1:
        if (arg0->f840 == -1) {
            arg0->f840 = FUN_0017ccb0(arg0, 8, 0, &result);
            arg0->f856 = result;
        }
        r = arg0->f840;
        *arg2 = 0x10000;
        break;
    case 3:
    case 2:
        if (arg0->f844 == -1) {
            arg0->f844 = FUN_0017ccb0(arg0, 4, 4, &result);
            arg0->f860 = result;
        }
        *arg2 = 0x10000;
        r = arg0->f844;
        break;
    case 9:
        *arg2 = 7;
        break;
    case 10:
        *arg2 = 8;
        break;
    }
    return r;
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setTextureRegion(int handle, int iLevel, int offsetX, int offsetY, int width, int height, igImage *image) {

}
}
}

