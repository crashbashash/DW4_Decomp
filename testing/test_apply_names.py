#!/usr/bin/env python3
"""Naming batches preserve explicit aliases and rewrite every source, header and approval row;
they rewrite references only (never strings, members or locals), refuse a generic old name,
handle swaps, and rename unit-objects.json keys by address."""
import json
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]


def run_batch(base, *extra, check=True):
    """Run tools/apply_names.py on the fixture tree under `base` -> CompletedProcess."""
    return subprocess.run(['python3',str(ROOT/'tools/apply_names.py'),'--src',str(base/'src'),
                           '--asm',str(base/'asm'),'--names',str(base/'names'),
                           '--symbols',str(base/'symbols.txt'),'--no-regen',*extra],
                          check=check,capture_output=True,text=True)


def fixture(td, symbols, overlay, files):
    base=Path(td)
    for d in ('src','asm','names'):(base/d).mkdir()
    (base/'symbols.txt').write_text(''.join('%08x 000008 %s\n'%(va,name) for va,name in symbols))
    (base/'names/Test.tsv').write_text(''.join('0x%08x\t%s\tengine\n'%(va,name) for va,name in overlay))
    for path,text in files.items():
        (base/path).parent.mkdir(parents=True,exist_ok=True)
        (base/path).write_text(text)
    return base


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
            (base/'config/assembly-sources.tsv').write_text('FUN_00100000\tsrc/x.S\t#a\n')
            subprocess.run(['python3',str(ROOT/'tools/apply_names.py'),'--src',str(src),
                            '--asm',str(asm),'--names',str(names),'--symbols',str(base/'symbols.txt'),
                            '--apply','--no-regen'],check=True,capture_output=True,text=True)
            self.assertEqual((src/'engine/Lib.h').read_text(),'int Buffer_Free(void);\n')
            self.assertEqual((src/'engine/Lib_tail.inc').read_text(),'int g(){return Buffer_Free();}\n')
            self.assertEqual((inc/'lib.h').read_text(),'int Buffer_Free(void);\n')
            self.assertEqual((base/'config/source-approvals.tsv').read_text().splitlines()[1],
                             'volatile\tBuffer_Free\t1\t#a')
            self.assertEqual((base/'config/assembly-sources.tsv').read_text(),'Buffer_Free\tsrc/x.S\t#a\n')

    def test_string_literals_are_retail_data(self):
        # a CRI error string names its function; renaming the function must not touch .rodata
        source=('void MWSTM_ReqStart(void);\n'
                'static const char msg[] = "E211141 MWSTM_ReqStart: can\'t start";\n'
                "static const char tag = 'M';\n"
                '/* starts the stream through MWSTM_ReqStart */\n'
                'void f(void) { MWSTM_ReqStart(); }\n')
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=fixture(td,[(0x100000,'MWSTM_ReqStart')],[(0x100000,'mwsfsvr_StartStm')],
                         {'src/cri/mwsfsvr.c':source})
            run_batch(base,'--apply')
            self.assertEqual((base/'src/cri/mwsfsvr.c').read_text(),
                             source.replace('void MWSTM_ReqStart','void mwsfsvr_StartStm')
                                   .replace('through MWSTM_ReqStart','through mwsfsvr_StartStm')
                                   .replace('{ MWSTM_ReqStart()','{ mwsfsvr_StartStm()'))
            self.assertIn('"E211141 MWSTM_ReqStart: can\'t start"',(base/'src/cri/mwsfsvr.c').read_text())

    GENERIC={
        'src/runtime/crt0.S':('/* The program\'s entry point */\n\t.globl\tentry\n\t.ent\tentry\nentry:\n'
                              '\tjal\tmain\n\t.end\tentry\n'),
        'src/engine/table.c':('struct Node { int entry; };\n'
                              'void entry(void);\n'
                              'static const char *err = "bad entry";\n'
                              'int count(struct Node *n, int entry) { return n->entry + entry; }\n'
                              'int walk(struct Node *list) {\n'
                              '    struct Node *entry = list;   /* the entry being walked */\n'
                              '    return entry->entry;\n'
                              '}\n'
                              'void boot(void) { entry(); }\n'),
    }

    def test_generic_old_name_is_refused(self):
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=fixture(td,[(0x100008,'entry')],[(0x100008,'_start')],self.GENERIC)
            r=run_batch(base,'--apply',check=False)
            self.assertEqual(r.returncode,2)
            self.assertIn('`entry` (-> _start) is also an ordinary identifier',r.stderr)
            self.assertIn('src/engine/table.c',r.stderr)
            self.assertIn('--generic entry',r.stderr)
            for path,text in self.GENERIC.items():
                self.assertEqual((base/path).read_text(),text)

    def test_generic_override_rewrites_only_references(self):
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=fixture(td,[(0x100008,'entry')],[(0x100008,'_start')],self.GENERIC)
            run_batch(base,'--apply','--generic','entry')
            self.assertEqual((base/'src/runtime/crt0.S').read_text(),
                             '/* The program\'s entry point */\n\t.globl\t_start\n\t.ent\t_start\n_start:\n'
                             '\tjal\tmain\n\t.end\t_start\n')
            text=self.GENERIC['src/engine/table.c']
            text=text.replace('void entry(void)','void _start(void)').replace('{ entry(); }','{ _start(); }')
            self.assertEqual((base/'src/engine/table.c').read_text(),text)

    def test_captured_by_a_local_is_refused(self):
        source='int f(void) { int buf = 1; return FUN_00100000(buf); }\n'
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=fixture(td,[(0x100000,'FUN_00100000')],[(0x100000,'buf')],{'src/engine/a.c':source})
            r=run_batch(base,'--apply',check=False)
            self.assertEqual(r.returncode,2)
            self.assertIn('would name the local or member `buf`',r.stderr)
            self.assertEqual((base/'src/engine/a.c').read_text(),source)

    def test_swap_rewritten_in_one_pass(self):
        # 0x100000 and 0x100010 trade names; the file still uses the old ones, which its
        # definitions' address order shows
        source=('void sjrbf_Init(void) { }\n'
                'void SJRBF_Init(void) { sjrbf_Init(); }\n')
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=fixture(td,[(0x100000,'sjrbf_Init'),(0x100010,'SJRBF_Init')],
                         [(0x100000,'SJRBF_Init'),(0x100010,'sjrbf_Init')],{'src/cri/sjrbf.c':source})
            run_batch(base,'--apply')
            self.assertEqual((base/'src/cri/sjrbf.c').read_text(),
                             'void SJRBF_Init(void) { }\n'
                             'void sjrbf_Init(void) { SJRBF_Init(); }\n')

    SWAP_FILES={
        # written with the batch's names already (a body below its lock wrapper)
        'src/cri/sjrbf.c':('void SJRBF_Init(void) { sjrbf_Init(); }\n'
                           'void sjrbf_Init(void) { sjrbf_Error(); }\n'
                           'void sjrbf_Error(void) { }\n'),
        # still the names in symbols.txt
        'src/cri/user.c':'void g(void) { sjrbf_Init(); FUN_00100020(); }\n',
        # nothing says which
        'src/cri/other.c':'void h(void) { SJRBF_Init(); }\n',
    }

    def swap_fixture(self, td):
        return fixture(td,[(0x100000,'sjrbf_Init'),(0x100010,'SJRBF_Init'),(0x100020,'FUN_00100020')],
                       [(0x100000,'SJRBF_Init'),(0x100010,'sjrbf_Init'),(0x100020,'sjrbf_Error')],
                       self.SWAP_FILES)

    def test_swap_with_an_undecidable_file_is_refused(self):
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=self.swap_fixture(td)
            r=run_batch(base,'--apply',check=False)
            self.assertEqual(r.returncode,2)
            self.assertIn('src/cri/other.c uses only names this batch reuses',r.stderr)
            for path,text in self.SWAP_FILES.items():
                self.assertEqual((base/path).read_text(),text)

    def test_swap_leaves_text_that_already_has_the_new_names(self):
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=self.swap_fixture(td)
            r=run_batch(base,'--apply','--assume-old',str(base/'src/cri/other.c'))
            self.assertIn('src/cri/sjrbf.c already uses the new names',r.stdout)
            self.assertEqual((base/'src/cri/sjrbf.c').read_text(),self.SWAP_FILES['src/cri/sjrbf.c'])
            self.assertEqual((base/'src/cri/user.c').read_text(),'void g(void) { SJRBF_Init(); sjrbf_Error(); }\n')
            self.assertEqual((base/'src/cri/other.c').read_text(),'void h(void) { sjrbf_Init(); }\n')

    def test_unit_objects_keys_follow_addresses(self):
        objects={'0x00100000':{'whole_file':True,
                               'emitted':{'FUN_00100010':'0x00100010','B':'0x00100020','A':'0x00100030',
                                          'FUN_00100040':'0x00100050'},
                               'externals':{'FUN_00100060':'0x00100060'},
                               'data':{'FUN_00100010':'0x004d0000'},
                               'symbol':'FUN_00100000'}}
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=fixture(td,[(0x100000,'FUN_00100000'),(0x100010,'FUN_00100010'),(0x100020,'A'),
                             (0x100030,'B'),(0x100040,'FUN_00100040'),(0x100050,'Kept'),
                             (0x100060,'FUN_00100060')],
                         [(0x100000,'Owner'),(0x100010,'Member'),(0x100020,'B'),(0x100030,'A'),
                          (0x100040,'Moved'),(0x100060,'External')],{})
            (base/'unit-objects.json').write_text(json.dumps(objects,indent=2)+'\n')
            run_batch(base,'--apply')
            text=(base/'unit-objects.json').read_text()
            row=json.loads(text)['0x00100000']
            # 0x100020/0x100030 trade names, so keys holding them keep theirs; a key whose
            # address is not the renamed function's (FUN_00100040 -> 0x100050) is left alone
            self.assertEqual(row['emitted'],{'Member':'0x00100010','B':'0x00100020','A':'0x00100030',
                                             'FUN_00100040':'0x00100050'})
            self.assertEqual(row['externals'],{'External':'0x00100060'})
            self.assertEqual(row['data'],{'FUN_00100010':'0x004d0000'})
            self.assertEqual(row['symbol'],'Owner')
            self.assertEqual(text,json.dumps(json.loads(text),indent=2)+'\n')

    def test_unit_objects_stale_keys_renamed(self):
        objects={'0x00100000':{'whole_file':True,'emitted':{'A':'0x00100010','B':'0x00100020'}}}
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=fixture(td,[(0x100000,'FUN_00100000'),(0x100010,'A'),(0x100020,'B')],
                         [(0x100010,'B'),(0x100020,'A')],{})
            (base/'unit-objects.json').write_text(json.dumps(objects,indent=2)+'\n')
            run_batch(base,'--apply')
            self.assertEqual(json.loads((base/'unit-objects.json').read_text())['0x00100000']['emitted'],
                             {'B':'0x00100010','A':'0x00100020'})


if __name__=='__main__':unittest.main()
