// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Bitcoin Green developers
// Copyright (c) 2018 The XgamingUP developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
        (0, uint256("0x0000003acbcf97f39cdb4964f3d71262e6726f9f30355ff9c4443bcfa55e03b6"));
        (54200, uint256("0x79bcdaf228f1718536b8263c747aebd9d753570d10e11a7bd1f27e35f9281565"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1559206604, // * UNIX timestamp of last checkpoint block
    110783,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00000fc68d1d787940bf0039ade6c31b90f6ae80eb2eb2ff3ddb4f11678ecace"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1538474401,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00000c56b6c1ce252cdbca2946eb499023de10e05894224e1f4ccd045d3e4d14"));
	
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1538474402,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xb1;
        pchMessageStart[1] = 0x3a;
        pchMessageStart[2] = 0x2b;
        pchMessageStart[3] = 0xc4;
        vAlertPubKey = ParseHex("041F97DAE0C2570B67DCD62FCB20F422500C4DE2AAA0C5965D25BC144CEED5C403CFB18261514FD517DA098D3BC7E3638914F7B896A6ADF0839C886D375697136E");
        nDefaultPort = 17140;
        bnProofOfWorkLimit = ~uint256(0) >> 16;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // XgamingUP: 1 day
        nTargetSpacing = 1 * 60;  // XgamingUP: 1 minutes
        nMaturity = 155;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 20000000 * COIN;
		nStakeInputMinimal = 10 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 500;
        nModifierUpdateBlock = 1; // we use the version 2 for XGA
		
        const char* pszTimestamp = "The Bitcoin protocol does not care";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0442976F7200975E487B03E4C879DECCDB801A029F0551ED897BB0707ADB58EB6FE5CFF64EC9F60A70E0729DCBE5B6969D4EB584F69997D9AFDC1E6CB3A9BCAB4D") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1555920000;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 237311;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000003acbcf97f39cdb4964f3d71262e6726f9f30355ff9c4443bcfa55e03b6"));
        assert(genesis.hashMerkleRoot == uint256("0x2af901602794727aad2d46f89dca5b1097fe2ea66c2d4b926b8d6d90620a5732"));

        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("xgamingup.online", "dnsseed.xgamingup.online"));
        vSeeds.push_back(CDNSSeedData("seed1.xgamingup.online", "seed1.xgamingup.online"));
        vSeeds.push_back(CDNSSeedData("seed2.xgamingup.online", "seed2.xgamingup.online"));
        vSeeds.push_back(CDNSSeedData("seed3.xgamingup.online", "seed3.xgamingup.online"));
        vSeeds.push_back(CDNSSeedData("seed4.xgamingup.online", "seed4.xgamingup.online"));
        vSeeds.push_back(CDNSSeedData("seed5.xgamingup.online", "seed5.xgamingup.online"));
        vSeeds.push_back(CDNSSeedData("seed6.xgamingup.online", "seed6.xgamingup.online"));
        vSeeds.push_back(CDNSSeedData("seed7.xgamingup.online", "seed7.xgamingup.online"));
        vSeeds.push_back(CDNSSeedData("seed8.xgamingup.online", "seed8.xgamingup.online"));
        vSeeds.push_back(CDNSSeedData("seed9.xgamingup.online", "seed9.xgamingup.online"));

        // XgamingUP addresses start with 'X'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 75);
        // XgamingUP script addresses start with '3'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 4);
        // XgamingUP private keys start with 'G'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 38);
        // XgamingUP BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // XgamingUP BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04F1C02AC30661551FDD3A2A065B54E3CB2B33762ACBFD03866FE2FF18E5778FDFF1F0518CD309A2DCF8C7FF1BC9426A1F0D9550FE6FC041DBD63A68E7077211E3";
        strMasternodePoolDummyAddress = "XSnKjocNbo5FniBjoripCtZ85pP8sEGg4h";
        nStartMasternodePayments = genesis.nTime + 14400; // 4 hours after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x1c;
        pchMessageStart[1] = 0x2a;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0x02;
        vAlertPubKey = ParseHex("04FA13D2BBBC1DD6AA0FBA147ADFFA94F389B98A5ABD8A554BE1556FDF6FF457C6A77241B95F6E4B6206971805E97968A6F90936A869406D09D09F77BD4265AB6B");
        nDefaultPort = 18140;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 60; // XgamingUP: 1 day
        nTargetSpacing = 1 * 60;  // XgamingUP: 1 minute
        nLastPOWBlock = 2000;
        nMaturity = 55;
        nMasternodeCountDrift = 3;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 20000000 * COIN;
		nStakeInputMinimal = 10 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1555920001;
        genesis.nNonce = 1139226;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000fc68d1d787940bf0039ade6c31b90f6ae80eb2eb2ff3ddb4f11678ecace"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet XgamingUP addresses start with 'a'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        // Testnet XgamingUP script addresses start with '8'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        // Testnet private keys start with 'a'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 83);
        // Testnet XgamingUP BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet XgamingUP BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet XgamingUP BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04A26A326715D2CF607AB32A6340D1F54D9EBCD4E2CB05286881987C93ADCF7CFA2582BF164CEB9B0051D627845CAB6562DCF64520EF31CB1214154B8B677CA05A";
        strMasternodePoolDummyAddress = "xSnKjocNbo5FniBjoripCtZ85pP8sEGg4h";
        nStartMasternodePayments = genesis.nTime + 14400; // 4 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0x02;
        pchMessageStart[2] = 0xc1;
        pchMessageStart[3] = 0xd3;
        nSubsidyHalvingInterval = 1500;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // XgamingUP: 1 day
        nTargetSpacing = 1 * 60;        // XgamingUP: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1555920002;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 228719;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19110;
		nStakeInputMinimal = 10 * COIN;
        assert(hashGenesisBlock == uint256("0x00000c56b6c1ce252cdbca2946eb499023de10e05894224e1f4ccd045d3e4d14"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 20110;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
