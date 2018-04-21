MASTERNODE BUILD NOTES
======================
Some notes on how to build a Kreds Masternode in Ubuntu server. Using Windows Qt Client to configure.


System requirements
--------------------
On Ubuntu TLS 64bit server is recommended with at least 512MB 
of memory and 15GB space available when running a Masternode.


Notes
-----
You need exactly 200000 KREDS to run a Masternode. Masternode input must have at least 15 confirmations.
Building a new wallet.dat is also recommended (a seperate .conf is needed). Masternode earnings are
going to this wallet.dat and address. Send only newly earned coins away and pay attention for transaction fees.
To fix a broken accountaddress 0 (possible when sending huge amounts of coins away), do a self TX of 200000 KREDS.


Start
-----
Open your Windows Kreds-Qt Client and open the debug console.

	masternode genkey
	copy the generated code to a text file
	---
	getaccountaddress 0
	copy the generated address to a text file
	---
	encryptwallet "strong password"
	Send 200000 KREDS to "address 0"

Build Instructions: Ubuntu & Debian
-----------------------------------

	$ adduser <NEW USER>
	$ passwd <PSW>
	$ gpasswd -a <NEW USER> sudo
	---
	$ sudo apt-get install build-essential
	$ sudo apt-get install libtool autotools-dev autoconf automake libssl-dev libevent-dev
	$ sudo apt-get install libboost1.54-all-dev
	$ sudo add-apt-repository ppa:bitcoin/bitcoin
	$ sudo apt-get install libdb4.8-dev libdb4.8++-dev
	$ sudo apt-get install miniupnpc*-dev
	$ sudo apt-get install git ntp make g++ gcc autoconf cpp ngrep iftop sysstat unzip
	$ sudo update-rc.d ntp enable
	$ sudo apt-get update
	$ sudo apt-get upgrade
	---
	optiopnal linux gui: $ sudo apt-get install lubuntu-desktop
	---
	optional, if problems with boost version: 
	$ sudo apt-get remove libboost*
	$ sudo apt-get purge libboost*
	$ sudo apt-get install libboost-all-dev


	Swapfile:
	---------
	$ sudo dd if=/dev/zero of=/swapfile bs=2M count=1024
	$ sudo mkswap /swapfile
	$ sudo swapon /swapfile

	
	FireWall:
	---------
	$ sudo apt-get install ufw
	$ sudo ufw allow ssh/tcp
	$ sudo ufw limit ssh/tcp
	$ sudo ufw allow 3950/tcp
	$ sudo ufw logging on
	$ sudo ufw enable
	$ sudo ufw status


	Install Kreds
	------------
	mkdir .kreds
	cd .kreds
	wget https://github.com/KredsBlockchain/kreds-core/releases/download/v1.0.0.4/kreds-linux64-v1.0.0.4.tar.xz
	tar xf kreds-linux64-v1.0.0.4.tar.xz
	
	$ sudo cp kredsd /usr/bin
	$ sudo chmod 775 /usr/bin/kredsd

	
	Create a kreds.conf in nano
	-------------------------------
	cd .kreds
	nano
	---
	rpcuser=<anything>
	rpcpassword=<anything>
	rpcallowip=127.0.0.1
	maxconnections=256
	listen=1
	server=1
	daemon=1
	masternode=1
	masternodeprivkey=XXXXXX
	externalip=xxx.xxx.xxx.xxx:3950
	---
	save nano: Ctrl +  O
	exit nano: Ctrl +  X
	cd


	Create CRON
	-----------
	cd /etc/cron.d
	crontab -e
	2 (for nano)
	
	at bottom of newly created file, insert:
	---
	@reboot /usr/bin/kredsd -shrinkdebugfile    [to start masternode  (or wherever you keep your daemon)]
	*/20 * * * * /usr/bin/kredsd
	---
	save nano: Ctrl +  O
	exit nano: Ctrl +  X
	cd
	
	
	Manually start kredsd
	-------------------------
	cd .kreds
	./kredsd	
	
	
	limcoinxd commands
	------------------
	./kredsd getinfo
	./kredsd masternode list
	./kredsd masternode debug
	./kredsd masternode stop
	./kredsd help
	
	
	Start Mining
	----------------------
	./kreds.cli setgenerate true
	./kreds.cli gethashespersec
	

Windows Kreds-Qt Client configuration 
-----------------------------------------
(if using a seperate wallet.dat, a seperate kreds.conf is needed)

	---
	go to kreds.conf in %appdata%
	
	---
	rpcuser=<anything>
	rpcpassword=<anything>
	maxconnections=256
	masternode=1
	masternodeprivkey=XXXXXXXXXXXXXXXXXX
	masternodeaddr=xxx.xxx.xxx.xxx:3950
	---

	
	Windows Kreds-Qt Client console
	-----------------------------------
	masternode start <PSW>

	
	Windows Kreds-Qt Client console commands
	--------------------------------------------
	masternode list    	 <<find your MN IP
	masternode debug
	masternode stop
	getinfo
	help
