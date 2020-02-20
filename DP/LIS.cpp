#include <bits/stdc++.h>
using namespace std;

/*最長増加or減少部分列----------*/
/*第一引数 : 対象となるvector
  第二引数 : true:狭義 false:広義  デフォルト:false
  第三引数 : true:増加 false:減少  デフォルト:true
*/
template<class T>
std::vector<T> lis(const std::vector<T> &a, bool strict=0, bool UporNot=1) {
    std::vector<T> lis;
    if(UporNot) {
        for(auto &p : a) {
            typename std::vector<T>::iterator iter;
            if(strict) iter = std::lower_bound(lis.begin(), lis.end(), p);
            else iter = std::upper_bound(lis.begin(), lis.end(), p);
            if(lis.end()==iter) lis.emplace_back(p);
            else *iter = p;
        }
    }else {
        vector<T> rev = a;
        reverse(rev.begin(), rev.end());
        for(auto &p : rev) {
            typename std::vector<T>::iterator iter;
            if(strict) iter = std::lower_bound(lis.begin(), lis.end(), p);
            else iter = std::upper_bound(lis.begin(), lis.end(), p);
            if(lis.end()==iter) lis.emplace_back(p);
            else *iter = p;
        }
    }
    return lis;
}

/*------------------------------*/