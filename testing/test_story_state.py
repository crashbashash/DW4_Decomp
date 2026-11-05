#!/usr/bin/env python3
"""Read-only story analysis checks for raw saves, cards and both command lines."""
import io
from pathlib import Path
import subprocess
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import diff_story
import ps2mc_extract
import save_probe


class StoryTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.payload = bytes(save_probe.BLOCK * save_probe.NBLOCKS)

    def write(self, name, payload):
        path = self.root / name
        path.write_bytes(payload)
        return path

    def test_raw_save_regions_and_source_preservation(self):
        payload = bytearray(self.payload)
        payload[0x320] = 1
        payload[0x724] = 1
        payload[0x730:0x734] = (257).to_bytes(4, "little")
        path = self.write("sample.savedata", payload)
        before = path.read_bytes()
        state = diff_story.story_state(path)
        self.assertEqual({k: len(v) for k, v in state.items()},
                         {"flags": 1024, "folder": 12, "counter": 80})
        self.assertEqual(state["flags"][0], 1)
        self.assertEqual(state["folder"][4], 1)
        self.assertEqual(int.from_bytes(state["counter"][4:8], "little"), 257)
        self.assertEqual(path.read_bytes(), before)

    def fake_card(self, payload, has_save=True):
        root = object()
        directory = SimpleNamespace(name=save_probe.SAVE_NAME, is_dir=lambda: True)
        entry = SimpleNamespace(name=save_probe.SAVE_NAME, is_file=lambda: True)
        return SimpleNamespace(
            file=io.BytesIO(), get_root_entry=lambda: root,
            find_sub_entries=lambda parent: ([directory] if has_save else [])
                if parent is root else [entry],
            read_data_cluster=lambda found: payload)

    def test_memory_card_extraction_closes_input_without_writes(self):
        path = self.write("sample.ps2", ps2mc_extract.SB_MAGIC + bytes(512))
        before = path.read_bytes()
        card = self.fake_card(self.payload)
        with patch("ps2mc_extract.open_card", return_value=(card, "flat")) as opened:
            self.assertEqual(save_probe.read_save_payload(path), self.payload)
        opened.assert_called_once_with(path)
        self.assertTrue(card.file.closed)
        self.assertEqual(path.read_bytes(), before)

    def test_missing_or_truncated_card_entry_fails_and_closes(self):
        path = self.write("sample.ps2", ps2mc_extract.SB_MAGIC + bytes(512))
        for payload, present in [(self.payload, False), (bytes(100), True)]:
            with self.subTest(present=present):
                card = self.fake_card(payload, present)
                with patch("ps2mc_extract.open_card", return_value=(card, "flat")):
                    with self.assertRaises(ValueError):
                        save_probe.read_save_payload(path)
                self.assertTrue(card.file.closed)

    def test_invalid_payload_and_missing_optional_package_are_clear(self):
        with self.assertRaisesRegex(ValueError, "81920-byte"):
            save_probe.read_save_payload(self.write("short.savedata", bytes(100)))
        card = self.write("sample.ps2", ps2mc_extract.SB_MAGIC + bytes(512))
        error = ModuleNotFoundError("missing ps2mc", name="ps2mc")
        with patch("ps2mc_extract.open_card", side_effect=error):
            with self.assertRaisesRegex(ValueError, "optional ps2mc"):
                save_probe.read_save_payload(card)

    def test_cli_reports_changes(self):
        first = self.write("before.savedata", self.payload)
        payload = bytearray(self.payload)
        payload[0x320] = 1
        payload[0x724] = 1
        payload[0x730:0x734] = (257).to_bytes(4, "little")
        second = self.write("after.savedata", payload)
        result = subprocess.run([sys.executable, str(ROOT / "scripts/diff_story.py"),
                                 str(first), str(second)], cwd=self.root,
                                text=True, capture_output=True, check=True)
        self.assertIn("flags +000 (off 0x0320): 0x00 -> 0x01", result.stdout)
        self.assertIn("folder +004 (off 0x0724): 0x00 -> 0x01", result.stdout)
        self.assertEqual(first.read_bytes(), self.payload)
        self.assertEqual(second.read_bytes(), payload)


if __name__ == "__main__":
    unittest.main()
