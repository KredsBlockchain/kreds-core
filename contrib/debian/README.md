
Debian
====================
This directory contains files used to package kredsd/kreds-qt
for Debian-based Linux systems. If you compile kredsd/kreds-qt yourself, there are some useful files here.

## kreds: URI support ##


kreds-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install kreds-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your kreds-qt binary to `/usr/bin`
and the `../../share/pixmaps/kreds128.png` to `/usr/share/pixmaps`

kreds-qt.protocol (KDE)

