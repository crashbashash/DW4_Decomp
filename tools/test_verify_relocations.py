"""MWCC relocation order, function slicing and independent GNU linking."""
import os
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import unittest
from unittest.mock import patch
import verify

class RelocationOrder(unittest.TestCase):
    def test_symbol_value_is_hex_but_size_is_decimal(self):
        with patch.object(verify.subprocess,'run') as run:
            run.return_value.stdout=' 9 .text PROGBITS\n 5: 00000020 76 FUNC GLOBAL DEFAULT 9 target\n'
            syms,sections=verify.object_syms('fixture.o')
        self.assertEqual(syms['target'],(9,32,76))

    def test_processor_specific_binding_keeps_final_section_and_name(self):
        with patch.object(verify.subprocess, 'run') as run:
            run.return_value.stdout = (' 9 .text PROGBITS\n'
                ' 23: 00000000 128 FUNC <processor specific>: 13 DEFAULT 9 __dt__10IntListRefFv\n')
            syms, _ = verify.object_syms('fixture.o')
        self.assertEqual(syms['__dt__10IntListRefFv'], (9, 0, 128))
        self.assertNotIn('DEFAULT', syms)

    def test_selected_body_excludes_helpers_and_rebases_without_sorting(self):
        rows=[('.text',0,verify.R_26,'helper',0),
              ('.text',40,verify.R_HI16,'value',0),
              ('.rodata',0,verify.R_32,'table',0),
              ('.text',36,verify.R_LO16,'value',0),
              ('.text',48,verify.R_26,'next_body',0)]
        self.assertEqual(verify.function_relocs(rows,32,16),
                         [('.text',8,verify.R_HI16,'value',0),
                          ('.text',4,verify.R_LO16,'value',0)])

    def test_backward_low_half_keeps_its_high_half_pair(self):
        # Reduced from the owner lookup's real MWCC object: a loop-bottom HI16
        # pairs with a LO16 in an earlier instruction, after an earlier pair.
        output="""Relocation section '.rel.text' at offset 0x200 contains 4 entries:
 Offset Info Type Sym.Value Symbol's Name
00000000 00000405 R_MIPS_HI16 00000000 DAT_0058f000
00000008 00000406 R_MIPS_LO16 00000000 DAT_0058f000
0000000c 00000405 R_MIPS_HI16 00000000 DAT_0058f000
00000004 00000406 R_MIPS_LO16 00000000 DAT_0058f000
"""
        with patch.object(verify.subprocess,'run') as run:
            run.return_value.stdout=output
            rows=verify.object_relocs('owner.o')
        self.assertEqual([r[1] for r in rows],[0,8,12,4])
        code=struct.pack('<4I',0x3c010000,0x8c220000,0x8c230000,0x3c010000)
        result,_,unresolved=verify.apply_relocs(code,rows,lambda _:0x58f000,0)
        self.assertFalse(unresolved)
        self.assertEqual(struct.unpack('<4I',result),
                         (0x3c010059,0x8c22f000,0x8c23f000,0x3c010059))

    def test_real_second_body_agrees_with_gnu_but_extra_text_is_rejected(self):
        root=Path(verify.ROOT);va=0x2d1540
        required=(Path(verify.WIBO_DEFAULT),Path(verify.MWCC_DEFAULT),Path(verify.ELF_DEFAULT))
        if not all(p.exists() for p in required) or not shutil.which('mipsel-linux-gnu-ld'):
            self.skipTest('private retail compiler/ELF or GNU linker unavailable')
        source=(root/'src/engine/igAliasMemoryPool_Construct.c').read_text()
        # This unknown relocation belongs only to the preceding body. It must
        # never be applied to the constructor's first instruction.
        source='extern void UnknownBeforeTarget(void);\nvoid OtherBody(void){UnknownBeforeTarget();}\n'+source
        with tempfile.TemporaryDirectory(prefix='dw4-relocation-slice-') as td:
            td=Path(td);path=td/'slice.c';obj=td/'slice.o';linked=td/'slice.elf';script=td/'slice.ld'
            path.write_text(source)
            subprocess.run([verify.WIBO_DEFAULT,verify.MWCC_DEFAULT,'-c','-O3','-I'+str(root/'include'),str(path),'-o',str(obj)],
                           check=True,capture_output=True,env=dict(os.environ,MWCIncludes=str(root/'include')))
            by_name,by_va=verify.load_symbols(str(root/'config/SLUS-20836/symbols.txt'))
            name=by_va[va][0];off,size,ndx=verify.object_sym(str(obj),name)
            headers=verify.elf_section_headers(str(obj))
            self.assertGreater(len([1 for section,h in headers if section=='.text' and h[5]]),1)
            self.assertEqual(off,0) # MWCC repeats the section name, each at offset0.
            ok,report=verify.verify_one(va,str(path),symbols=str(root/'config/SLUS-20836/symbols.txt'),verbose=True)
            self.assertFalse(ok,report)
            self.assertIn('per-function linking requires an isolated body',report)
            self.assertNotIn('!![',report)
            self.assertNotIn('unresolved relocation',report)
            # Independently relocate the whole real object with GNU ld, placing
            # this second symbol at its retail VA. UnknownBeforeTarget is a
            # controlled link-only address, never executed.
            syms,secs=verify.object_syms(str(obj));assignments=[]
            for symbol,(section,_,_) in syms.items():
                if section=='UND':
                    address=0x1900000 if symbol=='UnknownBeforeTarget' else verify.sym_address(symbol,by_name)
                    self.assertIsNotNone(address,symbol)
                    assignments.append(f'{symbol} = 0x{address:x};')
            # GNU ld concatenates the duplicate-named input sections in order,
            # respecting each alignment; calculate the selected body's position.
            cursor=0;position=None
            for i,(section,h) in enumerate(headers):
                if section!='.text':continue
                alignment=h[8] or 1;cursor=(cursor+alignment-1)//alignment*alignment
                if i==ndx:position=cursor+off
                cursor+=h[5]
            self.assertIsNotNone(position)
            script.write_text('\n'.join(assignments)+f'\nSECTIONS {{ . = 0x{va-position:x}; .text : {{ *(.text) }} /DISCARD/ : {{ *(.reginfo) *(.mdebug*) *(.comment) }} }}\n')
            subprocess.run(['mipsel-linux-gnu-ld','--no-warn-mismatch','-T',str(script),str(obj),'-o',str(linked)],check=True,capture_output=True)
            self.assertEqual(verify.object_sym(str(linked),name)[0],va)
            actual=verify.object_section(str(linked),'.text')[position:position+size]
            self.assertEqual(actual,verify.va_bytes(verify.read_elf(verify.ELF_DEFAULT),va,size))

if __name__=='__main__':unittest.main()
