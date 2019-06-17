# The SpectreSecurityCoin

We introduce you a new cryptocoin called SpectreSecurityCoin.
SpectreSecurityCoin is a safe, anonymous, fast and highly profitable coin with Masternodes and advanced reward system with Long-Term Development & Support.
Welcome to the future!

## Main Features:

*	ASIC Resistance
*	NiceHash Resistance
*	Nvidia & AMD GPU Mining
*	Instamine Protection
*	Wallet Built-in Block Explorer
*	Masternode Reward Protection
*	Friendly Masternode Setup
*	Long-Term Development & Support

### Headless ( Server ) Installation. This is for shops, exchanges, application, and programmers.
Make sure you have install Ubuntu 16.04 x64. The wallet will not build with Ubuntu 18.04 Bionic Beaver.
From console type the following commands as root or with sudo.

*	apt-get update
*	apt -y install software-properties-common
*	apt-add-repository -y ppa:bitcoin/bitcoin
*	apt-get update
*	apt install -y make build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils libgmp-dev libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev libboost-all-dev  software-properties-common libdb4.8-dev libdb4.8++-dev libminiupnpc-dev libzmq3-dev ufw pkg-config libevent-dev libdb5.3++ unzip libzmq5

Once the software is built please use the strip command to remove debugging symbols

*	strip SpectreSecurityCoind

### Masternode Information
*	Please use script : https://github.com/SpectreSecurityCoin/SpectreSecurityCoinMNInstaller

### Troubleshooting 
Here are some simple steps to help you troubleshoot connections issues

*	shut off wallet and remove all blochain folder but wallet.dat and conf
*	get binary from https://github.com/SpectreSecurityCoin/SpectreSecurityCoin/releases/download/v1.0.1.7-1/SpectreSecurityCoind-Linux.zip or build source
*	only have rpcuser and rpc password in conf along with rpcport=13337 and port=13338 and rpcallowip=127.0.0.1
*	start wallet with .SpectreSecurityCoind -server -daemon -listen and tail debug file. Does it sync with chain. if not proceed
*	stop wallet and add to conf addnode=seed1.spectresecurity.io:13338 and add maxconnections=1
*	start wallet with .SpectreSecurityCoind -server -daemon -listen and tail debug file. Does it sync with chain. if not proceed
*	stop wallet, remove all but wallet.dat and conf and use the block chain from https://bootstrap.spectresecurity.io/boot_strap.zip ( this will contain peer.dat file, try with it first, in error remove this file. )
*	start wallet with .SpectreSecurityCoind -server -daemon -listen and tail debug file. Does it sync with chain?

###### License

SpectreSecurityCoin is released under the terms of the MIT license. See COPYING for more information or see http://opensource.org/licenses/MIT.
