#!/bin/bash

choice=$(printf "Lock\nLogOut\nRestart\nShutdown" | dmenu -i -p "System:")

case "$choice" in
  Lock) slock ;;
  LogOut) pkill -KILL -u "$USER" ;;
  Restart) systemctl reboot ;;
  Shutdown) systemctl poweroff ;;
esac
