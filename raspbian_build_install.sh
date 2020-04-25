#!/bin/bash

# 1 Download the last raspbian version 4.19 Raspbian Buster with Desktop
echo 'The procedure to install Raspbian on your sd card (4Go minimum) for Raspberry PI'
echo 'Downloading last Raspbian Buster Version'
echo ' $ wget https://downloads.raspberrypi.org/raspbian_latest'

#2 Decompress the archive with unzip
echo '$ Unzip Raspbian Buster'
echo '$ unzip *.zip'

#3 Download Etcher wich can enable an SD card to boot on Raspbian
echo '$ wget https://github.com/balena-io/etcher/releases/download/v1.5.80/balena-etcher-electron-1.5.80-linux-ia32.zip'
echo '$ unzip balena*.zip'
echo '$ cd balena-etcher-electron-1.5.80-linux-x64/'
echo './balenaEtcher-1.5.80-x64.AppImage'
echo 'From the balenaEtcher App: ...'
echo 'Click on select image and choose ../2020-02-13-raspbian-buster/2020-02-13-raspbian-buster.img'
echo 'Click on Flash!'
echo 'Enter your superuser password'


echo '#####################################################'
#4 Boot on Raspbian and configure it
echo 'When finished, you can unplug your SD card and put it in RPI and power on the RPI, plug a keyboard and mouse, HDMI cable'
echo 'The system should start'
echo 'You have to configure it thanks to the graphical interface : Country, Language,Timezone, mdp gucos, selecting the network'
echo 'To finish, set up your internet connection by connecting you on your wifi network from the rpi'
