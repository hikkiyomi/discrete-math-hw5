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

map<string, vector<string>> countries_for_task_k = {
    {"Portugal", {"Spain"}},
    {"Spain", {"Portugal", "Andorra", /* "France" */}},
    {"Andorra", {"Spain", "France"}},
    {"Monaco", {/* "France" */}},
    {"France", {/* "Spain", */ "Andorra", /* "Monaco", */ "Italy", "Switzerland", "Luxembourg", "Belgium", "Germany"}},
    {"Luxembourg", {"France", "Belgium", /* "Germany" */}},
    {"Belgium", {"France", "Luxembourg", "Netherlands", "Germany"}},
    {"Netherlands", {"Belgium", "Germany"}},
    {"Germany", {/* "Denmark", */ "Netherlands", /* "Luxembourg", */ /* "Switzerland", */ "Austria", "Czechia", "Poland", "Belgium", "France"}},
    {"Denmark", {/* "Germany" */}},
    {"Switzerland", {/* "Germany", */ "France", "Liechtenstein", "Austria", "Italy"}},
    {"Liechtenstein", {"Switzerland", "Austria"}},
    {"Italy", {"Switzerland", "France", "Austria", "Slovenia", /* "San-Marino", "Vatican" */}},
    {"Vatican", {/* "Italy" */}},
    {"San-Marino", {/* "Italy" */}},
    {"Slovenia", {"Austria", "Italy", "Croatia", "Hungary"}},
    {"Austria", {"Germany", "Czechia", "Slovakia", "Hungary", "Slovenia", "Italy", "Liechtenstein", "Switzerland"}},
    {"Czechia", {"Germany", "Poland", "Slovakia", "Austria"}},
    {"Croatia", {"Slovenia", "Hungary", "Serbia", /* "Bosnia", */ "Montenegro"}},
    {"Bosnia", {/* "Croatia", */ "Serbia", "Montenegro"}},
    {"Montenegro", {"Croatia", "Bosnia", "Serbia", "Albania"}},
    {"Albania", {"Montenegro", "Serbia", "Macedonia", "Greece"}},
    {"Greece", {"Albania", "Macedonia", "Bulgaria", "Turkey"}},
    {"Turkey", {"Bulgaria", "Greece"}},
    {"Macedonia", {"Bulgaria", "Serbia", "Albania", "Greece"}},
    {"Bulgaria", {"Turkey", "Greece", "Macedonia", "Serbia", /* "Romania" */}},
    {"Serbia", {"Hungary", "Romania", "Bulgaria", "Macedonia", "Albania", "Montenegro", "Bosnia", "Croatia"}},
    {"Romania", {"Moldova", "Ukraine", /* "Bulgaria", */ "Serbia", "Hungary"}},
    {"Hungary", {"Romania", "Serbia", "Croatia", "Slovenia", "Austria", "Slovakia", /* "Ukraine" */}},
    {"Slovakia", {"Poland", "Ukraine", "Hungary", "Austria", "Czechia"}},
    {"Poland", {"Lithuania", /* "Belarus", */ "Ukraine", "Slovakia", "Czechia", "Germany", "Russia"}},
    {"Moldova", {"Romania", "Ukraine"}},
    {"Ukraine", {"Moldova", "Romania", /* "Hungary", */ "Slovakia", "Poland", "Belarus", "Russia"}},
    {"Belarus", {"Russia", "Ukraine", /* "Poland", */ "Lithuania", "Latvia"}},
    {"Lithuania", {"Belarus", "Poland", "Latvia", "Russia"}},
    {"Latvia", {"Lithuania", "Estonia", "Belarus", "Russia"}},
    {"Estonia", {"Latvia", "Russia"}},
    {"Russia", {"Estonia", "Latvia", "Lithuania", "Poland", "Belarus", "Ukraine", "Finland", "Norway"}},
    {"Finland", {"Russia", "Sweden", /* "Norway" */}},
    {"Norway", {"Russia", "Sweden", /* "Finland" */}},
    {"Sweden", {"Norway", "Finland"}}
};

