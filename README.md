# Nanofetch

[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/tinyopsec/nanofetch/ci.yml)](https://github.com/tinyopsec/nanofetch/actions)
[![GitHub license](https://img.shields.io/github/license/tinyopsec/nanofetch)](LICENSE)
[![GitHub contributors](https://img.shields.io/github/contributors/tinyopsec/nanofetch)](https://github.com/tinyopsec/nanofetch/graphs/contributors)
[![GitHub top language](https://img.shields.io/github/languages/top/tinyopsec/nanofetch?logo=c)](https://github.com/tinyopsec/nanofetch)
[![GitHub commit activity](https://img.shields.io/github/commit-activity/m/tinyopsec/nanofetch)](https://github.com/tinyopsec/nanofetch/commits)
[![Latest release](https://img.shields.io/github/v/release/tinyopsec/nanofetch?logo=github)](https://github.com/tinyopsec/nanofetch/releases)

A **lightweight, fast, and customizable** system information tool written in C++. Inspired by [Neofetch](https://github.com/dylanaraps/neofetch) and [Fastfetch](https://github.com/fastfetch-cli/fastfetch), Nanofetch focuses on speed, simplicity, and elegant output with gradient support.

---

## ⚡ Quick Start

```bash
Download the nanofetch file from the repository
cd /path/to/nanofetch
makepkg -si
nanofetch

or

yay -S nanofetch (Only on arch-based systems is YAY needed)
```

---

## 🖼️ Preview
![Nanofetch preview 1](https://github.com/tinyopsec/nanofetch/raw/main/screenshots/example01.png)
![Nanofetch preview 2](https://github.com/tinyopsec/nanofetch/raw/main/screenshots/example02.png)

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
g++ -std=c++20 -O2 -o nanofetch nanofetch.cpp
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
~/home/<username>/.config/nanofetch/       # User configuration (edit here)
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

Edit `~home/<username>/.config/nanofetch/config.txt`:

```ini
gradient_info=neon         # Info text gradient
gradient_logo=rainbow      # Logo gradient
```

**Available gradients:** `mono`, `blue`, `red`, `green`, `purple`, `orange`, `neon`, `aqua`, `sunset`, `forest`, `rainbow`, `magenta`, `gray`

### Toggle Information Fields

Edit `~/home/<username>/.config/nanofetch/options.txt`:

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
g++ -std=c++20 -g -o nanofetch nanofetch.cpp
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

- Follow C++20 standards
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
