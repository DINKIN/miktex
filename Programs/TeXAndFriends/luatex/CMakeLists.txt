## CMakeLists.txt					-*- CMake -*-
##
## Copyright (C) 2010-2016 Christian Schenk
## 
## This file is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published
## by the Free Software Foundation; either version 2, or (at your
## option) any later version.
## 
## This file is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this file; if not, write to the Free Software
## Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
## USA.

set(MIKTEX_CURRENT_FOLDER "${MIKTEX_IDE_TEX_AND_FRIENDS_FOLDER}/LuaTeX")

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/source
  ${CMAKE_SOURCE_DIR}/${MIKTEX_REL_SYNCTEX_DIR}
)

add_definitions(
  -DAPPTAG=luatex
  -DLUA_COMPAT_ALL
  -DLUA_COMPAT_MODULE
  -DMIKTEX_LUATEX
  -DNO_DUMP_SHARE
  -DPDF_PARSER_ONLY
  -DSYNCTEX_ENGINE_H="synctex-luatex.h"
  -DUSE_MIKTEX_EXIT
  -DpdfTeX
  -DHAVE_STRUCTTREEROOT_H
)

if(MIKTEX_NATIVE_WINDOWS)
  add_definitions(
    -DUNICODE
    -D_UNICODE
    -DWIN32_LEAN_AND_MEAN
  )
endif()

ignore_warnings()

if(WITH_CONTEXT_SUPPORT)
  add_definitions(-DWITH_CONTEXT_SUPPORT=1)
endif()

###############################################################################
## luatex-miktex-static
###############################################################################

set(generated_texmf_sources
  ${CMAKE_BINARY_DIR}/include/miktex/texapp.defaults.h
  ${CMAKE_BINARY_DIR}/include/miktex/texmfapp.defaults.h
)

set(miktex_sources
  ${generated_texmf_sources}
  miktex/luatex.h
  miktex/miktex.cpp
)

add_library(luatex-miktex-static STATIC ${miktex_sources})

set_property(TARGET luatex-miktex-static PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})

add_dependencies(luatex-miktex-static gen-defaults)

set_source_files_properties(
  ${generated_texmf_sources}
  PROPERTIES
    GENERATED TRUE
)

target_link_libraries(luatex-miktex-static
  PUBLIC
    ${app_dll_name}
    ${core_dll_name}
    ${kpsemu_dll_name}
)

###############################################################################
## luatex-luasocket-static
###############################################################################

set(luasocket_sources
  source/luasocket/src/auxiliar.c
  source/luasocket/src/auxiliar.h
  source/luasocket/src/buffer.c
  source/luasocket/src/buffer.h
  source/luasocket/src/except.c
  source/luasocket/src/except.h
  source/luasocket/src/inet.c
  source/luasocket/src/inet.h
  source/luasocket/src/io.c
  source/luasocket/src/io.h
  source/luasocket/src/lua_preload.c
  source/luasocket/src/luasocket.c
  source/luasocket/src/luasocket.h
  source/luasocket/src/mime.c
  source/luasocket/src/mime.h
  source/luasocket/src/options.c
  source/luasocket/src/options.h
  source/luasocket/src/select.c
  source/luasocket/src/select.h
  source/luasocket/src/serial.c
  source/luasocket/src/socket.c
  source/luasocket/src/socket.h
  source/luasocket/src/tcp.c
  source/luasocket/src/tcp.h
  source/luasocket/src/timeout.c
  source/luasocket/src/timeout.h
  source/luasocket/src/udp.c
  source/luasocket/src/udp.h
  source/luasocket/src/usocket.h
)

add_library(luatex-luasocket-static STATIC ${luasocket_sources})

set_property(TARGET luatex-luasocket-static PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})

target_link_libraries(luatex-luasocket-static
  PUBLIC
    ${lua_lib_name}
)

###############################################################################
## luatex-luamisc-static
###############################################################################

