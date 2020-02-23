#include <bits/stdc++.h>
using namespace std;

/*-------------------------------------*/
//bit全探索
int main1(){
    int n; //全探索する集合の要素数
    for(int bit = 0; bit < (1<<n)-1; bit++){
        /*処理*/
    }
}

/*--------------------------------------*/

//bit部分集合の列挙による集合内探索。全探索でも使用可
int main2(){
    int A;  /*探索対象のbit集合*/ /*例-> (1<<2)| (1<<4) | (1<<7) で{2,4,7}を表す*/
    for(int bit = A;; bit = (bit-1) & A){
        /*処理*/

        if(!bit) break; /*break処理*/
    }
}

/*---------------------------------------*/

//{0,1,...,n-1}のn個の要素数のbit集合から要素数k個の部分集合のみ列挙して探索
//k = 0ではうまく動かないので例外処理が必要
int next_combination(int sub){
    int x = sub & -sub, y = sub + x;
    return(((sub & ~y) / x) >> 1) | y;
}

int main3(){
    int n;  int k;
    int bit = (1<<k)-1;
    for(; bit < (1<<n); bit = next_combination(bit)){
        /*処理*/
    }
}