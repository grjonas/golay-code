#include "binary.hpp"

void print_binary_word(BinaryWord binary_word)
{
    for (int i = 0; i < binary_word.size(); ++i)
    {
        if (binary_word.size() - 1 == i)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << binary_word[i] << " ";
        }
    }
}

// TODO: This is obviously innefficient, fix later
BinaryMatrix::BinaryMatrix(std::size_t row_number, std::size_t column_number)
{
    BinaryWord word{};

    for (int i = 0; i < column_number; ++i)
    {
        word.push_back(0);
    }

    for (int i = 0; i < row_number; ++i)
    {
        this->body.push_back(word);
    }
}

BinaryMatrix::BinaryMatrix(std::initializer_list<std::initializer_list<bool>> values)
{
    for (const auto& row : values)
    {
        this->body.push_back(row);
    }
}

BinaryMatrix& BinaryMatrix::operator=(std::initializer_list<std::initializer_list<bool>> values)
{
    BinaryMatrix new_matrix{values};
    (*this) = new_matrix;
    return *this;
}

std::optional<BinaryMatrix> BinaryMatrix::operator*(const BinaryMatrix& matrix_b)
{
    // ================================================================================
    // https://en.wikipedia.org/wiki/Matrix_multiplication
    // A [m * n] * B [n * p] = C [m * p]
    //
    // A = | a11, ..., a1n |
    //     | ..., ..., ... |
    //     | am1, ..., amn |
    //
    // B = | b11, ..., b1p |
    //     | ..., ..., ... |
    //     | bn1, ..., bnp |
    //
    // C = | a11, ..., a1p |
    //     | ..., ..., ... |
    //     | am1, ..., amp |
    // ================================================================================

    BinaryMatrix& matrix_a = (*this);
    std::size_t m   = matrix_a.get_row_number();
    std::size_t n_a = matrix_a.get_column_number();
    std::size_t n_b = matrix_b.get_row_number();
    std::size_t p   = matrix_b.get_column_number();

    if (n_a != n_b)
    {
        return std::nullopt;
    }

    std::size_t n = n_a;
    BinaryMatrix matrix_c(m, p);

    for (std::size_t i = 0; i < m; ++i)
    {
        for (std::size_t j = 0; j < p; ++j)
        {
            bool value = 0;
            for (std::size_t k = 0; k < n; ++k)
            {
                auto get_cell = [](BinaryMatrix& matrix, std::size_t x, std::size_t y)
                {
                    BinaryWord word = matrix[x];

                    if (word.size() <= y)
                    {
                        UNREACHABLE;
                    }

                    return word[y];
                };

                // value = matrix_a[i][k] + matrix_b[k][j];
                value = get_cell(matrix_a, i, k) + get_cell(matrix_b, k, j);
            }
            matrix_c[i][j] = value;
        }
    }

    return matrix_c;
}

// const BinaryWord& BinaryMatrix::operator[](std::size_t index) const
// {
//     if (this->get_row_number() <= index)
//     {
//         UNREACHABLE;
//     }
//
//     return this->body[index];
// }
//
// BinaryWord& BinaryMatrix::operator[](std::size_t index)
// {
//     if (this->get_row_number() <= index)
//     {
//         UNREACHABLE;
//     }
//
//     return this->body[index];
// }

BinarySymmetricChannel::BinarySymmetricChannel(double error_rate) :
    error_rate{error_rate},
    random_number_generator(0, 1)
{}

bool BinarySymmetricChannel::send_element(bool element)
{
    return random_number_generator.generate() < error_rate ? !element : element;
}

BinaryWord BinarySymmetricChannel::send_elements(BinaryWord elements)
{
    for (auto&& element : elements)
    {
        double random_number = random_number_generator.generate();
        // std::cout << random_number << " < " << error_rate << " == " << (random_number < error_rate) << std::endl;

        if (random_number < error_rate)
        {
            element = !element;
        }
    }

    return elements;
}
