#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fastio ios_base::sync_with_stdio(false); cin.tie(0)
#define sz(v) (int)v.size()

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;

template<class T>
bool ckmin(T& a, const T& b) {
    if (a > b) {
        a = b;
        return true;
    }

    return false;
}

template<class T>
bool ckmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return true;
    }

    return false;
}

const ll INF = ll(2e9) + 100100, LINF = ll(1e18) + 100100;
const double EPS = 1e-12, PI = atan2(0.0, -1.0);
const signed MODS[] = {signed(1e9) + 7, signed(1e9) + 9, 998244353};
const signed PS[] = {117, 239, signed(1e5) + 3, 177013};
const signed N = 110, MAXLOG = 20;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

map<string, vector<string>> countries = {
    {"Portugal", {"Spain"}},
    {"Spain", {"Portugal", "Andorra", "France"}},
    {"Andorra", {"Spain", "France"}},
    {"Monaco", {"France"}},
    {"France", {"Spain", "Andorra", "Monaco", "Italy", "Switzerland", "Luxembourg", "Belgium", "Germany"}},
    {"Luxembourg", {"France", "Belgium", "Germany"}},
    {"Belgium", {"France", "Luxembourg", "Netherlands", "Germany"}},
    {"Netherlands", {"Belgium", "Germany"}},
    {"Germany", {"Denmark", "Netherlands", "Luxembourg", "Switzerland", "Austria", "Czechia", "Poland", "Belgium", "France"}},
    {"Denmark", {"Germany"}},
    {"Switzerland", {"Germany", "France", "Liechtenstein", "Austria", "Italy"}},
    {"Liechtenstein", {"Switzerland", "Austria"}},
    {"Italy", {"Switzerland", "France", "Austria", "Slovenia", "San-Marino", "Vatican"}},
    {"Vatican", {"Italy"}},
    {"San-Marino", {"Italy"}},
    {"Slovenia", {"Austria", "Italy", "Croatia", "Hungary"}},
    {"Austria", {"Germany", "Czechia", "Slovakia", "Hungary", "Slovenia", "Italy", "Liechtenstein", "Switzerland"}},
    {"Czechia", {"Germany", "Poland", "Slovakia", "Austria"}},
    {"Croatia", {"Slovenia", "Hungary", "Serbia", "Bosnia", "Montenegro"}},
    {"Bosnia", {"Croatia", "Serbia", "Montenegro"}},
    {"Montenegro", {"Croatia", "Bosnia", "Serbia", "Albania"}},
    {"Albania", {"Montenegro", "Serbia", "Macedonia", "Greece"}},
    {"Greece", {"Albania", "Macedonia", "Bulgaria", "Turkey"}},
    {"Turkey", {"Bulgaria", "Greece"}},
    {"Macedonia", {"Bulgaria", "Serbia", "Albania", "Greece"}},
    {"Bulgaria", {"Turkey", "Greece", "Macedonia", "Serbia", "Romania"}},
    {"Serbia", {"Hungary", "Romania", "Bulgaria", "Macedonia", "Albania", "Montenegro", "Bosnia", "Croatia"}},
    {"Romania", {"Moldova", "Ukraine", "Bulgaria", "Serbia", "Hungary"}},
    {"Hungary", {"Romania", "Serbia", "Croatia", "Slovenia", "Austria", "Slovakia", "Ukraine"}},
    {"Slovakia", {"Poland", "Ukraine", "Hungary", "Austria", "Czechia"}},
    {"Poland", {"Lithuania", "Belarus", "Ukraine", "Slovakia", "Czechia", "Germany", "Russia"}},
    {"Moldova", {"Romania", "Ukraine"}},
    {"Ukraine", {"Moldova", "Romania", "Hungary", "Slovakia", "Poland", "Belarus", "Russia"}},
    {"Belarus", {"Russia", "Ukraine", "Poland", "Lithuania", "Latvia"}},
    {"Lithuania", {"Belarus", "Poland", "Latvia", "Russia"}},
    {"Latvia", {"Lithuania", "Estonia", "Belarus", "Russia"}},
    {"Estonia", {"Latvia", "Russia"}},
    {"Russia", {"Estonia", "Latvia", "Lithuania", "Poland", "Belarus", "Ukraine", "Finland", "Norway"}},
    {"Finland", {"Russia", "Sweden", "Norway"}},
    {"Norway", {"Russia", "Sweden", "Finland"}},
    {"Sweden", {"Norway", "Finland"}}
};

