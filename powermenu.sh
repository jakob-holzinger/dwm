#!/bin/bash

choice=$(printf "Sperren\nAbmelden\nNeustarten\nHerunterfahren" | dmenu -i -p "System:")

case "$choice" in
  Lock) slock ;;
  Log Out) pkill -KILL -u "$USER" ;;
  Restart) systemctl reboot ;;
  Shutdown) systemctl poweroff ;;
esac
