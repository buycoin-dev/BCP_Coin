// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

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

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x40;
        pchMessageStart[1] = 0xfb;
        pchMessageStart[2] = 0xa7;
        pchMessageStart[3] = 0xd4;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 9037;
        nRPCPort = 9038;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //genesis.nTime = 1508461261
        //genesis.nNonce = 88632
        //genesis.nVersion = 1
        //genesis.GetHash = 00000762d57623d4801bbfba5d951550caca5f7f23cc684c124f702f8441703f
        //genesis.hashMerkleRoot = c8160e0606a8b63ef4735f35814544502c2bdf61878853898059654ca4fe53b6


        const char* pszTimestamp = "2017, November 18, BuyCoin POS Based make for swap";
        CTransaction txNew;
        txNew.nTime = 1508461261;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1508461261;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 88632;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000762d57623d4801bbfba5d951550caca5f7f23cc684c124f702f8441703f"));
        assert(genesis.hashMerkleRoot == uint256("0xc8160e0606a8b63ef4735f35814544502c2bdf61878853898059654ca4fe53b6"));

        vSeeds.push_back(CDNSSeedData("nodea.buy-coin.me", "nodea.buy-coin.me"));
        vSeeds.push_back(CDNSSeedData("nodeb.buy-coin.me", "nodeb.buy-coin.me"));
        vSeeds.push_back(CDNSSeedData("nodec.buy-coin.me", "nodec.buy-coin.me"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(26);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(55);
        base58Prefixes[SECRET_KEY] =     list_of(191);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x68)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x58)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
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
        //genesis.nTime = 1508256000
        //genesis.nNonce = 7811
        //genesis.nVersion = 1
        //genesis.hashMerkleRoot = c8160e0606a8b63ef4735f35814544502c2bdf61878853898059654ca4fe53b6
        //genesis.GetHash = 0000c10df3830440cae780ba8854c3d3eb3c4c5ae2b301588ae8e48dce83768a



        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xf7;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0x0c;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("");
        nDefaultPort = 19037;
        nRPCPort = 19038;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 7811;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000c10df3830440cae780ba8854c3d3eb3c4c5ae2b301588ae8e48dce83768a"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//genesis.nTime = 1508298000
//genesis.nNonce = 0
//genesis.nVersion = 1
//genesis.hashMerkleRoot = c8160e0606a8b63ef4735f35814544502c2bdf61878853898059654ca4fe53b6
//genesis.GetHash = 00b48e118decd60d250bafae6c2972f5fbfc3ef9596d97ea8447f22205c7ec0c



class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xac;
        pchMessageStart[2] = 0xbd;
        pchMessageStart[3] = 0xcd;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 0;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 4;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19444;
        strDataDir = "regtest";

        assert(hashGenesisBlock == uint256("0x00b48e118decd60d250bafae6c2972f5fbfc3ef9596d97ea8447f22205c7ec0c"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

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
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
