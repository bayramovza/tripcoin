// Copyright (c) 2014 The Tripcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TRIPCOIN_CHAINPARAMSBASE_H
#define TRIPCOIN_CHAINPARAMSBASE_H

#include <string>
#include <vector>

/**
 * CBaseChainParams defines the base parameters (shared between tripcoin-cli and tripcoind)
 * of a given instance of the Tripcoin system.
 */
class CBaseChainParams
{
public:
    enum Network {
        MAIN,
        TESTNET,
        REGTEST,

        MAX_NETWORK_TYPES
    };

    const std::string& DataDir() const { return strDataDir; }
    int RPCPort() const { return nRPCPort; }

protected:
    CBaseChainParams() {}

    int nRPCPort;
    std::string strDataDir;
};

/**
 * Return the currently selected parameters. This won't change after app
 * startup, except for unit tests.
 */
const CBaseChainParams& BaseParams();

/** Sets the params returned by Params() to those for the given network. */
void SelectBaseParams(CBaseChainParams::Network network);

/**
 * Looks for -regtest or -testnet and returns the appropriate Network ID.
 * Returns MAX_NETWORK_TYPES if an invalid combination is given.
 */
CBaseChainParams::Network NetworkIdFromCommandLine();

/**
 * Calls NetworkIdFromCommandLine() and then calls SelectParams as appropriate.
 * Returns false if an invalid combination is given.
 */
bool SelectBaseParamsFromCommandLine();

/**
 * Return true if SelectBaseParamsFromCommandLine() has been called to select
 * a network.
 */
bool AreBaseParamsConfigured();

#endif // TRIPCOIN_CHAINPARAMSBASE_H
