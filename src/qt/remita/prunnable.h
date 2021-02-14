//Copyright (c) 2019 The PIVX developers
//Copyright (c) 2020 The remita developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef remita_CORE_NEW_GUI_PRUNNABLE_H
#define remita_CORE_NEW_GUI_PRUNNABLE_H

class Runnable {
public:
    virtual void run(int type) = 0;
    virtual void onError(QString error, int type) = 0;
};

#endif //remita_CORE_NEW_GUI_PRUNNABLE_H
