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

// Main preamble for "Hello" frame, with incorrect checksum
// included computed checksum is tx_crc=82851162,
// official client returns rx_crc=4080661043
static __u8 IN_SITU_FAILURE[] = {
    0x01, // Tag: Hello
    0x01, // Segment Count: 1
    
    0x1c, 0x00, 0x00, 0x00, // Segment 1 length
    0x00, 0x00, // Segment 1 padding (none)
    
    // Segments 2-4, all empty
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    
    0x00, 0x00, // reserved bytes
    0x5a, 0x35, 0xf0, 0x04 // checksum
};

TEST(Crcs, Hello) {
    ASSERT_EQ(sizeof(IN_SITU_FAILURE), 32u);
    ASSERT_EQ(sizeof(IN_SITU_FAILURE) - sizeof(uint32_t), 28u);
}

TEST(Crcs, InSitu) {
    unsigned val = ceph_crc32c(0, (unsigned char *) IN_SITU_FAILURE, sizeof(IN_SITU_FAILURE) - 4);
    ASSERT_EQ(4080661043u, val);
}