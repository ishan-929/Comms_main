---
title: "The Comms Trasnporter"
author: "Ishan K."
description: "Microphone that can record anything!"
created_at: "2026-07-09"
---

# July 8th: Starting the Project!!

Today was the day that I started working on this project. With me,
the only "microphone" module I had was the KY037, a module that detects 
sound, but not something that is able to take in audio data. Regardless,
I tested it out being that it would be the fiets time I worked with sound.
The code is in the Source file named along the lines of KY037, and it is a 
simple code where if sound detected, turn the led on, otherwise, keep it off. 
It was pretty cool to experient with since id clap and such and it would just 
detect it. Its not ideal though since any sound can trigger it, so I decided to 
do reserach on microphone modules I could actually use. I decided to go with the 
INMP441, a commonly used MEMS Microphone incorperating a tiny disk like diaphragm 
that is able to easily capture audio data from the changes in vibration in air (sound).

Before using it since I didnt have it, I decided to alos test ESP-Now, the communication
protocol I would be using im order to let one device speak to another for this project.
ESp_now is plenty enough powerful in order to create this project since ESP_NOW supports 
a range of 220 meters, which is WELL over what we need given this is ideally going to be
inside houses. Ive had experience with ESp_now before, os the concept wasnt new to me and
when I thought of the project, was already set on doing this. Besides testing the KY047
module and ESP_NOW today, today also just went into a little bit of reseraching as to what 
I should use or even how I should approach this project. I decided so far that id need
a microphone, speaker, dac, OLEd display, and something to use to naviagte on the screen
on the OLED Display. (This project again is a comms teleporter, so the idea behind the screen
is that there would be a home menu of all the rooms and you select which one you want.
After that, just clikc, record, and it sends instantly!).

Thats about it for this day.

**Total time spent: 2hr**

# July 9th: More Research + RaedMe_src's!!

Today I just jotted down evertyhing that I had done the day before, plus
researched a bit more into the parts id use, why id want to incoorperate it 
into the project, and how to even use them. I only answered those questions
today to an extent with the INMP441, but strongly with an SD Card Reader.

The SD card reader was only so many lines you had to know such as making a file
on the Sd card, wrign to it, closing it to save, it was pretty easy. Unlike the SD Card reader
though, the INMP441 was just a pain. Its setup is so long due to ti using a communication protocol called I2S,
which is basiclaly just an optimized communication system for audio sample transfer, so perfect for the mic, I mean
its the only one it gets anyway. The setup was extremely long, and Im still not proficient at it. I dont think im going to memorize all
of it, but I think as long as if I ever see it again and read it, id know what it mean is all that I need for now. I didnt make a code
incoorperating the Sd Card Reader, but, I did make a ESp_NOW code with the INMP441 where one ESp32 thats connected to teh INMP441 takes audio data 
and the esp32 its connected too gets that data and prints it in serial monitor. I thought it was pretty cool, but I also had to find a way
to convert that audio data into an actual audio for an esp32 to play, all in the hardware, so that was something to look forward too. 

Along with this is Source Code Read Me's I wrote about each set of practice src's I creare sort of as a way to show what codes
I made to understand what Im using. (INMP441 first time)

**Total time spent: 4hr**

# July 12th: Final ESP_NOW Code with INMP441

Today was the day that I perfected the code with the INMP441. Essentialy, what happened was that the last time I was working on this,
the code wss just so buggy. Large numbers would appear on the Serial Monitor, and it just wouldnt even work half the time as I kept getting
0's and not actual numbers and all that good Stuff. It made me feel like ripping my hair out because I was geniunyl at it for 4-5 hours...
Not much reddit posts or youtbe videos at all since majority of what they do are just explaingin what it is but not much on how to code it.
Because of this, I read 80 lines not even knwoing what each of them truly meant, besides some you can obviously get some kidn of context clues.
I mean initally I thought what even is ".intr_alloc_flags = ESP_INTR_FLAG_LEVEL1" right or even "i2s_driver_install(I2S_PORT, &config, 0, NULL)"
right... so alot of today was furthmore trying to understand INMP441 and all the ideas behind it such as whats needed to set it up,
why they are needed to set it up, different options you have available for the setup for certain cokmmands and when youd use them, etc. Alos because of this,
I ditched the ESp_NOW code for now and decided to contiue it another day since what mattered ight now was understanding the INMP441.

I went into so many errors it honestly ticked me off. I had to learn the differenc between the two channels, the bytes and bit idea behind it all,
and it just wasnt a pleasent experince. 

Someones gotta make a channel about not only explaing what they are but HOW TO CODE THEM man...

**Total time spent: 5hr**

# July 13th: ESp_NOW Code Done!

After taking a hell of a long time of understaning how to program a tiny module, 
I decided to take it on with ESp_NOW. I would need this in order to talk into one
device and send it to another, so this step was really exciitng to me, as I strated to make
my project come to life surely but slowly. the code wasnt much harder to do once I knew
how to set it up, adn it was just adding ESP_NOW setup lines to the codes. WHen I tested it,
it worked pretty well and i was happy with the results that I got. Along with this day would be me figuring out what 
I would do next. I learned SD Card Reader just to not rely on the ESp32 ram capacity for audio data just to be safe,
as well as the microphone module in order to record data. There were big questions that still needed answering...
like how will the OLED Screen look, how to use a speaker  and dac (never used speaker or dac), what Id use to navigate the
Home page such as buttons or a rotary encoder, , and how Id convert the data into an audio file jst from the hardware, etc. 
After searching up the parts Id use, I decided on a near final List, here:

(To make one device)
-One ESP32 Board
-One INMP441
-One Micro SD Card (for refrence, 8gb is enough for a 37 hour straight file, crazy)
-One Micro SD Card reader for the Micro SD Card
-One 3Watt 4 Ohm Speaker
-One Max98357A DAC
-One Rotary Encoder
-One Red LED
-One Green LED
-A whole bunch of wires and capacitors

This is the near final list, and I doubt Ill change much at this point. Hopefully all are able to intertwine into this one big project,
and I plan on learning CAD as well as PCB Design for this project since I thought Itd be cool if I turn it into an actual product of some sort.

Thats about it in terms of Planning + ESp_NOW code with the INMP441

**Total time spent: 4hr**

# July 16th - 17th : OLED SCreen Home Design Making!

As the title for the journal suggests, these two days were about working on the Display and the Home Screen.
Before the Home Screen though, I wanted to make a loading Screen that plays everytime you turn the device on.
Itd show a "TCT" logo (The Comms Transporter), along with some kind of logo to show thta its loading. I settled on a
progress bar that shows it filling overtime till It cant anymore, then proceeds to take your ight to the Home page.
I thought It was pretty neat and Im proud of it, though, Il probbaly chage either the way the progress bar progresses overtime
or redesign the idea completelty, since a progress bar is kind of old school, not something like a character continuously running
on a land till its done loading or something, thatd be pretty cool. 

That was the Loading Screen, and it takes about 5 seconds till its over with. Ill probably end up chaning that timing as well,
since im not sure if the people would complain if it took "that long" to "boot up". I never went into actual loading Screens,
so if I could add some kind of realness to it, I'd love to do that. For now though after that, I decided to work on the Home page.
I recorded a Lapse video that showed me creating the Loading Screen, but not the icons since I frogot to clikc record :/
but basically its the same as the loading Screen Lapse video, It was all doen in photo pew where the icons were all drawn 16x16 pixels, 
a nice scrollbar all the way to the left of the screen that takes up the whole y amount, it was pretty cool. 



