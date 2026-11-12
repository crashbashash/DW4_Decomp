#!/usr/bin/env python3
"""Naming batches preserve explicit aliases and rewrite every source, header and approval row."""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]

class ApplyNames(unittest.TestCase):
    def test_explicit_thunk_and_same_basename_sources(self):
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=Path(td);src=base/'src';asm=base/'asm';names=base/'names'
            src.mkdir();asm.mkdir();names.mkdir()
            (base/'symbols.txt').write_text('00100000 000008 FUN_00100000\n00100010 000008 thunk_FUN_00100000\n')
            (names/'Test.tsv').write_text('0x00100000\tBuffer_Free\tengine\n0x00100010\tBuffer_FreeAlias\tengine\n')
            (src/'FUN_00100000.c').write_text('int FUN_00100000(){return 0;}\n')
            (src/'thunk_FUN_00100000.c').write_text('int thunk_FUN_00100000(){return FUN_00100000();}\n')
            for ext in ('c','cpp'):
                (src/f'merged.{ext}').write_text('int caller(){return thunk_FUN_00100000()+FUN_00100000();}\n')
            subprocess.run(['python3',str(ROOT/'tools/apply_names.py'),'--src',str(src),
                            '--asm',str(asm),'--names',str(names),'--symbols',str(base/'symbols.txt'),
                            '--apply','--no-regen'],check=True,capture_output=True,text=True)
            self.assertEqual((src/'engine/Buffer_FreeAlias.c').read_text(),
                             'int Buffer_FreeAlias(){return Buffer_Free();}\n')
            for ext in ('c','cpp'):
                self.assertEqual((src/f'merged.{ext}').read_text(),
                                 'int caller(){return Buffer_FreeAlias()+Buffer_Free();}\n')
            self.assertFalse((src/'thunk_FUN_00100000.c').exists())

    def test_headers_fragments_and_approvals(self):
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=Path(td);src=base/'src';asm=base/'asm';names=base/'names';inc=base/'include'/'dw4'
            for d in (src/'engine',asm,names,inc,base/'config'):d.mkdir(parents=True)
            (base/'symbols.txt').write_text('00100000 000008 FUN_00100000\n')
            (names/'Test.tsv').write_text('0x00100000\tBuffer_Free\tengine\n')
            (src/'engine/Lib.h').write_text('int FUN_00100000(void);\n')
            (src/'engine/Lib_tail.inc').write_text('int g(){return FUN_00100000();}\n')
            (inc/'lib.h').write_text('int FUN_00100000(void);\n')
            (base/'config/source-approvals.tsv').write_text('# kind function count anchor\n'
                                                            'volatile\tFUN_00100000\t1\t#a\n')
            subprocess.run(['python3',str(ROOT/'tools/apply_names.py'),'--src',str(src),
                            '--asm',str(asm),'--names',str(names),'--symbols',str(base/'symbols.txt'),
                            '--apply','--no-regen'],check=True,capture_output=True,text=True)
            self.assertEqual((src/'engine/Lib.h').read_text(),'int Buffer_Free(void);\n')
            self.assertEqual((src/'engine/Lib_tail.inc').read_text(),'int g(){return Buffer_Free();}\n')
            self.assertEqual((inc/'lib.h').read_text(),'int Buffer_Free(void);\n')
            self.assertEqual((base/'config/source-approvals.tsv').read_text().splitlines()[1],
                             'volatile\tBuffer_Free\t1\t#a')
if __name__=='__main__':unittest.main()
