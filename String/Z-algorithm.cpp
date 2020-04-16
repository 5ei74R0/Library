//
// Created on 2020/04/16.
//

/**
 * Z-Algorithm.
 *
 * @param str:
 *      const &string
 * @return:
 *      std::vector<int>.
 *      -> size of "longest common prefix"(  str and str[i, end)  )
 */
std::vector<int> z_algorithm(const string &str) {
    std::vector<int> Z(str.size());
    Z[0] = str.size();
    int i = 1, j = 0;
    while(i < str.size()) {
        while(i + j < str.size() && str[j] == str[i+j]) ++j;
        Z[i] = j;
        if(j == 0) {
            ++i;
        }
        else {
            int k = 1;
            while(i+k < str.size() && k+Z[k] < j) {
                Z[i+k] = Z[k];
                ++k;
            }
            i += k;
            j -= k;
        }
    }
    return Z;
}
