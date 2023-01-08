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
1. Print the files in /3DP Files:
    - 1x 'd1_mount.stl'
    - 4x 'LED_mount_brick.stl'
Whilst printing:
2. Partly dismantle the LEGO kit so that you have the light brown base separated. This should come apart from the black 'pot' easily with a push from the underside.
3. Flash the D1 mini using the files in /lego_bonsai_LED:
    - Open the .ino file in the Arduino IDE
    - Change the credentials in 'ssid.h' to match your WiFi network
    - Compile and upload to your board (you may need to install the appropriate boards and libraries in the IDE)
When the prints are done:
4. Attach the printed LED mounts in the corners of the brown base piece and drill a small hole to feed the wires through. Use the adhesive to stick the LEDs to the mounts
![20230106_172618](https://user-images.githubusercontent.com/70813915/211201521-d07996c2-adb7-45d6-968d-9f2c913a51ee.jpg)

5. Solder the LEDs, data to D1 on the D1 mini
![Screenshot 2023-01-08 at 14 22 51](https://user-images.githubusercontent.com/70813915/211201461-b2d8ea2e-0020-4d19-a0b2-9fdd1fa81409.png)
![20230106_181714](https://user-images.githubusercontent.com/70813915/211201490-f5ea73cd-219a-4ec8-b1db-fa11b572ab60.jpg)
![20230106_181534](https://user-images.githubusercontent.com/70813915/211201644-cb01a18c-28da-41ed-b001-3111688708a2.jpg)

6. Attach the D1 Mini to the underside of the brown base using the printed d1_mount. The USB port should be face-down (towards the ground)
![20230106_182100](https://user-images.githubusercontent.com/70813915/211201591-385994e0-6ba5-415e-ac79-958cdd1de27f.jpg)
![20230106_181645](https://user-images.githubusercontent.com/70813915/211201623-1ca23e7f-ccfd-48c0-92e7-2dcdbfbbf2ef.jpg)

7. Reassemble the tree
8. Power on and navigate to the IP address assigned by your router
9. Use the web interface to change the colour and power state of the LEDs
