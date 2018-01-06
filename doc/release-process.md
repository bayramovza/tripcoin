Release Process
====================

* update translations (ping wumpus, Diapolo or tcatm on IRC)
* see https://github.com/tripcoin/tripcoin/blob/master/doc/translation_process.md#syncing-with-transifex

* * *

###update (commit) version in sources

	contrib/verifysfbinaries/verify.sh
	doc/README*
	share/setup.nsi
	src/clientversion.h (change CLIENT_VERSION_IS_RELEASE to true)

###tag version in git

	git tag -s v(new version, e.g. 0.8.0)

###write release notes. git shortlog helps a lot, for example:

	git shortlog --no-merges v(current version, e.g. 0.7.2)..v(new version, e.g. 0.8.0)

* * *

###update gitian

 In order to take advantage of the new caching features in gitian, be sure to update to a recent version (`e9741525c` or later is recommended)

###perform gitian builds

 From a directory containing the tripcoin source, gitian-builder and gitian.sigs
  
	export SIGNER=(your gitian key, ie bluematt, sipa, etc)
	export VERSION=(new version, e.g. 0.8.0)
	pushd ./tripcoin
	git checkout v${VERSION}
	popd
	pushd ./gitian-builder

###fetch and build inputs: (first time, or when dependency versions change)
 
	mkdir -p inputs
	wget -P inputs https://tripcoincore.org/cfields/osslsigncode-Backports-to-1.7.1.patch
	wget -P inputs http://downloads.sourceforge.net/project/osslsigncode/osslsigncode/osslsigncode-1.7.1.tar.gz

 Register and download the Apple SDK: (see OSX Readme for details)
 
 https://developer.apple.com/devcenter/download.action?path=/Developer_Tools/xcode_6.1.1/xcode_6.1.1.dmg
 
 Using a Mac, create a tarball for the 10.9 SDK and copy it to the inputs directory:
 
	tar -C /Volumes/Xcode/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/ -czf MacOSX10.9.sdk.tar.gz MacOSX10.9.sdk

###Optional: Seed the Gitian sources cache

  By default, gitian will fetch source files as needed. For offline builds, they can be fetched ahead of time:

	make -C ../tripcoin/depends download SOURCES_PATH=`pwd`/cache/common

  Only missing files will be fetched, so this is safe to re-run for each build.

