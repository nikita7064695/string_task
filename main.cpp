#include <iostream>
#include <optional>
#include <string>
#include <string_view>
using namespace std;

optional<uint64_t>parseNumber(string_view strofnumbers) {
    bool hasDigit = false;
    uint64_t result{0};
    while(!strofnumbers.empty() && isspace(strofnumbers[0])) {
        strofnumbers.remove_prefix(1);
    }
    while (isdigit(strofnumbers[0])) {
        result = result * 10 + (strofnumbers[0] - '0');
        strofnumbers.remove_prefix(1);
        hasDigit = true;
    }
    if (!hasDigit)
        return nullopt;
    while(!strofnumbers.empty() && isspace(strofnumbers[0])) {
        strofnumbers.remove_prefix(1);
    }
    if (!strofnumbers.empty())
        return nullopt;
    if (result < 1 || result > 64) {
        return nullopt;
    }
    return result;
}

int main() {
    string input_stroka;
    std::cin >> input_stroka;
    string_view strofnumbers {input_stroka};
    size_t start {0};
    size_t pos;
    uint64_t bitmask{0};
    while (start < strofnumbers.length()) {
        pos = strofnumbers.find(',', start);
        if (pos == string::npos) {
            string_view last_chislo = strofnumbers.substr(start);
            auto optional_res = parseNumber(last_chislo);
            if (!optional_res.has_value())
                return 1;
            bitmask |= (1ULL << (optional_res.value() - 1));
            break;
        }else {
            string_view chislo = strofnumbers.substr(start, pos - start);
            auto optional_res = parseNumber(chislo);
            if (!optional_res.has_value())
                return 1;
            bitmask |= (1ULL << (optional_res.value() - 1));
            start = pos + 1;
        }
    }
    cout << bitmask;

    return 0;
}