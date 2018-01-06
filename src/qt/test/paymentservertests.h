// Copyright (c) 2009-2014 The Tripcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TRIPCOIN_QT_TEST_PAYMENTSERVERTESTS_H
#define TRIPCOIN_QT_TEST_PAYMENTSERVERTESTS_H

#include "../paymentserver.h"

#include <QObject>
#include <QTest>

class PaymentServerTests : public QObject
{
    Q_OBJECT

private slots:
    void paymentServerTests();
};

// Dummy class to receive paymentserver signals.
// If SendCoinsRecipient was a proper QObject, then
// we could use QSignalSpy... but it's not.
class RecipientCatcher : public QObject
{
    Q_OBJECT

public slots:
    void getRecipient(SendCoinsRecipient r);

public:
    SendCoinsRecipient recipient;
};

#endif // TRIPCOIN_QT_TEST_PAYMENTSERVERTESTS_H
