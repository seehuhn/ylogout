/* pixmapdimen.h - Header file for "pixmapdimen.c"
 *
 * Copyright (C) 1998, 2013  Jochen Voss
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef FILE_PIXMAPDIMEN_H_SEEN
#define FILE_PIXMAPDIMEN_H_SEEN

extern  void  get_pixmap_dimensions (Display *d, Pixmap pixmap,
                                     unsigned *width_return,
                                     unsigned *height_return);

#endif /* FILE_PIXMAPDIMEN_H_SEEN */
