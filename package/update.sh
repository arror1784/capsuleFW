#!/bin/bash

TARGET_FOLDER="./targets"

TARGET_IP=""
TARGET_PASSWD=""

SERVICES=(
"daphne.service"
"react.service"
)

ROOT_UPDATE_TARGET=(
"capsuleFW"
"capsuleSetting.json"
"rc.local"
"autostart"
"sshd_config"
"lightdm.conf"
"black_image.jpg"
"daphne.service"
"react.service"
)
ROOT_UPDATE_PATH=(
"/opt/capsuleFW/bin/capsuleFW"
"/opt/capsuleFW/capsuleSetting.json"
"/etc/rc.local"
"/etc/xdg/lxsession/LXDE-pi/autostart"
"/etc/ssh/sshd_config"
"/etc/lightdm/lightdm.conf"
"/usr/share/rpd-wallpaper/black_image.jpg"
"/etc/systemd/system/daphne.service"
"/etc/systemd/system/react.service"
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

SSHPASS="sshpass -p ${TARGET_PASSWD}"

SSH_COMMAND_PI="${SSHPASS} ssh pi@${TARGET_IP}"
SSH_COMMAND_ROOT="${SSHPASS} ssh root@${TARGET_IP}"

#capsuleFW process kill

for (( i = 0 ; i < ${#ROOT_UPDATE_TARGET[@]} ; i++ )) ; do
	echo ${ROOT_UPDATE_TARGET[$i]} ${ROOT_UPDATE_PATH[$i]}
	cp ${TARGET_FOLDER}/${ROOT_UPDATE_TARGET[$i]} ${ROOT_UPDATE_PATH[$i]}
done

for (( i = 0 ; i < ${#PI_UPDATE_TARGET[@]} ; i++ )) ; do
	echo ${PI_UPDATE_TARGET[$i]} ${PI_UPDATE_PATH[$i]}
	cp ${TARGET_FOLDER}/${PI_UPDATE_TARGET[$i]} pi@${TARGET_IP}:${PI_UPDATE_PATH[$i]}
done

#${SSH_COMMAND_ROOT} mkdir /opt/capsuleFW_react/ 2>&1 > /dev/null
rm -rf /opt/capsuleFW_react
cp -r ./capsuleFW_react /opt/

for (( i = 0 ; i < ${#SERVICES[@]} ; i++ )) ; do
	chmod 755 /etc/init.d/${SERVICES[$i]}
	#${SSHPASS} ssh pi@${TARGET_IP} sudo update-rc.d ${SERVICES[$i]} defaults
	
	systemctl enable ${SERVICES[$i]}
	systemctl start ${SERVICES[$i]}

done

#frontend
#yarn installed
0
if type yarn 2> /dev/null; then
	echo "yarn installed"
else
	echo "yarn install"
	curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | apt-key add -
	echo \"deb https://dl.yarnpkg.com/debian/ stable main\" | tee /etc/apt/sources.list.d/yarn.list

	apt-get update -y
	apt-get install yarn -y

	yarn global add serve
fi

#backend
if ${SSH_COMMAND_PI} type redis-server 2> /dev/null; then
	echo "redis-server installed"
else
	echo "redis-server install"
	${SSH_COMMAND_PI} "sudo apt-get install redis-server -y"
fi
pip3 install -r /opt/capsuleFW_react/backend/requirements.txt

python3 /opt/capsuleFW_react/backend/manage.py makemigrations
python3 /opt/capsuleFW_react/backend/manage.py migrate

echo "Finish"

pkill capsuleFW


