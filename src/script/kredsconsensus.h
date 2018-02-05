// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers 
// Copyright (c) 2015-2017 The Dash developers 
// Copyright (c) 2015-2017 The Kreds developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KREDS_KREDSCONSENSUS_H
#define KREDS_KREDSCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_KREDS_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/kreds-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBKREDSCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define KREDSCONSENSUS_API_VER 1

typedef enum kredsconsensus_error_t
{
    kredsconsensus_ERR_OK = 0,
    kredsconsensus_ERR_TX_INDEX,
    kredsconsensus_ERR_TX_SIZE_MISMATCH,
    kredsconsensus_ERR_TX_DESERIALIZE,
    kredsconsensus_ERR_AMOUNT_REQUIRED,
    kredsconsensus_ERR_INVALID_FLAGS,
} kredsconsensus_error;

/** Script verification flags */
enum
{
    kredsconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    kredsconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    kredsconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    kredsconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    kredsconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    kredsconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    kredsconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    kredsconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = kredsconsensus_SCRIPT_FLAGS_VERIFY_P2SH | kredsconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               kredsconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | kredsconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               kredsconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | kredsconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not NULL, err will contain an error/success code for the operation
EXPORT_SYMBOL int kredsconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, kredsconsensus_error* err);

EXPORT_SYMBOL int kredsconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, kredsconsensus_error* err);

EXPORT_SYMBOL unsigned int kredsconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // KREDS_KREDSCONSENSUS_H
