//
// Created by OtsuKotsu on 2020/08/05.
//
// Mo's algorithm
// 区間クエリの並べ替え順の保持と区間の伸縮による遷移、実行結果の格納を担う。区間は半開区間[l,r)

struct mo_s_algorithm {
    using i32 = int_fast32_t;
    i32 sqrt_n;
    i32 idx_l, idx_r;
    std::vector<i32> query_order;
    std::vector<std::pair<i32, i32>> &query_ranges;

    explicit mo_s_algorithm(std::vector<std::pair<i32, i32>> &query_ranges):
            query_ranges(query_ranges), query_order(query_ranges.size()), sqrt_n((i32)std::sqrt(query_ranges.size())), idx_l(0), idx_r(0)
    {
        for(i32 i = 0; i < query_ranges.size(); ++i) query_order[i] = i;
        std::sort(query_order.begin(), query_order.end(), [&](i32 a, i32 b) {
            if(query_ranges[a].first / sqrt_n != query_ranges[b].first / sqrt_n) return query_ranges[a].first < query_ranges[b].first;
            return query_ranges[a].second < query_ranges[b].second;
        });
    }

    template<class T = i32>
    void execute(vector<T> &answer_container, T initial_ans) {
        T current_answer = initial_ans;
        if(answer_container.size() != query_ranges.size()) printf("error! size is not same!");
        for(auto &id : query_order) {
            while(idx_l > query_ranges[id].first) --idx_l, add(idx_l, current_answer);
            while(idx_r < query_ranges[id].second) add(idx_r, current_answer), ++idx_r;
            while(idx_l < query_ranges[id].first) del(idx_l, current_answer), ++idx_l;
            while(idx_r > query_ranges[id].second) --idx_r, del(idx_r, current_answer);
            answer_container[id] = current_answer;
        }
    }

    template<class T = i32>
    inline void add(i32 idx, T &target);

    template<class T = i32>
    inline void del(i32 idx, T &target);
};

template<class T>
void mo_s_algorithm::add(i32 idx, T &target) {
    /* rewrite here */
}

template<class T>
void mo_s_algorithm::del(i32 idx, T &target) {
    /* rewrite here */
}
