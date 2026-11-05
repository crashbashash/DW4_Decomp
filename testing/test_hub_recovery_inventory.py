#!/usr/bin/env python3
"""Check hub source-call parsing and independently recognizable retail scripts."""
import json
from pathlib import Path
import sys
import unittest

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
import hub_recovery_inventory as hub


class HubInventory(unittest.TestCase):
    def test_strings_comments_and_nested_arguments(self):
        text='''-- be:Fake(1)
msg = "be:Fake(2)"
be:sd("SUBWND", nil, player(0, 1), "GENERATE", "BANK/I<0>")
--[[ be:Fake(3) ]]
be:DMsetLua("bankshop.lua")
'''
        self.assertEqual(list(hub.calls(text)),[
            ('sd',['"SUBWND"','nil','player ( 0 , 1 )','"GENERATE"','"BANK/I<0>"'],3),
            ('DMsetLua',['"bankshop.lua"'],5)])

    def test_dynamic_expression_is_not_a_literal(self):
        self.assertIsNone(hub.literal('mode'))
        self.assertIsNone(hub.literal('"BANK" .. "OTHER"'))
        self.assertEqual(hub.literal('"BANK"'),'BANK')

    def test_core_packs_and_shop_dispatches(self):
        data=hub.inventory();packs={p['entry']:p for p in data['packs']}
        self.assertEqual({e:p['chunks'] for e,p in packs.items()},
                         {816:155,820:64,824:114,828:60})
        self.assertTrue({'bankshop.lua','diskshop.lua','weaponshop.lua',
                         'armorshop.lua','chipshop.lua','junkshop.lua'}
                        <=set(packs[828]['queued_named_chunks']))
        self.assertEqual(set(packs[828]['subwindow_modes']),
                         {'BANK','DISK','WPU','APU','CHIP','JUNK'})
        self.assertEqual(set(packs[824]['subwindow_modes']),{'BANK','CNOS','LABO','XDATA'})
        self.assertFalse(data['unbound_be_names'])
        # Every reached direct edge must remain represented. Virtual receivers
        # are deliberately not manufactured from script method-name strings.
        addresses={r['address'] for r in data['functions']}
        for row in data['functions']:
            self.assertTrue({e['function'] for e in row['direct'] if e['function'] is not None}<=addresses)


if __name__=='__main__':unittest.main()