map<string, vector<string>> countries_for_task_j = {
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
 * Solution of item B using Floyd-Warshall Algorithm,
 * that is searching the shortest path lengths between
 * each pair of vertices.
 */
void TaskB() {
    cout << "Task B starting...\n\n";

    // Floyd-Warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adjacency_matrix[i][k] < INF && adjacency_matrix[k][j] < INF) {
                    ckmin(adjacency_matrix[i][j], adjacency_matrix[i][k] + adjacency_matrix[k][j]);
                }
            }
        }
    }

    vector<int> eccentricity(n, 0);

    // eccentricity[v] = max dist(v, u)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ckmax(eccentricity[i], adjacency_matrix[i][j]);
        }
    }

    // radius(G) = min eccentricity[v] forall v in G
    int radius = *min_element(eccentricity.begin(), eccentricity.end());
    // diameter(G) = max eccentricity[v] forall v in G
    int diameter = *max_element(eccentricity.begin(), eccentricity.end());
    vector<string> center;

    // center(G) = {v in G | eccentricity[v] = radius(G)}
    for (int i = 0; i < n; ++i) {
        if (eccentricity[i] == radius) {
            center.push_back(number_country[i]);
        }
    }

    cout << "Radius: " << radius << "\n";
    cout << "Diameter: " << diameter << "\n";
    cout << "Center: { ";
    
    for (const auto& country : center) {
        cout << country << " ";
    }

    cout << "}";
    cout << "\n---------------\n";
}

/**
 * @brief 
 * Brute force through all vertices and ban colors
 * That the current vertex cannot have
 * 
 * Choose the color randomly
 * 
 * @param color is used to indicate the color of vertices
 * @param v is the current vertex
 * @param colors is the total amount of available colors
 * @return true if the required coloring is found
 * @return false if the coloring is bad
 */
bool FindVertexColoring(vector<int>& color, int v, int colors) {
    set<int> banned;

    for (auto to : adjacency_list[v]) { // banning colors
        if (color[to] != -1) {
            banned.insert(color[to]);
        }
    }

    if (sz(banned) == colors) { // no available colors
        return false;
    }

    while (true) {
        color[v] = rng() % colors; // choosing color randomly

        if (!banned.count(color[v])) {
            break;
        }
    }

    for (auto to : adjacency_list[v]) {
        if (color[to] != -1) {
            continue;
        }

        if (!FindVertexColoring(color, to, colors)) { // if we need to backtrack
            return false;
        }
    }

    return true;
}

/**
 * @brief 
 * Solution of item C using brute force (FindVertexColoring function)
 * No heuristics needed
 */
void TaskC() {
    cout << "Task C starting...\n\n";

    // Init color array and amount of attempts of coloring vertices
    vector<int> color;
    int tries = 10000;

    for (int colors = 2; colors <= n; ++colors) {
        bool ok = false;

        for (int attempt = 0; attempt < tries; ++attempt) {
            color.assign(n, -1); // Re-init the color array, so we can make another attempt

            if (FindVertexColoring(color, rng() % n, colors)) { // If we found a good coloring, then exit
                ok = true;

                break;
            }
        }

        if (ok) {
            break;
        }
    }

    set<int> colors;

    for (auto i : color) {
        colors.insert(i);
    }

    cout << "Colors used: " << sz(colors) << "\n";

    for (int i = 0; i < n; ++i) {
        cout << number_country[i] << " " << color[i] << "\n";
    }

    cout << "\n---------------\n";
}

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

vector<int> task_f_ans; // saves answer

/**
 * @brief 
 * Brute force through all possible variants. That's it.
 * 
 * @param degs is responsible for the list of vertices
 * @param used marks banned vertices
 * @param taken is responsible for saving current stable set
 * @param i is just an index that goes through list of vertices
 */
