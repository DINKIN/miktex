/* dvicopy-miktex.h:                                    -*- C++ -*-

   Copyright (C) 1996-2016 Christian Schenk

   This file is part of DVIcopy.

   DVIcopy is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   DVIcopy is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with DVIcopy; if not, write to the Free Software Foundation,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */

#if !defined(_MSC_VER)
#  pragma once
#endif

#include <miktex/TeXAndFriends/config.h>

#if !defined(THEDATA)
#  define THEDATA(x) C4P_VAR(x)
#endif

#include "dvicopydefs.h"
#include <miktex/TeXAndFriends/WebApp>

#if !defined(MIKTEXHELP_DVICOPY)
#  include <miktex/Core/Help>
#endif

using namespace MiKTeX::TeXAndFriends;
using namespace MiKTeX::Core;

class DVICOPYCLASS :
  public WebApp
{
#define OPT_MAG 1000
#define OPT_SELECT 1001
#define OPT_MAX_PAGES 1002
#define OPT_PAGE_START 1003

public:
  void AddOptions() override
  {
    WebApp::AddOptions();
    AddOption(MIKTEXTEXT("mag\0Override existing magnification with MAG."), OPT_MAG,  POPT_ARG_STRING, "MAG");
    AddOption("magnification", "mag");
    AddOption(MIKTEXTEXT("select\0Select a page range (start page and page count), for example `2 12' or `5.*.-2 4'. This option can be used up to 10 times.  This option cannot be used together with -max-pages or -page-start."), OPT_SELECT,  POPT_ARG_STRING, "SEL");
    AddOption(MIKTEXTEXT("max-pages\0Process N pages; default one million. This option cannot be used together with -select."), OPT_MAX_PAGES, POPT_ARG_STRING, "N");
    AddOption(MIKTEXTEXT("page-start\0Start at PAGE-SPEC, for example `2' or `5.*.-2'. This option cannot be used together with -select."), OPT_PAGE_START, POPT_ARG_STRING, MIKTEXTEXT("PAGE-SPEC"));
  }

public:
  void SetupOptions()
  {
    if (maxPages.length() > 0 || pageStart.length() > 0)
    {
      if (selections.size() > 0)
      {
        FatalError(MIKTEXTEXT("-select was specified together with -max-pages and/or -page-start."));
      }
      if (maxPages.length() == 0)
      {
        maxPages = "1000000";
      }
      if (pageStart.length() == 0)
      {
        pageStart = "*";
      }
      std::string str = pageStart;
      str += " ";
      str += maxPages;
      selections.push_back(str);
    }
        
    if (selections.size() > maxselections)
    {
      FatalError(MIKTEXTEXT("Too mant page selections."));
    }
        
    for (std::vector<std::string>::const_iterator it = selections.begin(); it != selections.end(); ++ it)
    {
      if (it->length() + 8 >= sizeof(THEDATA(options)[0]))
      {
        FatalError(MIKTEXTEXT("Invalid page selection."));
      }
#if defined(_MSC_VER) && _MSC_VER >= 1400
      sprintf_s(THEDATA(options)[THEDATA(nopt)++], (sizeof(THEDATA(options)[0]) / sizeof(THEDATA(options)[0][0])), MIKTEXTEXT("select %s"), it->c_str());
#else
      sprintf(THEDATA(options)[THEDATA(nopt)++], MIKTEXTEXT("select %s"), it->c_str());
#endif
    }

    if (mag.length() > 0)
    {
      if (mag.length() + 5 >= sizeof(THEDATA(options)[0]))
      {
        FatalError(MIKTEXTEXT("Invalid magnification."));
      }
#if defined(_MSC_VER) && _MSC_VER >= 1400
      sprintf_s(THEDATA(options)[THEDATA(nopt)++], (sizeof(THEDATA(options)[0]) / sizeof(THEDATA(options)[0][0])), MIKTEXTEXT("mag %s"), mag.c_str());
#else
      sprintf(THEDATA(options)[THEDATA(nopt)++], MIKTEXTEXT("mag %s"), mag.c_str());
#endif
    }
  }

public:
  const char * GetUsage() const override
  {
    return MIKTEXTEXT("[OPTION...] INDVI OUTDVI");
  }

public:
  bool ProcessOption(int opt, const std::string & optArg) override
  {
    bool done = true;
    switch (opt)
      {
      case OPT_SELECT:
        selections.push_back(optArg);
        break;
      case OPT_MAG:
        if (!mag.empty())
        {
          FatalError(MIKTEXTEXT("-mag was specified more than once."));
        }
        mag = optArg;
        break;
      case OPT_MAX_PAGES:
        if (!maxPages.empty())
        {
          FatalError(MIKTEXTEXT("-max-pages was specified more than once."));
        }
        maxPages = optArg;
        break;
      case OPT_PAGE_START:
        if (!pageStart.empty())
        {
          FatalError(MIKTEXTEXT("-page-start was specified more than once."));
        }
        pageStart = optArg;
        break;
      default:
        done = WebApp::ProcessOption(opt, optArg);
        break;
      }
    return done;
  }

private:
  std::vector<std::string> selections;

private:
  std::string mag;

private:
  std::string pageStart;

private:
  std::string maxPages;

public:
  unsigned long GetHelpId() const override
  {
    return MIKTEXHELP_DVICOPY;
  }
};

extern DVICOPYCLASS DVICOPYAPP;
#define THEAPP DVICOPYAPP

inline void setupoptions()
{
  THEAPP.SetupOptions();
}

#include <miktex/TeXAndFriends/WebApp.inl>
