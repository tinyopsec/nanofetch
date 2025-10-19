# Nanofetch

[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/runrakali/nanofetch/ci.yml)](https://github.com/runrakali/nanofetch/actions)
[![GitHub license](https://img.shields.io/github/license/runrakali/nanofetch)](LICENSE)
[![GitHub contributors](https://img.shields.io/github/contributors/runrakali/nanofetch)](https://github.com/runrakali/nanofetch/graphs/contributors)
[![GitHub top language](https://img.shields.io/github/languages/top/runrakali/nanofetch?logo=c)](https://github.com/runrakali/nanofetch)
[![GitHub commit activity](https://img.shields.io/github/commit-activity/m/runrakali/nanofetch)](https://github.com/runrakali/nanofetch/commits)
[![Latest release](https://img.shields.io/github/v/release/runrakali/nanofetch?logo=github)](https://github.com/runrakali/nanofetch/releases)

A **lightweight, fast, and customizable** system information tool written in C++. Inspired by [Neofetch](https://github.com/dylanaraps/neofetch) and [Fastfetch](https://github.com/fastfetch-cli/fastfetch), Nanofetch focuses on speed, simplicity, and elegant output with gradient support.

---

## ⚡ Quick Start

```bash
git clone https://github.com/runrakali/nanofetch.git
cd nanofetch
makepkg -si
nanofetch
```

---

## 🖼️ Preview

```
     ████████           OS: Arch Linux x86_64
   ██        ██         Kernel: 6.6.10-arch1-1
  ██          ██        Uptime: 2h 34m
 ██            ██       Packages: 1247 (pacman)
 ██    ████    ██       Shell: zsh 5.9
 ██            ██       CPU: Intel i7-9750H (12) @ 4.50GHz
  ██          ██        Memory: 8192 MiB / 16384 MiB
   ██        ██         GPU: NVIDIA GeForce GTX 1660 Ti
     ████████           Terminal: kitty
```

---

## ✨ Features

- 🚀 **Blazing fast** - Written in modern C++17
- 🎨 **Gradient themes** - 13 built-in color schemes (rainbow, neon, sunset, etc.)
- ⚙️ **Highly customizable** - Toggle any info field, use custom ASCII logos
- 📁 **XDG compliant** - Follows XDG Base Directory specification
- 🔧 **No dependencies** - Uses only standard Linux utilities
- 🪶 **Minimal** - Single binary, small footprint

---

## 🧩 Supported Platforms

**Currently supported:**
- ✅ Arch Linux and derivatives (Manjaro, EndeavourOS, Artix, etc.)

**Planned support:**
- 🔜 Debian/Ubuntu (`.deb`)
- 🔜 Fedora/RHEL (`.rpm`)
- 🔜 Void, Gentoo, Alpine
- 🔜 BSD variants

---

## 📦 Installation

### Arch Linux

```bash
makepkg -si
```

### From Source

```bash
g++ -std=c++17 -O2 -o nanofetch nanofetch.cpp
sudo install -Dm755 nanofetch /usr/bin/nanofetch
sudo install -Dm644 logo.txt /usr/share/nanofetch/logo.txt
sudo install -Dm644 config.txt /usr/share/nanofetch/config.txt
sudo install -Dm644 options.txt /usr/share/nanofetch/options.txt
sudo install -Dm644 settings.txt /usr/share/nanofetch/settings.txt
```

---

## 🚀 Usage

Simply run:

```bash
nanofetch
```

On first launch, Nanofetch automatically:
1. Creates `~/.config/nanofetch/`
2. Copies default configs from `/usr/share/nanofetch/`
3. Displays your system information

---

## ⚙️ Configuration

### File Locations

Nanofetch follows the XDG Base Directory specification:

```
~/.config/nanofetch/       # User configuration (edit here)
├── logo.txt               # Custom ASCII logo
├── config.txt             # Gradient settings
├── options.txt            # Toggle info fields
└── settings.txt           # General settings

/usr/share/nanofetch/      # System defaults (don't edit)
├── logo.txt
├── config.txt
├── options.txt
└── settings.txt
```

### Gradient Themes

Edit `~/.config/nanofetch/config.txt`:

```ini
gradient_info=neon         # Info text gradient
gradient_logo=rainbow      # Logo gradient
```

**Available gradients:** `mono`, `blue`, `red`, `green`, `purple`, `orange`, `neon`, `aqua`, `sunset`, `forest`, `rainbow`, `magenta`, `gray`

### Toggle Information Fields

Edit `~/.config/nanofetch/options.txt`:

```ini
os=true
kernel=true
uptime=true
packages=true
shell=true
cpu=true
memory=true
gpu=true
# ... set any to false to hide
```

### Customize Logo

Replace `~/.config/nanofetch/logo.txt` with your own ASCII art, or change the path in `settings.txt`:

```ini
logo=custom-logo.txt
theme=cyan
max_label_width=13
```

---

## 🛠️ Build from Source

### Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+)
- Linux with `/proc` filesystem
- Standard Unix utilities (optional, for some features)

### Compilation

```bash
g++ -std=c++17 -O2 -o nanofetch nanofetch.cpp
```

### Development

```bash
git clone https://github.com/runrakali/nanofetch.git
cd nanofetch
g++ -std=c++17 -g -o nanofetch nanofetch.cpp
./nanofetch
```

---

## 🤝 Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Guidelines

- Follow C++17 standards
- Maintain XDG Base Directory compliance
- Keep code clean and readable (no inline comments)
- Test on multiple distributions when possible

---

## 📋 Roadmap

- [ ] Add distro detection for Debian/Ubuntu
- [ ] Support for `.deb` and `.rpm` packages
- [ ] GPU temperature and usage stats
- [ ] Network interface information
- [ ] Battery status for laptops
- [ ] Custom color definitions
- [ ] Image/logo support (via kitty/sixel)

---

## 🐛 Known Issues

- Terminal font detection is limited
- Display resolution detection requires `xrandr` (X11 only)
- Some GTK theme info requires `gsettings`

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

## 🙏 Acknowledgments

- Inspired by [Neofetch](https://github.com/dylanaraps/neofetch) by Dylan Araps
- Inspired by [Fastfetch](https://github.com/fastfetch-cli/fastfetch)
- Thanks to all [contributors](https://github.com/runrakali/nanofetch/graphs/contributors)

---

## 📞 Support

- 🐛 [Report bugs](https://github.com/runrakali/nanofetch/issues)
- 💡 [Request features](https://github.com/runrakali/nanofetch/issues)
- ⭐ Star the project if you like it!

---

<div align="center">
Made with ❤️ by the Nanofetch community
</div>
