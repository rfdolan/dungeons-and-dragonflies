DUNGEONS AND DRAGONFLIES 

Raymond Dolan (rfdolan@wpi.edu)
Alejandra Garza (agarza@wpi.edu)

This project serves as our final project for IMGD 3000 taught by Professor Claypool
----------------------------------------------------------------------------------
Platform: Windows

To build:

0) Follow the Setup developer environment for Windows instructions, under "Windows
Setup" section, see: http://dragonfly.wpi.edu/engine/index.html#setup

1) Build by pressing F7 from Visual Studio or by selecting Build->Compile
(NOTE: This project was developed in Visual Studio 2019).

2) Run project by pressing F5

3) After running project, view logs from test by going to vs2019/dragonfly
---------------------------------------------------------------------------------
This directory contains Microsoft Visual Studio v16 (2019) solution
files.

The Solution assumes a directory setup as follows:

Projects/         Location of Visual Studio projects.
-gameX/           Source code for game.
--vs-2019/        Visual Studio solution files.
---Debug/         Location of .exe that runs in Debug mode.
---Release/       Location of .exe that runs in Release mode.
--df-font.txt     Fonts used by Dragonfly.
--df-config.txt   Config file used by Dragonfly (optional).
--sounds/         Sounds used for game.
--sprites/        Sprites used for game.
-SFML-2.5/        SFML directory (version 2.5.*).
-dragonfly/       Location of Dragonfly include/ and lib/ sub-directories.
---------------------------------------------------------------------------------