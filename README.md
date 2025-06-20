# Cub3D - 3D Graphics Engine 🎮

[![42 Project](https://img.shields.io/badge/42-Project-000000?style=flat&logo=42)](https://42.fr/)
[![Score](https://img.shields.io/badge/Score-116%2F100-success?style=flat)](https://github.com/rjaada/Cub3D_42_Project)
[![Language](https://img.shields.io/badge/Language-C-blue?style=flat&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Graphics](https://img.shields.io/badge/Graphics-MLX42-red?style=flat)](https://github.com/codam-coding-college/MLX42)

> A 3D graphics engine built from scratch using raycasting technology, inspired by classic games like Wolfenstein 3D.

## 🏆 Achievement
**Final Score: 116/100** - Exceeded project requirements with bonus implementations.

## 👥 Team
- **Rachid Jaada** ([@rjaada](https://github.com/rjaada))
- **Charlotte Schnathmeier** ([@char-projects]([https://github.com/cschnath](https://github.com/char-projects)))

## 📋 Overview

Cub3D is a 3D graphics engine that renders a first-person perspective of a maze using **raycasting algorithms**. This project demonstrates advanced mathematical programming, computer graphics principles, and real-time rendering techniques.

### 🎯 Core Concept
The engine casts rays from the player's position to detect walls and calculate distances, then renders textured walls with proper perspective projection - the same technique used in classic 3D games.

## ✨ Features

### 🔧 Core Implementation
- **Real-time raycasting engine** with mathematical precision
- **Texture mapping system** with proper UV coordinate handling
- **Smooth player movement** with WASD controls
- **Camera rotation** with arrow keys
- **Map parsing** from `.cub` configuration files
- **Comprehensive error handling** and memory management

### 🎮 Bonus Features
- ✅ **Wall collision detection** with refined movement mechanics
- ✅ **Mouse rotation controls** (M to toggle, N to disable)
- ✅ **Interactive minimap** with real-time player tracking
- ✅ **Enhanced navigation** with dynamic camera movement

## 🛠️ Technical Architecture

### File Structure
```
src/
├── main.c                 # Program entry point and MLX initialization
├── raycasting.c          # Core raycasting algorithm implementation  
├── texture_rendering.c   # Wall texture mapping and rendering
├── movements.c           # Player movement and collision detection
├── file_parsing.c        # .cub file parser and validation
├── map_validation.c      # Map boundary and character validation
├── 2Dmap.c              # Minimap rendering system
└── cleanup.c            # Memory management and resource cleanup
```

### Key Technologies
- **C Programming Language** - Low-level system programming
- **MLX42 Graphics Library** - Cross-platform graphics rendering
- **Mathematical Algorithms** - Trigonometry and linear algebra
- **Memory Management** - Manual allocation and cleanup
- **File I/O** - Custom parsing for map configurations

## 🚀 Installation & Usage

### Prerequisites
- GCC compiler
- MLX42 library
- CMake (for MLX42 build)
- Math library (`-lm`)

### Build Instructions
```bash
# Clone the repository
git clone https://github.com/rjaada/Cub3D_42_Project.git
cd Cub3D_42_Project

# Build the project
make

# Run with a map file
./cub3D maps/val1.cub
```

### Controls
- **WASD** - Move player (forward/left/backward/right)
- **Arrow Keys** - Rotate camera left/right
- **M** - Toggle mouse rotation mode
- **N** - Disable mouse rotation
- **ESC** - Exit program

## 🗺️ Map Format

Maps are defined in `.cub` files with the following format:

```
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png

F 220,100,0
C 0,128,255

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
100000000N000000000000001
1000000000000000000000001
1111111111111111111111111
```

### Map Elements
- `1` - Wall
- `0` - Empty space
- `N/S/E/W` - Player starting position and orientation
- Texture paths for each wall direction
- Floor (F) and ceiling (C) RGB colors

## 🧠 Learning Outcomes

### Technical Skills Developed
- **Graphics Programming** - Understanding of 3D rendering pipelines
- **Mathematical Computing** - Implementation of trigonometric algorithms
- **Memory Management** - Efficient resource allocation and cleanup
- **Software Architecture** - Modular design with clear separation of concerns
- **Error Handling** - Robust parsing and validation systems

### Collaboration Experience
Working with Charlotte taught valuable lessons in:
- **Pair Programming** - Real-time collaborative development
- **Code Integration** - Merging complex graphics components
- **Project Planning** - Dividing algorithmic challenges effectively
- **Quality Assurance** - Cross-testing and debugging strategies

## 🏗️ Project Highlights

### Mathematical Precision
- Implementation of **DDA (Digital Differential Analyzer)** for ray casting
- **Distance correction** to prevent fish-eye effect
- **Texture coordinate calculation** for proper wall mapping

### Performance Optimization
- **Real-time rendering** at smooth frame rates
- **Efficient memory usage** with proper cleanup
- **Optimized raycasting** for responsive gameplay

### Code Quality
- **Norminette compliant** - Adheres to 42 School coding standards
- **Modular architecture** - 19 organized source files
- **Comprehensive validation** - Handles edge cases and malformed input

## 📊 Project Statistics
- **Duration:** ~280 hours of development
- **Lines of Code:** 2000+ lines of C
- **Team Size:** 2 developers
- **Final Score:** 116/100 (Bonus implementation)

## 🎓 42 School Context

This project is part of the 42 School curriculum, designed to teach:
- Low-level graphics programming
- Mathematical algorithm implementation  
- Collaborative software development
- Real-world problem-solving skills

The **116/100 score** reflects not only completion of mandatory features but excellence in bonus implementations and code quality.

---

**Built with passion for graphics programming and mathematical precision.** 🚀
