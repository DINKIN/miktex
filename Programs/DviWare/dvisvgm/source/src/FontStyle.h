/*************************************************************************
** FontStyle.h                                                          **
**                                                                      **
** This file is part of dvisvgm -- a fast DVI to SVG converter          **
** Copyright (C) 2005-2016 Martin Gieseking <martin.gieseking@uos.de>   **
**                                                                      **
** This program is free software; you can redistribute it and/or        **
** modify it under the terms of the GNU General Public License as       **
** published by the Free Software Foundation; either version 3 of       **
** the License, or (at your option) any later version.                  **
**                                                                      **
** This program is distributed in the hope that it will be useful, but  **
** WITHOUT ANY WARRANTY; without even the implied warranty of           **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         **
** GNU General Public License for more details.                         **
**                                                                      **
** You should have received a copy of the GNU General Public License    **
** along with this program; if not, see <http://www.gnu.org/licenses/>. **
*************************************************************************/

#ifndef FONTSTYLE
#define FONTSTYLE

struct FontStyle {
	FontStyle () : bold(0), extend(1), slant(0) {}
	FontStyle (float b, float e, float s) : bold(b), extend(e), slant(s) {}
	double bold;   ///< stroke width in pt used to draw the glyph outlines
	double extend; ///< factor to strech/shrink the glyphs horizontally
	double slant;  ///< horizontal slanting/skewing value (= tan(phi))
};

#endif
