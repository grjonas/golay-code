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
