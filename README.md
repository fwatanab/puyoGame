# PuyoGame

A simple Puyo Puyo clone built using C++ and SDL2. This project demonstrates fundamental game development concepts, including rendering, input handling, and game logic.

## Features

- Puyo Puyo-style gameplay
- Basic rendering using SDL2
- Cross-platform compatibility via Docker
- Modular code structure for easy extension

---

## Prerequisites

To build and run this project, you need:

- **Docker**: To ensure a consistent development environment
- **Docker Compose**: For easy service management

---

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/fwatanab/puyoGame.git
cd puyogame
```

## Build and Run with Docker

1. Build the Docker image:

```bash
make build
```

2. Run the game in a container:
```bash
make run
```

3. Check the running container status:
```bash
make status
```
4. View logs (optional):
```bash
make logs
```

5. Stop and clean up:
```bash
make stop
make clean
```
---

## Development
### Running Locally (Optional)
If you prefer to run the project without Docker, ensure you have the following installed:

- SDL2
- SDL2_image  

Install the required dependencies:

```bash
sudo apt-get update && sudo apt-get install -y \
    build-essential \
    cmake \
    libsdl2-dev \
    libsdl2-image-dev
```
Then build and run the project:

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
./PuyoGame
```
---

## Troubleshooting

### Common Errors

1. SDL2_image not found
- Ensure libsdl2-image-dev is installed or use pkg-config in CMakeLists.txt.
2. Docker issues
- Ensure Docker is running and your user has permissions to run Docker commands.
3. Display not working
- Ensure X11 forwarding is enabled or a compatible display environment is available.
