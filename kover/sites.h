/** -*- adrian-c -*-
	 kover - Kover is an easy to use WYSIWYG CD cover printer with CDDB support.
	 Copyright (C) 2001-2002 by Adrian Reber 
	 
	 This program is free software; you can redistribute it and/or modify
	 it under the terms of the GNU General Public License as published by
	 the Free Software Foundation; either version 2 of the License, or
	 (at your option) any later version.
	 
	 This program is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	 GNU General Public License for more details.
	 
	 You should have received a copy of the GNU General Public License
	 along with this program; if not, write to the Free Software
	 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
	 
	 File: sites.h
	 
	 Description: entity for the sites

	 Changes:
	 
	 24 Apr 2002: Initial release
	 
*/

/* $Id: sites.h,v 1.6 2002/05/05 22:01:54 adrian Exp $ */

#ifndef SITES_H
#define SITES_H

#include "../config.h"
#include "kover.h"
#include "net.h"
#include "cddb.h"
#include "server.h"

using namespace std;

class sites : public net, cddb {

public:
	 sites();
	 ~sites();
	 bool gen_server_list(list <server *> &server_list);
private:
	 list <string> site;

};

#endif /* SITES_H */
