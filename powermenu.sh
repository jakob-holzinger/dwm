#!/bin/bash

choice=$(printf "Lock\nLogOut\nSuspend\nRestart\nShutdown" | dmenu -i -p "System:")

case "$choice" in
  Lock) slock ;;
  LogOut) pkill -KILL -u "$USER" ;;
  Suspend) systemctl suspend ;;
  Restart) systemctl reboot ;;
  Shutdown) systemctl poweroff ;;
esac
