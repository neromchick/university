#ifndef WALLET_H
#define WALLET_H

#include <QObject>

class Wallet : public QObject {
    Q_OBJECT
public:
    static Wallet& instance() {
        static Wallet inst;
        return inst;
    }

    void addMoney(int amount) {
        m_balance += amount;
        emit balanceChanged(m_balance);
    }

    int balance() const { return m_balance; }

signals:
    void balanceChanged(int newBalance);

private:
    Wallet() : m_balance(0) {}
    int m_balance;
};

#endif
