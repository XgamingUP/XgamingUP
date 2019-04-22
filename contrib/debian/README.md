
Debian
====================
This directory contains files used to package xgamingupd/xgamingup-qt
for Debian-based Linux systems. If you compile xgamingupd/xgamingup-qt yourself, there are some useful files here.

## xgamingup: URI support ##


xgamingup-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install xgamingup-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your xgamingupqt binary to `/usr/bin`
and the `../../share/pixmaps/xgamingup128.png` to `/usr/share/pixmaps`

xgamingup-qt.protocol (KDE)

