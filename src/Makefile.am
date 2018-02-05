# Copyright (c) 2013-2016 The Kreds Developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

KREDS_CONFIG_INCLUDES=-I$(builddir)/config
KREDS_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

KREDS_INCLUDES += -I$(srcdir)/secp256k1/include
KREDS_INCLUDES += $(UNIVALUE_CFLAGS)

LIBKREDS_SERVER=libkreds_server.a
LIBKREDS_COMMON=libkreds_common.a
LIBKREDS_CONSENSUS=libkreds_consensus.a
LIBKREDS_CLI=libkreds_cli.a
LIBKREDS_UTIL=libkreds_util.a
LIBKREDS_CRYPTO=crypto/libkreds_crypto.a
LIBKREDSQT=qt/libkredsqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBKREDS_ZMQ=libkreds_zmq.a
endif
if BUILD_KREDS_LIBS
LIBKREDSCONSENSUS=libkredsconsensus.la
endif
if ENABLE_WALLET
LIBKREDS_WALLET=libkreds_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBKREDS_CRYPTO) \
  $(LIBKREDS_UTIL) \
  $(LIBKREDS_COMMON) \
  $(LIBKREDS_CONSENSUS) \
  $(LIBKREDS_SERVER) \
  $(LIBKREDS_CLI) \
  $(LIBKREDS_WALLET) \
  $(LIBKREDS_ZMQ)

lib_LTLIBRARIES = $(LIBKREDSCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_KREDSD
  bin_PROGRAMS += kredsd
endif

if BUILD_KREDS_UTILS
  bin_PROGRAMS += kreds-cli kreds-tx
endif

.PHONY: FORCE check-symbols check-security
# Kreds #
KREDS_CORE_H = \
  activemasternode.h \
  addrdb.h \
  addrman.h \
  base58.h \
  bloom.h \
  blockencodings.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  key.h \
  keepass.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  masternode.h \
  masternode-pos.h \
  masternodeman.h \
  masternodeconfig.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  protocol.h \
  random.h \
  reverselock.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  spork.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libkreds_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between kredsd and kreds-qt
libkreds_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(KREDS_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libkreds_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libkreds_server_a_SOURCES = \
  activemasternode.cpp \
  addrman.cpp \
  addrdb.cpp \
  bloom.cpp \
  blockencodings.cpp \
  bitpool.cpp \
  chain.cpp \
  checkpoints.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(KREDS_CORE_H)

if ENABLE_ZMQ
libkreds_zmq_a_CPPFLAGS = $(KREDS_INCLUDES) $(ZMQ_CFLAGS)
libkreds_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libkreds_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between kredsd and kreds-qt, but only linked
# when wallet enabled
libkreds_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(KREDS_INCLUDES)
libkreds_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libkreds_wallet_a_SOURCES = \
  activemasternode.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  policy/rbf.cpp \
  $(KREDS_CORE_H)

# crypto primitives library
crypto_libkreds_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(KREDS_CONFIG_INCLUDES)
crypto_libkreds_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libkreds_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/Lyra2RE/Lyra2RE.c \
  crypto/Lyra2RE/Lyra2RE.h \
  crypto/Lyra2RE/Lyra2.c \
  crypto/Lyra2RE/Lyra2.h \
  crypto/Lyra2RE/Sponge.c \
  crypto/Lyra2RE/Sponge.h \
  crypto/Lyra2RE/blake.c \
  crypto/Lyra2RE/blake.h \
  crypto/Lyra2RE/groestl.c \
  crypto/Lyra2RE/groestl.h \
  crypto/Lyra2RE/keccak.c \
  crypto/Lyra2RE/keccak.h \
  crypto/Lyra2RE/skein.c \
  crypto/Lyra2RE/skein.h \
  crypto/Lyra2RE/cubehash.c \
  crypto/Lyra2RE/cubehash.h \
  crypto/Lyra2RE/bmw.c \
  crypto/Lyra2RE/bmw.h

# consensus: shared between all executables that validate any consensus rules.
libkreds_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(KREDS_INCLUDES)
libkreds_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libkreds_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/kredsconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

# common: shared between kredsd, and kreds-qt and non-server tools
libkreds_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(KREDS_INCLUDES)
libkreds_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libkreds_common_a_SOURCES = \
  activemasternode.cpp \
  masternode.cpp \
  masternode-pos.cpp \
  masternodeconfig.cpp \
  masternodeman.cpp \
  amount.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  spork.cpp \
  warnings.cpp \
  $(KREDS_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libkreds_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(KREDS_INCLUDES)
libkreds_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libkreds_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(KREDS_CORE_H)

if GLIBC_BACK_COMPAT
libkreds_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between kreds-cli and kreds-qt
libkreds_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(KREDS_INCLUDES)
libkreds_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libkreds_cli_a_SOURCES = \
  rpc/client.cpp \
  $(KREDS_CORE_H)

nodist_libkreds_util_a_SOURCES = $(srcdir)/obj/build.h
#

# kredsd binary #
kredsd_SOURCES = kredsd.cpp
kredsd_CPPFLAGS = $(AM_CPPFLAGS) $(KREDS_INCLUDES)
kredsd_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
kredsd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
kredsd_SOURCES += kredsd-res.rc
endif

kredsd_LDADD = \
  $(LIBKREDS_SERVER) \
  $(LIBKREDS_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBKREDS_UTIL) \
  $(LIBKREDS_WALLET) \
  $(LIBKREDS_ZMQ) \
  $(LIBKREDS_CONSENSUS) \
  $(LIBKREDS_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

kredsd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# kreds-cli binary #
kreds_cli_SOURCES = kreds-cli.cpp
kreds_cli_CPPFLAGS = $(AM_CPPFLAGS) $(KREDS_INCLUDES) $(EVENT_CFLAGS)
kreds_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
kreds_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
kreds_cli_SOURCES += kreds-cli-res.rc
endif

kreds_cli_LDADD = \
  $(LIBKREDS_CLI) \
  $(LIBUNIVALUE) \
  $(LIBKREDS_UTIL) \
  $(LIBKREDS_CRYPTO)

kreds_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# kreds-tx binary #
kreds_tx_SOURCES = kreds-tx.cpp
kreds_tx_CPPFLAGS = $(AM_CPPFLAGS) $(KREDS_INCLUDES)
kreds_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
kreds_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
kreds_tx_SOURCES += kreds-tx-res.rc
endif

kreds_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBKREDS_COMMON) \
  $(LIBKREDS_UTIL) \
  $(LIBKREDS_CONSENSUS) \
  $(LIBKREDS_CRYPTO) \
  $(LIBSECP256K1)

kreds_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# kredsconsensus library #
if BUILD_KREDS_LIBS
include_HEADERS = script/kredsconsensus.h
libkredsconsensus_la_SOURCES = $(crypto_libkreds_crypto_a_SOURCES) $(libkreds_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libkredsconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libkredsconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libkredsconsensus_la_LIBADD = $(LIBSECP256K1)
libkredsconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_KREDS_INTERNAL
libkredsconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = $(CTAES_DIST)

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