set(luamisc_sources
  source/luafilesystem/src/lfs.c
  source/luafilesystem/src/lfs.h
  source/luamd5/luamd5.h
  source/luamd5/md5.c
  source/luamd5/md5_lua.c
  source/luamd5/md5lib.c
  source/luapeg/lpeg.c
  source/luapeg/lpeg.h
  source/luaprofiler/clocks.c
  source/luaprofiler/clocks.h
  source/luaprofiler/core_profiler.c
  source/luaprofiler/core_profiler.h
  source/luaprofiler/function_meter.c
  source/luaprofiler/function_meter.h
  source/luaprofiler/lua50_profiler.c
  source/luaprofiler/luaprofiler.h
  source/luaprofiler/stack.c
  source/luaprofiler/stack.h
  source/luazip/src/luazip.c
  source/luazip/src/luazip.h
  source/luazlib/lgzip.c
  source/luazlib/lzlib.c
  source/slnunicode/slnunico.c
)

add_library(luatex-luamisc-static STATIC ${luamisc_sources})

set_property(TARGET luatex-luamisc-static PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})

target_link_libraries(luatex-luamisc-static
  PUBLIC
    ${core_dll_name}
    ${lua_lib_name}
    ${zlib_dll_name}
    ${zzip_dll_name}
)

if(MIKTEX_NATIVE_WINDOWS)
  target_link_libraries(luatex-luamisc-static
    PUBLIC
      ${unxemu_dll_name}
  )
endif()

###############################################################################
## luatex-unilib-static
###############################################################################

set(unilib_sources
  source/unilib/ArabicForms.c
  source/unilib/alphabet.c
  source/unilib/char.c
  source/unilib/chardata.h
  source/unilib/charset.h
  source/unilib/cjk.c
  source/unilib/combiners.h
  source/unilib/gwwiconv.c
  source/unilib/gwwiconv.h
  source/unilib/ucharmap.c
  source/unilib/unialt.c
  source/unilib/unibasics.h
  source/unilib/usprintf.c
  source/unilib/ustring.c
  source/unilib/ustring.h
  source/unilib/utype.c
  source/unilib/utype.h
)

add_library(luatex-unilib-static STATIC ${unilib_sources})

set_property(TARGET luatex-unilib-static PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})

target_include_directories(luatex-unilib-static
  PUBLIC
    source/unilib
)

target_link_libraries(luatex-unilib-static
  PUBLIC
    ${core_dll_name}
    ${kpsemu_dll_name}
    ${w2cemu_dll_name}
)

###############################################################################
## luatex-luafontforge-static
###############################################################################

configure_file(
  ff-config.h.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/ff-config.h
)

