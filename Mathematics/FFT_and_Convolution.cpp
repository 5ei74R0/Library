//
// Created by OtsuKotsu on 2020/06/21.
//
// FFT
// convolutionは整数列を返すときはstd::roundによって丸められる
//

#include <bits/stdc++.h>

long double Pi = std::acos(-1.0L);

std::vector<std::complex<long double>> rec_fft(std::vector<std::complex<long double>> f, bool inverse=false) {
    if(f.size() == 1) {
        return std::vector<std::complex<long double>>(1, f[0]);
    }
    int N = f.size();
    std::vector<std::complex<long double>> f_e, f_o, F_e, F_o, F(N);
    for(int i = 0; i < N; ++i) {
        if(i&1) f_o.push_back(f[i]);
        else f_e.push_back(f[i]);
    }
    F_e = rec_fft(f_e, inverse);
    F_o = rec_fft(f_o, inverse);

    std::complex<long double> w = 1, pow(std::cos(Pi/(N>>1)), std::sin(Pi/(N>>1)) * (inverse? 1 : -1));
    for(int i = 0; i < N/2; ++i, w *= pow) {
        F[i] = F_e[i] + w * F_o[i];
        F[i+N/2] = F_e[i] - w * F_o[i];
    }
    return F;
}

std::vector<std::complex<long double>> fft(std::vector<std::complex<long double>> f) {
    int p_of_2 = 1;
    while(f.size() > p_of_2) p_of_2 <<= 1;
    while(p_of_2 > f.size()) f.emplace_back(0, 0);
    return rec_fft(std::move(f));
}
std::vector<std::complex<long double>> fft_inv(std::vector<std::complex<long double>> f) {
    int p_of_2 = 1;
    while(f.size() > p_of_2) p_of_2 <<= 1;
    while(p_of_2 > f.size()) f.emplace_back(0, 0);
    std::vector<std::complex<long double>> ret = rec_fft(std::move(f), true);
    for(auto &val : ret) val /= (long double)(ret.size());
    return ret;
}

template<class T = int_fast32_t, class U, class V>
std::vector<T> convolution(std::vector<U> f, std::vector<V> g, bool Round = std::is_integral<T>::value) {
    int n = f.size() + g.size() - 1;
    int p_of_2 = 1;
    while(n > p_of_2) p_of_2 <<= 1;
    while(p_of_2 > f.size()) f.push_back(0);
    while(p_of_2 > g.size()) g.push_back(0);

    std::vector<std::complex<long double>> f_complex, g_complex, F, G, RES, res_complex;
    for(auto &val : f) f_complex.emplace_back(val, 0);
    for(auto &val : g) g_complex.emplace_back(val, 0);
    F = fft(f_complex), G = fft(g_complex);

    for(int i = 0; i < p_of_2; ++i) RES.push_back(F[i] * G[i]);
    res_complex = fft_inv(RES);
    std::vector<T> res(res_complex.size());
    for(int i = 0; i < res.size(); ++i) res[i] = (Round? std::round(res_complex[i].real()) : res_complex[i].real());
    return res;
}



/* Verify on https://atcoder.jp/contests/atc001/tasks/fft_c =========*/
signed main(){
    using namespace std;

    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    size_t n; cin >> n;
    vector<int_fast32_t> a(n), b(n);
    for(int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    auto ab = convolution(a, b);

    printf("0\n");
    for(int i = 0; i < n*2-1; ++i) printf("%d\n", (int)(ab[i]));

}