void FindMaxStableSet(const vector<pair<int, int>>& degs, vector<int>& used, vector<int>& taken, int i) {
    if (i == n) {
        if (sz(taken) > sz(task_f_ans)) { // updating answer
            task_f_ans = taken;
        }

        return;
    }

    int v = degs[i].second; // current vertex

    // Case 1: We do not take this vertex
    FindMaxStableSet(degs, used, taken, i + 1);

    if (used[v] > 0) {
        return;
    }

    // Case 2: We take this vertex

    taken.push_back(v);
    ++used[v];

    for (auto to : adjacency_list[v]) { // banning adjacent vertices
        ++used[to];
    }

    FindMaxStableSet(degs, used, taken, i + 1);

    for (auto to : adjacency_list[v]) { // unbanning
        --used[to];
    }

    --used[v];
    taken.pop_back();
}

/**
 * @brief 
 * Solution of item F using brute force
 * No heuristics used
 */
void TaskF() {
    cout << "Task F starting...\n\n";

    // Init degrees
    vector<int> deg(n);

    for (int i = 0; i < n; ++i) {
        deg[i] = sz(adjacency_list[i]);
    }

    vector<pair<int, int>> v;

    for (int i = 0; i < n; ++i) {
        v.push_back({deg[i], i});
    }

    // I actually sorted vertices by their degrees, but that does not speed up solution
    sort(v.begin(), v.end());

    // Init arrays for brute force
    vector<int> used(n, 0);
    vector<int> taken;
    
    FindMaxStableSet(v, used, taken, 0);

    for (auto i : task_f_ans) {
        cout << number_country[i] << " ";
    }

    cout << "\n---------------\n";
}

int task_g_cnt = 0;
const int kTaskGLimit = 100000000;
vector<pair<int, int>> task_g_ans;

/**
 * Sizes of matching depending f the value of kTaskGLimit
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

/**
 * @brief 
 * Solution of item H using greedy.
 * Take the vertex that covers the most of available edges,
 * Then "delete" those edges and update degrees
 * 
 * P.S. I really do not know if that algorithm gives the optimal answer.
 * But the brute force would prolly end when the Sun collapses.
 * Sorry :(
 */
void TaskH() {
    cout << "Task H starting...\n\n";

    // Init arrays for algorithm
    vector<bool> used(n, false); // is responsible for marking visited vertices
    vector<int> taken; // saves the answer
    vector<int> deg(n); // degrees of vertices

    for (int i = 0; i < n; ++i) { // init
        deg[i] = sz(adjacency_list[i]);
    }

    set<pair<int, int>, greater<pair<int, int>>> s;

    for (int i = 0; i < n; ++i) { // init greedy
        s.insert({deg[i], i});
    }

    int edges_covered = 0;

    while (edges_covered < 84) { // |E| = 84
        auto [degree, v] = *s.begin(); // greedily take the "optimal" vertex
        s.erase(s.begin());

        // Save this vertex
        used[v] = true;
        edges_covered += degree;
        taken.push_back(v);

        for (auto to : adjacency_list[v]) { // update degrees
            if (used[to]) {
                continue;
            }

            s.erase({deg[to], to});
            --deg[to];
            s.insert({deg[to], to});
        }
    }

    for (auto v : taken) {
        cout << number_country[v] << "\n";
    }

    cout << "\n---------------\n";
}

/**
 * @brief 
 * Solution of item J using brute force
 * with simple magical heuristics:
 * - Choosing starting and subsequent vertices randomly
 * - Sorting adjacent vertices by their degree
 * 
 * This function finds the Hamiltonian path. I had to delete some edges so the path exists.
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

/**
 * @brief 
 * 1. Iterate through each edge that starts from vertex v
 *    Delete this edge
 *    Call FindEulerPath from the other end of this edge
 * 2. Add vertex v to an answer
 * 
 * @param used is responsible for deleting edges
 * @param answer saves the Eulerian path 
 * @param v is the current vertex
 */
void FindEulerPath(vector<vector<bool>>& used, vector<int>& answer, int v) {
    for (auto to : adjacency_list[v]) {
        if (!used[v][to]) {
            used[v][to] = used[to][v] = true;
            FindEulerPath(used, answer, to);
        }
    }

    answer.push_back(v);
}

