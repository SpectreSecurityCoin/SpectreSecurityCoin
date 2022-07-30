// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main/main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
	static MapCheckpoints mapCheckpoints =
			boost::assign::map_list_of
			(0,           Params().HashGenesisBlock() )
            (2000, uint256("0xe51b4a048676b0cb3727ad2d510a6260783813c78b5e0a372639e28cdba64227"))
            (4000, uint256("0x25ca15500c2d0dc38a9e01effcbcd357dd50f44a1ad3d6c6ca624a90a031749e"))
            (8000, uint256("0xbef28d00194fce3286e6460adbdf8719bb342cfb454c4869335a8f8efff24008"))
            (12000, uint256("0x7044341b277aa6ec3dcb272fc40bb9e024f966b583ecf82d3dcc7b0ed9832786"))
            (16000, uint256("0x9ecaaabc4b2fdfadd290595481e42318178ff1c4d39843fa4a34d58b464be530"))
            (24000, uint256("0x7a853d8e30cb25b1481f919d03a752299455d9666aab73f6e777ca52097c3a4c"))
            (32000, uint256("0x499ff6221c42bf1eef57bce709bb6588adb9593449719c7fa80a07088349e71a"))
            (48000, uint256("0x43bc18363fa169d5afda20d0dc8b3e5b9dfc4964f175b23b07deab47468109fd"))
            (64000, uint256("0x725bf8cfdb52b934251794901a9cd700bbc7ab84a97af2ef72c7d7cb9be9e109"))
            (96000, uint256("0x50d06254990319d9339448d52df2aa5b7505c4b486f6c2c0e2a1387184fcf805"))
            (128000, uint256("0x655badd6316ed3921481f9c5df43630fba87de91b897227b7b6bbe0c31ba528d"))
            (148000, uint256("0x5c03950779fedcb4fa76bef0322ab7b0b5c5bf6f427fdb60ba9c6f5802a3e8e4"))
            (157000, uint256("0x0d00349d826054724e97876a55206c44a587c60d93dbe3a9467aa402ca18d5de"))
			(385752, uint256("0x68e2678165ee580367f458df378dc891a2b10089a97ad093a828f3f2c18929f2"))
			(481240, uint256("0xb9042c144bd9d970a0af82e14215a5d48b3824f99bc63ff4ec2b0a99e9975f23"))
			(521240, uint256("0x01c1b30a927468a5d9a80e804a0d1cf4d8968d7d7272cd325a5daefb3795270a"))
			(581247, uint256("0xd86b47979ba896cfe803c7f0249ee00b8f9ac2b98cd267661ab11e8410dcebe0"))
		;


    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
