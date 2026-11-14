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
            levels = p2GetDisplayListBlendWeightCount(arg3);
            limit = p2GetDisplayListBlendMatrixCount(arg3);
            if (levels != 0) {
                enabled = true;
                if (levels > 0 && levels < 5 && vc->_blendMatricesCount < 121 && !GPR_00554b6c
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
                if (levels > 0 && levels < 5 && vc->_blendMatricesCount < 121 && !GPR_00554b6c) {
                    result = 2;
                    p2SetBlendIndexArray(va->f36);
                    p2SetBlendWeightArray(va->f32);
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

int FUN_001774c0(igPsx2VisualContext *vc, Geometry1774 *geom, unsigned char *useTexture) {
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
    *useTexture = 0;
    if (vc->_bVertexBlendingEnabled) {
        matrices = 0;
        texture = 0;
        if (prebuilt) {
            levels = geom->f120;
            limit = geom->f116;
        } else {
            attrs = geom->attrs;
            node = (AttrNode1774 *)FUN_0015f4a0((S_15f430 *)attrs, 6, 0);
            int m1 = g_igUnsignedCharList_metaObject[0]; /* matching construct: spelling sweep — the compared metas are locals, spilled with sw */
            if (m1 == node->obj->meta()) {
                matrices = node->obj->f16;
                levels = node->f24;
            } else {
                int m2 = DAT_005610b0[0];
                if (m2 == node->obj->meta()) {
                    matrices = node->obj->f16;
                    levels = 3;
                } else {
                    int m3 = g_igVec4ucList_metaObject[0];
                    if (m3 == node->obj->meta()) {
                        levels = 3;
                        matrices = node->obj->f16;
                    }
                }
            }
            node = (AttrNode1774 *)FUN_0015f4a0((S_15f430 *)attrs, 5, 0);
            if (node != 0) {
                value = node->obj;
                if (value->meta() == g_igCharList_metaObject[0]) {
                    int a = node->f32;
                    p2SetComponentLayout(3, 1, 7 - a, a);
                    texture = value->f16;
                    *useTexture = 1;
                } else if (node->obj->meta() == g_igUnsignedCharList_metaObject[0]) {
                    int a = node->f32;
                    p2SetComponentLayout(3, 0, 8 - a, a);
                    texture = value->f16;
                    *useTexture = 1;
                } else if (node->obj->meta() == g_igShortList_metaObject[0]) {
                    int a = node->f32;
                    p2SetComponentLayout(3, 1, 0xF - a, a);
                    texture = value->f16;
                    *useTexture = 1;
                } else if (node->obj->meta() == g_igUnsignedShortList_metaObject[0]) {
                    int a = node->f32;
                    p2SetComponentLayout(3, 0, 0x10 - a, a);
                    texture = value->f16;
                    *useTexture = 1;
                } else {
                    texture = node->obj->f16;
                }
            }
            limit = vc->_blendMatricesCount;
        }
        if (levels > 0 && levels < 5 && vc->_blendMatricesCount < 121 && !GPR_00554b6c && limit >= vc->_blendMatricesCount) {
            result = 2;
            if (!prebuilt) {
                p2SetBlendIndexArray(matrices);
                p2SetBlendWeightArray(texture);
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

void Gap__Gfx__igPsx2VisualContext__vfunc_256(igPsx2VisualContextSlots *self)
{
    self->vfunc_255();
}

bool Gap__Gfx__igPsx2VisualContext__vfunc_257(void *context, unsigned int capability) {
    bool supported = false;
    switch (capability) {
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

bool Gap__Gfx__igPsx2VisualContext__vfunc_255(igPsx2VisualContextStats *self, unsigned int capability, unsigned char enabled)
{
    StatNodeView *node;

    bool supported = self->supports(capability);
    if (supported) {
        if (capability == 31) {
            DAT_00554b70 = enabled;
        }
        if (capability == 34) {
            DAT_00554b74 = enabled;
        }
        if (capability == 31) {
        } else if (capability == 34) {
        } else if (capability == 57) {
            for (node = self->nodes; node != 0; node = node->next) {
                node->f16 = 1;
                node->f8 = 0;
            }
        }
    }
    return supported;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_258(void) {
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
    FUN_001f6f50(&g_gsStatCurrent, DAT_00560ed0[0], DAT_00560ec8[0], DAT_00560ea0[0]);
}

float Gap__Gfx__igPsx2VisualContext__vfunc_259(void *unused, int id) {
    float result = -1.0f;
    float elapsed = DELTA(5);
    if (!(elapsed <= 0.0f)) {
        switch (id) {
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
        if (id >= 60 && id < 187) {
            result = (float)g_gsEventCount[id] / elapsed;
            g_gsEventCount[id] = 0;
        }
    }
    if (result == -1.0f) {
        if (id == 42) {
            GsStatBlock snapshot;
            FUN_001f6f50(&snapshot);
            result = (float)snapshot.c[3];
        } else if (id == 43) {
            GsStatBlock snapshot;
            FUN_001f6f50(&snapshot);
            result = (float)snapshot.c[4];
        }
    }
    return result;
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
                igObject_Destroy(temp_a0);
            }
            ((StatAllocator *)FUN_00165d00((int *)arg0))->vX(temp_s1);
        } while (temp_s0 != 0);
    }
    arg0->f610 = 0;
}

void FUN_00179e00(StatContext *arg0) {
    int s3;
    int s2;
    int idx;
    StatNode *n;
    int a1;
    Ref_1778e0 sp6C((O_1778e0 *)igStringObj_Create(FUN_00165d00((int *)arg0)));
    Ref_1778e0 sp68((O_1778e0 *)igStringObj_Create(FUN_00165d00((int *)arg0)));
    s3 = ((G_1778e0 *)g_objectSystem[0])->f56;
    s2 = 0;
    igStringObj_Set((O_1778e0 *)sp6C, STATISTICS_CAPTURE);
    igStringObj_SetInt(sp68, 0, DAT_004de6a8);
    { int y = sp68->f12; int x = sp6C->f12;
    a1 = sp68->f8;
    if (a1 == 0) a1 = g_stringObjEmptyText[0];
    igStringObj_Insert(sp6C, a1, x, y); }
    while ((idx = igRegistry_GetSectionIndex(s3, sp6C->f8 == 0 ? g_stringObjEmptyText[0] : sp6C->f8, 0)) != -1) {
        n = (StatNode *)((StatAllocator *)FUN_00165d00((int *)arg0))->v52(960);
        if (n == 0) break;
        n->f16 = 1;
        n->f0 = s2;
        thunk_igRegistry_GetValueInt(s3, idx, text_numCapture, &n->f4, 1, 0);
        thunk_igRegistry_GetValueInt(s3, idx, text_startCapture, &n->f8, -1 - n->f4, 0);
        n->f12 = (O_1778e0 *)((O_1778e0 *)igStringObj_Create(FUN_00165d00((int *)arg0)));
        thunk_igRegistry_GetValueStringObj(s3, idx, text_stringCapture, &n->f12, DAT_004dc870, 0);
        s2 += 1;
        n->f952 = arg0->f1552;
        arg0->f1552 = n;
        igStringObj_SetInt(sp68, s2, DAT_004de6a8);
        igStringObj_Set((O_1778e0 *)sp6C, STATISTICS_CAPTURE);
        { int y = sp68->f12; int x = sp6C->f12;
        a1 = sp68->f8;
        if (a1 == 0) a1 = g_stringObjEmptyText[0];
        igStringObj_Insert(sp6C, a1, x, y); }
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
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)temp_a0->_refCount - 1;
        if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    a[12] = 0;
    temp_a0_2 = (igObject *)(a[13]);
    if (temp_a0_2 != 0) {
        temp_a0_2->_refCount = (int)temp_a0_2->_refCount - 1;
        if ((temp_a0_2->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
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
            igObject_Destroy(o);
        }
    }
    arg0->f52 = 0;
    o = arg0->f48;
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
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
                    igObject_Destroy(o);
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
    int sp5C;
    int bi;
    Buf_17a070 *b;
    T *o;
    int i;
    sp5C = 0x40;
    thunk_igRegistry_GetValueInt(*(int *)((char *)g_objectSystem[0] + 56), 4, IG_GFX_VC_TEXTURE_ARRAY_SIZE, &sp5C, 0x40, 0);
    Buf_17a070 *r = (Buf_17a070 *)Memory_AllocateBufferDirect(0x14, FUN_00165d10((int *)self));
    if (r != 0) {
        bi = (int)r;
        b = (Buf_17a070 *)bi;
        int n = sp5C;
        Owner_17a070 *ow;
        int k;
        int *old;
        int *tok;
        b->f8 = 0;
        if (g_stringPool[0] == 0) {
            int pool = StringPool_Allocate(0x10);
            if (pool != 0) pool = StringPool_Construct(pool);
            g_stringPool[0] = pool;
        }
        tok = (int *)StringPool_Intern(g_stringPool[0], IG_GFX_VC_TEXTURE_ARRAY_SIZE);
        old = (int *)b->f8;
        if (old != 0) {
            int *h = old - 2;
            int c = old[-1] - 1;
            old[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
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
    o = (T *)igIntList_Create(FUN_00165d10((int *)self));
    if (o != 0) o->references = o->references + 1;
    {
        T *old2 = self->f332;
        if (old2 != 0) {
            --old2->references;
            if (((unsigned long long)(long long)old2->references & 0x7fffffULL) == 0) igObject_Destroy(old2);
        }
    }
    self->f332 = o;
    {
        T *c = self->f332;
        --c->references;
        if (((unsigned long long)(long long)c->references & 0x7fffffULL) == 0) igObject_Destroy(c);
    }
}

void FUN_0017a7e0(S0_17a070 *arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int sp2C;
    int sp28;
    int sp24;
    int sp20;

    FUN_0017a870(arg0, 0);
    p2GetDisplaySize(&sp2C, &sp28, &sp24, &sp20);
    *(int *)((char *)(arg0) + 1524) = p2LoadTexture(0, sp2C, sp28, sp24, 1);
    *(int *)((char *)(arg0) + 1528) = p2LoadTexture(0, sp2C, sp28, sp24, 2);
    *(int *)((char *)(arg0) + 1532) = p2LoadTexture(0, sp2C, sp28, sp20, 3);
}

void FUN_0017a870(S0_17a070 *arg0, int arg1) {
    int temp_a0;
    int temp_a0_2;
    int temp_a0_3;

    if (arg1 == 0) {
        temp_a0 = arg0->f5F4;
        if (temp_a0 != 0) {
            FUN_0020c9f0(temp_a0);
            arg0->f5F4 = 0;
        }
        temp_a0_2 = arg0->f5F8;
        if (temp_a0_2 != 0) {
            FUN_0020c9f0(temp_a0_2);
            arg0->f5F8 = 0;
        }
        temp_a0_3 = arg0->f5FC;
        if (temp_a0_3 != 0) {
            FUN_0020c9f0(temp_a0_3);
            arg0->f5FC = 0;
        }
    }
}

int Gap__Gfx__igPsx2VisualContext__vfunc_142(void) {
    return 0;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_117(struct TextureStateView117 *arg0, int arg1, int arg2) {
    int n;
    int j;
    if (arg1 < 15) {
        n = arg1;
    } else {
        n = 15;
    }
    if (n < 8) {
        if (arg0->a[n] == (arg2 & 0xFF)) {
            DAT_00560a08[n] += 1;
        }
    }
    arg0->a[n] = arg2;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    p2CurrentProgram[0] = n;
    p2CurrentGsRegisters[0] = &p2GsRegisterSets[j];
    if (arg2 != 0) {
        p2EnableCapability(1, n);
    } else {
        p2DisableCapability(1, n);
    }
    p2CurrentProgram[0] = 0;
    p2CurrentGsRegisters[0] = p2GsRegisterSets;
}

unsigned char Gap__Gfx__igPsx2VisualContext__vfunc_118(int arg0, int arg1) { int i = (arg1 < 15 ? arg1 : 15); return *(unsigned char *)(i + arg0 + 564); }

void Gap__Gfx__igPsx2VisualContext__vfunc_120(TexContext *a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    FUN_0017aa20(a0, a1, a2, a3, a4, a5, 1);
}

int thunk_FUN_0017aa20(TexContext *context, int width, int height, int format, int kind, unsigned int flags, unsigned int levels)
{
    return FUN_0017aa20(context, width, height, format, kind, flags, levels);
}

inline void adoptNewImage(MipImage *&image, AdoptReference)
{
    igRelease(image);
    image = (MipImage *)FUN_0014df70(0);
}

int FUN_0017aa20(TexContext *context, int width, int height, int format, int kind, unsigned int flags,
                                       unsigned int levels)
{
    TexList *list = context->texList;
    int index;
    unsigned int mipLevels;
    TexEntry *entry;
    int i;

    if (list->freeCount <= 0) {
        list->data = (TexEntry *)(thunk_Memory_ReallocateAligned(list->data, (list->count + 4) * sizeof(TexEntry), 16));
        memset(&list->data[list->count], 0, 4 * sizeof(TexEntry));
        if (list->freeCapacity < 4) {
            list->freeIndices = FUN_002ed520(list)->reallocate(list->freeIndices, 8);
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
    igRelease(entry->palette);
    entry->palette = 0;
    igRelease(entry->image);
    entry->image = 0;
    entry->depth = -1;
    entry->mipCount = mipLevels > 6 ? 6 : mipLevels;
    entry->mipImages = 0;
    entry->buffers = ((TexMemoryPool *)FUN_00165ce0((int *)context))->allocate(32);
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

        entry->mipImages = ((TexMemoryPool *)FUN_00165ce0((int *)context))->allocateArray(4, 6);
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

int Gap__Gfx__igPsx2VisualContext__vfunc_124(void) {
    return 0;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_126(void) {

}

void Gap__Gfx__igPsx2VisualContext__vfunc_125(igPsx2VisualContext *arg0, int arg1, int *arg2, int *arg3, int *arg4, int *arg5, char *arg6) {
    void *temp_a0;

    temp_a0 = (void *)(*(int *)((char *)(arg0->_pTexList) + 16) + (arg1 * 0x88));
    *arg2 = *(int *)((char *)(temp_a0) + 116);
    *arg3 = *(int *)((char *)(temp_a0) + 120);
    *arg4 = *(int *)((char *)(temp_a0) + 124);
    *arg5 = *(int *)((char *)(temp_a0) + 128);
    *arg6 = 0;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_128(igPsx2VisualContextSlots_17a070 *self, int value, int option)
{
    self->vfunc_125(value, 0);
}

bool Gap__Gfx__igPsx2VisualContext__vfunc_127(TexContext *context, int index, int stage)
{
    bool result;
    bool clutDirty;
    ClutEntry *clut;
    int clutIndex = -1;
    TexEntry *entry;
    bool enabled;
    bool reload;
    int isTarget;

    if (index == -1) {
        FUN_0020c880(stage);
        return false;
    }
    entry = &context->texList->data[index];
    result = true;
    clutDirty = false;
    clut = 0;
    enabled = result;
    if (DAT_00554b78) {
        enabled = false;
    }
    if (!enabled) {
        return true;
    }
    if (entry->buffers[0] == 0) {
        FUN_0017b5f0(context, entry);
    }
    if (entry->clut >= 0 || entry->altClut >= 0) {
        if (entry->clut >= 0) {
            clut = &context->clutList->data[entry->clut];
            clutIndex = entry->clut;
        } else if (entry->altClut >= 0) {
            clut = &context->clutList->data[entry->altClut];
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
    if (context->currentTex != index || entry->stage != stage || clutDirty || reload) {
        if (reload) {
            entry->reload = false;
            FUN_0020c840(entry->buffers[0], entry->image->pixels);
        }
        FUN_0017b400(context, entry, stage, clut, clutIndex);
        entry->stage = stage;
        context->currentTex = index;
        result = FUN_0020bb20(entry->buffers, stage, (unsigned char)!context->texPageEnable) != 0;
    }
    return result;
}

void FUN_0017b5f0(TexContext *context, TexEntry *entry)
{
    int level = 0;
    int format;
    int count;

    if (FUN_00159f70(entry->format)) {
        format = DAT_0048acb0[entry->format - 0x10000];
    } else {
        format = DAT_0048ac40[entry->format];
    }
    entry->buffers[0] = p2LoadTexture(entry->image ? entry->image->pixels : 0, entry->width, entry->height, format, 0);
    level++;
    count = entry->mipCount;
    if (count != 0) {
        if (entry->flags & 1) {
            int width = entry->width;
            int height = entry->height;
            igSmartPointer<MipImage> previous(entry->image, kRetainReference);
            int i;

            for (i = 0; i < count; i++) {
                igSmartPointer<MipImage> mip((MipImage *)FUN_0014df70(FUN_00165cf0((int *)context)));
                int mipFormat;

                mip->reduceFrom(previous);
                entry->mipImages[i] = mip;
                if (FUN_00159f70(entry->format)) {
                    mipFormat = DAT_0048acb0[entry->format - 0x10000];
                } else {
                    mipFormat = DAT_0048ac40[entry->format];
                }
                entry->buffers[level] = p2LoadTexture(mip->pixels, mip->width, mip->height, mipFormat, 0);
                FUN_0020c7b0(entry->buffers[0], entry->buffers[level]);
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

                if (FUN_00159f70(entry->format)) {
                    mipFormat = DAT_0048acb0[entry->format - 0x10000];
                } else {
                    mipFormat = DAT_0048ac40[entry->format];
                }
                mip = entry->mipImages[i];
                entry->buffers[level] = p2LoadTexture(mip->pixels, mip->width, mip->height, mipFormat, 0);
                FUN_0020c7b0(entry->buffers[0], entry->buffers[level]);
                level++;
            }
        }
    }
    if (entry->clut >= 0 || entry->altClut >= 0) {
        entry->bufferIndex = level;
    }
}

int Gap__Gfx__igPsx2VisualContext__vfunc_129(void *arg0) {
    return *(int *)((char *)(arg0) + 336);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_130(UCodeContextView *context, int index) {
    UCodeSlot *slot = &context->slots->_data[index];
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
            FUN_0020c8b0(slot->buffers[0]);
            if (slot->buffer != 0) {
                FUN_0020c8b0(slot->buffer);
            }
        }
    } else if (slot->buffers != 0) {
        for (i = 0; i < 8; i++) {
            if (slot->buffers[i] != 0) {
                p2WaitDmaSequence(2, FUN_0020b270(slot->buffers[i]));
                FUN_0020c9f0(slot->buffers[i]);
                slot->buffers[i] = 0;
            }
        }
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_131(TexContext *context, int index)
{
    TexEntry *entry = &context->texList->data[index];
    TexList *list;

    context->unloadTexture(index);
    if (entry->clut >= 0) {
        ClutObject *clut = entry->image->clut;
        if (clut != 0 && clut->locked == 0) {
            FUN_0016ab80((Oab80 *)context, entry->clut);
            clut->handle = -1;
        }
    }
    if (entry->kind == 3 && entry->buffers[0] != 0) {
        FUN_0020c9f0(entry->buffers[0]);
        if (entry->buffer != 0) {
            FUN_0020c9f0(entry->buffer);
        }
    }
    if (entry->format < 0x10000) {
        g_gsRawCounter[0] += -(DAT_0048ac70[entry->format] * (entry->width * entry->height));
    }
    if (entry->format >= 0x10000) {
        g_gsRawCounter[0] += (int)-((DAT_0048aca0[entry->format - 0x10000] * (entry->width * entry->height)) >> 1);
    }
    FUN_0017a180(entry);
    list = context->texList;
    if (index < list->count && index >= 0) {
        if (list->freeCount >= list->freeCapacity) {
            ListAllocator *allocator = FUN_002ed520(list);
            list->freeCapacity += 8;
            list->freeIndices = allocator->reallocate(list->freeIndices, list->freeCapacity * 2);
        }
        list->freeIndices[list->freeCount] = index;
        list->freeCount++;
    }
}

void Gap__Gfx__igPsx2VisualContext__vfunc_132(igPsx2VisualContextSlots_17a070 *self, int value, int index, int option)
{
    self->vfunc_131(value, index, 0);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_260(igPsx2VisualContext *arg0, int arg1, int arg2) {
    int a0;
    int var_a3;
    int var_a4;
    char *s0;

    s0 = (char *)(*(int *)((char *)(arg0->_pTexList) + 16) + (arg1 * 0x88));
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
    c->vX(arg2, (var_a4 * (*(int *)(s0 + 32) * *(int *)(s0 + 36))) / var_a3, var_a3, var_a4);
    *(char *)(s0 + 81) = 1;
    return 1;
}

int Gap__Gfx__igPsx2VisualContext__vfunc_135(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + (arg1 * 0x88))) + 48);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_134(void) {
    return 0;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_138(TextureContext138 *arg0, int arg1, int arg2) {
    int temp_a3;

    temp_a3 = arg1 * 0x88;
    if (arg2 == *(int *)((char *)arg0->f324->f16 + temp_a3 + 4)) {
        DAT_00560a28[0] += 1;
    }
    *(int *)((char *)arg0->f324->f16 + temp_a3 + 4) = arg2;
    *(char *)((char *)arg0->f324->f16 + temp_a3 + 80) = 1;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_140(struct TextureContext140 *arg0, int arg1, int arg2) {
    struct TextureEntry140 *e = arg0->tab->arr + arg1; if (arg2 == e->v) { DAT_00560a2c[0] += 1; } e = arg0->tab->arr + arg1; e->v = arg2; e = arg0->tab->arr + arg1; e->flag = 1;
}

int Gap__Gfx__igPsx2VisualContext__vfunc_139(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + (arg1 * 0x88))) + 4);
}

int Gap__Gfx__igPsx2VisualContext__vfunc_141(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + (arg1 * 0x88))) + 8);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_136(struct igPsx2VisualContext *arg0, int arg1, int arg2, int arg3) {
    int temp_v1;
    temp_v1 = arg1 * 0x88;
    if (arg2 == *(int *)(((struct TextureList136 *)arg0->_pTexList)->e + temp_v1 + 12)) {
        DAT_00560a34[0] += 1;
    }
    if (arg3 == *(int *)(((struct TextureList136 *)arg0->_pTexList)->e + temp_v1 + 16)) {
        DAT_00560a38[0] += 1;
    }
    *(int *)(((struct TextureList136 *)arg0->_pTexList)->e + temp_v1 + 12) = arg2;
    *(int *)(((struct TextureList136 *)arg0->_pTexList)->e + temp_v1 + 16) = arg3;
    *(char *)(((struct TextureList136 *)arg0->_pTexList)->e + temp_v1 + 80) = 1;
}

void Gap__Gfx__igPsx2VisualContext__vfunc_137(void *arg0, int arg1, int *arg2, int *arg3) {
    int temp_a1;

    temp_a1 = arg1 * 0x88;
    *arg2 = *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + temp_a1)) + 12);
    *arg3 = *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 324)) + 16) + temp_a1)) + 16);
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

void FUN_0017c710(int arg0, int arg1, int arg2) {
    if (arg1 < 8) {
        unsigned char v = *(unsigned char *)(arg1 + arg0 + 540); if (v == (arg2 & 0xFF)) {
            DAT_00560a3c[arg1] = DAT_00560a3c[arg1] + 1;
        }
    }
    *(char *)(arg1 + arg0 + 540) = arg2;
    if (arg1 == 0) {
        if (arg2 != 0) {
            p2EnableCapability(0x1A, arg1);
            return;
        }
        p2DisableCapability(0x1A, arg1);
    }
}

unsigned char FUN_0017c790(int arg0, int arg1) {
    return *(int *)((char *)((arg1 + arg0)) + 540);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_148(VisualContextSlots *arg0, int arg1, int arg2) {
    int a3;
    arg1 = arg1 < 15 ? arg1 : 15;
    if (arg1 < 8) {
        if (arg0->slot[arg1] == arg2) {
            DAT_00560a5c[arg1] += 1;
        }
    }
    arg0->slot[arg1] = arg2;
    a3 = arg1 > 1 ? arg1 - 1 : 0;
p2CurrentProgram[0] = arg1; p2CurrentGsRegisters[0] = &p2GsRegisterSets[a3]; FUN_00208f70(DAT_0048acf0[arg2]);
    p2CurrentProgram[0] = 0;
    p2CurrentGsRegisters[0] = p2GsRegisterSets;
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
    p2CurrentProgram[0] = n;
    p2CurrentGsRegisters[0] = &p2GsRegisterSets[j];
    context->_bTextureColorComponent = colorComponent;
    FUN_00209090(DAT_0048acf0[function], colorComponent);
    p2CurrentProgram[0] = 0;
    p2CurrentGsRegisters[0] = p2GsRegisterSets;
}

int Gap__Gfx__igPsx2VisualContext__vfunc_149(int arg0, int a1) {
 int i = a1 < 15 ? a1 : 15; int off = i * 4; int *p = (int *)(off + (int)arg0); return p[145];
}

void Gap__Gfx__igPsx2VisualContext__vfunc_150(struct TextureStageView150 *p, int n, int x, int y) {
    int i;
    n = n < 15 ? n : 15;
    if (n < 8) {
        if (p->a[n] == x) {
            DAT_00560a7c[n] += 1;
        }
        if (p->b[n] == y) {
            DAT_00560a9c[n] += 1;
        }
    }
    p->a[n] = x;
    p->b[n] = y;
    if (n > 1) {
        i = n - 1;
    } else {
        i = 0;
    }
    p2CurrentProgram[0] = n;
    p2CurrentGsRegisters[0] = &p2GsRegisterSets[i];
    switch (x) {
    case 0:
        p2DisableCapability(10);
        break;
    case 2:
        p2EnableCapability(10);
        FUN_00208170(1);
        break;
    case 1:
        p2EnableCapability(10);
        FUN_00208170(0);
        break;
    case 3:
        p2EnableCapability(10);
        FUN_00208170(3);
        break;
    case 5:
        p2EnableCapability(10);
        FUN_00208170(2);
        break;
    }
    p2CurrentProgram[0] = 0;
    p2CurrentGsRegisters[0] = &p2GsRegisterSets[0];
}

/* The base is kept in its own local rather than written back into the parameter; otherwise the add
 * is emitted with the operands swapped. */
void Gap__Gfx__igPsx2VisualContext__vfunc_151(int arg0, int arg1, int *arg2, int *arg3) {
    int i = arg1 < 15 ? arg1 : 15;
    int off = i * 4;
    int p = off + arg0;
    *arg2 = *(int *)(p + 644);
    *arg3 = *(int *)(p + 708);
}

int FUN_0017cb80(struct ClutContextCB80 *arg0, int arg1, int *arg2) {
    int sp3C = 0;
    int r = -1;
    switch (arg1) {
    case 0:
        if (arg0->f836 == -1) {
            arg0->f836 = FUN_0017ccb0(arg0, 0, 8, &sp3C);
            arg0->f852 = sp3C;
        }
        r = arg0->f836;
        *arg2 = 0x10000;
        break;
    case 1:
        if (arg0->f840 == -1) {
            arg0->f840 = FUN_0017ccb0(arg0, 8, 0, &sp3C);
            arg0->f856 = sp3C;
        }
        r = arg0->f840;
        *arg2 = 0x10000;
        break;
    case 3:
    case 2:
        if (arg0->f844 == -1) {
            arg0->f844 = FUN_0017ccb0(arg0, 4, 4, &sp3C);
            arg0->f860 = sp3C;
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

void Gap__Gfx__igPsx2VisualContext__vfunc_122(void) {

}

