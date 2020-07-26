#!/bin/bash

SERVICES=(
"daphne.service"
"react.service"
)

ROOT_UPDATE_TARGET=(
"capsuleFW"
)
ROOT_UPDATE_PATH=(
"/opt/capsuleFW/bin/capsuleFW"
)

if [ $# -eq 0 ]; then
    echo "usage : %s [files] [dir] [version]" $0
    exit 0
fi
TARGET_FILE_NAME=$1
TARGET_FOLDER_NAME=${TARGET_FILE_NAME%%.*}

unzip -o $TARGET_FILE_NAME -d $2

for (( i = 0 ; i < ${#SERVICES[@]} ; i++ )) ; do
	systemctl stop ${SERVICES[$i]}
done


rm -r /opt/capsuleFW/version.json
cp -rf $3 /opt/capsuleFW/

rm -r /opt/capsuleFW_react
cp -rf ${TARGET_FOLDER_NAME}/capsuleFW_react /opt/
echo "${TARGET_FOLDER_NAME}/capsuleFW_react"

#frontend
#yarn installed
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
if type redis-server 2> /dev/null; then
	echo "redis-server installed"
else
	echo "redis-server install"
	apt-get install redis-server -y
fi
pip3 install -r /opt/capsuleFW_react/backend/requirements.txt

python3 /opt/capsuleFW_react/backend/manage.py makemigrations
python3 /opt/capsuleFW_react/backend/manage.py migrate

pkill capsuleFW

rm -rf /opt/capsuleFW/bin/capsuleFW
cp -rf ${TARGET_FOLDER_NAME}/capsuleFW /opt/capsuleFW/bin/capsuleFW
chmod 755 /opt/capsuleFW/bin/capsuleFW

for (( i = 0 ; i < ${#SERVICES[@]} ; i++ )) ; do
	systemctl enable ${SERVICES[$i]}
	systemctl start ${SERVICES[$i]}
done

chmod +x ${TARGET_FOLDER_NAME}/HGCommandSender
${TARGET_FOLDER_NAME}/HGCommandSender "H201"

shutdown -h now