int n = sz(countries);
vector<vector<int>> adjacency_matrix(n, vector<int>(n, INF));
vector<vector<int>> adjacency_list(n);

map<string, int> country_number;
map<int, string> number_country;
int free_number = 0;

int task_g_cnt = 0;
const int kTaskGLimit = 10000000;
vector<pair<int, int>> task_g_ans;

/**
 * @brief 
 * Sizes of matching depending on the value of kTaskGLimit
 * 
 * 1 - 19
 * 10 - 19
 * 100 - 19
 * 1000 - 19
 * 10000 - 19
 * 100000 - 19
 * 1000000 - 19
 * 10000000 - 19
 * 100000000 - 19
 */

/**
 * @brief
 * Brute force function for finding max matching for graph.
 * Uses greedy algorithm that is limited by some number that defines the number
 * Of considered matchings. Greedy algorithm is based on picking the edge that will
 * Ban as little as possible edges.
 * 
 * @param edges stores edges)
 * @param used is responsible for banning vertices (i.e. edges as well)
 * @param taken saves the current set of edges
 * @param i is used to iterate through the list of edges
 */
void FindMaxMatching(const vector<pair<int, int>>& edges, vector<int>& used, vector<pair<int, int>>& taken, int i) {
    if (i == sz(edges)) {
        ++task_g_cnt; // mark that we considered another matching

        if (sz(task_g_ans) < sz(taken)) { // update answer
            task_g_ans = taken;
        }

        return;
    }

    if (task_g_cnt > kTaskGLimit) { // if we reached the limit, exit
        return;
    }

    auto [u, v] = edges[i]; 

    // Case 1: We take this edge
    if (used[u] == 0 && used[v] == 0) {
        taken.push_back(edges[i]);
        ++used[u];
        ++used[v];

        FindMaxMatching(edges, used, taken, i + 1);

        --used[v];
        --used[u];
        taken.pop_back();
    }

    if (task_g_cnt > kTaskGLimit) { // if we reached the limit, exit
        return;
    }

    // Case 2: We do not take this edge
    FindMaxMatching(edges, used, taken, i + 1);
}

/**
 * @brief 
 * Solution of item G using brute force with greedy algorithm.
 * More info about algorithm is above (see description of FindMaxMatching function)
 */
void TaskG() {
    cout << "Task G starting...\n\n";

    vector<int> deg(n);
    
    for (int i = 0; i < n; ++i) {
        deg[i] = sz(adjacency_list[i]); // init list of degrees
    }

    vector<pair<int, int>> edges;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjacency_matrix[i][j] == 1) {
                edges.push_back({i, j}); // init list of edges
            }
        }
    }

    // Sort edges in the ascending order of the banned edges
    sort(edges.begin(), edges.end(), [&](const auto& a, const auto& b) {
        return deg[a.first] + deg[a.second] < deg[b.first] + deg[b.second];
    });

    // Init arrays for brute force
    vector<int> used(n, 0);
    vector<pair<int, int>> taken;

    FindMaxMatching(edges, used, taken, 0);

    cout << "Matching size: " << sz(task_g_ans) << "\n";

    for (auto [u, v] : task_g_ans) {
        cout << number_country[u] << " <-> " << number_country[v] << "\n";
    }
    
    cout << "\n---------------\n";
}

signed main() {
    fastio;

    // ! ---------------------------------
    // ! DO NOT TOUCH

    for (int i = 0; i < n; ++i) { // init adjacency_matrix
        adjacency_matrix[i][i] = 0;
    }

    for (const auto& [country, neighbors] : countries) { // init country-number and number-country relation
        if (!country_number.count(country)) {
            country_number[country] = free_number++;
            number_country[free_number - 1] = country;
        }

        for (const auto& go : neighbors) {
            if (!country_number.count(go)) {
                country_number[go] = free_number++;
                number_country[free_number - 1] = go;
            }

            // also initializing adjacency_matrix
            // and adjacency_list
            adjacency_matrix[country_number[country]][country_number[go]] = 1;
            adjacency_list[country_number[country]].push_back(country_number[go]);
        }
    }

    // ! DO NOT TOUCH
    // ! ---------------------------------

    // Launch tasks here:

    TaskG();

    // -----------------
    
    return 0;
}
