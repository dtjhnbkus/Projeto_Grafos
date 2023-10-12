#include <bits/stdc++.h>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

using namespace std;


void prim(vector<vector<pair<int, int>>>& graph, int init, bool ord_agm, int *soma) {
    int n = graph.size();

    priority_queue<pair<int, int>> pq;
    vector<int> agm(n, -1);
    vector<bool> visited(n, false);
    vector<int> pesos(n, INT_MAX);

    pesos[init] = 0;
    pq.push({0, init});

    while (!pq.empty()) {
        pair<int, int> edge = pq.top();
        pq.pop();
        visited[edge.second] = true;

        for (pair<int, int> edges : graph[edge.second]) {
            if (!visited[edges.first] && edges.second < pesos[edges.first]) {
                pesos[edges.first] = edges.second;
                pq.push({-edges.second, edges.first});
                agm[edges.first] = edge.second;
            }
        }
    }
    vector<vector<int>> graph_agm(n);
    for (int peso : pesos)
        *soma += peso;

    if (ord_agm) {
        for (int i = 0; i < n; i++) {
            if (agm[i] != -1) {
                if (i > agm[i]) {
                    graph_agm[agm[i]].push_back(i);
                } else {
                    graph_agm[i].push_back(agm[i]);
                }
            }
        }
        for (int i = 0; i < graph_agm.size(); i++)
            if (graph_agm[i].size() > 0)
                for (int v : graph_agm[i])
                    cout << "(" << i + 1 << "," << v + 1 << ")" << " ";
        cout << endl;
    } else {
        for (int i = 0; i < n; i++)
            if (agm[i] != -1)
                graph_agm[i].push_back(agm[i]);

        cout << *soma << endl;
    }
}

int main(int argc, char **argv) {
    int init = 0, arq_in = 0, arq_out = 0;
    bool ord_agm = false, set_arq = false, set_init = false, output = false;
    ifstream arquivo;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-f")) {
            set_arq = true;
            arq_in = i + 1;
        }
        if (!strcmp(argv[i], "-i"))
            set_init = true;

        if (!strcmp(argv[i], "-s"))
            ord_agm = true;

        if (!strcmp(argv[i], "-o")) {
            arq_out = i + 1;
            output = true;
        }
        if (!strcmp(argv[i], "-h")) {
            cout << CYAN << "\n\t<---------------- HELP ---------------->" << endl;
            cout << GREEN << "\n-o <arquivo> : redireciona a saida para o arquivo" << endl;
            cout << GREEN << "-f <arquivo> : indica o arquivo que contem a entrada" << endl;
            cout << GREEN << "-s : mostra a solução (em ordem crescente), caso não informado o custo será mostrado!" << endl;
            cout << GREEN << "-i : vértice inicial" << RESET << "\n\n";
        }
    }

    if (set_arq)
        arquivo.open(argv[arq_in]);

    if (arquivo.fail() == 1) {
        cout << "O arquivo não foi encontrado, digite o nome do arquivo após o -f!\n\nExemplo: ./bin -f arquivo.txt\n\n";
        return 1;
    }

    int n, m;
    arquivo >> n >> m;

    vector<vector<pair<int, int>>> graph(n);

    for (int i = 0; i < m; i++) {
        int v, w, p;

        arquivo >> v >> w >> p;

        graph[v - 1].push_back({w - 1, p});
        graph[w - 1].push_back({v - 1, p});
    }

    arquivo.close();

    if (set_init) {
        int j;
        for (j = 0; j < argc; j++) {
            int i, neg = 0;
            for (i = 0; i < strlen(argv[j]); i++) {
                if (argv[j][i] >= 48 && argv[j][i] <= 57 || argv[j][i] == '-') {
                    if (argv[j][i] == '-') {
                        neg = 1;
                    } else {
                        init = init * 10 + argv[j][i] - '0';
                    }
                } else {
                    init = 0;
                    break;
                }
            }

            if (neg)
                init *= (-1);

            if (i == strlen(argv[j])) {
                init -= 1;
                break;
            }
        }
    }

    if (init >= n || init < 0) {
        cout << "Vertice informado pelo -i não pertence ao grafo!\n";
        return 1;
    }
    int soma = 0;
    prim(graph, init, ord_agm, &soma);

    if (output) {
        ofstream out_file;
        out_file.open(argv[arq_out]);

        if (out_file.fail() == 1) {
            cout << "Erro ao criar o arquivo, digite o nome do arquivo após -o!\n\nExemplo: ./bin -o arquivo.txt\n\n";
            return 1;
        }
        out_file << "agm: ";
        for (int i = 0; i < graph.size(); i++)
            if (graph[i].size() > 0)
                for (pair<int, int> edge : graph[i])
                    out_file << "(" << i + 1 << "," << edge.first + 1 << ") ";

        out_file << endl << "Custo: " << soma << endl;
    }

    return 0;
}