/**
 * @brief 
 * Solution of item K using DFS
 * FindEulerPath is a function that makes depth-first search
 * 
 * This function finds the Eulerian path. I had to delete some edges so the path exists.
 * After getting a path, I added some edges to get an answer to task K.
 */
void TaskK() {
    cout << "Task K starting...\n\n";

    // Init arrays
    vector<vector<bool>> used(n, vector<bool>(n, false));
    vector<int> answer;

    FindEulerPath(used, answer, country_number["Portugal"]);
    
    reverse(answer.begin(), answer.end());

    for (auto i : answer) {
        cout << number_country[i] << ", ";
    }

    cout << "\n---------------\n";
}

vector<int> cut_vertices;

/**
 * @brief
 * Function for finding cut vertices. Nothing more.
 * @param used is for marking visited vertices
 * @param timer is the current timer
 * @param tin saves time (and depth) of the first visit of vertex
 * @param fup saves minimal time (and depth) of vertex that can be achieved from the subtree of DFS
 * @param v is the current vertex
 * @param p is the parent vertex
 */
void FindCutVertices(
    vector<bool>& used,
    int& timer,
    vector<int>& tin,
    vector<int>& fup,
    int v,
    int p = -1
) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;

    for (auto to : adjacency_list[v]) {
        if (to == p) { // we do not want to loop endlessly
            continue;
        }

        if (used[to]) {
            ckmin(fup[v], tin[to]); // update minimal time
        } else {
            FindCutVertices(used, timer, tin, fup, to, v);

            ckmin(fup[v], fup[to]); // update minimal time

            // If the minimal time (depth) is greater or equal than the current time (depth) and the current vertex has a parent, then v is a cut vertex.
            if (tin[v] <= fup[to] && p != -1) {
                cut_vertices.push_back(v);
            }

            ++children; // increase the number of "branches" of dfs-tree
        }
    }

    if (p == -1 && children > 1) { // check the starting vertex. If it has more than 1 "branches" of dfs-tree, then it is a cut vertex
        cut_vertices.push_back(v);
    }
}

/**
 * @brief 
 * This is not a solution for item L
 * This is just a function for finding cut vertices, which are needed in item L
 */
void TaskL() {
    cout << "Task L starting...\n\n";
    
    vector<bool> used(n, false);
    int timer = 0;
    vector<int> tin(n), fup(n);

    FindCutVertices(used, timer, tin, fup, country_number["Russia"]);

    for (auto i : cut_vertices) {
        cout << number_country[i] << "\n";
    }

    cout << "\n---------------\n";
}

vector<pair<int, int>> bridges;

/**
 * @brief
 * Function for finding bridges. Nothing more.
 * @param used is for marking visited vertices
 * @param timer is the current timer
 * @param tin saves time (and depth) of the first visit of vertex
 * @param fup saves minimal time (and depth) of vertex that can be achieved from the subtree of DFS
 * @param v is the current vertex
 * @param p is the parent vertex
 */
void FindBridges(
    vector<bool>& used,
    int timer,
    vector<int>& tin,
    vector<int>& fup,
    int v,
    int p = -1
) {
    used[v] = true;
    tin[v] = fup[v] = timer++;

    for (auto to : adjacency_list[v]) {
        if (to == p) { // we do not want to loop endlessly
            continue;
        }

        if (used[to]) {
            ckmin(fup[v], tin[to]); // update minimal time
        } else {
            FindBridges(used, timer, tin, fup, to, v);

            ckmin(fup[v], fup[to]); // update minimal time

            // If the minimal time (depth) is greater than the current time (depth), then v <-> to is bridge.
            if (tin[v] < fup[to]) {
                bridges.push_back({v, to});
            }
        }
    }
}

/**
 * @brief 
 * This is not a solution for item M. This is just a function for finding bridges,
 * Which are needed in item M
 */
