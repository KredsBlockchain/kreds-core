Start Ubuntu 14.04 Image connect via Putty
----------------
apt-get update

apt-get dist-upgrade


Setup Swapfile
----------------
dd if=/dev/zero of=/mnt/myswap.swap bs=1M count=1000

mkswap /mnt/myswap.swap

swapon /mnt/myswap.swap

Cron Swapfile
----------------
nano /etc/fstab
/mnt/myswap.swap none swap sw 0 0

Install Addons :
----------------
apt-get install build-essential libtool autotools-dev autoconf pkg-config libssl-dev

apt-get install libboost-all-dev git npm nodejs nodejs-legacy libminiupnpc-dev redis-server libevent-dev

add-apt-repository ppa:bitcoin/bitcoin

apt-get update

apt-get install libdb4.8-dev libdb4.8++-dev


Install Kreds:
----------------
cd

git clone https://github.com/KredsBlockchain/kreds-core.git

cd kreds-core/


./autogen.sh

./configure

make


cd ~/.kreds/

nano kreds.conf

Edit Config :


rpcuser=USERNAME

rpcpassword=PASS

rpcallowip=127.0.0.1

rpcport=3950

daemon=1

server=1


cd ~/kreds-core/src/

./kredsd

Afer some time you can check your connection with
./kreds-cli getinfo 

Output should look like :

{    "version" : 1000000,  
    "protocolversion" : 70083,    
    "walletversion" : 130000,    
    "balance" : 5985.07007229,    
    "blocks" : 284984,    
    "timeoffset" : 0,    
    "connections" : 7,    
    "proxy" : "",    
    "difficulty" : 1.81900189,    
    "testnet" : false,    
    "keypoololdest" : 1488996130,    
    "keypoolsize" : 1001,    
    "paytxfee" : 0.00000000,    
    "relayfee" : 0.00005000,    
    "errors" : ""    }

