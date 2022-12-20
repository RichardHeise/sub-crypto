#include "utils.hpp"

using namespace std;

char32_t utf8_to_utf32(char utf8)
{
    wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
    return conv.from_bytes(&utf8, &utf8 + 1)[0];
}

char utf32_to_utf8(char32_t utf32)
{
    wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
    return conv.to_bytes(utf32)[0];
}
