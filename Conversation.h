/**************************************************************************
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

using namespace Platform;
using namespace Windows::UI::Xaml::Data;

/* strings required by Windows::Data::Json. Defined here on puprose */
String^ conversationKey = "conversation";
String^ messageKey      = "message";
String^ fromContactKey  = "fromContact";
String^ payloadKey      = "payload";
String^ timeReceivedKey = "timeReceived";
String^ isReceivedKey       = "isReceived";
String^ messageIdKey    = "messageId";

namespace RingClientUWP
{
public ref class ConversationMessage sealed
{
public:
    property bool FromContact;
    property String^ Payload;
    property std::time_t TimeReceived;
    property bool IsReceived;
    property uint64_t MessageId;

    /* functions */
    JsonObject^ ToJsonObject();
};

public ref class Conversation sealed
{
private:

public:
    /* functions */
    Conversation();
    void addMessage(bool fromContact,
                    String^ payload,
                    std::time_t timeReceived,
                    bool isReceived,
                    uint64_t MessageId);

internal:
    /* properties */
    property Vector<ConversationMessage^>^ _messages {
        Vector<ConversationMessage^>^ get() {
            return messagesList_;
        }
    }

private:
    /* members */
    Vector<ConversationMessage^>^ messagesList_;

};
#define MSG_FROM_CONTACT true
#define MSG_FROM_ME false
}

