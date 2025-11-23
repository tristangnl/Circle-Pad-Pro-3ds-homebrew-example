# Circle-Pad-Pro-3ds-homebrew-example

I created this simple example program to show homebrew developers how to **integrate Circle Pad Pro support** on the **Nintendo 3DS** by **reading its inputs**.

> [!NOTE]
> It also read New 3ds inputs

## About this project

#### Why

The **[Circle Pad Pro](https://niwanetwork.org/wiki/Nintendo_3DS_Circle_Pad_Pro)**(or Slide Pad Expansion) is an accessory for the Nintendo **Old 3DS** and **Old 3DS XL** systems. It adds a second **analog stick** as well as additional **ZL** and **ZR** shoulder triggers that communicates with the device via the **[infrared port](https://www.3dbrew.org/wiki/Circle_Pad_Pro)**. It was only compatible with a **limited selection** of **games**.

On the **[New 3DS/2DS](https://fr.wikipedia.org/wiki/New_Nintendo_3DS)** models, these extra buttons are built directly **into the hardware**, which makes the Circle Pad Pro accessory obsolete. Handling its inputs is more complex than reading the built-in buttons, since it relies on infrared communication and there are no official functions or examples provided in the **[libctru](https://github.com/devkitPro/libctru/tree/master)** library. That's why few homebrew developers consider adding support for it.


This is **unfortunate** for players who own this accessory, still use an Old 3ds and would like to see official games and homebrews gain support for the Circle Pad Pro through **patches** or **plugins** thanks to 3DS modding.

#### How

I initially started by looking for **existing projects** and found [3DS-CPP](https://github.com/RedTopper/3DS-CPP) by RedTrooper, which was unfortunately outdated. I managed to compile it by updating parts of the code with a newer version of the libctru library, but I was never able to get it to recognize my Circle Pad Pro, as it kept returning **error codes**. 

Then, I suspected it was a **permissions** problem, thinking the 3DS might not **allow infrared data transfers** with the **.3dsx** format. I considered compiling it as a **.cia** application, but I didn’t know how to do it. That’s why I looked for a recent homebrew project as a **reference**, to understand the Makefile and configuration files such as the .rsf.

I used [Red Viper](https://github.com/skyfloogle/red-viper), a homebrew that had just been updated and was the most recent at the time. But when I started exploring the source code, I finally found the files (**cpp.c** and **extrapad.c**) **containing the functionality** I had been trying to **get working for months**. After all my research, I had thought that no homebrew project supported the Circle Pad Pro so I was amazed to come across this project by chance.


By studying the code, I created a main.c file that uses these two source files to provide a **simple example** .3dsx of how to use them.


## Shoutout
I’d like to give a huge thanks to **Skyfloogle** for his work on infrared communications, as well as to all the contributors of the **3ds virtual boy emulator**, Red Viper.
I’d also like to thank **RedTrooper**, who conducted research and developed a program on this topic a few years ago.
Finally, many thanks to the authors of libctru and everyone who has worked on the Nintendo 3DS.

## useful links 

#### Doc and source code
libctru doc: https://libctru.devkitpro.org/
libctru github: https://github.com/devkitPro/libctru/tree/master

libctru ir.h (functions for using infrared protocol): https://libctru.devkitpro.org/ir_8h.html
source code ir.h(O3ds + CPP): https://github.com/devkitPro/libctru/blob/master/libctru/include/3ds/services/ir.h

libctru irrst.h (functions for handling new buttons on N3ds): https://libctru.devkitpro.org/irrst_8h.html
source code irrst.h (N3ds + cstick + zr/zl): https://github.com/devkitPro/libctru/blob/master/libctru/include/3ds/services/irrst.h


#### Wiki

Infared Service 3ds(homebrew): https://3dbrew.org/wiki/IR_Services

Circle pad pro Protocol: https://www.3dbrew.org/wiki/Circle_Pad_Pro

NintendoWiki: https://niwanetwork.org/wiki/Nintendo_3DS_Circle_Pad_Pro

Nintendo3ds fandom: https://nintendo3ds.fandom.com/wiki/Circle_Pad_Pro

#### projects using CPP

3DS-CPP by RedTrooper: https://github.com/RedTopper/3DS-CPP

Red Viper: https://github.com/skyfloogle/red-viper

Circle Pad Pro demo by AzureMarker : https://github.com/AzureMarker/n3ds-circle-pad-pro-demo

Some research by ianrabt : https://github.com/ianrabt/3ds-circle-pad-pro-test

#### forums
gbatemp CPP developpment on 3ds(2015): https://gbatemp.net/threads/infra-red-resource-thread.399336/



