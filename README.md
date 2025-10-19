# Nanofetch

[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/runrakali/nanofetch/ci.yml)](https://github.com/runrakali/nanofetch/actions)
[![GitHub license](https://img.shields.io/github/license/runrakali/nanofetch)](LICENSE)
[![GitHub contributors](https://img.shields.io/github/contributors/runrakali/nanofetch)](https://github.com/runrakali/nanofetch/graphs/contributors)
[![GitHub top language](https://img.shields.io/github/languages/top/runrakali/nanofetch?logo=c)](https://github.com/runrakali/nanofetch)
[![GitHub commit activity](https://img.shields.io/github/commit-activity/m/runrakali/nanofetch)](https://github.com/runrakali/nanofetch/commits)
[![Latest release](https://img.shields.io/github/v/release/runrakali/nanofetch?logo=github)](https://github.com/runrakali/nanofetch/releases)

Nanofetch is a **lightweight, fast, and customizable** command-line tool for displaying system information in a visually clean way inspired by [Neofetch](https://github.com/dylanaraps/neofetch) and [Fastfetch](https://github.com/fastfetch-cli/fastfetch).

Written in **C++**, focused on **speed**, **simplicity**, and **clarity**.  
Its goal is to be a minimal yet flexible alternative to Fastfetch for users who prefer simplicity or smaller systems.

> ⚡ Nanofetch currently supports only **Arch-based distributions** that use `makepkg`.

---

## 🖼️ Screenshots

(Coming soon — will be added after the first public release)

---

## 🧩 Supported Platforms

Currently supported:
- **Arch Linux** and all Arch-based distributions (Manjaro, EndeavourOS, Artix, etc.)

Planned future support:
- Debian / Ubuntu (`.deb` packages)
- Fedora / RHEL (`.rpm` packages)
- Void, Gentoo, Alpine, BSDs, and more

---

## ⚙️ Installation

After installation via makepkg -si, the files will be located as follows:
System files (installed by the package):
bash
/usr/bin/nanofetch                    # Executable file
/usr/share/nanofetch/logo.txt         # Default system logo
/usr/share/nanofetch/config.txt       # System gradient configuration
/usr/share/nanofetch/options.txt      # System options
/usr/share/nanofetch/settings.txt     # System settings

User configurations (created on first launch):

bash
~/.config/nanofetch/logo.txt          # Your personal logo
~/.config/nanofetch/config.txt        # Your gradients
~/.config/nanofetch/options.txt       # Your options
~/.config/nanofetch/settings.txt      # Your settings

How it works:

During installation: Files are copied to /usr/share/nanofetch/
On first launch: nanofetch automatically:
Creates ~/.config/nanofetch/
Copies files from /usr/share/nanofetch/ to it

On subsequent launches: Reads from ~/.config/nanofetch/

Check file locations:

bash
# System files
ls -la /usr/share/nanofetch/

# User files (after first launch)
ls -la ~/.config/nanofetch/

# Which files were installed by the package
pacman -Ql nanofetch

Edit configuration:

bash
# Edit your personal settings
nano ~/.config/nanofetch/config.txt

# Change gradients
nano ~/.config/nanofetch/config.txt

# Change logo
nano ~/.config/nanofetch/logo.txt

Important: Edit the files in ~/.config/nanofetch/, not in /usr/share/nanofetch/, because system files

Translated with DeepL.com (free version)
