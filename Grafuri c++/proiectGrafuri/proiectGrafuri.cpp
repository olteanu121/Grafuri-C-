// proiectGrafuri.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>
#include <cstring>

using namespace std;

vector<pair<int, int>> graf[100000];

void citeste_graf(string file_path) {
    ifstream fin(file_path);
    int nr_noduri, nr_muchii;
    fin >> nr_noduri >> nr_muchii;
    for (int i = 0; i < nr_muchii; i++) {
        int u, v, cost;
        fin >> u >> v >> cost;
        graf[u].push_back({ v, cost });
        graf[v].push_back({ u, cost });
    }
    fin.close();
}

bool este_conex(int nr_noduri) {
    bool vizitat[nr_noduri];
    memset(vizitat, false, sizeof(vizitat));
    queue<int> coada;
    coada.push(0);
    while (!coada.empty()) {
        int u = coada.front();
        coada.pop();
        if (!vizitat[u]) {
            vizitat[u] = true;
            for (auto vecin : graf[u]) {
                int v = vecin.first;
                if (!vizitat[v]) {
                    coada.push(v);
                }
            }
        }
    }
    for (int i = 0; i < nr_noduri; i++) {
        if (!vizitat[i]) {
            return false;
        }
    }
    return true;
}

int drum_minim(int sursa, int destinatie) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int distante[100000];
    memset(distante, INT_MAX, sizeof(distante));
    pq.push({ 0, sursa });
    distante[sursa] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto vecin : graf[u]) {
            int v = vecin.first;
            int cost = vecin.second;
            if (distante[u] + cost < distante[v]) {
                distante[v] = distante[u] + cost;
                pq.push({ distante[v], v });
            }
        }
    }
    return distante[destinatie];
}

int main() {
    string nume_fisier = "graf.txt";
    citeste_graf(nume_fisier);
    int nr_noduri = sizeof(graf) / sizeof(graf[0]);
    if (!este_conex(nr_noduri)) {
        cout << "Graful nu este conex!";
        return 0;
    }
    int sursa, destinatie;
    cout << "Introduceti nodul de start: ";
    cin >> sursa;
    cout << "Introduceti nodul destinatie: ";
    cin >> destinatie;
    int distanta = drum_minim(sursa, destinatie);
    cout << "Distanta minima intre nodurile " << sursa << " si " << destinatie << " este: " << distanta;
    return 0;
}

