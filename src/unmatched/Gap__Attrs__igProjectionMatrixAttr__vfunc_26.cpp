#include "dw4/reflected.h"

extern "C" {
void igMatrix44f_SetIdentity(float *m);
void Gap__Attrs__igProjectionMatrixAttr__vfunc_26(igProjectionMatrixAttr *self, igObject *context);
}

class VisualContextMatrixSlots {
public:
    virtual void vfunc_2(); virtual void vfunc_3(); virtual void vfunc_4(); virtual void vfunc_5(); virtual void vfunc_6(); virtual void vfunc_7();
    virtual void vfunc_8(); virtual void vfunc_9(); virtual void vfunc_10(); virtual void vfunc_11(); virtual void vfunc_12(); virtual void vfunc_13();
    virtual void vfunc_14(); virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual void vfunc_20(); virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23(); virtual void vfunc_24(); virtual void vfunc_25();
    virtual void vfunc_26(); virtual void vfunc_27(); virtual void vfunc_28(); virtual void vfunc_29(); virtual void vfunc_30(); virtual void vfunc_31();
    virtual void vfunc_32(); virtual void vfunc_33(); virtual void vfunc_34(); virtual void vfunc_35(); virtual void vfunc_36(); virtual void vfunc_37();
    virtual void vfunc_38(); virtual void vfunc_39(); virtual void vfunc_40(); virtual void vfunc_41(); virtual void vfunc_42(); virtual void vfunc_43();
    virtual void vfunc_44(); virtual void vfunc_45(); virtual void vfunc_46(); virtual void vfunc_47(); virtual void vfunc_48(); virtual void vfunc_49();
    virtual void vfunc_50(); virtual void vfunc_51(); virtual void vfunc_52(); virtual void vfunc_53(); virtual void vfunc_54(); virtual void vfunc_55();
    virtual void vfunc_56(); virtual void vfunc_57(); virtual void vfunc_58(); virtual void vfunc_59(); virtual void vfunc_60(); virtual void vfunc_61();
    virtual void vfunc_62(); virtual void vfunc_63(); virtual void vfunc_64(); virtual void vfunc_65(); virtual void vfunc_66(); virtual void vfunc_67();
    virtual void vfunc_68(); virtual void vfunc_69(); virtual void vfunc_70(); virtual void vfunc_71(); virtual void vfunc_72(); virtual void vfunc_73();
    virtual void vfunc_74(); virtual void vfunc_75(); virtual void vfunc_76(); virtual void vfunc_77(); virtual void vfunc_78(); virtual void vfunc_79();
    virtual void vfunc_80(); virtual void vfunc_81(); virtual void vfunc_82(); virtual void vfunc_83(); virtual void vfunc_84(); virtual void vfunc_85();
    virtual void vfunc_86(); virtual void vfunc_87(); virtual void vfunc_88(); virtual void vfunc_89(); virtual void vfunc_90(); virtual void vfunc_91();
    virtual void vfunc_92(); virtual void vfunc_93(); virtual void vfunc_94(); virtual void vfunc_95(); virtual void vfunc_96(); virtual void vfunc_97();
    virtual void vfunc_98(); virtual void vfunc_99(); virtual void vfunc_100(); virtual void vfunc_101(); virtual void vfunc_102(); virtual void vfunc_103();
    virtual void vfunc_104(); virtual void vfunc_105(); virtual void vfunc_106(); virtual void vfunc_107(); virtual void vfunc_108(); virtual void vfunc_109();
    virtual void vfunc_110(); virtual void vfunc_111(); virtual void vfunc_112(); virtual void vfunc_113(); virtual void vfunc_114(); virtual void vfunc_115();
    virtual void vfunc_116(); virtual void vfunc_117(); virtual void vfunc_118(); virtual void vfunc_119(); virtual void vfunc_120(); virtual void vfunc_121();
    virtual void vfunc_122(); virtual void vfunc_123(); virtual void vfunc_124(); virtual void vfunc_125(); virtual void vfunc_126(); virtual void vfunc_127();
    virtual void vfunc_128(); virtual void vfunc_129(); virtual void vfunc_130(); virtual void vfunc_131(); virtual void vfunc_132(); virtual void vfunc_133();
    virtual void vfunc_134(); virtual void vfunc_135(); virtual void vfunc_136(); virtual void vfunc_137(); virtual void vfunc_138(); virtual void vfunc_139();
    virtual void vfunc_140(); virtual void vfunc_141(); virtual void vfunc_142(); virtual void vfunc_143(); virtual void vfunc_144(); virtual void vfunc_145();
    virtual void vfunc_146(); virtual void vfunc_147(); virtual void vfunc_148(); virtual void vfunc_149(); virtual void vfunc_150(); virtual void vfunc_151();
    virtual void vfunc_152(); virtual void vfunc_153(); virtual void vfunc_154(); virtual void vfunc_155(); virtual void vfunc_156(); virtual void vfunc_157();
    virtual void vfunc_158(); virtual void vfunc_159(); virtual void vfunc_160(); virtual void vfunc_161(); virtual void vfunc_162(); virtual void vfunc_163();
    virtual void vfunc_164(); virtual void vfunc_165(); virtual void vfunc_166(); virtual void vfunc_167(); virtual void vfunc_168(); virtual void vfunc_169();
    virtual void vfunc_170(); virtual void vfunc_171(); virtual void vfunc_172(); virtual void vfunc_173(); virtual void vfunc_174(); virtual void vfunc_175();
    virtual void vfunc_176(); virtual void vfunc_177(); virtual void vfunc_178(); virtual void vfunc_179(); virtual void vfunc_180(); virtual void vfunc_181();
    virtual void vfunc_182(); virtual void vfunc_183(); virtual void vfunc_184(); virtual void vfunc_185(); virtual void vfunc_186(); virtual void vfunc_187();
    virtual void vfunc_188(); virtual void vfunc_189(); virtual void vfunc_190(); virtual void vfunc_191(); virtual void vfunc_192(); virtual void vfunc_193();
    virtual void vfunc_194(); virtual void vfunc_195(); virtual void vfunc_196(); virtual void vfunc_197(); virtual void vfunc_198(); virtual void vfunc_199();
    virtual void vfunc_200(); virtual void vfunc_201(); virtual void vfunc_202(); virtual void vfunc_203(); virtual void vfunc_204(); virtual void vfunc_205();
    virtual void vfunc_206(); virtual void vfunc_207();
    virtual void getMatrix(int which, float *m);
};

class MatrixAttrSlots {
public:
    virtual void vfunc_2(); virtual void vfunc_3(); virtual void vfunc_4(); virtual void vfunc_5(); virtual void vfunc_6(); virtual void vfunc_7();
    virtual void vfunc_8(); virtual void vfunc_9(); virtual void vfunc_10(); virtual void vfunc_11(); virtual void vfunc_12(); virtual void vfunc_13();
    virtual void vfunc_14(); virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual void vfunc_20(); virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23(); virtual void vfunc_24(); virtual void vfunc_25();
    virtual void vfunc_26(); virtual void vfunc_27(); virtual void vfunc_28(); virtual void vfunc_29(); virtual void vfunc_30(); virtual void vfunc_31();
    virtual void setMatrix(const float *m);
};

void Gap__Attrs__igProjectionMatrixAttr__vfunc_26(igProjectionMatrixAttr *self, igObject *context)
{
    float m[16];

    igMatrix44f_SetIdentity(m);
    ((VisualContextMatrixSlots *)context)->getMatrix(0, m);
    ((MatrixAttrSlots *)self)->setMatrix(m);
}