set(luafontforge_sources
  source/luafontloader/fontforge/fontforge/PfEd.h
  source/luafontloader/fontforge/fontforge/autohint.c
  source/luafontloader/fontforge/fontforge/baseviews.h
  source/luafontloader/fontforge/fontforge/clipnoui.c
  source/luafontloader/fontforge/fontforge/configure-pfaedit.h
  source/luafontloader/fontforge/fontforge/cvundoes.c
  source/luafontloader/fontforge/fontforge/dumppfa.c
  source/luafontloader/fontforge/fontforge/edgelist.h
  source/luafontloader/fontforge/fontforge/edgelist2.h
  source/luafontloader/fontforge/fontforge/encoding.c
  source/luafontloader/fontforge/fontforge/encoding.h
  source/luafontloader/fontforge/fontforge/featurefile.c
  source/luafontloader/fontforge/fontforge/fontforgevw.h
  source/luafontloader/fontforge/fontforge/fontviewbase.c
  source/luafontloader/fontforge/fontforge/fvcomposit.c
  source/luafontloader/fontforge/fontforge/fvfonts.c
  source/luafontloader/fontforge/fontforge/lookups.c
  source/luafontloader/fontforge/fontforge/lookups.h
  source/luafontloader/fontforge/fontforge/macbinary.c
  source/luafontloader/fontforge/fontforge/macenc.c
  source/luafontloader/fontforge/fontforge/mathconstants.c
  source/luafontloader/fontforge/fontforge/memory.c
  source/luafontloader/fontforge/fontforge/mm.c
  source/luafontloader/fontforge/fontforge/mm.h
  source/luafontloader/fontforge/fontforge/namelist.c
  source/luafontloader/fontforge/fontforge/noprefs.c
  source/luafontloader/fontforge/fontforge/nouiutil.c
  source/luafontloader/fontforge/fontforge/parsepfa.c
  source/luafontloader/fontforge/fontforge/parsettf.c
  source/luafontloader/fontforge/fontforge/parsettfatt.c
  source/luafontloader/fontforge/fontforge/pfaedit.h
  source/luafontloader/fontforge/fontforge/plugins.h
  source/luafontloader/fontforge/fontforge/psfont.h
  source/luafontloader/fontforge/fontforge/psread.c
  source/luafontloader/fontforge/fontforge/pua.c
  source/luafontloader/fontforge/fontforge/python.c
  source/luafontloader/fontforge/fontforge/scripting.h
  source/luafontloader/fontforge/fontforge/sd.h
  source/luafontloader/fontforge/fontforge/sfd1.c
  source/luafontloader/fontforge/fontforge/sfd1.h
  source/luafontloader/fontforge/fontforge/splinechar.c
  source/luafontloader/fontforge/fontforge/splinefill.c
  source/luafontloader/fontforge/fontforge/splinefont.c
  source/luafontloader/fontforge/fontforge/splinefont.h
  source/luafontloader/fontforge/fontforge/splineorder2.c
  source/luafontloader/fontforge/fontforge/splineoverlap.c
  source/luafontloader/fontforge/fontforge/splinerefigure.c
  source/luafontloader/fontforge/fontforge/splinesave.c
  source/luafontloader/fontforge/fontforge/splinesaveafm.c
  source/luafontloader/fontforge/fontforge/splinestroke.c
  source/luafontloader/fontforge/fontforge/splineutil.c
  source/luafontloader/fontforge/fontforge/splineutil2.c
  source/luafontloader/fontforge/fontforge/start.c
  source/luafontloader/fontforge/fontforge/stemdb.c
  source/luafontloader/fontforge/fontforge/stemdb.h
  source/luafontloader/fontforge/fontforge/tottf.c
  source/luafontloader/fontforge/fontforge/tottfgpos.c
  source/luafontloader/fontforge/fontforge/ttf.h
  source/luafontloader/fontforge/fontforge/ttfspecial.c
  source/luafontloader/fontforge/fontforge/uiinterface.h
  source/luafontloader/fontforge/fontforge/unicoderange.h
  source/luafontloader/fontforge/gutils/fsys.c
  source/luafontloader/fontforge/inc/basics.h
  source/luafontloader/fontforge/inc/gfile.h
  source/luafontloader/fontforge/inc/gimage.h
  source/luafontloader/fontforge/inc/intl.h
  source/luafontloader/src/ffdummies.c
  source/luafontloader/src/ffdummies.h
  source/luafontloader/src/luafflib.c
)

add_library(luatex-luafontforge-static STATIC ${luafontforge_sources})

set_property(TARGET luatex-luafontforge-static PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})

target_compile_definitions(luatex-luafontforge-static
  PRIVATE
    -DFONTFORGE_CONFIG_NO_WINDOWING_UI=1
    -DLUA_FF_LIB=1
    -DNODYNAMIC=1
    -DUSE_OUR_MEMORY=1
    -DX_DISPLAY_MISSING=1
    -D_NO_FREETYPE=1
    -D_NO_LIBUNINAMESLIST=1
    -D_NO_PYTHON=1
)
  
target_include_directories(luatex-luafontforge-static
  PRIVATE
    source/luafontloader/fontforge/fontforge
    source/luafontloader/fontforge/inc
)

target_link_libraries(luatex-luafontforge-static
  PUBLIC
    ${core_dll_name}
    ${kpsemu_dll_name}
    ${lua_lib_name}
    ${w2cemu_dll_name}
    luatex-unilib-static
)

###############################################################################
## luatex-static
###############################################################################

