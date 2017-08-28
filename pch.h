﻿/**************************************************************************
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
* You should have received a copy of the GNU Gen5eral Public License       *
* along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
**************************************************************************/

#pragma once

#include <iomanip>
#include <ppltasks.h>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Refactor: get rid of these (and potentially usage of the pch)
#include "AccountListItem.h"
#include "AccountsViewModel.h"

#include "Contact.h"
#include "ContactItem.h"
#include "ContactListModel.h"
#include "Conversation.h"

#include "SmartPanelItem.h"
#include "SmartPanelItemsViewModel.h"

#include "ContactRequestItem.h"
#include "ContactRequestItemsViewModel.h"