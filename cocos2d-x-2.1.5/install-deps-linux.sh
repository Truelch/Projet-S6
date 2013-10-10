#!/bin/bash

if lsb_release -d | grep -qi 'arch'
then
	DEPENDS='gcc'
	DEPENDS+=' libx11'
	DEPENDS+=' libxmu'
	DEPENDS+=' glu'
	DEPENDS+=' libxi'
	DEPENDS+=' glfw'
	DEPENDS+=' libzip'
	DEPENDS+=' curl'
	DEPENDS+=' fontconfig'
	DEPENDS+=' sqlite'
	DEPENDS+=' glew'
else
	DEPENDS='libx11-dev'
	DEPENDS+=' libxmu-dev'
	DEPENDS+=' libglu1-mesa-dev'
	DEPENDS+=' libgl2ps-dev'
	DEPENDS+=' libxi-dev'
	DEPENDS+=' libglfw-dev'
	DEPENDS+=' g++'
	DEPENDS+=' libzip-dev'
	DEPENDS+=' libcurl4-gnutls-dev'
	DEPENDS+=' libfontconfig1-dev'
	DEPENDS+=' libsqlite3-dev'
	DEPENDS+=' libglew-dev'
fi

MISSING=
echo "Checking for missing packages ..."
for i in $DEPENDS; do
	if lsb_release -d | grep -qi 'arch'
	then
		if ! pacman -Q $i > /dev/null; then
			MISSING+="$i "
		fi
	else
		if ! dpkg-query -W --showformat='${Status}\n' $i | grep "install ok installed" > /dev/null; then
			MISSING+="$i "
		fi
	fi
done

if [ -n "$MISSING" ]; then
    TXTCOLOR_DEFAULT="\033[0;m"
    TXTCOLOR_GREEN="\033[0;32m"
    echo -e $TXTCOLOR_GREEN"Missing packages: $MISSING.\nYou may be asked for your password for package installation."$TXTCOLOR_DEFAULT
	if lsb_release -d | grep -qi 'arch'
	then
		sudo pacman -S $MISSING --noconfirm
	else
		sudo apt-get --force-yes --yes install $MISSING
	fi
fi

