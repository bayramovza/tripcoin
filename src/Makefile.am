DIST_SUBDIRS = secp256k1
AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS) -D__STDC_LIMIT_MACROS"
endif

TRIPCOIN_CONFIG_INCLUDES=-I$(builddir)/config
TRIPCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

TRIPCOIN_INCLUDES += -I$(srcdir)/secp256k1/include

LIBTRIPCOIN_SERVER=libtripcoin_server.a
LIBTRIPCOIN_WALLET=libtripcoin_wallet.a
LIBTRIPCOIN_COMMON=libtripcoin_common.a
LIBTRIPCOIN_CLI=libtripcoin_cli.a
LIBTRIPCOIN_UTIL=libtripcoin_util.a
LIBTRIPCOIN_CRYPTO=crypto/libtripcoin_crypto.a
LIBTRIPCOIN_UNIVALUE=univalue/libtripcoin_univalue.a
LIBTRIPCOINQT=qt/libtripcoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libtripcoin_crypto.a \
  libtripcoin_util.a \
  libtripcoin_common.a \
  univalue/libtripcoin_univalue.a \
  libtripcoin_server.a \
  libtripcoin_cli.a
if ENABLE_WALLET
TRIPCOIN_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libtripcoin_wallet.a
endif

if BUILD_TRIPCOIN_LIBS
lib_LTLIBRARIES = libtripcoinconsensus.la
LIBTRIPCOIN_CONSENSUS=libtripcoinconsensus.la
else
LIBTRIPCOIN_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_TRIPCOIND
  bin_PROGRAMS += tripcoind
endif

if BUILD_TRIPCOIN_UTILS
  bin_PROGRAMS += tripcoin-cli tripcoin-tx
endif

.PHONY: FORCE
# tripcoin core #
TRIPCOIN_CORE_H = \
  addrman.h \
  alert.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/params.h \
  consensus/validation.h \
  core_io.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  pow.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  scheduler.h \
  script/interpreter.h \
  script/script.h \
  script/script_error.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  wallet/walletdb.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libtripcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between tripcoind and tripcoin-qt
libtripcoin_server_a_CPPFLAGS = $(TRIPCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS)
libtripcoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  validationinterface.cpp \
  $(JSON_H) \
  $(TRIPCOIN_CORE_H)

# wallet: shared between tripcoind and tripcoin-qt, but only linked
# when wallet enabled
libtripcoin_wallet_a_CPPFLAGS = $(TRIPCOIN_INCLUDES)
libtripcoin_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  $(TRIPCOIN_CORE_H)

# crypto primitives library
crypto_libtripcoin_crypto_a_CPPFLAGS = $(TRIPCOIN_CONFIG_INCLUDES)
crypto_libtripcoin_crypto_a_SOURCES = \
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
  crypto/sha512.h

# univalue JSON library
univalue_libtripcoin_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue.h \
  univalue/univalue_escapes.h \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp

# common: shared between tripcoind, and tripcoin-qt and non-server tools
libtripcoin_common_a_CPPFLAGS = $(TRIPCOIN_INCLUDES)
libtripcoin_common_a_SOURCES = \
  amount.cpp \
  arith_uint256.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  protocol.cpp \
  pubkey.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(TRIPCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libtripcoin_util_a_CPPFLAGS = $(TRIPCOIN_INCLUDES)
libtripcoin_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(TRIPCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libtripcoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between tripcoin-cli and tripcoin-qt
libtripcoin_cli_a_CPPFLAGS = $(TRIPCOIN_INCLUDES)
libtripcoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(TRIPCOIN_CORE_H)

nodist_libtripcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# tripcoind binary #
tripcoind_SOURCES = tripcoind.cpp
tripcoind_CPPFLAGS = $(TRIPCOIN_INCLUDES)
tripcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
tripcoind_SOURCES += tripcoind-res.rc
endif

tripcoind_LDADD = \
  $(LIBTRIPCOIN_SERVER) \
  $(LIBTRIPCOIN_COMMON) \
  $(LIBTRIPCOIN_UNIVALUE) \
  $(LIBTRIPCOIN_UTIL) \
  $(LIBTRIPCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_WALLET
tripcoind_LDADD += libtripcoin_wallet.a
endif

tripcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
#

# tripcoin-cli binary #
tripcoin_cli_SOURCES = tripcoin-cli.cpp
tripcoin_cli_CPPFLAGS = $(TRIPCOIN_INCLUDES)
tripcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
tripcoin_cli_SOURCES += tripcoin-cli-res.rc
endif

tripcoin_cli_LDADD = \
  $(LIBTRIPCOIN_CLI) \
  $(LIBTRIPCOIN_UTIL) \
  $(LIBSECP256K1)

tripcoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS)
#

# tripcoin-tx binary #
tripcoin_tx_SOURCES = tripcoin-tx.cpp
tripcoin_tx_CPPFLAGS = $(TRIPCOIN_INCLUDES)
tripcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
tripcoin_tx_SOURCES += tripcoin-tx-res.rc
endif

tripcoin_tx_LDADD = \
  $(LIBTRIPCOIN_UNIVALUE) \
  $(LIBTRIPCOIN_COMMON) \
  $(LIBTRIPCOIN_UTIL) \
  $(LIBTRIPCOIN_CRYPTO) \
  $(LIBSECP256K1)

tripcoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# tripcoinconsensus library #
if BUILD_TRIPCOIN_LIBS
include_HEADERS = script/tripcoinconsensus.h
libtripcoinconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/tripcoinconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libtripcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libtripcoinconsensus_la_LDFLAGS = -no-undefined $(RELDFLAGS)
libtripcoinconsensus_la_LIBADD = $(CRYPTO_LIBS)
libtripcoinconsensus_la_CPPFLAGS = $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_TRIPCOIN_INTERNAL

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
