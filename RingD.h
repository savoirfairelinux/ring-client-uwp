/***************************************************************************
 * Copyright (C) 2016 by Savoir-faire Linux                                *
 * Author: J�ger Nicolas <nicolas.jager@savoirfairelinux.com>              *
 * Author: Traczyk Andreas <traczyk.andreas@savoirfairelinux.com>          *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 **************************************************************************/
#pragma once

using namespace concurrency;

namespace RingClientUWP
{
// TODO :: move the tasks in private, use enum for order
ref class Task
{
public:
    property String^ order;
};

ref class MessageText : public Task {

public:
    property String^ accountId;
    property String^ to;
    property String^ payload;
};

ref class File : public Task {

};


public ref class RingD sealed
{

public:
    static property RingD^ instance
    {
        RingD^ get()
        {
            static RingD^ instance_ = ref new RingD();
            return instance_;
        }
    }

    /* properties */

    /* functions */
internal:
    void startDaemon();
    void pushEvents();

    void emitSendMessage(String^ accountId, String^ to, String^ payload);
    void emitStartDaemon(Task^ task);
    void emitStopDaemon(Task^ task);

    event RingDaemonSendMessage^ ringDaemonSendMessage;
    event RingDaemonStart^ ringDaemonStart;
    event RingDaemonStop^ ringDaemonStop;

private:
    RingD(); // singleton
    std::string localFolder_;
    std::queue<Task^> listEvents;

};
}