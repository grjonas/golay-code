#include "dependencies.hpp"
#include "binary.hpp"
#include "golay.hpp"

// User Scenarios:
// 1. Scenario 1:
//     * user, upon given a vector length, provides a vector of that size
//     (vector elements sould be part of finite field).
//     * Vector is encoded.
//     * encoded vector is shown
//     * vector is sent through channel
//     * received vector is shown
//     * where and how many errors happen are shown
//     * vector is decoded
//     * decoded vector is shown
// 2. Scenario 2:
//     * user writes text (can be from multiple lines)
//     * text is divided into required length vectors of F_q elements
//     * every vector is sent through the channel and shown
//     * every vector is encoded, and then sent through the channel and shown
// 3. Scenario 3:
//     * user provided a picture (bmp 24 bit format).
//     * program show the picture
//     * picture is divided into vectors
//     * sends picture through channel and then shows it.
//     * encoded picture, then sends it through channel and then shows it.
//  Additionally, in scenarios 2 and 3, everything (text and picture) should be constantly shown in:
//     * it's starting state
//     * in it's state without encoding
//     * in it's state with encoding
//  There is helpful information, that we assume isn't sent through the channel.
//  Here is what that means:
//  ```
//      Pirma, jei reikia papildyti duomenų srautą (pavyzdžiui, nuliais)
//      iki reikiamo ilgio (kad būtų galima suskaidyti reikiamo ilgio vektoriais).
//      Tokiu atveju dekodavus kai kada gali būti neaišku, kiek buvo papildyta,
//      t. y. kiek reikia pašalinti. Kad to išvengtume, informaciją apie tai, kiek buvo papildyta,
//      laikykime tarnybine ir jos neiškraipykime.
//      Antra, jei iškraipoma paveiksliukų antraštėse esanti informacija,
//      tai gali būti, kad tų paveiksliukų išvis nepavyks parodyti.
//      Todėl paveiksliukų antraštėse esančią informaciją irgi laikykime tarnybine
//      ir jos neiškraipykime.
//  ```

// Programuotojo požiūriu turėtų būti realizuoti tokie moduliai (klasės):
//     (Jei q nėra pirminis) Baigtinis kūnas Fq, veiksmai su jo elementais: sudėtis, daugyba ir t.t.
//     (Jei reikia) Veiksmai su matricomis, sudarytomis iš baigtinio kūno Fq elementų.
//     (Jei reikia) Veiksmai su polinomais virš baigtinio kūno Fq.
//     Kodavimas kodu C.
//     Siuntimas kanalu.
//     Dekodavimas, naudojant nurodytą dekodavimo algoritmą iš duotos literatūros
//     (dėmesio! Turi būti realizuotas būtent nurodytas dekodavimo algoritmas iš nurodytos literatūros!).
//     (Jei reikia) Teksto (paveiksliuko) skaidymas reikiamo ilgio vektoriais iš kūno Fq elementų.
//     Vektorių iš kūno Fq elementų sujungimas į vieną tekstą (paveiksliuką).

// TODO: check if double is high enough precision for error rate.
// using Settings = struct
// {
//     int finite_field_size; // q in F_q
//     double error_rate; // 0 <= q_e <= 1
// };

#define MESSAGE_LENGTH 12
#define LINE_SIZE 256


void discard_line()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool read_line(char* buffer, size_t size)
{
    if (fgets(buffer, size, stdin) == NULL)
    {
        return false;
    }

    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
    }
    else
    {
        discard_line();
    }

    return true;
}

bool read_binary_word(size_t length, BinaryWord& word)
{
    assert(word.size() == length);

    char line[LINE_SIZE];

    if (!read_line(line, sizeof(line)))
    {
        return false;
    }

    size_t true_length = strlen(line);
    size_t found_bits = 0;

    for (size_t i = 0; i < true_length; ++i)
    {
        char c = line[i];
        if (c == '0')
        {
            word[found_bits] = 0;
            ++found_bits;
        }
        else if (c == '1')
        {
            word[found_bits] = 1;
            ++found_bits;
        }
        else if (c == ' ' || c == '\t')
        {
        }
        else
        {
            return false;
        }
    }

    return found_bits == 12;
}

