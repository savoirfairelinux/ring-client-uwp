/***************************************************************************
* Copyright (C) 2016 by Savoir-faire Linux                                *
* Author: J�ger Nicolas <nicolas.jager@savoirfairelinux.com>              *
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

using namespace Windows::Storage;

namespace RingClientUWP
{

/* forward declaration */
ref class RingDebug;

/* delegate */
delegate void debugMessageToScreen(Platform::String^ message);

/* this is how to implement a singleton class*/
public ref class RingDebug sealed
{
public:
    /* singleton */
    static property RingDebug^ instance
    {
        RingDebug^ get()
        {
            static RingDebug^ instance_ = ref new RingDebug();
            return instance_;
        }
    }

    property StorageFile^ _logFile;

    /* properties */

    /* functions */
internal:
    enum class Type { MSG, WNG, ERR };
    void print(const std::string& message, const Type& type = Type::MSG);

    /* event */
    event debugMessageToScreen^ messageToScreen;

private:
    RingDebug(); // singleton
};

void WriteLine(String^ str)
{
    std::wstringstream wStringstream;
    wStringstream << str->Data() << "\n";
    OutputDebugString(wStringstream.str().c_str());
}

void WriteException(Exception^ ex)
{
    std::wstringstream wStringstream;
    wStringstream << "0x" << ex->HResult << ": " << ex->Message->Data();
    OutputDebugString(wStringstream.str().c_str());
}

#define MSG_(cstr) CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(CoreDispatcherPriority::High, \
ref new DispatchedHandler([=]() { RingDebug::instance->print(cstr); }))

#define WNG_(cstr) CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(CoreDispatcherPriority::High, \
ref new DispatchedHandler([=]() { RingDebug::instance->print(std::string(cstr), RingDebug::Type::WNG); }))

#define ERR_(cstr) CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(CoreDispatcherPriority::High, \
ref new DispatchedHandler([=]() { RingDebug::instance->print(std::string(cstr), RingDebug::Type::ERR); }))

}
