# LEGO Bonsai LED Kit

All design and code files for DIY LED kit for Lego Bonsai Tree.

![DSC02053](https://user-images.githubusercontent.com/70813915/211199511-c4aabc67-97b1-49e3-9a09-76af79a30d8f.jpg)

This project is a DIY version of the commercially available LED kits for the LEGO Bonsai Tree. Main features:
- Wemos D1 Mini ESP8266 board
- 4x WS2812B LEDs
- Web interface for operation including colour selection

## Requirements
Hardware-wise, you will need:
- Wemos D1 Mini or equivalent clone
- 4x WS2812B LEDs
- <10g 3D printing filament
- <1m wire
- Micro USB cable and 5V USB power supply
- WiFi Access

The system should not draw more than about 5V/300mA at maximum LED brightness. I used 32awg servo wire to connect the LEDs, this is at your discretion but make sure your wire is rated for enough current for all LEDs! (Each WS2812b LED uses a max of ~60mA).

The printed part for the ESP8266 board is sized to fit the D1 Mini and clones thereof. You may need to add some small scaling factor (1-2% larger or smaller) in your slicer to ensure the Lego-compatible prints fit well depending on the calibration of your printer. The parts fit well at default size from my Prusa Mini+.

## Build Instructions
1. 
