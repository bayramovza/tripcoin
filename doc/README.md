Tripcoin Core 0.11.0
=====================

Setup
---------------------
[Tripcoin Core](http://tripcoin.org/en/download) is the original Tripcoin client and it builds the backbone of the network. However, it downloads and stores the entire history of Tripcoin transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

Running
---------------------
The following are some helpful notes on how to run Tripcoin on your native platform. 

### Unix

You need the Qt4 run-time libraries to run Tripcoin-Qt. On Debian or Ubuntu:

	sudo apt-get install libqtgui4

Unpack the files into a directory and run:

- bin/32/tripcoin-qt (GUI, 32-bit) or bin/32/tripcoind (headless, 32-bit)
- bin/64/tripcoin-qt (GUI, 64-bit) or bin/64/tripcoind (headless, 64-bit)



### Windows

Unpack the files into a directory, and then run tripcoin-qt.exe.

### OSX

Drag Tripcoin-Qt to your applications folder, and then run Tripcoin-Qt.

### Need Help?

* See the documentation at the [Tripcoin Wiki](https://en.tripcoin.it/wiki/Main_Page)
for help and more information.
* Ask for help on [#tripcoin](http://webchat.freenode.net?channels=tripcoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=tripcoin).
* Ask for help on the [TripcoinTalk](https://tripcointalk.org/) forums, in the [Technical Support board](https://tripcointalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build Tripcoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Tripcoin repo's [root README](https://github.com/tripcoin/tripcoin/blob/master/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/tripcoin/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)

### Resources
* Discuss on the [TripcoinTalk](https://tripcointalk.org/) forums, in the [Development & Technical Discussion board](https://tripcointalk.org/index.php?board=6.0).
* Discuss on [#tripcoin-dev](http://webchat.freenode.net/?channels=tripcoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=tripcoin-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
