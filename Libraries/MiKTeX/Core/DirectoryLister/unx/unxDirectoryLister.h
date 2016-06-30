/* unxDirectoryLister.h:                                -*- C++ -*-

   Copyright (C) 1996-2016 Christian Schenk

   This file is part of the MiKTeX Core Library.

   The MiKTeX Core Library is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2, or
   (at your option) any later version.

   The MiKTeX Core Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the MiKTeX Core Library; if not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA. */

#if defined(_MSC_VER)
#  pragma once
#endif

#if !defined(F2A2B73E1341485FAFAB1FC525782032)
#define F2A2B73E1341485FAFAB1FC525782032

#include "miktex/Core/DirectoryLister.h"
#include "miktex/Core/PathName.h"

BEGIN_INTERNAL_NAMESPACE;

class unxDirectoryLister :
  public MiKTeX::Core::DirectoryLister
{
public:
  void Close() override;

public:
  bool GetNext(MiKTeX::Core::DirectoryEntry & direntry) override;

public:
  bool GetNext(MiKTeX::Core::DirectoryEntry2 & direntry2) override;

public:
  unxDirectoryLister(const MiKTeX::Core::PathName & directory, const char * lpszPattern, int options);

public:
  ~unxDirectoryLister() override;

private:
  bool GetNext(MiKTeX::Core::DirectoryEntry2 & direntry2, bool simple);

private:
  DIR * pDir = nullptr;

private:
  MiKTeX::Core::PathName directory;

private:
  std::string pattern;

private:
  int options = (int)Options::None;

private:
  friend class MiKTeX::Core::DirectoryLister;
};

END_INTERNAL_NAMESPACE;

#endif