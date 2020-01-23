// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

#include <iostream>
#include <string.h>

#include "include/types.h"
#include "include/crc32c.h"
#include "include/utime.h"
#include "common/Clock.h"

#include "gtest/gtest.h"

#include "common/sctp_crc32.h"
#include "common/crc32c_intel_baseline.h"
#include "common/crc32c_aarch64.h"

TEST(Crcs, Hello) {
    std::cout << "This is a test!" << std::endl;
}
