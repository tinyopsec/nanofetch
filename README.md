# Nanofetch

[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/tinyopsec/nanofetch/ci.yml?style=flat-square)](https://github.com/tinyopsec/nanofetch/actions)
[![License](https://img.shields.io/github/license/tinyopsec/nanofetch?style=flat-square)](LICENSE)
[![GitHub Stars](https://img.shields.io/github/stars/tinyopsec/nanofetch?style=flat-square)](https://github.com/tinyopsec/nanofetch/stargazers)
[![Contributors](https://img.shields.io/github/contributors/tinyopsec/nanofetch?style=flat-square)](https://github.com/tinyopsec/nanofetch/graphs/contributors)
[![Latest Release](https://img.shields.io/github/v/release/tinyopsec/nanofetch?style=flat-square)](https://github.com/tinyopsec/nanofetch/releases)
[![Commit Activity](https://img.shields.io/github/commit-activity/m/tinyopsec/nanofetch?style=flat-square)](https://github.com/tinyopsec/nanofetch/commits)
[![Language: C++](https://img.shields.io/github/languages/top/tinyopsec/nanofetch?style=flat-square&logo=c%2B%2B)](https://github.com/tinyopsec/nanofetch)

> A **lightweight, blazingly fast, and highly customizable** system information tool written in modern C++. Display your system stats with style using gradient themes and custom ASCII art.

Nanofetch is a minimal alternative to Neofetch and Fastfetch, designed for speed, simplicity, and visual elegance. Perfect for showcasing your Arch Linux setup with zero bloat.

---

## 🖼️ Preview

![Nanofetch Example 1](https://github.com/tinyopsec/nanofetch/raw/main/screenshots/example01.png)
![Nanofetch Example 2](https://github.com/tinyopsec/nanofetch/raw/main/screenshots/example02.png)

---

## ✨ Features

- **🚀 Blazing Fast** — Written in modern C++17 with performance in mind
- **🎨 Gradient Themes** — 13 built-in color schemes including rainbow, neon, sunset, and more
- **⚙️ Highly Customizable** — Toggle any information field and use custom ASCII logos
- **📁 XDG Compliant** — Follows XDG Base Directory specification for clean config management
- **🔧 Zero Dependencies** — Uses only standard Linux utilities and system calls
- **🪶 Minimal Footprint** — Single binary with a small memory footprint

---

## 🧩 Supported Platforms

**Currently Supported:**
- ✅ Arch Linux and derivatives (Manjaro, EndeavourOS, Artix, ArcoLinux, etc.)

**Planned Support:**
- 📋 Debian/Ubuntu (`.deb` packages)
- 📋 Fedora/RHEL (`.rpm` packages)
- 📋 Void Linux
- 📋 Gentoo
- 📋 Alpine Linux
- 📋 BSD variants (FreeBSD, OpenBSD)

---

## 📦 Installation

### Arch Linux (AUR)

Install directly from the AUR using your preferred AUR helper:

```bash
yay -S nanofetch
```

Or with `paru`:

```bash
paru -S nanofetch
```

### Arch Linux (Manual Build)

Clone the repository and build with `makepkg`:

```bash
git clone https://github.com/tinyopsec/nanofetch.git
cd nanofetch
makepkg -si
```

### From Source (Any Linux Distribution)

For manual installation on any Linux distribution:

```bash
install folder nanofetch
cd nanofetch
g++ -std=c++17 -O2 -o nanofetch nanofetch.cpp
sudo install -Dm755 nanofetch /usr/bin/nanofetch
sudo install -Dm644 logo.txt /usr/share/nanofetch/logo.txt
sudo install -Dm644 config.txt /usr/share/nanofetch/config.txt
sudo install -Dm644 options.txt /usr/share/nanofetch/options.txt
sudo install -Dm644 settings.txt /usr/share/nanofetch/settings.txt
```

---

## 🗑️ Uninstallation

### Arch Linux (AUR)

```bash
yay -R nanofetch
```

Or with `paru`:

```bash
paru -R nanofetch
```

### Manual Uninstallation

```bash
sudo rm /usr/bin/nanofetch
sudo rm -rf /usr/share/nanofetch
rm -rf ~/home/<user>/.config/nanofetch
```

---

## 🚀 Usage

Simply run Nanofetch in your terminal:

```bash
nanofetch
```

### First Launch

On first run, Nanofetch automatically:
1. Creates the configuration directory at `~/home/<user>/.config/nanofetch/`
2. Copies default configuration files from `/usr/share/nanofetch/`
3. Displays your system information with default settings

---

## ⚙️ Configuration

### Configuration File Structure

Nanofetch follows the XDG Base Directory specification:

```
~/home/<user>/.config/nanofetch/           # User configuration (edit these)
├── logo.txt                   # Custom ASCII logo
├── config.txt                 # Gradient theme settings
├── options.txt                # Toggle information fields
└── settings.txt               # General settings

/usr/share/nanofetch/          # System defaults (do not edit)
├── logo.txt
├── config.txt
├── options.txt
└── settings.txt
```

### Gradient Themes

Customize your color schemes by editing `~/home/<user>/.config/nanofetch/config.txt`:

```ini
gradient_info=neon            # Gradient for system information text
gradient_logo=rainbow         # Gradient for ASCII logo
```

**Available Gradients:**

| Theme      | Description                                    |
|------------|------------------------------------------------|
| `mono`     | Monochrome white                               |
| `blue`     | Classic blue tones                             |
| `red`      | Vibrant red gradient                           |
| `green`    | Fresh green hues                               |
| `purple`   | Royal purple shades                            |
| `orange`   | Warm orange tones                              |
| `neon`     | Bright cyan and green neon effect              |
| `aqua`     | Cool aqua and cyan                             |
| `sunset`   | Warm sunset colors                             |
| `forest`   | Deep forest greens                             |
| `rainbow`  | Full spectrum rainbow                          |
| `magenta`  | Bold magenta and pink                          |
| `gray`     | Neutral grayscale                              |

### Toggle Information Fields

Control which system information is displayed by editing `~/home/<user>/.config/nanofetch/options.txt`:

```ini
os=true                        # Operating system
kernel=true                    # Kernel version
uptime=true                    # System uptime
packages=true                  # Installed packages count
shell=true                     # Current shell
cpu=true                       # CPU model
memory=true                    # RAM usage
gpu=true                       # GPU information
resolution=true                # Screen resolution
de=true                        # Desktop environment
wm=true                        # Window manager
theme=true                     # GTK theme
icons=true                     # Icon theme
terminal=true                  # Terminal emulator
```

Set any field to `false` to hide it from the output.

### Custom ASCII Logo

Replace the default logo by editing `~/home/<user>/.config/nanofetch/logo.txt` with your own ASCII art. Alternatively, specify a different logo file in `~/.config/nanofetch/settings.txt`:

```ini
logo=custom-logo.txt           # Path to custom logo file
theme=cyan                     # Default theme color
max_label_width=13             # Maximum width for info labels
```

---

## 🛠️ Build from Source

### Requirements

- **Compiler:** GCC 7+ or Clang 5+ with C++17 support
- **System:** Linux with `/proc` filesystem
- **Optional:** Standard Unix utilities for extended features (e.g., `xrandr` for resolution detection)

### Compilation

Basic compilation command:

```bash
g++ -std=c++17 -O2 -o nanofetch nanofetch.cpp
```

### Development Build

For development with debug symbols:

```bash
git clone https://github.com/tinyopsec/nanofetch.git
cd nanofetch
g++ -std=c++17 -g -Wall -Wextra -o nanofetch nanofetch.cpp
./nanofetch
```

---

## 🤝 Contributing

Contributions are welcome and appreciated! Whether you want to fix bugs, add features, or improve documentation, feel free to contribute.

### How to Contribute

1. **Fork** the repository
2. **Create** a feature branch
   ```bash
   git checkout -b feature/amazing-feature
   ```
3. **Commit** your changes
   ```bash
   git commit -m 'Add amazing feature'
   ```
4. **Push** to your branch
   ```bash
   git push origin feature/amazing-feature
   ```
5. **Open** a Pull Request

### Contribution Guidelines

- Follow **C++17/20 standards** for all code
- Maintain **XDG Base Directory compliance**
- Write **clean, readable code** without excessive inline comments
- Test on **multiple distributions** when possible
- Update **documentation** for new features
- Ensure **backwards compatibility** when modifying configuration files

---

## 📋 Roadmap

### Planned Features

- [ ] Automatic distro detection for Debian/Ubuntu
- [ ] Official `.deb` and `.rpm` package support
- [ ] GPU temperature and usage statistics
- [ ] Network interface information (IP, bandwidth)
- [ ] Battery status and health for laptops
- [ ] Custom color definitions with hex codes
- [ ] Image/logo support via kitty graphics protocol or sixel
- [ ] Plugin system for custom information modules
- [ ] JSON export mode for scripting
- [ ] Multi-language support for system information

### Under Consideration

- [ ] Wayland-native display detection
- [ ] Disk usage and filesystem information
- [ ] Docker/container detection
- [ ] System load averages
- [ ] Color scheme preview tool

---

## 🐛 Known Issues

- **Font Detection:** Terminal font detection is limited and may not work on all terminal emulators
- **Resolution Detection:** Display resolution requires `xrandr` (X11 only, Wayland support pending)
- **GTK Theme Info:** Some GTK theme information requires `gsettings` to be installed
- **Multi-GPU Systems:** GPU detection may only show the primary GPU on multi-GPU setups

Report issues at the [GitHub issue tracker](https://github.com/tinyopsec/nanofetch/issues).

---

## 📜 License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

- Inspired by [**Neofetch**](https://github.com/dylanaraps/neofetch) by Dylan Araps
- Inspired by [**Fastfetch**](https://github.com/fastfetch-cli/fastfetch)
- Thanks to all [contributors](https://github.com/tinyopsec/nanofetch/graphs/contributors) who help improve Nanofetch
- Special thanks to the Arch Linux and open-source communities

---

## 📞 Support & Community

- 🐛 [**Report Bugs**](https://github.com/tinyopsec/nanofetch/issues) — Found a bug? Let us know
- 💡 [**Request Features**](https://github.com/tinyopsec/nanofetch/issues) — Have an idea? Share it with us
- ⭐ **Star the Project** — If you like Nanofetch, give it a star on GitHub
- 🔀 **Fork & Customize** — Make it your own and share your improvements

---

<div align="center">

**Made with ❤️ by tech hat and the Nanofetch community**

[⬆ Back to Top](#nanofetch)

</div>