bool read_error_rate(double& error_rate)
{
    // error_rate = 0.1;
    // return true;

    int result = scanf("%lf", &error_rate);
    discard_line();
    if (result == 1 && 0.0 <= error_rate && error_rate <= 1.0)
    {
        return true;
    }

    printf("Error rate has to be a real number between 0.0 and 1.0.\n");
    return false;
}

void report_errors(BinaryWord& before, BinaryWord& after)
{
    assert(before.size() == after.size());

    size_t length = before.size();
    for (size_t i = 0; i < length; ++i)
    {
        if (before[i] != after[i])
        {
            printf("Error in index %ld, switched from a '%s' to a '%s'\n",
                    i, before[i] ? "1" : "0", after[i] ? "1" : "0");
        }
    }
}

void edit_received_word(BinaryWord& received)
{
    printf("Type a valid index to switch the bit, anything else to finish.\n");

    while (true)
    {
        printf("Position: ");

        long int index = 0;
        if (scanf("%ld", &index) != 1
                || index < 0
                || (size_t) index >= received.size())
        {
            discard_line();
            break;
        }
        discard_line();

        bool before = received[index];
        bool after  = !received[index];

        received[index] = !received[index];
        printf("Changed bit in index %ld from a '%s' to a '%s'\n",
                index, before ? "1" : "0", after ? "1" : "0");

    }

    // printf("New word: ");
    // print_binary_word(received);
}

bool scenario_one()
{
    BinaryWord initial_word(12, false);
    double p_e = 0.0;

    printf("Enter a binary vector of length 12 (example, \"010101111111\"), spaces and tabs are allowed:\n");
    if (!read_binary_word(12, initial_word))
    {
        printf("Failed to read word of 12 bits.\n");
        return false;
    }
    assert(initial_word.size() == 12);

    printf("Enter a channel error rate:\n");
    if (!read_error_rate(p_e))
    {
        return false;
    }

    // ================================================================================
    // Encoding
    // ================================================================================
    BinaryWord encoded_word = golay::encode_word(initial_word);
    printf("Encoded word: ");
    print_binary_word(encoded_word);

    // ================================================================================
    // Passing through channel
    // ================================================================================
    BinarySymmetricChannel channel(p_e);
    BinaryWord received_word = channel.send_elements(encoded_word);
    printf("Receving word: ");
    print_binary_word(received_word);

    char answer[LINE_SIZE];
    printf("Edit the received word before decoding? (y\\n)\n");
    if (read_line(answer, sizeof(answer)) && (answer[0] == 'y' || answer[1] == 'n'))
    {
        edit_received_word(received_word);
        printf("Received word after editing: ");
        print_binary_word(received_word);
    }
    report_errors(encoded_word, received_word);
    
    // ================================================================================
    // Decoding
    // ================================================================================
    std::optional<BinaryWord> decoded_word_optional = golay::decode_word(received_word);
    if (!decoded_word_optional.has_value())
    {
        printf("Failed to decode\n");
        return false;
    }
    BinaryWord decoded_word = decoded_word_optional.value();

    printf("Decoded word:\n");
    print_binary_word(decoded_word);

    printf(decoded_word == initial_word ? "Success!\n" : "Failure!\n");

    return true;
    // scenario_one_logic(initial_word, p_e);
}

bool testing_scenario(BinaryWord initial_word, double p_e)
{
    // ================================================================================
    // Receiving input
    // ================================================================================
    RandomNumberGenerator random_number_generator(0, 1);
    std::cout << random_number_generator.generate() << std::endl;

    // BinaryWord initial_word =
    //     { 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0 };
    assert(initial_word.size() == 12);

    // ================================================================================
    // Encoding
    // ================================================================================
    BinaryWord encoded_word = golay::encode_word(initial_word);

    // ================================================================================
    // Passing through channel
    // ================================================================================
    BinarySymmetricChannel channel(p_e);
    BinaryWord received_word = channel.send_elements(encoded_word);

    
    // ================================================================================
    // Decoding
    // ================================================================================
    std::optional<BinaryWord> decoded_word_optional = golay::decode_word(received_word);
    if (!decoded_word_optional.has_value())
    {
        return false;
    }
    BinaryWord decoded_word = decoded_word_optional.value();
    
    // ================================================================================
    // Showing output
    // ================================================================================
    print_binary_word(initial_word);
    print_binary_word(decoded_word);

    return true;
}
int main()
{
    return scenario_one() ? 0 : 1;
}