###Build Tripcoin Core for Linux, Windows, and OS X:
  
	./bin/gbuild --commit tripcoin=v${VERSION} ../tripcoin/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-linux --destination ../gitian.sigs/ ../tripcoin/contrib/gitian-descriptors/gitian-linux.yml
	mv build/out/tripcoin-*.tar.gz build/out/src/tripcoin-*.tar.gz ../
	./bin/gbuild --commit tripcoin=v${VERSION} ../tripcoin/contrib/gitian-descriptors/gitian-win.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win-unsigned --destination ../gitian.sigs/ ../tripcoin/contrib/gitian-descriptors/gitian-win.yml
	mv build/out/tripcoin-*-win-unsigned.tar.gz inputs/tripcoin-win-unsigned.tar.gz
	mv build/out/tripcoin-*.zip build/out/tripcoin-*.exe ../
	./bin/gbuild --commit tripcoin=v${VERSION} ../tripcoin/contrib/gitian-descriptors/gitian-osx.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-osx-unsigned --destination ../gitian.sigs/ ../tripcoin/contrib/gitian-descriptors/gitian-osx.yml
	mv build/out/tripcoin-*-osx-unsigned.tar.gz inputs/tripcoin-osx-unsigned.tar.gz
	mv build/out/tripcoin-*.tar.gz build/out/tripcoin-*.dmg ../
	popd
  Build output expected:

  1. source tarball (tripcoin-${VERSION}.tar.gz)
  2. linux 32-bit and 64-bit dist tarballs (tripcoin-${VERSION}-linux[32|64].tar.gz)
  3. windows 32-bit and 64-bit unsigned installers and dist zips (tripcoin-${VERSION}-win[32|64]-setup-unsigned.exe, tripcoin-${VERSION}-win[32|64].zip)
  4. OSX unsigned installer and dist tarball (tripcoin-${VERSION}-osx-unsigned.dmg, tripcoin-${VERSION}-osx64.tar.gz)
  5. Gitian signatures (in gitian.sigs/${VERSION}-<linux|{win,osx}-unsigned>/(your gitian key)/

###Next steps:

Commit your signature to gitian.sigs:

	pushd gitian.sigs
	git add ${VERSION}-linux/${SIGNER}
	git add ${VERSION}-win-unsigned/${SIGNER}
	git add ${VERSION}-osx-unsigned/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

  Wait for Windows/OSX detached signatures:
	Once the Windows/OSX builds each have 3 matching signatures, they will be signed with their respective release keys.
	Detached signatures will then be committed to the tripcoin-detached-sigs repository, which can be combined with the unsigned apps to create signed binaries.

  Create the signed OSX binary:

	pushd ./gitian-builder
	./bin/gbuild -i --commit signature=v${VERSION} ../tripcoin/contrib/gitian-descriptors/gitian-osx-signer.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-osx-signed --destination ../gitian.sigs/ ../tripcoin/contrib/gitian-descriptors/gitian-osx-signer.yml
	mv build/out/tripcoin-osx-signed.dmg ../tripcoin-${VERSION}-osx.dmg
	popd

  Create the signed Windows binaries:

	pushd ./gitian-builder
	./bin/gbuild -i --commit signature=v${VERSION} ../tripcoin/contrib/gitian-descriptors/gitian-win-signer.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win-signed --destination ../gitian.sigs/ ../tripcoin/contrib/gitian-descriptors/gitian-win-signer.yml
	mv build/out/tripcoin-*win64-setup.exe ../tripcoin-${VERSION}-win64-setup.exe
	mv build/out/tripcoin-*win32-setup.exe ../tripcoin-${VERSION}-win32-setup.exe
	popd

Commit your signature for the signed OSX/Windows binaries:

	pushd gitian.sigs
	git add ${VERSION}-osx-signed/${SIGNER}
	git add ${VERSION}-win-signed/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

-------------------------------------------------------------------------

### After 3 or more people have gitian-built and their results match:

- Create `SHA256SUMS.asc` for the builds, and GPG-sign it:
```bash
sha256sum * > SHA256SUMS
gpg --digest-algo sha256 --clearsign SHA256SUMS # outputs SHA256SUMS.asc
rm SHA256SUMS
```
(the digest algorithm is forced to sha256 to avoid confusion of the `Hash:` header that GPG adds with the SHA256 used for the files)
Note: check that SHA256SUMS itself doesn't end up in SHA256SUMS, which is a spurious/nonsensical entry.

- Upload zips and installers, as well as `SHA256SUMS.asc` from last step, to the tripcoin.org server
  into `/var/www/bin/tripcoin-core-${VERSION}`

- Update tripcoin.org version

  - First, check to see if the Tripcoin.org maintainers have prepared a
    release: https://github.com/tripcoin/tripcoin.org/labels/Releases

      - If they have, it will have previously failed their Travis CI
        checks because the final release files weren't uploaded.
        Trigger a Travis CI rebuild---if it passes, merge.

  - If they have not prepared a release, follow the Tripcoin.org release
    instructions: https://github.com/tripcoin/tripcoin.org#release-notes

  - After the pull request is merged, the website will automatically show the newest version within 15 minutes, as well
    as update the OS download links. Ping @saivann/@harding (saivann/harding on Freenode) in case anything goes wrong

- Announce the release:

  - Release sticky on tripcointalk: https://tripcointalk.org/index.php?board=1.0

  - Tripcoin-development mailing list

  - Update title of #tripcoin on Freenode IRC

  - Optionally reddit /r/Tripcoin, ... but this will usually sort out itself

- Notify BlueMatt so that he can start building [https://launchpad.net/~tripcoin/+archive/ubuntu/tripcoin](the PPAs)

- Add release notes for the new version to the directory `doc/release-notes` in git master

- Celebrate
