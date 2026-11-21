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

bool testing_scenario(BinaryWord initial_word, double p_e);
bool scenario_one();

int main()
{
    return scenario_one() ? 0 : 1;
}

bool scenario_one()
{
    BinaryWord initial_word =
        { 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0 };
    double p_e = 0.1;

    printf("Enter a binary vector of length 12 (example, \"010101111111\"):\n");


    printf("Enter a channel error rate:\n");

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
