#pragma once
#define DEBUG_SHOW_LINE_WORKING std::cout << "\u001b[02m" << __FILE__ << ":" << __LINE__ << " I'm here" \
                                          << "\u001b[0m" << std::endl;
#include <random>
#include <iostream>
#include <string>

namespace Util
{
    inline double randd()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);

        return dis(gen);
    }

    inline double randi(int lower, int upper)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(lower, upper);

        return dis(gen);
    }

    namespace TColor
    {
        const std::string RESET = "\u001b[0m";

        const std::string BLACK = "\u001b[30m";
        const std::string RED = "\u001b[31m";
        const std::string GREEN = "\u001b[32m";
        const std::string YELLOW = "\u001b[33m";
        const std::string BLUE = "\u001b[34m";
        const std::string MAGENTA = "\u001b[35m";
        const std::string CYAN = "\u001b[36m";
        const std::string WHITE = "\u001b[37m";

        const std::string bgBLACK = "\u001b[40m";
        const std::string bgRED = "\u001b[41m";
        const std::string bgGREEN = "\u001b[42m";
        const std::string bgYELLOW = "\u001b[43m";
        const std::string bgBLUE = "\u001b[44m";
        const std::string bgMAGENTA = "\u001b[45m";
        const std::string bgCYAN = "\u001b[46m";
        const std::string bgWHITE = "\u001b[47m";

        const std::string BOLD = "\u001b[1m";
        const std::string UNDERLINE = "\u001b[4m";
        const std::string REVERSED = "\u001b[7m";
    } // namespace TColor
}

// Overload operator<< to print vectors!
inline std::ostream &operator<<(std::ostream &os, const std::vector<double> &input)
{
    for (auto const &i : input)
    {
        os << i << " ";
    }
    return os;
}

class StringStream
{
private:
    template <typename T>
    typename std::enable_if<
        false == std::is_convertible<T, std::string>::value,
        std::string>::type static toStr(T const &val)
    {
        return std::to_string(val);
    }

    static std::string toStr(std::string const &val)
    {
        return val;
    }

public:
    StringStream() = default;
    ~StringStream() = default;

    template <typename... Ts>
    static std::string stringify(Ts const &...vals)
    {
        std::string stringify_string;
        using unused = int[];

        (void)unused{0, (stringify_string += StringStream::toStr(vals), 0)...};

        return stringify_string;
    }
};