#include "golay.hpp"

namespace golay
{
    static BinaryMatrix generative_matrix
    {
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 /* */, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0 /*, 1 */ },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 /* */, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 /*, 1 */ },
        { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 /* */, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 /*, 1 */ },
        { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 /* */, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0 /*, 1 */ },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 /* */, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1 /*, 1 */ },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 /* */, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1 /*, 1 */ },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 /* */, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1 /*, 1 */ },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 /* */, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0 /*, 1 */ },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 /* */, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0 /*, 1 */ },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 /* */, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0 /*, 1 */ },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 /* */, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1 /*, 1 */ },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 /* */, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 /*, 0 */ }
    };

    static BinaryMatrix extended_generative_matrix
    {
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 /* */, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 /* */, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 },
        { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 /* */, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1 },
        { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 /* */, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 /* */, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 /* */, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 /* */, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 /* */, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 /* */, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 /* */, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 /* */, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 /* */, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }
    };

    static BinaryMatrix extended_parity_check_matrix
    {
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 },
        { 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1 },
        { 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
        { 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
        { 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1 },
        { 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1 },
        { 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1 },
        { 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }
    };

    static BinaryMatrix extended_matrix_B
    {
        { 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 },
        { 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1 },
        { 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
        { 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
        { 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1 },
        { 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1 },
        { 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1 },
        { 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }
    };

    BinaryWord extended_encode_word(BinaryWord word)
    {
        return extended_generative_matrix * word;
    }

    BinaryWord encode_word(BinaryWord word)
    {
        return generative_matrix * word;
    }

    // Algorhitm 3.6.1 (IMLD for C_24)
    std::optional<BinaryWord> extended_get_error_word(BinaryWord word)
    {
        // 1. Compute the syndrome s = wH.
        BinaryWord syndrome = extended_parity_check_matrix * word;
        BinaryWord zero_word(12, false); // { false, false, false, false, false, false, false, false, false, false, false, false };

        // 2. If wt(s) <= 3, then u = [s, 0].
        if (weight(syndrome) <= 3)
        {
            return concat_words(syndrome, zero_word);
        }

        // 3. If wt(s + b_i) <= 2 for some row b_i of B then u = [s + b_i, e_i].
        for (int i = 0; i < extended_matrix_B.get_row_number(); ++i)
        {
            BinaryWord syndrome_plus_row =
                add_binary_words(syndrome, extended_matrix_B.get_rows()[i]);

            if (weight(syndrome_plus_row) <= 2)
            {
                BinaryWord error_in_row = zero_word;
                error_in_row[i] = true;
                return concat_words(syndrome_plus_row, error_in_row);
            }
        }

        // 4. Compute the second syndrome sB.
        BinaryWord second_syndrome = extended_matrix_B * syndrome;

        // 5. If wt(sB) <= 3 then u = [0, sB].
        if (weight(second_syndrome) <= 3)
        {
            return concat_words(zero_word, second_syndrome);
        }

        // 6. If wt(sB + b_i) <= 2 for some row b_i of B then u = [e_i, sB + b_i].
        for (int i = 0; i < extended_matrix_B.get_row_number(); ++i)
        {
            BinaryWord second_syndrome_plus_row =
                add_binary_words(second_syndrome, extended_matrix_B.get_rows()[i]);

            if (weight(second_syndrome_plus_row) <= 2)
            {
                BinaryWord error_in_row = zero_word;
                error_in_row[i] = true;
                return concat_words(error_in_row, second_syndrome_plus_row);
            }
        }

        // 7. If u is not yet determined, then request retransmission.
        return std::nullopt;
    }

    std::optional<BinaryWord> extended_decode_word(BinaryWord word)
    {
        std::optional<BinaryWord> error_word_optional = extended_get_error_word(word);
        if (!error_word_optional.has_value())
        {
            return std::nullopt;
        }
        BinaryWord error_word =  error_word_optional.value();

        return add_binary_words(word, error_word);
    }

    std::optional<BinaryWord> decode_word(BinaryWord word)
    {
        BinaryWord new_word = word;

        new_word.push_back(weight(word) % 2 == 0);

        std::optional<BinaryWord> decoded_word_optional = extended_decode_word(new_word);
        if (!decoded_word_optional.has_value())
        {
            return std::nullopt;
        }
        BinaryWord decoded_word =  decoded_word_optional.value();

        // TODO: Is this right?
        for (int i = 0; i < 12; ++i)
        {
            decoded_word.pop_back();
        }

        return decoded_word;
    }
}
