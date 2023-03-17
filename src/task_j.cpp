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
    // {"Monaco", {"France"}},
    {"France", {"Spain", "Andorra", /* "Monaco", */ "Italy", "Switzerland", "Luxembourg", "Belgium", "Germany"}},
    {"Luxembourg", {"France", "Belgium", "Germany"}},
    {"Belgium", {"France", "Luxembourg", "Netherlands", "Germany"}},
    {"Netherlands", {"Belgium", "Germany"}},
    {"Germany", {/* "Denmark",  */"Netherlands", "Luxembourg", "Switzerland", "Austria", "Czechia", "Poland", "Belgium", "France"}},
    // {"Denmark", {"Germany"}},
    {"Switzerland", {"Germany", "France", "Liechtenstein", "Austria", "Italy"}},
    {"Liechtenstein", {"Switzerland", "Austria"}},
    {"Italy", {"Switzerland", "France", "Austria", "Slovenia", /* "San-Marino", "Vatican" */}},
    // {"Vatican", {"Italy"}},
    // {"San-Marino", {"Italy"}},
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

/**
 * @brief 
 * Solution of item J using brute force
 * with simple magical heuristics:
 * - Choosing starting and subsequent vertices randomly
 * - Sorting adjacent vertices by their degree
 * 
 * This function finds Hamiltonian path, so I had to delete some edges so the path exists.
 * After getting a path, I added some edges to get an answer to task J.
 */
void TaskJ() {
    cout << "Task J starting...\n\n";

    while (true) {
        // Init necessary arrays
        vector<bool> used(n, false);
        vector<int> way;
        vector<int> deg(n);

        for (int i = 0; i < n; ++i) { // Init degrees of vertices
            deg[i] = sz(adjacency_list[i]);
        }

        int cnt = 0;
        int v = rng() % n; // Randomly choosing starting vertex

        while (true) {
            ++cnt;
            way.push_back(v);
            used[v] = true;

            int min_deg = INF;
            vector<pair<int, int>> neighbors;

            for (auto to : adjacency_list[v]) {
                --deg[to];

                if (!used[to]) {
                    neighbors.push_back({deg[to], to});
                    ckmin(min_deg, deg[to]);
                }
            }

            if (sz(neighbors) == 0) { // If no neighbor is available, then we cannot continue the path
                break;
            }

            sort(neighbors.begin(), neighbors.end()); // Sort neighbors by ascending order of their degrees
            vector<int> go;

            for (int i = 0; i < sz(neighbors) && neighbors[i].first == min_deg; ++i) {
                go.push_back(neighbors[i].second);
            }

            v = go[rng() % sz(go)]; // Randomly choosing the next vertex of path
        }

        if (cnt == n) {
            for (auto i : way) {
                cout << number_country[i] << " ";
            }

            break;
        }
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

    TaskJ();

    // -----------------
    
    return 0;
}
