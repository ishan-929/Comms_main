#  A Comms Teleporter!

- A Device that is able to let you decide what room in your house you want to send audio too, record your voice, and send it to the device in that room to play back out loud!
- PLEASE NOTE: This project is still in the making. ESP_NOW to another one of these devices, a MAX98357A DAC, and a 3 Watt speaker are yet to be added. At its current stage,
  it is able to record audio and send it to the SD Card Module.

---

##  Contains...

- An INMP441 Microphone Module that is able to capture your Audio Data 
- A Micro SD Card and an SD Card reader that stores that audio data
- LEDs to let you know if your recording or not (green = yes, red = no).
- A rotary Encoder to let you Scroll on the pages on the SSD1306 OLED Screen and select

---

## Materials Required for the Project


- 1 [ESP32](https://www.alibaba.com/product-detail/Esp32-Development-Board-Wifi-Ultra-low_1601030060154.html?spm=a2700.prosearch.normal_offer.d_title.733a67afcJ84oK&priceId=3cf063b523884a038f0c1823b3017da3) , $3.00 
- 1 [SD Card Reader](https://www.alibaba.com/product-detail/Micro-SD-Card-Module-TF-Card_1601463910540.html?spm=a2700.prosearch.normal_offer.d_title.14c367afjk1aiV&priceId=25debad767474e719ee8c87758902714) , $0.30 
- 1 [Micro SD Card](https://www.alibaba.com/product-detail/Shine-True-Custom-Mini-SD-Memory_1601595206889.html?spm=a2700.prosearch.normal_offer.d_title.376567afGpLVhv&selectedCarrierCode=SEMI_MANAGED_STANDARD%40%40STANDARD&priceId=12dcffaac9154ae1a2794e56279c8a5e) ,$1.70 
- 1 | [INMP441](https://www.alibaba.com/product-detail/INMP441-Omni-directional-MEMS-Microphone-Module_1601724989762.html?spm=a2700.prosearch.normal_offer.d_title.2ed267afZyfFCn&priceId=7a26cbf665ef4a119280b80428e141b3) , $1.00 
- 1 | [1.54" SSD1306 OLED Display](https://www.alibaba.com/trade/search?SearchText=ssd1306+oled+display+1.54+inch) , $2.50 
- 1 | [Rotary Encoder](https://www.alibaba.com/trade/search?SearchText=rotary+encoder+module+ky-040) , $0.40 
- 2 | [LEDS](https://www.alibaba.com/product-detail/China-Manufacturer-Red-Green-Blue-Yellow_1600947326535.html) , $0.10 
- 2 | [220 Ohm Resistors](https://www.alibaba.com/product-detail/Fuse-Resistor-2W-1-100R-150_1600789699976.html?spm=a2700.prosearch.normal_offer.d_title.3e1367afspSEj6&selectedCarrierCode=SEMI_MANAGED_STANDARD%40%40STANDARD&priceId=8e6c4a268a5c41369eeee7eb861f39ca) , $0.04 
- 2 | [104 Ceramic Capacitors](https://www.alibaba.com/trade/search?SearchText=104+ceramic+capacitor) , $0.05 
- cables as needed [about 27-35](https://www.alibaba.com/product-detail/TZT-Hot-Sell-140pcs-U-Shape_1601466408418.html?spm=a2700.prosearch.normal_offer.d_title.27e067afdBlNmu&priceId=dec8cd697f8a4587b4fe52e36af310c9) , $0.65 
- Total: ~$9.74 (not including shipping or anything)

---

##  Assembling the project

### 1. Assembly
- **Soldering:** [You might have to solder INMP441 pins and ESP32 pins onto itself, so thats the first step.]
- **Icon Creation** [I created the Icons on Photopea, then uploaded them onto image2cpp, which is linked to this text](https://javl.github.io/image2cpp/)
- **Wiring:** [You can check out the pinout here:] <img width="1539" height="1108" alt="Screenshot 2026-07-31 220816" src="https://github.com/user-attachments/assets/a7e429ee-bb55-4d8d-b8e4-c4b1f71a8897" />
- **Video** [You can check out my video on my system here:] https://drive.google.com/file/d/1JQtBzxquqxLIkbg-6mlFQjLLs1y0eG3C


  ## AI-Declaration
  - AI was used mostly in part of the Screen aspects, in terms of how I can go about from ""one screen to another" and the logic behind that since it was new to me. Alot of Logic in the Recording screen as well was done with the help of AI since that part always consisted of constant bugs and logic errors
    with the buffers.
