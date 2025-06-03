# Forest Runner

A fast-paced 2D pixel-art runner game built using SDL2.  
Dodge obstacles, collect power-ups, and survive as long as possible!

## 🎮 Features

- Infinite side-scrolling with randomized level chunks
- Collectibles: Coins, Apples (+3 pts), Carrots (invincibility), Tomatoes (fly)
- Game states: Menu, Pause, Play, Game Over
- Pixel-art visuals and smooth controls

## 📁 Folder Structure

project/
│
├── assets/ # All images, fonts, tilesets
├── src/ # All C++ source and header files
├── build/ # (Created during compilation)
├── Makefile # For compiling
├── .gitignore
└── README.md


## 🛠️ Requirements

- C++17
- SDL2
- SDL2_image
- SDL2_ttf

### 🐧 Linux / 🧰 macOS

Install dependencies via package manager:
```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
# or
brew install sdl2 sdl2_image sdl2_ttf

make
./runner

to clean:

make clean
