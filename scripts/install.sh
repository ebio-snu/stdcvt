#!/bin/bash

TARGET_DIR="/home/pi/stdcvt"
LOG_DIR="/var/log/stdcvt"

update-rc.d -f stdcvt remove
rm /etc/init.d/stdcvt
ln -s "$TARGET_DIR/scripts/stdcvt" /etc/init.d/stdcvt
update-rc.d stdcvt defaults

mkdir $LOG_DIR
