//
// Created by OtsuKotsu on 2020/06/26.
//
// 桁DPテンプレート
//
//      dpは-1埋め。
//      conditionはboolを持ったり、引数増やしてより多くの状態を持ったり、整数で状態管理したりする。
//      最後の桁にたどり着いた時の挙動と、次の桁に移るときの挙動を記述して用いる。
//
//      x以下の数について、上の桁から見る実装になっている。
//
//      細部は詰めること。

#include <bits/stdc++.h>

constexpr int Digit_MAX = 20000;
constexpr int num_of_state = 2;

uint_fast64_t dp[Digit_MAX][2][num_of_state];  // dp[digit][tight][condition]


uint_fast64_t rec(const std::string &x, int digit = 0, bool tight = true, int condition = 0) {
    if(digit == x.size()) {
        // rewrite here
        // decide the action where digit == x.size()
        // e.g.
        if(condition) return 1;
        else return 0;
    }

    uint_fast64_t &res = dp[digit][tight][condition];
    if(~res) return res;  // res is not -1 (null)  same as "res != -1"

    //  ||
    //  ||   res is null
    // \  /
    //  \/

    res = 0;
    int ub = (tight? x[digit] - '0' : 9);  // upper_bound of num of digit

    for(int i = 0; i <= ub; ++i) {
        // rewrite here
        // e.g.
        int next_condition = condition || (i==4) || (i == 9);

        res += rec(x, digit+1, tight && i == ub,
                   next_condition);
    }
    return res;
}



/*  https://atcoder.jp/contests/abc007/tasks/abc007_4  */
signed main(){
    using namespace std;

    cin.tie(nullptr);
    ios::sync_with_stdio(false);
//    cout << fixed << setprecision(15);

    int_fast64_t a,b; cin >> a >> b;

    memset(dp, -1, sizeof(dp));
    int_fast64_t u = rec(to_string(b));

    memset(dp, -1, sizeof(dp));
    int_fast64_t l = rec(to_string(a-1));

    cout << u - l << '\n';
}
