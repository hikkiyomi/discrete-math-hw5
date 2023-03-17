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

/**
 * @brief 
 * Solution of task E using... kind of dynamic programming, I guess.
 */
void TaskE() {
    cout << "Task E starting...\n\n";

    vector<vector<int>> cliques;

    for (int i = 0; i < n; ++i) { // firstly we have cliques of size 1.
        cliques.push_back({i});
    }

    for (int clique_size = 2;; ++clique_size) {
        vector<vector<int>> n_cliques;

        for (const auto& cur : cliques) { // iterate through all the available cliques
            for (int v = 0; v < n; ++v) { // try to add a new vertex to this clique
                bool can_be_added = true;

                for (auto u : cur) {
                    if (v == u || adjacency_matrix[v][u] == INF) { // if vertex v is already in clique or it does not make up a complete graph, then we cannot add it
                        can_be_added = false;
                        break;
                    }
                }

                if (can_be_added) { // add the vertex v if we can
                    n_cliques.push_back({cur.begin(), cur.end()});
                    n_cliques.back().push_back(v);
                    sort(n_cliques.back().begin(), n_cliques.back().end()); // do not mind it
                }
            }
        }

        sort(n_cliques.begin(), n_cliques.end()); // do not mind it
        n_cliques.erase(unique(n_cliques.begin(), n_cliques.end()), n_cliques.end()); // do not mind it

        if (n_cliques.empty()) { // if we cannot make up cliques of bigger size, then we stop
            break;
        }

        cliques = n_cliques; // update current cliques with cliques of bigger size
    }

    cout << "Max clique size: " << sz(cliques[0]) << "\n";

    for (const auto& clique : cliques) {
        cout << "{";

        for (auto x : clique) {
            cout << number_country[x] << ",";
        }

        cout << "}\n";
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

    TaskE();

    // -----------------
    
    return 0;
}
