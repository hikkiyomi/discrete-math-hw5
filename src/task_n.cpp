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

map<string, vector<string>> countries_default = {
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

map<string, vector<pair<string, int>>> countries = {
    {"Portugal", {{"Spain", 624}}},
    {"Spain", {{"Portugal", 624}, {"Andorra", 615}, {"France", 1276}}},
    {"Andorra", {{"Spain", 615}, {"France", 861}}},
    {"Monaco", {{"France", 958}}},
    {"France", {{"Spain", 1276}, {"Andorra", 861}, {"Monaco", 958}, {"Italy", 1420}, {"Switzerland", 571}, {"Luxembourg", 373}, {"Belgium", 312}, {"Germany", 1054}}},
    {"Luxembourg", {{"France", 373}, {"Belgium", 204}, {"Germany", 740}}},
    {"Belgium", {{"France", 312}, {"Luxembourg", 204}, {"Netherlands", 210}, {"Germany", 757}}},
    {"Netherlands", {{"Belgium", 210}, {"Germany", 656}}},
    {"Germany", {{"Denmark", 439}, {"Netherlands", 656}, {"Luxembourg", 740}, {"Switzerland", 955}, {"Austria", 681}, {"Czechia", 350}, {"Poland", 574}, {"Belgium", 757}, {"France", 1054}}},
    {"Denmark", {{"Germany", 439}}},
    {"Switzerland", {{"Germany", 955}, {"France", 571}, {"Liechtenstein", 231}, {"Austria", 840}, {"Italy", 924}}},
    {"Liechtenstein", {{"Switzerland", 231}, {"Austria", 650}}},
    {"Italy", {{"Switzerland", 924}, {"France", 1420}, {"Austria", 1122}, {"Slovenia", 753}, {"San-Marino", 313}, {"Vatican", 5}}},
    {"Vatican", {{"Italy", 5}}},
    {"San-Marino", {{"Italy", 313}}},
    {"Slovenia", {{"Austria", 384}, {"Italy", 753}, {"Croatia", 140}, {"Hungary", 462}}},
    {"Austria", {{"Germany", 681}, {"Czechia", 334}, {"Slovakia", 80}, {"Hungary", 243}, {"Slovenia", 384}, {"Italy", 1122}, {"Liechtenstein", 650}, {"Switzerland", 840}}},
    {"Czechia", {{"Germany", 350}, {"Poland", 637}, {"Slovakia", 329}, {"Austria", 334}}},
    {"Croatia", {{"Slovenia", 140}, {"Hungary", 300}, {"Serbia", 393}, {"Bosnia", 400}, {"Montenegro", 713}}},
    {"Bosnia", {{"Croatia", 400}, {"Serbia", 292}, {"Montenegro", 230}}},
    {"Montenegro", {{"Croatia", 713}, {"Bosnia", 230}, {"Serbia", 456}, {"Albania", 160}}},
    {"Albania", {{"Montenegro", 160}, {"Serbia", 456}, {"Macedonia", 333}, {"Greece", 856}}},
    {"Greece", {{"Albania", 856}, {"Macedonia", 696}, {"Bulgaria", 793}, {"Turkey", 1546}}},
    {"Turkey", {{"Bulgaria", 1000}, {"Greece", 1546}}},
    {"Macedonia", {{"Bulgaria", 242}, {"Serbia", 432}, {"Albania", 333}, {"Greece", 696}}},
    {"Bulgaria", {{"Turkey", 1000}, {"Greece", 793}, {"Macedonia", 242}, {"Serbia", 400}, {"Romania", 383}}},
    {"Serbia", {{"Hungary", 380}, {"Romania", 596}, {"Bulgaria", 400}, {"Macedonia", 432}, {"Albania", 456}, {"Montenegro", 456}, {"Bosnia", 292}, {"Croatia", 393}}},
    {"Romania", {{"Moldova", 490}, {"Ukraine", 919}, {"Bulgaria", 771}, {"Serbia", 596}, {"Hungary", 837}}},
    {"Hungary", {{"Romania", 837}, {"Serbia", 380}, {"Croatia", 300}, {"Slovenia", 462}, {"Austria", 243}, {"Slovakia", 201}, {"Ukraine", 1116}}},
    {"Slovakia", {{"Poland", 661}, {"Ukraine", 1326}, {"Hungary", 201}, {"Austria", 80}, {"Czechia", 329}}},
    {"Poland", {{"Lithuania", 523}, {"Belarus", 553}, {"Ukraine", 816}, {"Slovakia", 661}, {"Czechia", 637}, {"Germany", 574}, {"Russia", 1260}}},
    {"Moldova", {{"Romania", 490}, {"Ukraine", 470}}},
    {"Ukraine", {{"Moldova", 470}, {"Romania", 919}, {"Hungary", 1116}, {"Slovakia", 1326}, {"Poland", 816}, {"Belarus", 528}, {"Russia", 862}}},
    {"Belarus", {{"Russia", 714}, {"Ukraine", 528}, {"Poland", 553}, {"Lithuania", 183}, {"Latvia", 480}}},
    {"Lithuania", {{"Belarus", 183}, {"Poland", 523}, {"Latvia", 295}, {"Russia", 943}}},
    {"Latvia", {{"Lithuania", 295}, {"Estonia", 309}, {"Belarus", 480}, {"Russia", 920}}},
    {"Estonia", {{"Latvia", 309}, {"Russia", 1025}}},
    {"Russia", {{"Estonia", 1025}, {"Latvia", 920}, {"Lithuania", 943}, {"Poland", 1260}, {"Belarus", 714}, {"Ukraine", 862}, {"Finland", 1088}, {"Norway", 2100}}},
    {"Finland", {{"Russia", 1088}, {"Sweden", 524}, {"Norway", 1020}}},
    {"Norway", {{"Russia", 2100}, {"Sweden", 522}, {"Finland", 1020}}},
    {"Sweden", {{"Norway", 522}, {"Finland", 524}}}
};

int n = sz(countries);
vector<vector<int>> adjacency_matrix(n, vector<int>(n, INF));
vector<vector<int>> adjacency_list(n);

map<string, int> country_number;
map<int, string> number_country;
int free_number = 0;

/**
 * @brief 
 * Disjoint Set Union Structure
 * Used for Kruskal's algorithm
 * With two heuristics:
 * - Size heuristic
 * - Parent heuristic
 */
class DSU {
public:
    DSU(int _n) { // init vertices
        n = _n;
        parent.resize(n);
        sze.resize(n);

        for (int i = 0; i < n; ++i) {
            Make(i);
        }
    }

    void Make(int v) { // init vertex
        parent[v] = v;
        sze[v] = 1;
    }

    int Find(int v) { // find_parent with heuristic
        return v == parent[v] ? v : parent[v] = Find(parent[v]);
    }

    bool Unite(int a, int b) {
        a = Find(a);
        b = Find(b);

        if (a != b) { // if they do not belong to the same component, then unite
            if (sze[a] < sze[b]) { // size heuristic
                swap(a, b);
            }

            parent[b] = a;
            sze[a] += sze[b];

            return true;
        }

        return false;
    }
private:
    int n;
    vector<int> parent;
    vector<int> sze;
};

struct Edge { // structure of edge. That's it.
    int from;
    int to;
    int weight;

    Edge(int _from, int _to, int _weight)
        : from(_from)
        , to(_to)
        , weight(_weight)
    {}

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

/**
 * @brief 
 * Solution of item N using Kruskal's algorithm
 * @return vector<pair<int, int>> (for item O)
 */
vector<Edge> TaskN() {
    cout << "Task N starting...\n\n";

    vector<Edge> edges;

    for (const auto& [country, neighbors] : countries) { // just adding edges
        for (const auto& [neighbor, weight] : neighbors) {
            edges.emplace_back(country_number[country], country_number[neighbor], weight);
        }
    }

    // Kruskal's algorithm is based on greedy algorithm
    // We sort edges by their weight in ascending order
    // And start taking them
    // If the edge does not create a cycle, it is ok. We should take it.

    sort(edges.begin(), edges.end());

    int total_weight = 0;
    vector<Edge> mst;
    DSU dsu(n); // init DSU

    for (auto [u, v, w] : edges) {
        if (dsu.Unite(u, v)) { // if the edge (u, v) does not create a cycle, then we take it
            total_weight += w;
            mst.emplace_back(u, v, w);
        }
    }

    cout << "Total weight: " << total_weight << "\n";

    for (auto [u, v, w] : mst) {
        cout << number_country[u] << " <-> " << number_country[v] << "\n";
    }

    cout << "\n---------------\n";

    return mst;
}

signed main() {
    fastio;

    // ! ---------------------------------
    // ! DO NOT TOUCH

    for (int i = 0; i < n; ++i) { // init adjacency_matrix
        adjacency_matrix[i][i] = 0;
    }

    for (const auto& [country, neighbors] : countries_default) { // init country-number and number-country relation
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

    TaskN();

    // -----------------
    
    return 0;
}
