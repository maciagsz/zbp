#include <zbp/poli_static/ifc/IOperation.hpp>
#include <zbp/poli_static/Hashing.hpp>

#include <functional>
#include <bitset>
#include <cmath>
#include <climits>

using namespace zbp::poli_static;

/**
 * ChatGPT-generated code
 */
int Hashing::execute_impl(int a, int b)
{
    // Używamy hashów standardowych jako bazowych komponentów
    std::hash<int> hasher;
    size_t h1 = hasher(a);
    size_t h2 = hasher(b);

    // Operacje bitowe na wynikach hashów
    size_t mixed = (h1 << 5) ^ (h2 >> 3) ^ (h1 >> 2) ^ (h2 << 7);

    // Zakoduj dane do bitsetów
    std::bitset<32> bits_a(static_cast<unsigned int>(a));
    std::bitset<32> bits_b(static_cast<unsigned int>(b));

    // XOR bitów i licz histogram jedynek
    std::bitset<32> combined = bits_a ^ bits_b;
    size_t ones = combined.count();

    // Skomplikowana transformacja: rotacja bitów i modyfikacja matematyczna
    size_t rotated = (mixed << (ones % 13)) | (mixed >> (32 - (ones % 13)));

    // Hashowanie z użyciem funkcji trygonometrycznej dla losowości
    double sine = std::sin(static_cast<double>(a ^ b));
    double log_mix = std::log(std::abs(sine) + 1.0);

    // Finalne mieszanie i konwersja do int
    size_t final_mix = static_cast<size_t>(rotated ^ static_cast<size_t>(log_mix * 1e6));

    // Ograniczenie do zakresu int
    return static_cast<int>(final_mix % INT_MAX);
}