void TaskM() {
    cout << "Task M starting...\n\n";

    vector<bool> used(n, false);
    int timer = 0;
    vector<int> tin(n), fup(n);

    FindBridges(used, timer, tin, fup, country_number["Russia"]);

    for (auto [from, to] : bridges) {
        cout << number_country[from] << " <-> " << number_country[to] << "\n";
    }

    cout << "\n---------------\n";
}

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

vector<vector<int>> tree_list(n);
vector<int> s(n);

/**
 * @brief 
 * Counting sizes of subtrees
 * @param v - current vertex
 * @param p - parent vertex
 */
void CountSizes(int v, int p = -1) {
    s[v] = 1;

    for (auto to : tree_list[v]) {
        if (to == p) {
            continue;
        }

        CountSizes(to, v); // recursively calculate sizes of subtrees
        s[v] += s[to];
    }
}

/**
 * @brief 
 * Finding centroid using depth-first search
 * @param v - current vertex
 * @param p - parent vertex
 * @return int - centroid vertex
 */
int FindCentroid(int v, int p = -1) {
    for (auto to : tree_list[v]) {
        if (to == p) {
            continue;
        }

        if (s[to] > n / 2) { // if there is a subtree that has size > n / 2, v is not a centroid
            return FindCentroid(to, v);
        }
    }

    return v;
}

/**
 * @brief 
 * Solution of item O using DFS (for unweighted tree)
 */
void TaskO_unweighted() {
    vector<Edge> edges = TaskN();

    cout << "Task O starting...\n\n";

    for (auto [u, v, w] : edges) { // constructing tree using edges from task N
        tree_list[u].emplace_back(v);
        tree_list[v].emplace_back(u);
    }

    CountSizes(0); // init sizes
    vector<int> centroid = {FindCentroid(0)}; // finding first centroid

    for (auto to : tree_list[centroid[0]]) { // checking if there is the second centroid
        bool ok = true;

        for (auto to_to : tree_list[to]) {
            if (s[to_to] > n / 2) {
                ok = false;
            }
        }

        if (ok) {
            centroid.push_back(to);
            break;
        }
    }

    for (auto v : centroid) {
        cout << number_country[v] << " ";
    }

    cout << "\n---------------\n";
}

vector<vector<pair<int, int>>> tree_list_w(n);

/**
 * @brief 
 * Function for calculating weight of branch
 * @param v is current vertex
 * @param cur_weight is current weight of branch
 * @param p is parent vertex
 * @return int 
 */
int CalculateWeight(int v, int cur_weight, int p = -1) {
    // Iterate through all the edges that are incident to our vertex
    for (auto [to, w] : tree_list_w[v]) {
        if (to == p) { // check if the next vertex is parent so we do not loop endlessly
            continue;
        }

        // Add weights of branches to the current weight of branch
        cur_weight += CalculateWeight(to, w, v);
    }

    return cur_weight;
}

/**
 * @brief 
 * Solution of item O using DFS (for weighted tree)
 */
void TaskO_weighted() {
    vector<Edge> edges = TaskN();

    cout << "Task O starting...\n\n";

    for (auto [u, v, w] : edges) { // init adjacency list with weights
        tree_list_w[u].emplace_back(v, w);
        tree_list_w[v].emplace_back(u, w);
    }

    vector<int> weight(n, 0);

    for (int v = 0; v < n; ++v) {
        // Iterate through all branches and gather their weights
        // Update the weight of the current vertex
        // (weight[v] = max(weight[v], branch_weight))

        for (auto [to, w] : tree_list_w[v]) {
            ckmax(weight[v], CalculateWeight(to, w, v));
        }
    }

    int min_weight = *min_element(weight.begin(), weight.end());
    vector<int> centroid;

    for (int v = 0; v < n; ++v) { // find centroids
        if (weight[v] == min_weight) {
            centroid.push_back(v);
        }
    }

    for (auto i : centroid) {
        cout << number_country[i] << " ";
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

    

    // -----------------
    
    return 0;
}
