#pragma once

#include "dependencies.hpp"

using BinaryWord = std::vector<bool>;

void print_binary_word(const BinaryWord& binary_word);
size_t weight(const BinaryWord& word);
BinaryWord add_binary_words(const BinaryWord& word_a, const BinaryWord& word_b);
BinaryWord concat_words(const BinaryWord& word_a, const BinaryWord& word_b);

class BinaryMatrix
{
    public:
        BinaryMatrix(std::size_t row_number, std::size_t get_column_number);
        BinaryMatrix(std::initializer_list<std::initializer_list<bool>> values);
        BinaryMatrix& operator=(std::initializer_list<std::initializer_list<bool>> values);

        std::optional<BinaryMatrix> operator*(const BinaryMatrix& matrix_b);
        BinaryWord   operator*(const BinaryWord& word);
        std::optional<std::reference_wrapper<const BinaryWord>> operator[](std::size_t index) const;
        std::optional<std::reference_wrapper<BinaryWord>>       operator[](std::size_t index);

        std::vector<BinaryWord> get_rows();
        std::size_t get_row_number   () const;
        std::size_t get_column_number() const;

    private:
        std::vector<BinaryWord> body;
};

class BinarySymmetricChannel
{
    public:
        BinarySymmetricChannel(double error_rate);

        bool send_element(bool element);
        BinaryWord send_elements(BinaryWord elements);

    private:
        double error_rate;
        RandomNumberGenerator random_number_generator;
};
