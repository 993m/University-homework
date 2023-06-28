// kruskal, O(elogv)

#include <bits/stdc++.h>

using namespace std;
ifstream fin("apm.in");
ofstream fout("apm.out");
int n, m, ct, sel, parent[200001], h[200001];

struct Edge {
    int x, y, c;
} e[400001];

vector<Edge> v;

bool comp(Edge e1, Edge e2){
    return (e1.c < e2.c);
}

int root(int x){
    if(parent[x] == 0) return x;
    return root(parent[x]);
}

int main() {
    fin >> n >> m;
    for (int i=1; i<=m; i++) {
        fin >> e[i].x >> e[i].y >> e[i].c;
    }

	// sortez muchiile
    sort(e+1, e+m+1, comp);

	// parcurg vectorul cat timp am muchii in el si nu am selectat inca n-1 muchii (nr maxim de muchii intr-un arbore cu n noduri)
    for(int i=1; i<=m and sel<n-1; i++){
		// aflu in ce multimi se afla nodurile care formeaza muchia curenta (afland radacinile arborilor in care se afla)
        int r1 = root(e[i].x);
        int r2 = root(e[i].y);
		
		// daca nodurile se afla in multimi diferite (adica in arbori diferiti), 
		// inseamna ca pot adauga muchia fara sa se formeze vreun ciclu 
        if(r1 != r2){
			// cresc numarul de muchii selectate
            sel++;

			// unificarea multimilor (adaug arborele de inaltime mai mica arborelui cu inaltime mai mare => se pastreaza complexitatea O(logn))
            if(h[r1] < h[r2]) parent[r1] = r2;
            else if(h[r1] == h[r2]) parent[r1] = r2, h[r2] += 1;
            else parent[r2] = r1;

			// actualizez costul apm-ului
            ct += e[i].c;
			// adaug muchia tocmai introdusa in vectorul cu muchiile apm-ului
            v.push_back(e[i]);
        }
    }

    fout<<ct<<'\n'<<v.size()<<'\n';
    for(auto e: v) fout<<e.x<<" "<<e.y<<'\n';
    return 0;
}