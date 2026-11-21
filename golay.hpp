#pragma once

#include "dependencies.hpp"
#include "binary.hpp"

namespace golay
{
    BinaryWord encode_word(BinaryWord word);
    std::optional<BinaryWord> decode_word(BinaryWord word);
}