set(luatexlib_cwebs
  source/dvi/dvigen.w
  source/font/dofont.w
  source/font/luafont.w
  source/font/mapfile.w
  source/font/pkin.w
  source/font/sfnt.w
  source/font/subfont.w
  source/font/texfont.w
  source/font/tfmofm.w
  source/font/tounicode.w
  source/font/tt_glyf.w
  source/font/tt_table.w
  source/font/vfovf.w
  source/font/vfpacket.w
  source/font/writecff.w
  source/font/writeenc.w
  source/font/writefont.w
  source/font/writet1.w
  source/font/writet3.w
  source/font/writettf.w
  source/font/writetype0.w
  source/font/writetype2.w
  source/image/writeimg.w
  source/image/writejbig2.w
  source/image/writejp2.w
  source/image/writejpg.w
  source/image/writepng.w
  source/lang/hnjalloc.w
  source/lang/hyphen.w
  source/lang/texlang.w
  source/lua/luainit.w
  source/lua/luanode.w
  source/lua/luastuff.w
  source/lua/luatoken.w
  source/lua/texluac.w
  source/pdf/pdfaction.w
  source/pdf/pdfannot.w
  source/pdf/pdfcolorstack.w
  source/pdf/pdfdest.w
  source/pdf/pdffont.w
  source/pdf/pdfgen.w
  source/pdf/pdfglyph.w
  source/pdf/pdfimage.w
  source/pdf/pdflink.w
  source/pdf/pdflistout.w
  source/pdf/pdfliteral.w
  source/pdf/pdfobj.w
  source/pdf/pdfoutline.w
  source/pdf/pdfpage.w
  source/pdf/pdfpagetree.w
  source/pdf/pdfrule.w
  source/pdf/pdfsaverestore.w
  source/pdf/pdfsetmatrix.w
  source/pdf/pdfshipout.w
  source/pdf/pdftables.w
  source/pdf/pdfthread.w
  source/pdf/pdfxform.w
  source/tex/align.w
  source/tex/arithmetic.w
  source/tex/buildpage.w
  source/tex/commands.w
  source/tex/conditional.w
  source/tex/directions.w
  source/tex/dumpdata.w
  source/tex/equivalents.w
  source/tex/errors.w
  source/tex/expand.w
  source/tex/extensions.w
  source/tex/filename.w
  source/tex/inputstack.w
  source/tex/linebreak.w
  source/tex/mainbody.w
  source/tex/maincontrol.w
  source/tex/mathcodes.w
  source/tex/memoryword.w
  source/tex/mlist.w
  source/tex/nesting.w
  source/tex/packaging.w
  source/tex/postlinebreak.w
  source/tex/primitive.w
  source/tex/printing.w
  source/tex/scanning.w
  source/tex/stringpool.w
  source/tex/texdeffont.w
  source/tex/texfileio.w
  source/tex/texmath.w
  source/tex/texnodes.w
  source/tex/textcodes.w
  source/tex/textoken.w
  source/utils/avlstuff.w
  source/utils/managed-sa.w
  source/utils/unistring.w
  source/utils/utils.w
)

set(luatexlib_ccwebs
  source/image/pdftoepdf.w
)

foreach(cweb ${luatexlib_cwebs})
  get_filename_component(fn ${cweb} NAME_WE)
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/${fn}.c
    COMMAND
      ctangle ${CMAKE_CURRENT_SOURCE_DIR}/${cweb}
    WORKING_DIRECTORY
      ${CMAKE_CURRENT_BINARY_DIR}
    MAIN_DEPENDENCY
      ${cweb}
    DEPENDS
      ctangle
      ${CMAKE_CURRENT_SOURCE_DIR}/${cweb}
    VERBATIM
  )
  set(luatexlib_cweb_sources ${luatexlib_cweb_sources}
    ${CMAKE_CURRENT_BINARY_DIR}/${fn}.c
  )
endforeach()

foreach(ccweb ${luatexlib_ccwebs})
  get_filename_component(fn ${ccweb} NAME_WE)
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/${fn}.cc
    COMMAND
      ctangle ${CMAKE_CURRENT_SOURCE_DIR}/${ccweb} - ${CMAKE_CURRENT_BINARY_DIR}/${fn}.cc
    WORKING_DIRECTORY
      ${CMAKE_CURRENT_BINARY_DIR}
    MAIN_DEPENDENCY
      ${ccweb}
    DEPENDS
      ctangle
      ${CMAKE_CURRENT_SOURCE_DIR}/${ccweb}
    VERBATIM
  )
  set(luatexlib_cweb_sources ${luatexlib_cweb_sources}
    ${CMAKE_CURRENT_BINARY_DIR}/${fn}.cc
  )
endforeach()

set_source_files_properties(
  ${luatexlib_cweb_sources}
  PROPERTIES
    GENERATED TRUE
)

