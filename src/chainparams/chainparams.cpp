// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2014-2015 Dash Developers
// Copyright (c) 2017-2018 The Stipend developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"
#include "chainparams.h"
#include "main/main.h"

#include "misc/util.h"
#include "misc/base58.h"
#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//
// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// Hardcoded seeds.
static void getHardcodedSeeds(std::vector<CAddress> &vSeedsOut)
{
    std::vector<std::string> ips;
    ips.push_back("seed2.spectresecurity.io");
    ips.push_back("seed3.spectresecurity.io");
    ips.push_back("seed4.spectresecurity.io");
    ips.push_back("seed1.spectresecurity.io");

    const int64_t oneWeek = 7 * 24 * 60 * 60;
    for (size_t i = 0; i < ips.size(); ++i)
    {
        CAddress addr(CService(ips[i], 46978));
        addr.nTime = GetTime() - GetRand(oneWeek) - oneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
	pchMessageStart[0] = 0xe5;
	pchMessageStart[1] = 0x5a;
	pchMessageStart[2] = 0xc4;
        pchMessageStart[3] = 0x54;
        vAlertPubKey = ParseHex("7501131e64effceb1644efc56ed3594ef64425850aa52617506177cf245575f0aa11e5b1777cfd8621ea39a7996872a07631ea25b3fdda00df37f5e982fe58850a");
        nDefaultPort = 13338;
        nRPCPort = 13337;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16); // starting difficulty is 1 / 2^12

        const char* pszTimestamp = "Get Up And Work";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();

	// original 1516154401
        CTransaction txNew(1, 1533231882, vin, vout, 0);

        LogPrintf("genesis mainnet transaction:  %s\n", txNew.ToString().c_str());

        genesis.vtx.push_back(txNew);

        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1533231882; // Wednesday, 17-Jan-18 02:00:01 UTC
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 85996;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000085b1b62409321db3b40d0e3b56ff0c018a6ad213973934c6c2973bacefc7"));
        assert(genesis.hashMerkleRoot == uint256("0x7496ba2ae6f0ecf42ea5978d7ce4fb47b3115530958fc3bce552064fcc4a6b81"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63); // S
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,21);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,23);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,41);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x99)(0x75)(0x45)(0xE2).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x99)(0x73)(0x43)(0xE3).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("1",  "seed2.spectresecurity.io"));
        vSeeds.push_back(CDNSSeedData("2",  "seed3.spectresecurity.io"));
        vSeeds.push_back(CDNSSeedData("3",  "seed4.spectresecurity.io"));
        vSeeds.push_back(CDNSSeedData("4",  "seed1.spectresecurity.io"));


	convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        getHardcodedSeeds(vFixedSeeds);

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "SFoQDUrp63QWqFhjEr3Fmc4ubHRhyzjKUC";

        nLastPOWBlock = 250000;
        nPOSStartBlock = 500;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc4;
        pchMessageStart[1] = 0xd5;
        pchMessageStart[2] = 0xa6;
        pchMessageStart[3] = 0xb8;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
       // vAlertPubKey = ParseHex("7501131e15af76eb1d0e4a656ed3594ef64425850aa52617506177cf245575f0aa11e5b1777cfd8621ea39a7996872a07631ea25b3fdda00df37f5e982fe58850a");
        nDefaultPort = 59432;
        nRPCPort = 59433;
        strDataDir = "testnet";
        genesis.nTime    = 1518016375;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 435534;
        hashGenesisBlock = uint256("0x01");

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x0000db7a0ad742470a4380145305fb364134d221b41f7bcf7f82a45722b30104"));
        assert(genesis.hashMerkleRoot == uint256("0x7496ba2ae6f0ecf42ea5978d7ce4fb47b3115530958fc3bce552064fcc4a6b81"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,85); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,25);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,43);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x98)(0x74)(0x44)(0xE1).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x98)(0x72)(0x42)(0xE2).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 210000;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
