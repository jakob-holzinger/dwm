#!/bin/bash

choice=$(printf "Sperren\nAbmelden\nNeustarten\nHerunterfahren" | dmenu -i -p "System:")

case "$choice" in
  Sperren) slock ;;
  Abmelden) pkill -KILL -u "$USER" ;;
  Neustarten) systemctl reboot ;;
  Herunterfahren) systemctl poweroff ;;
esac
