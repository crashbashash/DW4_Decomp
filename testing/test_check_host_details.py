#!/usr/bin/env python3
"""Self-test for scripts/check_host_details.py: every rule fires on a fake sample, placeholders pass, exceptions work."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "scripts"))
import check_host_details as chd


def rules(text, path="docs/x.md"):
    return {h[2] for h in chd.scan_text(path, text)}


class Rules(unittest.TestCase):
    def test_each_rule_fires(self):
        samples = {
            "home-path": ["see /home/alice/Projects/x", "see /Users/bob/dev", "C:\\Users\\carol\\dev"],
            "workspace-path": ["open /workspace/repo/file.c"],
            "gpu-model": ["a GeForce RTX 4090", "on an RX 7900 XT", "Radeon RX 6600", "Arc A770"],
            "cpu-model": ["a Ryzen 9 7950X host", "Core i7-12700K", "Xeon box", "Apple M2"],
            "controller-brand": ["the 8BitDo pad", "a Logitech F310", "a DualSense"],
            "driver-version": ["Mesa 24.1.0", "LLVM 17.0.6", "DRM 3.57", "Linux 6.8", "kernel 6.8.9"],
            "device-node": ["/dev/dri/renderD128", "/sys/class/drm/card0", "PCI 10de:2684", "1002:73bf"],
            "host-description": ["running Fedora 40", "on Ubuntu 22.04", "Hyprland session", "CachyOS"],
            "personal-email": ["mail someone@gmail.com"],
            "private-ip": ["host 192.168.1.20", "10.0.0.5", "172.16.4.9"],
            "secret": ["-----BEGIN RSA PRIVATE KEY-----", "ghp_" + "a" * 36, "AKIA" + "A" * 16],
            "emulator-slot": ["PINE slot 31234", "slot 31234 status", "--slot 31234", "slot-31234", "slot31234", "slots 31234"],
            "runtime-socket": ["/run/user/1000/pcsx2.sock", '"/run/user/%d/pcsx2.sock" % os.getuid()', "/run/user/$UID/x.sock",
                               "/run/user/<uid>/pcsx2.sock"],
            "x-display": ["DISPLAY=:7", "Xwayland :7", "display :7 is spare", "Xvfb :3"],
            "opt-path": ["/opt/emulator/usr/bin/emu-qt", "under /opt/data/cache/x.bin"],
            "tmp-session-path": ["/tmp/claude-1000/foo", "/tmp/x-home-someone-work/bar", "/tmp/session-12345/x",
                                 "/tmp/agent-scratch/x"],
            "cpu-vendor": ["Actual AMD CPU/GPU checks", "an Intel CPU host", "the AMD CPU"],
            "gpu-family": ["RDNA 3 card", "Navi 31", "Vega 64", "GeForce 1080", "Quadro P4000", "Mali-G78"],
        }
        for rule, items in samples.items():
            for item in items:
                self.assertIn(rule, rules(item), "%s should flag %r" % (rule, item))

    def test_a_generic_scratch_file_in_a_command_example_passes(self):
        self.assertEqual(rules("python3 scripts/lua_dump.py /tmp/lua_179.bin --limit=2"), set())

    def test_placeholders_and_generic_wording_pass(self):
        for ok in ["/home/example/x", "/home/user/x", "/home/runner/work", "../local/extracted", "<repo>/docs", "~/x",
                   "a desktop AMD GPU", "a physical gamepad", "an NVIDIA GPU", "Mesa Vulkan driver", "ubuntu-latest",
                   "the workspace root", "shcard10 renderDestination", "DualShock2 pad", "an Xbox 360 layout mapping",
                   "the configured PINE slot (PINE_SLOT)", "slot 40", "slots 1-8 are overwritten", "memory card slot 2",
                   "vX() (slot 1028)", "vtable slot 216",
                   "an X11 or XWayland display", "DISPLAY from the environment", "os.environ.get('XDG_RUNTIME_DIR')",
                   "/tmp/raster", "/tmp/lua-4.0.1", "--out-dir /tmp/ui", "../scratch/dw4menu/area620.bin",
                   "the CPU and GPU checks", "a desktop CPU", "an AMD GPU", "an Intel GPU",
                   "optimisation_level 0", "options", "opt speed", "0x9128013a"]:
            self.assertEqual(rules(ok), set(), ok)

    def test_exceptions_file(self):
        saved = list(chd.ALLOW)
        try:
            chd.ALLOW.append(("docs/fixture.md", chd.re.compile(r"RTX 4090")))
            self.assertEqual(rules("RTX 4090", path="docs/fixture.md"), set())
            self.assertIn("gpu-model", rules("RTX 4090", path="docs/other.md"))
        finally:
            chd.ALLOW[:] = saved

    def test_message_and_added_lines(self):
        self.assertIn("home-path", {h[2] for h in chd.scan_text("commit message", "fix path /home/dave/repo")})


if __name__ == "__main__":
    unittest.main()
