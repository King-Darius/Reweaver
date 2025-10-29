#[[
A library, that allows sending error reports to a Sentry server
using Exception and Message interfaces.
]]

set( TARGET lib-sentry-reporting )
set( TARGET_ROOT ${CMAKE_CURRENT_SOURCE_DIR} )

def_vars()

audacity_header_only_library( ${TARGET} "SentryHelper.h" "" "" "" )
