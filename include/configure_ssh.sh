#!/bin/bash

[ $UID -ne 0 ] && echo 'user must be root' && exit 1

if [ ! -e /home/tsserver/.ssh ]
then
	mkdir /home/tsserver/.ssh
	chown tsserver:tsserver /home/tsserver/.ssh
fi

echo 'IdentityFile ~/.ssh/tech_telecomsante_rsa' > /home/tsserver/.ssh/config
echo '' >> /home/tsserver/.ssh/config
echo 'Host git.telecomsante.fr' >> /home/tsserver/.ssh/config
echo '	User git' >> /home/tsserver/.ssh/config
echo '	IdentityFile ~/.ssh/tech_telecomsante_rsa' >> /home/tsserver/.ssh/config
echo '' >> /home/tsserver/.ssh/config
echo 'Host 10.0.0.*' >> /home/tsserver/.ssh/config
echo '	user tsante' >> /home/tsserver/.ssh/config
echo '	IdentityFile ~/.ssh/tech_telecomsante_rsa' >> /home/tsserver/.ssh/config

chown tsserver:tsserver /home/tsserver/.ssh/config

cat /home/tsserver/.ssh/tech_telecomsante_rsa.pub > /home/tsserver/authorized_keys

chown tsserver:tsserver /home/tsserver/authorized_keys

sed -i '/.*ServerAliveInterval*/d' /etc/ssh/ssh_config
sed -i '/.*TCPKeepAlive*/d' /etc/ssh/ssh_config
sed -i '/.*StrictHostKeyChecking*/d' /etc/ssh/ssh_config
echo 'ServerAliveInterval 10' >> /etc/ssh/ssh_config
echo 'TCPKeepAlive yes' >> /etc/ssh/ssh_config
echo 'StrictHostKeyChecking no' >> /etc/ssh/ssh_config

sed -i '/.*PermitRootLogin*/d' /etc/ssh/sshd_config
sed -i '/.*PasswordAuthentication*/d' /etc/ssh/sshd_config
echo 'PermitRootLogin no' >> /etc/ssh/sshd_config
echo 'PasswordAuthentication no' >>/etc/ssh/sshd_config

sed -i '/.*user_allow_other*/d' /etc/fuse.conf
echo 'user_allow_other' >> /etc/fuse.conf
