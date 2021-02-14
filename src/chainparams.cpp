// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
//Copyright (c) 2015-2020 The PIVX developers
//Copyright (c) 2020 The remita developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**



*/
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Biden ends deadlock over WTO leadership";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256S("000006a6a033adca8f3beaaedcae5f47c0f83b581c3dea6ec1d55521ebb5e01a"))/*
	(1000, uint256S("0x0000006b43065fdf445f07adca57fe5fd888902cb79c16fa48302cf1c0ab88ce"))
	(10000, uint256S("0xa2fd284213d913463d827c166ed0220b30de857794956b9dfbaaa5395891ef32"))
	(20000, uint256S("0x85acbdc4e8b609ddb3584c15f94248cc08d85c337736c12422f3e84a5bc51c4a"))*/;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1611351525, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256S("0x001"))
 ;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1610066000,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1610068000,
    0,
    100};


class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
/*
MAINNET block.nTime = 1610064000 
MAINNET block.nNonce = 1253332 
MAINNET block.GetHash = 000004b05215ad8b625ed097e62f0217cfb08c55d2370bb9f0a2745404a04c78
MAINNET block.hashMerkleRoot: 8f33220d9d6f05654bedc9e1a8c048ac234574622f54ad66f590036e45a206bc
*/        
        /*
        genesis = CreateGenesisBlock(1612566114, 478393, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
	    assert(consensus.hashGenesisBlock == uint256S("00000ed3b76741660190becc95ccffc17153a79af07b83097381414cc76d2681"));
        assert(genesis.hashMerkleRoot == uint256S("053593077ec4f021af2d3bb584529e87a1af2f8f671f8b7b767d2b99d2294ebd"));
        */
        /*
        const char* pszTimestamp = "Biden ends deadlock over WTO leadership";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0.00000050 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
        genesis.nVersion = 1;
        genesis.nTime = 1612728100;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 373036;*/

        genesis = CreateGenesisBlock(1612728100, 373036, 0x1e0ffff0, 1, 0.00000050 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256("000006a6a033adca8f3beaaedcae5f47c0f83b581c3dea6ec1d55521ebb5e01a"));
        assert(genesis.hashMerkleRoot == uint256("270c88942105e6734b0199ac9ac4cbd039816b39169c0db782cb6433d82fa123"));
 
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // remita starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 90;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 210000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.devAddress = "RJXje3mkVFFAaYa9h4gbPXhFSXei6Bi5Nu";
				
        // spork keys
        consensus.strSporkPubKey = "04784f46e422983f2019d6cf315c44288058f990f24bab9d9e014b011c796a3ff4124baa4fc60038f6917f5ebe15a2bf5f96d4c2762da2b080d4997b07da4abdec";
        consensus.strSporkPubKeyOld = "0403932c276751b17a83e2af9fb14b97838fcb297768ed185e3a11746bd5e4c20f1078f6b0f9b531c7807b3a7d6f38b8380f85bdbd5ee5bbc8d7681ded872b830f";
        consensus.nTime_EnforceNewSporkKey = 1610064000; // 01/08/2021 @ 12:00am (UTC)
        consensus.nTime_RejectOldSporkKey = 1610060000; // 01/08/2021 @ 12:00am (UTC)

        // height-based activations
        consensus.height_last_PoW = 1000;
        consensus.height_start_BIP65 = 1003;
        consensus.height_start_MessSignaturesV2 = 1030;  // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 1;
        consensus.height_start_StakeModifierV2 = 1001;
        consensus.height_start_TimeProtoV2 = 1030;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_PURPLE_FENIX].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xe4;
        pchMessageStart[1] = 0x82;
        pchMessageStart[2] = 0x3b;
        pchMessageStart[3] = 0x5f;
        nDefaultPort = 8351;

        vSeeds.push_back(CDNSSeedData("45.63.2.245", "45.63.2.245"));
        vSeeds.push_back(CDNSSeedData("207.246.94.60", "207.246.94.60"));
        vSeeds.push_back(CDNSSeedData("45.77.151.81", "45.77.151.81"));
        vSeeds.push_back(CDNSSeedData("45.77.96.149", "45.77.96.149"));

        // Note that of those with the service bits flag, most only support a subset of possible options

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 60); // REMIT addresses start with 'R'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 8); // REMIT script addresses start with '4'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63); // REMIT private keys start with 'S'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        // REMIT BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
	base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
	// REMIT BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
	base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
	// BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
	base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
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
/*
//! Modify the TESTNET genesis block so the timestamp is valid for a later start.
*/
        genesis = CreateGenesisBlock(1610066000, 0, 0x1e0ffff0, 1, 250 * COIN);        
        consensus.hashGenesisBlock = genesis.GetHash();
	//assert(consensus.hashGenesisBlock == uint256S("0x001"));
        //assert(genesis.hashMerkleRoot == uint256S("0x001"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 14;   // remita starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 60;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 99000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.devAddress = "RSGQZGPGzxMNQkNB5KPPbEDuEPaJytMY6q";

        // spork keys
        consensus.strSporkPubKey = "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f";
        consensus.strSporkPubKeyOld = "046f781df141e6ab82ca37ddb745803e2d4744137dcfdccd4e8f1e308e2001738e450e35a92828e85b99e18d88f4b78f7fe4eaf1072d91a06b82e44f02a4e425b2";
        consensus.nTime_EnforceNewSporkKey = 1610066000;
        consensus.nTime_RejectOldSporkKey = 1610060000;

        // height based activations
        consensus.height_last_PoW = 1000;
        consensus.height_start_BIP65 = 851019;                  // Block v5: d1ec8838ba8f644e78dd4f8e861d31e75457dfe607b31deade30e806b5f46c1c
        consensus.height_start_MessSignaturesV2 = 1347000;      // height_start_TimeProtoV2
        consensus.height_start_StakeModifierNewSelection = 51197;
        consensus.height_start_StakeModifierV2 = 1214000;       // Block v6: 1822577176173752aea33d1f60607cefe9e0b1c54ebaa77eb40201a385506199
        consensus.height_start_TimeProtoV2 = 1347000;           // Block v7: 30c173ffc09a13f288bf6e828216107037ce5b79536b1cebd750a014f4939882

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_PURPLE_FENIX].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        
        pchMessageStart[0] = 0xf3;
        pchMessageStart[1] = 0x24;
        pchMessageStart[2] = 0x9a;
        pchMessageStart[3] = 0x5f;
        nDefaultPort = 8452;

        vFixedSeeds.clear();
        vSeeds.clear();
        
        // nodes with support for servicebits filtering should be at the top

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 75); // REMIT addresses start with 'X'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 4); // REMIT script addresses start with '3'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 80); // REMIT private keys start with 'Z'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        // REMIT BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
	base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
	// REMIT BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
	base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
	// BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
	base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
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
/*
//! Modify the REGTEST genesis block so the timestamp is valid for a later start.
*/
        genesis = CreateGenesisBlock(1610068000, 0, 0x1e0ffff0, 1, 250 * COIN);        
        consensus.hashGenesisBlock = genesis.GetHash();
	//assert(consensus.hashGenesisBlock == uint256S("0x001"));
        //assert(genesis.hashMerkleRoot == uint256S("0x001"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 14;   // remita starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 30;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 99000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.devAddress = "RSGQZGPGzxMNQkNB5KPPbEDuEPaJytMY6q";

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "046f781df141e6ab82ca37ddb745803e2d4744137dcfdccd4e8f1e308e2001738e450e35a92828e85b99e18d88f4b78f7fe4eaf1072d91a06b82e44f02a4e425b2";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 1610068000;
        consensus.nTime_RejectOldSporkKey = 1610060000;

        // height based activations
        consensus.height_last_PoW = 350;
        consensus.height_start_BIP65 = 851019;              // Not defined for regtest. Inherit TestNet value.
        consensus.height_start_MessSignaturesV2 = 1;
        consensus.height_start_StakeModifierNewSelection = 0;
        consensus.height_start_StakeModifierV2 = 251;       // start with modifier V2 on regtest
        consensus.height_start_TimeProtoV2 = 999999999;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_PURPLE_FENIX].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xcb;
        pchMessageStart[2] = 0x7c;
        pchMessageStart[3] = 0xad;
        nDefaultPort = 8552;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }

    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
    {
        assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

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

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
