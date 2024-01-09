#include <set>

using ULL = unsigned long long;
typedef std::pair<std::pair<ULL, ULL>, std::pair<ULL, ULL>> pairOfIntPairs;

class PrimeNumbers
{
private:
    std::set<ULL> primeNums = { 2 };
    void generatePrimeNumbers(ULL max);
public:
    PrimeNumbers(ULL max);
    bool isPrime(ULL num);
    ULL getRandomValue();
};

class RSA
{
public:
    pairOfIntPairs generateKeys();
    ULL encrypt(ULL msg, std::pair<ULL, ULL> key);
    ULL decrypt(ULL eMsg, std::pair<ULL, ULL> privateKey);
};