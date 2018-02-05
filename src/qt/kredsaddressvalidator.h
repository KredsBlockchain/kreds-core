// Copyright (c) 2011-2014 The Kreds Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KREDS_QT_KREDSADDRESSVALIDATOR_H
#define KREDS_QT_KREDSADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class KredsAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KredsAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Kreds address widget validator, checks for a valid kreds address.
 */
class KredsAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KredsAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // KREDS_QT_KREDSADDRESSVALIDATOR_H