set(luatexlib_sources
  ${luatexlib_cweb_sources}
  ${CMAKE_SOURCE_DIR}/${MIKTEX_REL_MP_DIR}/source/lmplib.c
  ${CMAKE_SOURCE_DIR}/${MIKTEX_REL_SYNCTEX_DIR}/synctex-common.h
  ${CMAKE_SOURCE_DIR}/${MIKTEX_REL_SYNCTEX_DIR}/synctex-luatex.h
  ${CMAKE_SOURCE_DIR}/${MIKTEX_REL_SYNCTEX_DIR}/synctex.c
  ${CMAKE_SOURCE_DIR}/${MIKTEX_REL_SYNCTEX_DIR}/synctex.h
  source/dvi/dvigen.h
  source/font/luatexfont.h
  source/font/mapfile.h
  source/font/sfnt.h
  source/font/texfont.h
  source/font/tt_glyf.h
  source/font/tt_table.h
  source/font/writecff.h
  source/font/writettf.h
  source/image/epdf.h
  source/image/image.h
  source/image/pdftoepdf.h
  source/image/writeimg.h
  source/image/writejbig2.h
  source/image/writejp2.h
  source/image/writejpg.h
  source/image/writepng.h
  source/lang/hnjalloc.h
  source/lang/hyphen.h
  source/lang/texlang.h
  source/lua/lcallbacklib.c
  source/lua/lepdflib.cc
  source/lua/lfontlib.c
  source/lua/limglib.c
  source/lua/liolibext.c
  source/lua/lkpselib.c
  source/lua/llanglib.c
  source/lua/llfslibext.c
  source/lua/llualib.c
  source/lua/lnewtokenlib.c
  source/lua/lnodelib.c
  source/lua/loslibext.c
  source/lua/lpdflib.c
  source/lua/lpdfscannerlib.cc
  source/lua/lstatslib.c
  source/lua/lstrlibext.c
  source/lua/ltexiolib.c
  source/lua/ltexlib.c
  source/lua/luatex-api.h
  source/luatex.h
  source/pdf/pdfaction.h
  source/pdf/pdfannot.h
  source/pdf/pdfcolorstack.h
  source/pdf/pdfdest.h
  source/pdf/pdffont.h
  source/pdf/pdfgen.h
  source/pdf/pdfglyph.h
  source/pdf/pdfimage.h
  source/pdf/pdflink.h
  source/pdf/pdflistout.h
  source/pdf/pdfliteral.h
  source/pdf/pdfobj.h
  source/pdf/pdfoutline.h
  source/pdf/pdfpage.h
  source/pdf/pdfpagetree.h
  source/pdf/pdfrule.h
  source/pdf/pdfsaverestore.h
  source/pdf/pdfsetmatrix.h
  source/pdf/pdfshipout.h
  source/pdf/pdftables.h
  source/pdf/pdfthread.h
  source/pdf/pdftypes.h
  source/pdf/pdfxform.h
  source/tex/align.h
  source/tex/arithmetic.h
  source/tex/buildpage.h
  source/tex/commands.h
  source/tex/conditional.h
  source/tex/directions.h
  source/tex/dumpdata.h
  source/tex/equivalents.h
  source/tex/errors.h
  source/tex/expand.h
  source/tex/extensions.h
  source/tex/filename.h
  source/tex/inputstack.h
  source/tex/linebreak.h
  source/tex/mainbody.h
  source/tex/maincontrol.h
  source/tex/mathcodes.h
  source/tex/memoryword.h
  source/tex/mlist.h
  source/tex/nesting.h
  source/tex/packaging.h
  source/tex/postlinebreak.h
  source/tex/primitive.h
  source/tex/printing.h
  source/tex/scanning.h
  source/tex/stringpool.h
  source/tex/texdeffont.h
  source/tex/texfileio.h
  source/tex/texmath.h
  source/tex/texnodes.h
  source/tex/textcodes.h
  source/tex/textoken.h
  source/utils/avl.c
  source/utils/avl.h
  source/utils/avlstuff.h
  source/utils/managed-sa.h
  source/utils/unistring.h
  source/utils/utils.h
)

add_library(luatex-static STATIC ${luatexlib_sources})

set_property(TARGET luatex-static PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})

target_link_libraries(luatex-static
  PUBLIC
    ${core_dll_name}
    ${kpsemu_dll_name}
    ${lua_lib_name}
    ${mp_lib_name}
    ${png_dll_name}
    ${poppler_lib_name}
    ${w2cemu_dll_name}
    ${zlib_dll_name}
    luatex-luamisc-static
    luatex-luasocket-static
    luatex-luafontforge-static
)

