#pragma once

#include "dependencies.hpp"

using BinaryWord = std::vector<bool>;

void print_binary_word(BinaryWord binary_word);

class BinaryMatrix
{
    public:
        BinaryMatrix(std::initializer_list<std::initializer_list<bool>> values);
        BinaryMatrix& operator=(std::initializer_list<std::initializer_list<bool>> values);

        BinaryMatrix& operator*(const BinaryMatrix& matrix_a);

        std::size_t get_row_number();
        std::size_t get_column_number();

    private:
        std::vector<std::vector<bool>> body;
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
