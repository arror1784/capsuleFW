#!/bin/bash

TARGET_FOLDER="./targets"

TARGET_IP=""
TARGET_PASSWD=""

ROOT_UPDATE_TARGET=(
"capsuleFW"
"capsuleSetting.json"
"rc.local"
"autostart"
"sshd_config"
"lightdm.conf"
"black_image.jpg"
)
ROOT_UPDATE_PATH=(
"/opt/capsuleFW/bin/capsuleFW"
"/opt/capsuleFW/capsuleSetting.json"
"/etc/rc.local"
"/etc/xdg/lxsession/LXDE-pi/autostart"
"/etc/ssh/sshd_config"
"/etc/lightdm/lightdm.conf"
"/usr/share/rpd-wallpaper/black_image.jpg"
)

PI_UPDATE_TARGET=(
"desktop-items-0.conf"
"desktop-items-1.conf"
)

PI_UPDATE_PATH=(
"/home/pi/.config/pcmanfm/LXDE-pi/desktop-items-0.conf"
"/home/pi/.config/pcmanfm/LXDE-pi/desktop-items-1.conf"
)

if [ $# -eq 0 ]; then
	echo "usage : %s [address] [passwd]" $0
	exit 0
fi

TARGET_IP=$1
TARGET_PASSWD=$2

for (( i = 0 ; i < ${#ROOT_UPDATE_TARGET[@]} ; i++ )) ; do
	echo ${ROOT_UPDATE_TARGET[$i]} ${ROOT_UPDATE_PATH[$i]}
	sshpass -p "${TARGET_PASSWD}" scp ${TARGET_FOLDER}/${ROOT_UPDATE_TARGET[$i]} root@${TARGET_IP}:${ROOT_UPDATE_PATH[$i]}
done

for (( i = 0 ; i < ${#PI_UPDATE_TARGET[@]} ; i++ )) ; do
	echo ${PI_UPDATE_TARGET[$i]} ${PI_UPDATE_PATH[$i]}
	sshpass -p "${TARGET_PASSWD}" scp ${TARGET_FOLDER}/${PI_UPDATE_TARGET[$i]} pi@${TARGET_IP}:${PI_UPDATE_PATH[$i]}
done

echo "Finish"
