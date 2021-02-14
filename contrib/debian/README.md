
Debian
====================
This directory contains files used to package remitad/remita-qt
for Debian-based Linux systems. If you compile remitad/remita-qt yourself, there are some useful files here.

## remita: URI support ##


remita-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install remita-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your remita-qt binary to `/usr/bin`
and the `../../share/pixmaps/remita128.png` to `/usr/share/pixmaps`

remita-qt.protocol (KDE)

