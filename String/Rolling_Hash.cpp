//
// Created by OtsuKotsu on 2020/04/16.
//

/**
 * RollingHash
 *      func:
 *          constructor: makes hash table of string
 *          slice: get the hash of substr [begin, begin+length)
 *      description:
 *          rolling hash.
 *          mod 1^61-1.
 *          radix is random.
 *
 */
class rollingHash {
public:
    using U64 = unsigned long long int;
private:
    const U64 MOD = (1UL<<61) - 1;
    U64 BASE;
    std::vector<U64> POW_TABLE;
    std::vector<U64> HASH_TABLE;
    void MakeRandomBase() {
        std::random_device rnd;
        std::mt19937 mt(rnd());
        std::uniform_int_distribution<> rand(131, 1000000000);
        BASE = rand(mt);
        POW_TABLE[0] = 1UL;
        for(int i = 0; i < POW_TABLE.size()-1; ++i) POW_TABLE[i+1] = CalcMOD(Multiplication(POW_TABLE[i], BASE));
    }
    U64 Multiplication(U64 p, U64 q) {
        U64 p1 = p>>31, p2 = p & ((1UL<<31)-1),
                q1 = q>>31, q2 = q & ((1UL<<31)-1),
                m = p2*q1 + q2*p1,
                m1 = m>>30, m2 = m & ((1UL<<30)-1);
        return p1*q1*2 + m1 + (m2<<31) + p2*q2;
    }
    U64 CalcMOD(U64 p) {
        U64 p1 = p>>61, p2 = p & MOD;
        return p1+p2 - (p1+p2>=MOD ? MOD : 0);
    }
public:
    rollingHash(const string &s): HASH_TABLE(s.size()+1), POW_TABLE(s.size()+1) {
        MakeRandomBase();
        for(int i = 0; i < s.size(); ++i) {
            HASH_TABLE[i+1] = CalcMOD(Multiplication(HASH_TABLE[i], BASE) + s[i]);
        }
    }
    U64 slice(int begin, int length) {
        return CalcMOD(HASH_TABLE[begin+length]+MOD*7 - Multiplication(HASH_TABLE[begin], POW_TABLE[length]));
    }
};
