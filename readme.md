# 🏓 Classic Ping Pong (Pong) – C++ / SFML

A simple **classic Ping Pong (Pong) game** implemented in **C++** using **SFML**.  
This project focuses on learning **game loops, real-time input, collision detection, and frame-independent movement** without using a game engine.

---

## 🎮 Features

- Frame-independent ball movement using delta time
- Two-player paddle controls
  - Left paddle: `W` / `S`
  - Right paddle: `↑` / `↓`
- Ball–wall and ball–paddle collision detection
- Ball pause for 1 second after reset
- Paddle movement clamped within window boundaries
- Minimal classic Pong-style visuals

---

## 🛠️ Built With

- **C++**
- **SFML (Simple and Fast Multimedia Library)**

---

## 📦 Requirements

- `g++` (or any C++17-compatible compiler)
- **SFML** installed for your operating system

---

## ⚙️ Compilation

Make sure SFML is properly installed and linked.

```bash
g++ ping_pong.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
./game
```