# My OTA-Forever project

Push to GitHub, and every ESP32 linked to this repo installs the new firmware.

## One-time setup

1. **Signing key.** Run this in the repo folder:
   ```
   pip install cryptography
   python .github/ota/keygen.py
   gh secret set OTA_SIGNING_KEY < ota_signing_key.pem
   ```
   Don't commit `ota_signing_key.pem`. Keep a backup somewhere safe: devices only
   accept builds signed with this key.
2. **Repo visibility.** The repo must be **public**, because devices download releases
   without logging in.
3. **Devices.** Flash the OTA-Forever loader from the installer page. Join the WiFi network
   `OTA-Setup-XXXX` and enter your WiFi network and this repo (`owner/name`).

## Everyday use

- Edit `firmware/firmware.ino` and push.
- Open the **Actions** tab to watch the build. When it finishes, the release
  `ota-<branch>` contains the new firmware.
- Devices install it on their next power-on/reset. If the sketch calls
  `OTAForever.begin()`, they install it within a few minutes without a reset.

## ota.yml

| Key | Meaning |
|---|---|
| `sketch` | Folder holding `<folder>.ino` (default `firmware`) |
| `boards` | List of `chip` + `fqbn`. Supported chips: esp32, esp32s2, esp32s3, esp32c3, esp32c6 |
| `libraries` | Library Manager names, e.g. `ArduinoJson@7.2.1` |
| `core_version` | Pin the Arduino-ESP32 core version (empty = latest) |
| `branches` | Branches that publish updates (`"*"` = all) |

## Rules
- Keep `firmware/partitions.csv`. It makes USB uploads keep the loader intact.
- Firmware must fit in 1.4 MB per board. The build fails if it doesn't.
- In the Arduino IDE, add `libraries/` to your sketchbook (or install the OTAForever
  library) so `#include <OTAForever.h>` resolves.
