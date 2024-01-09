#include "RSA.hpp"

#include <random>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <utility>
#include <iostream>

std::tuple<ULL, ULL, ULL> extended_gcd(ULL a, ULL b)
{
    if (a == 0) {
        return std::make_tuple(b, 0, 1);
    }
 
    ULL gcd, x, y;
 
    // распаковываем возвращаемый функцией кортеж в переменные
    std::tie(gcd, x, y) = extended_gcd(b % a, a);
 
    return std::make_tuple(gcd, (y - (b/a) * x), x);
}

bool PrimeNumbers::isPrime(ULL num)
{
    for (ULL prime : primeNums) {
        if (prime >= num)
            break;

        if (num % prime == 0)
            return false;
    }
    return true;
}

void PrimeNumbers::generatePrimeNumbers(ULL max)
{
    primeNums = { 2 };
    for (ULL i = 3; i <= max; ++i)
        if (isPrime(i))
            primeNums.insert(i);
}

PrimeNumbers::PrimeNumbers(ULL max)
{
    generatePrimeNumbers(max);
}

ULL PrimeNumbers::getRandomValue()
{
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<std::size_t> distribution(0, primeNums.size() - 1);

    std::size_t idx = distribution(generator);

    auto it = primeNums.begin();
    std::advance(it, idx);

    return *it;
}

pairOfIntPairs RSA::generateKeys()
{
    PrimeNumbers primes(5000);
    ULL p = primes.getRandomValue();
    ULL q = primes.getRandomValue();
    ULL n = p * q;
    ULL phi = (p - 1) * (q - 1);
    std::cout << "p: " << p << " q: " << q << std::endl;
    std::cout << "phi: " << phi << std::endl;

    ULL e = 1;
    for (ULL i = 2; i < phi; ++i)
        if (phi % i != 0 && primes.isPrime(i)) {
            e = i;
            break;
        }
    
    std::tuple<ULL, long long, long long> tup = extended_gcd(phi, e);
    long long x = std::get<1>(tup), y = std::get<2>(tup);

    long long d1 = 0;
    if (e * x + phi * y == 1)
        d1 = x;
    else
        d1 = y;

    ULL d;
    if (d1 < 0)
        d = phi - std::abs(d1);
    else
        d = d1;

    if (d == e) {
        std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<std::size_t> distribution(0, 10);
        std::size_t coef = distribution(generator);
        d += coef * phi;
    }
    //int d = phi - std::abs(std::min(std::get<1>(tup), std::get<2>(tup)));
    return std::make_pair(std::make_pair(e, n), std::make_pair(d, n));
}

ULL RSA::encrypt(ULL msg, std::pair<ULL, ULL> key)
{
    ULL e = key.first;
    ULL n = key.second;
    if (msg >= n) {
        std::cout << "Too big message!";
        return 0;
    }

    ULL eMsg = msg;
    for (ULL i = 2; i <= e; ++i) {
        eMsg *= msg;
        eMsg %= n;
    }
    return eMsg;
}

ULL RSA::decrypt(ULL eMsg, std::pair<ULL, ULL> privateKey)
{
    ULL d = privateKey.first;
    ULL n = privateKey.second;
    ULL dMsg = eMsg;

    for (ULL i = 2; i <= d; ++i) {
        dMsg *= eMsg;
        dMsg %= n;
    }
    return dMsg;
}