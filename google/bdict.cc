// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "bdict.h"

// static
bool hunspell::BDict::Verify(const char* bdict_data, size_t bdict_length) {
  if (bdict_length <= sizeof(hunspell::BDict::Header))
    return false;

  const BDict::Header* header =
      reinterpret_cast<const hunspell::BDict::Header*>(bdict_data);
  if (header->signature != hunspell::BDict::SIGNATURE ||
      header->major_version > hunspell::BDict::MAJOR_VERSION ||
      header->dic_offset > bdict_length)
    return false;

  // Get the affix header, make sure there is enough room for it.
  if (header->aff_offset + sizeof(hunspell::BDict::AffHeader) > bdict_length)
    return false;

  // Make sure there is enough room for the affix group count dword.
  const hunspell::BDict::AffHeader* aff_header =
      reinterpret_cast<const hunspell::BDict::AffHeader*>(
          &bdict_data[header->aff_offset]);
  if (aff_header->affix_group_offset + sizeof(uint32) > bdict_length)
    return false;

  return true;
}
