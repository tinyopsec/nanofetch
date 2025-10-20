# Nanofetch

[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/tinyopsec/nanofetch/ci.yml)](https://github.com/tinyopsec/nanofetch/actions)
[![GitHub license](https://img.shields.io/github/license/tinyopsec/nanofetch)](LICENSE)
[![GitHub contributors](https://img.shields.io/github/contributors/tinyopsec/nanofetch)](https://github.com/tinyopsec/nanofetch/graphs/contributors)
[![GitHub top language](https://img.shields.io/github/languages/top/tinyopsec/nanofetch?logo=c%2B%2B)](https://github.com/tinyopsec/nanofetch)
[![GitHub commit activity](https://img.shields.io/github/commit-activity/m/tinyopsec/nanofetch)](https://github.com/tinyopsec/nanofetch/commits)
[![Latest release](https://img.shields.io/github/v/release/tinyopsec/nanofetch?logo=github)](https://github.com/tinyopsec/nanofetch/releases)

A **lightweight, fast, and customizable** system information tool written in C++.  
Inspired by [Neofetch](https://github.com/dylanaraps/neofetch) and [Fastfetch](https://github.com/fastfetch-cli/fastfetch),  
Nanofetch focuses on speed, simplicity, and elegant output with gradient support.

---

## ⚡ Quick Start

```bash
git clone https://github.com/tinyopsec/nanofetch.git
cd nanofetch
makepkg -si
nanofetch

🖼️ Preview

Nanofetch preview 1
Nanofetch preview 2
✨ Features

    🚀 Blazing fast — written in modern C++17

    🎨 Gradient themes — 13 built-in color schemes (rainbow, neon, sunset, etc.)

    ⚙️ Highly customizable — toggle any info field, use custom ASCII logos

    📁 XDG compliant — follows XDG Base Directory specification

    🔧 No dependencies — uses only standard Linux utilities

    🪶 Minimal — single binary, small footprint

📦 Installation
🧩 Method 1 — Install from AUR (recommended)

If you use an AUR helper like yay

:

yay -S nanofetch

    This will automatically download, build, and install Nanofetch from AUR.

🧰 Method 2 — Build manually with makepkg

git clone https://github.com/tinyopsec/nanofetch.git
cd nanofetch
makepkg -si

🧱 Method 3 — Build and install manually (from source)

g++ -std=c++20 -O2 -o nanofetch nanofetch.cpp
sudo install -Dm755 nanofetch /usr/bin/nanofetch
sudo install -Dm644 logo.txt /usr/share/nanofetch/logo.txt
sudo install -Dm644 config.txt /usr/share/nanofetch/config.txt
sudo install -Dm644 options.txt /usr/share/nanofetch/options.txt
sudo install -Dm644 settings.txt /usr/share/nanofetch/settings.txt

🚀 Usage

nanofetch

On first launch, Nanofetch automatically:

    Creates ~/.config/nanofetch/

    Copies default configs from /usr/share/nanofetch/

    Displays your system information

⚙️ Configuration

Nanofetch follows the XDG Base Directory specification.
Default Locations

~/.config/nanofetch/          # User configuration
├── logo.txt
├── config.txt
├── options.txt
└── settings.txt

/usr/share/nanofetch/         # System defaults
├── logo.txt
├── config.txt
├── options.txt
└── settings.txt

Example: Gradient Configuration

Edit ~/.config/nanofetch/config.txt:

gradient_info=neon
gradient_logo=rainbow

Available gradients: mono, blue, red, green, purple, orange, neon, aqua, sunset, forest, rainbow, magenta, gray
Example: Info Fields Toggle

Edit ~/.config/nanofetch/options.txt:

os=true
kernel=true
uptime=true
packages=true
shell=true
cpu=true
memory=true
gpu=true

Example: Custom Logo

Edit ~/.config/nanofetch/settings.txt:

logo=custom-logo.txt
theme=cyan
max_label_width=13

🧰 Build from Source
Requirements

    GCC 7+ or Clang 5+

    Linux with /proc

    Standard Unix utilities (optional)

Compile

g++ -std=c++20 -O2 -o nanofetch nanofetch.cpp

Develop

git clone https://github.com/tinyopsec/nanofetch.git
cd nanofetch
g++ -std=c++20 -g -o nanofetch nanofetch.cpp
./nanofetch

📋 Roadmap

Distro detection for Debian/Ubuntu

.deb and .rpm package builds

GPU temperature and usage

Battery and network info

Custom color themes

    Image/logo (kitty/sixel) support

🐛 Known Issues

    Font detection limited

    xrandr required for display info (X11 only)

    Some GTK data needs gsettings

📜 License

This project is licensed under the MIT License

.
🙏 Acknowledgments

    Neofetch

— Dylan Araps

Fastfetch

— contributors

Contributors
<div align="center">

⭐ Made with ❤️ by tech hat and the Nanofetch community ⭐
</div> ```
