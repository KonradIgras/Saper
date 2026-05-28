Minesweeper (Saper) on MKL05Z4
1. Project description and goal

The goal of this project was to implement the classic logic game “Minesweeper” on an embedded system based on the MKL05Z4 microcontroller. The project integrates a graphical OLED display and an external input device in the form of a computer mouse, creating a complete and interactive gaming system.

2. Hardware used
Microcontroller: NXP Kinetis MKL05Z4 (ARM Cortex-M0+ core)
Display: Monochrome 1.3” OLED, 128×64 pixels resolution
Input device: PS/2 computer mouse
3. System architecture (technical layer)
Graphics and display

The image is generated in the microcontroller RAM (1024-byte framebuffer) and then transmitted to the SSD1306 display driver using a software-based SPI protocol (bit-banging). This approach allows flexible pin mapping and full control over transmission timing.

Mouse communication

A bidirectional PS/2 protocol is used to read relative cursor movements and button states. Data is decoded in real time and mapped to the game grid.

Random number generation

A 32-bit seed for the LCG (Linear Congruential Generator) is generated using ADC readings from thermal noise on an unconnected pin (PTA8).

4. Game logic
Start: After power-up, the system initializes hardware and generates the game board automatically.
Movement: The player moves the cursor using the mouse.
Reveal: The left mouse button reveals tiles. The first click is always safe (prevents instant loss).
Flags: The right mouse button marks suspected mine locations.
Game over: Stepping on a mine immediately reveals all hidden bombs on the board.
Reset board: The scroll button is used to restart the game.
