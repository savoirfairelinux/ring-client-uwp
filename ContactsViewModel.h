/***************************************************************************
 * Copyright (C) 2016 by Savoir-faire Linux                                *
 * Author: Jäger Nicolas <nicolas.jager@savoirfairelinux.com>              *
 * Author: Traczyk Andreas <andreas.traczyk@savoirfairelinux.com>          *
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

using namespace Platform::Collections;
using namespace Concurrency;

namespace RingClientUWP
{

/* delegates */
delegate void ContactAdded(Contact^);
delegate void ContactDeleted(Contact^);

namespace ViewModel {
public ref class ContactsViewModel sealed
{
internal:
    /* singleton */
    static property ContactsViewModel^ instance
    {
        ContactsViewModel^ get()
        {
            static ContactsViewModel^ instance_ = ref new ContactsViewModel();
            return instance_;
        }
    }

    /* functions */
    Contact^    findContactByName(String^ name);
    Contact^    addNewContact(String^ name, String^ ringId);
    void        saveContactsToFile();
    void        openContactsFromFile();
    String^     Stringify();
    void        Destringify(String^ data);
    void        deleteContact(Contact^ contact);

    /* properties */
    property Vector<Contact^>^ contactsList
    {
        Vector<Contact^>^ get()
        {
            return contactsList_;
        }
    }

    /* events */
    event ContactAdded^ contactAdded;
    event ContactDeleted^ contactDeleted;

private:
    ContactsViewModel(); // singleton
    Vector<Contact^>^ contactsList_;
    Contact^ currentItem_;
    Contact^ oldItem_;

    void OnincomingMessage(Platform::String ^callId, Platform::String ^payload);
};
}
}