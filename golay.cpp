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
        UNREACHABLE;
    }

    BinaryWord encode_word(BinaryWord word)
    {
        return word * generative_matrix;
    }

    // Algorhitm 3.6.1 (IMLD for C_24)
    std::optional<BinaryWord> extended_decode_word(BinaryWord word)
    {
        // 1. Compute the syndrome s = wH.
        BinaryWord syndrome = word * extended_parity_check_matrix;
        BinaryWord zero_word =
            { false, false, false, false, false, false, false, false, false, false, false, false }

        // 2. If wt(s) <= 3, then u = [s, 0].
        if (weight(syndrome) <= 3)
        {
            return syndrome.push_back(zero_word);
        }

        // 3. If wt(s + b_i) <= 2 for some row b_i of B then u = [s + b_i, e_i].
        for (int i = 0; i < extended_matrix_B.get_row_number(); ++i)
        {
            BinaryWord syndrome_plus_row =
                add_binary_words(syndrome + extended_matrix_B.get_rows()[i]);

            if (weight(syndrome_plus_row) <= 2)
            {
                BinaryWord error_in_row = zero_word;
                error_in_row[i] = true;
                return syndrome_plus_row.push_back(error_in_row);
            }
        }

        // 4. Compute the second syndrome sB.
        BinaryWord second_syndrome = s * extended_matrix_B;

        // 5. If wt(sB) <= 3 then u = [0, sB].
        
        BinaryWord second_syndrome_times_B = second_syndrome * extended_matrix_B;
        if (weight(second_syndrome_times_B) <= 3)
        {
            return zero_word.push_back(second_syndrome_times_B);
        }

        // 6. If wt(sB + b_i) <= 2 for some row b_i of B then u = [e_i, sB + b_i].
        for (int i = 0; i < extended_matrix_B.get_row_number(); ++i)
        {
            BinaryWord sum =
                add_binary_words(second_syndrome_times_B + extended_matrix_B.get_rows()[i]);

            if (weight(sum) <= 2)
            {
                BinaryWord error_in_row = zero_word;
                error_in_row[i] = true;
                return error_in_row.push_back(sum);
            }
        }

        // 7. If u is not yet determined, then request retransmission.
        return std::nullopt;
    }

    std::optional<BinaryWord> decode_word(BinaryWord word)
    {
        BinaryWord new_word = word;
        if (weight(word) % 2 == 0)
        {
            new_word.push_back(false);
        }
        else
        {
            new_word.push_back(true);
        }

        std::optional<BinaryWord> decoded_word_optional = extended_decode_word(word);
        if (decoded_word_optional == std::nullopt)
        {
            return std::nullopt;
        }
        BinaryWord decoded_word =  decoded_word_optional.value();

        return decoded_word.pop_back();
    }
}
