if [ "$#" -ne 2 ]
	then
	echo "usage: " $0 "[product_name]"
	exit 1
fi

git clone https://github.com/waveshare/LCD-show.git

head -n -6 ./LCD-show/LCD35C-show > ./LCD-show/LCD32C-show-temp
chmod +x ./LCD-show/LCD32C-show-temp
./LCD-show/LCD32C-show-temp


cp ./config/capsuleFW /opt/capsuleFW/bin/capsuleFW

cp ./config/capsuleSetting.json /opt/capsuleFW/capsuleSetting.json
cp ./config/rc.local /etc/rc.local
cp ./config/autostart /etc/xdg/lxsession/LXDE-pi/autostart
cp ./config/sshd_config /etc/ssh/sshd_config
cp ./config/lightdm.conf /etc/lightdm/lightdm.conf
cp ./config/black_image.jpg /usr/share/rpd-wallpaper/black_image.jpg
cp ./config/cmdline.txt /boot/cmdline.txt
cp ./config/capsuleReactService /etc/init.d/capsuleReactService
cp ./config/capsuleDjangoService /etc/init.d/capsuleDjangoService
cp ./config/desktop-items-0.conf /home/pi/.config/pcmanfm/LXDE-pi/desktop-items-0.conf
cp ./config/desktop-items-1.conf /home/pi/.config/pcmanfm/LXDE-pi/desktop-items-1.conf
cp ./config/pcmanfm.conf /home/pi/.config/pcmanfm/LXDE-pi/pcmanfm.conf
cp ./config/LXDE-pi/desktop-items-0.conf /etc/xdg/pcmanfm/LXDE-pi/desktop-items-0.conf
cp ./config//LXDE-pi/desktop-items-1.conf /etc/xdg/pcmanfm/LXDE-pi/desktop-items-1.conf
cp ./config/LXDE-pi/pcmanfm.conf /etc/xdg/pcmanfm/LXDE-pi/pcmanfm.conf
cp ./config/C10.service /etc/avahi/services/C10.service
cp ./config/libstdc++.so.6.0.26 /usr/lib/arm-linux-gnueabihf/libstdc++.so.6
cp ./config/wpa_supplicant.conf /etc/wpa_supplicant/wpa_supplicant.conf

if [ "$1" == "C10"]; then
	cp ./config/C10/config.txt /boot/config.txt
	cp ./config/C10/99-calibration.conf /usr/share/X11/xorg.conf.d/99-calibration.conf
elif [ "$1" == "L10"]; then
	cp ./config/L10/config.txt /boot/config.txt
	cp ./config/L10/99-calibration.conf /usr/share/X11/xorg.conf.d/99-calibration.conf
else
	echo "no product " $1
fi
