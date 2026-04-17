# Word Shooter 🎯

A 2D interactive arcade game built using **C++** and **OpenGL**. This project focuses on implementing game logic, collision detection, and real-time string matching within a provided graphics framework.

## 🧠 My Implementation
While the basic drawing utilities were provided, I was responsible for:
* **Game Logic:** Developed the core mechanics in `wordshooter.cpp`, including the shooting physics and state management.
* **Dictionary Integration:** Implemented a search algorithm to validate formed words against a dictionary of **370,099 words**.
* **Coordinate Mapping:** Translated screen pixels to a 22x31 tile-based grid for accurate alphabet placement.
* **Scoring System:** Created logic to detect horizontal, vertical, and diagonal word matches and award points based on word length.

## 🛠️ Technical Stack
* **Language:** C++
* **Graphics:** OpenGL / GLUT
* **Platform:** Linux (Ubuntu)

## 🚀 How to Run
1. Ensure you have the OpenGL libraries installed.
2. Run `bash install-libraries.sh` to install dependencies.
3. Run `make` to compile.
4. Run `./game` to play.