###############################################################################
## luatex-program
###############################################################################

set(luatex_program_sources
  source/luatex.c
  source/luatex.h
  source/luatex_svnversion.h
  luatex-version.h
)

if(MIKTEX_NATIVE_WINDOWS)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/luatex.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/luatex.rc
    )
  list(APPEND ${luatex_program_sources}_sources
    ${CMAKE_CURRENT_BINARY_DIR}/luatex.rc
  )
endif()

if(MIKTEX_NATIVE_WINDOWS)
  add_library(${luatex_program_dll_name} SHARED ${luatex_program_sources})
  set_property(TARGET ${luatex_program_dll_name} PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})
endif()

set(libs
  ${app_dll_name}
  ${cairo_dll_name}
  ${core_dll_name}
  ${jpeg_dll_name}
  ${kpsemu_dll_name}
  ${lua_lib_name}
  ${md5_dll_name}
  ${mp_lib_name}
  ${pixman_lib_name}
  ${png_dll_name}
  ${poppler_lib_name}
  ${zzip_dll_name}
  ${w2cemu_dll_name}
  ${zlib_dll_name}

  luatex-luafontforge-static
  luatex-luamisc-static
  luatex-luasocket-static
  luatex-unilib-static

  luatex-static

  luatex-miktex-static
)

if(MIKTEX_NATIVE_WINDOWS)
  list(APPEND libs
    ${getopt_dll_name}
    ${unxemu_dll_name}
    ${utf8wrap_dll_name}
    ws2_32.lib
    wsock32.lib
  )
endif()

if(MIKTEX_NATIVE_WINDOWS)
  target_link_libraries(${luatex_program_dll_name} ${libs})
  rebase(${luatex_program_dll_name})
  install(TARGETS ${luatex_program_dll_name} DESTINATION "${MIKTEX_BINARY_DESTINATION_DIR}")
  set(program_libs ${luatex_program_dll_name})
else()
  set(program_libs ${libs})
endif()

###############################################################################
## luatex
###############################################################################

if(MIKTEX_NATIVE_WINDOWS)
  add_executable(${MIKTEX_PREFIX}luatex ${MIKTEX_LIBRARY_WRAPPER})
else()
  add_executable(${MIKTEX_PREFIX}luatex ${luatex_program_sources} ${MIKTEX_LIBRARY_WRAPPER})
endif()

set_property(TARGET ${MIKTEX_PREFIX}luatex PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})

target_link_libraries(${MIKTEX_PREFIX}luatex
  ${app_dll_name}
  ${core_dll_name}
  ${program_libs}
)

merge_trustinfo_manifest(${MIKTEX_PREFIX}luatex asInvoker)
merge_compatibility_manifest(${MIKTEX_PREFIX}luatex)

install(TARGETS ${MIKTEX_PREFIX}luatex DESTINATION "${MIKTEX_BINARY_DESTINATION_DIR}")

###############################################################################
## runtexlua
###############################################################################

add_executable(runtexlua ${luatex_program_sources} runtexlua.cpp)

set_property(TARGET runtexlua PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})

target_link_libraries(runtexlua
  ${app_dll_name}
  ${core_dll_name}
  ${program_libs}
)

merge_trustinfo_manifest(runtexlua asInvoker)
merge_compatibility_manifest(runtexlua)

install(TARGETS runtexlua DESTINATION "${MIKTEX_INTERNAL_BINARY_DIR}")

###############################################################################
## runmtxrun
###############################################################################

if(WITH_CONTEXT_SUPPORT)
  add_executable(runmtxrun ${luatex_program_sources} runmtxrun.cpp)
  set_property(TARGET runmtxrun PROPERTY FOLDER ${MIKTEX_CURRENT_FOLDER})
  target_link_libraries(runmtxrun
    ${app_dll_name}
    ${core_dll_name}
    ${program_libs}
  )
  merge_trustinfo_manifest(runmtxrun asInvoker)
  merge_compatibility_manifest(runmtxrun)
  install(TARGETS runmtxrun DESTINATION "${MIKTEX_INTERNAL_BINARY_DIR}")
endif()
