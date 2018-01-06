// Copyright (c) 2011-2014 The Tripcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TRIPCOIN_QT_TRIPCOINADDRESSVALIDATOR_H
#define TRIPCOIN_QT_TRIPCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class TripcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit TripcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Tripcoin address widget validator, checks for a valid tripcoin address.
 */
class TripcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit TripcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // TRIPCOIN_QT_TRIPCOINADDRESSVALIDATOR_H
