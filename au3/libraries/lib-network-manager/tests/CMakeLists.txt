#  SPDX-License-Identifier: GPL-2.0-or-later
# [[
# Unit tests for the offline network manager stub
# ]]

add_unit_test(
   NAME
      lib-network-manager
   SOURCES
      OfflineNetworkManagerTest.cpp
   LIBRARIES
      lib-network-manager
)
