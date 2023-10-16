#include <bits/stdc++.h>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

using namespace std;

vector<int> dijkstra(vector<vector<pair<int, int>>> &graph, int init) {
    int n = graph.size();
    priority_queue<pair<int, int>> pq;
    vector<int> dist(n, INT_MAX);

    dist[init] = 0;
    pq.push({0, init});

    while (!pq.empty()) {
        int v = pq.top().second;
        int custo = -pq.top().first;

        pq.pop();

        if (custo != dist[v]) continue;

        for (auto edge : graph[v]) {
            int u = edge.first;
            int peso = edge.second;

            if (dist[u] > dist[v] + peso) {
                dist[u] = dist[v] + peso;
                pq.push({-dist[u], u});
            }
        }
    }

    return dist;
}

int main(int argc, char **argv) {
    int init = 0, arq_in = 0, arq_out = 0;
    bool set_arq = false, set_init = false, output = false;
    ifstream arquivo;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-f")) {
            set_arq = true;
            arq_in = i + 1;
        }

        if (!strcmp(argv[i], "-i"))
            set_init = true;

        if (!strcmp(argv[i], "-o")) {
            arq_out = i + 1;
            output = true;
        }

        if (!strcmp(argv[i], "-h")) {
            cout << CYAN << "\n\t<---------------- HELP ---------------->" << endl;
            cout << GREEN << "-o <arquivo> : redireciona a saída para o arquivo" << endl;
            cout << GREEN << "-f <arquivo> : indica o arquivo que contém a entrada" << endl;
            cout << GREEN << "-i indica o vertice inicial, caso não ele imprimirá de todos para todos" << endl;
        }
    }

    if (set_arq)
        arquivo.open(argv[arq_in]);

    if (arquivo.fail() == 1) {
        cout << "O arquivo não foi encontrado, digite o nome do arquivo após o -f!\n\nExemplo: ./bin -f arquivo.txt\n\n";
        return 1;
    }

    // input o grafo com valores do arquivo!
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

    //vertice que inserido na execução
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

    //verificando se o vértice está no intervalo do grafo!
    if (init >= n || init < 0) {
        cout << "Vertice informado pelo -i não pertence ao grafo!\n";
        return 1;
    }

    // Executando o algoritmo de Dijkstra
    vector<int> dist = dijkstra(graph, init);

    for (int i = 0; i < dist.size(); i++) {
        if (dist[i] == INT_MAX) {
            cout << i + 1 << ":-1 ";
        } else {
            cout << i + 1 << ":" << dist[i] << " ";
        }
    }

    cout << endl;

    //criando o arquivo de saída
    if (output) {
        ofstream out_file;
        out_file.open(argv[arq_out]);

        if (out_file.fail() == 1) {
            cout << "Erro ao criar o arquivo, digite o nome do arquivo após -o!\n\nExemplo: ./bin -o arquivo.txt\n\n";
            return 1;
        }

        for (int i = 0; i < dist.size(); i++) {
            if (dist[i] == INT_MAX) {
                out_file << i + 1 << ":-1 ";
            } else {
                out_file << i + 1 << ":" << dist[i] << " ";
            }
        }

        out_file << endl;
    }

    return 0;
}
