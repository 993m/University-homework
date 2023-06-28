#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include<iomanip>
#include <algorithm>

using namespace std;
ifstream fin("input.txt");
ofstream fout("evolution.txt");

struct Chromosome{
    static int l;
    static double a, b;
    static double param_a, param_b, param_c, param_d;
    static double d;
    static int precision;
    static double crossoverProbability;
    static double mutationProbability;

    vector<bool> genes;

    Chromosome()= default;
    Chromosome(const vector<bool> &genes) : genes(genes) {}

    static vector<bool> generateGenes(){
        vector<bool> genes(l);
        for(int i=0; i<l; i++)
            if(rand()%2) genes[i] = 1;

        return genes;
    }

    double binaryToDecimal() const{
        int x = 0;
        for(int i=0,j=l-1; i<l; i++,j--)
            x += genes[i] * pow(2, j);

        return a + x * d;
    }

    friend ostream &operator<<(ostream &os, const Chromosome &chromosome) {
        for(auto g: chromosome.genes)
            os << g;
        return os;
    }

    double fitness() const{
        double x = this->binaryToDecimal();
        return x*x*x*param_a + x*x*param_b + x*param_c + param_d;
    }

    void afisareK(int k){
        for(int i=0; i<=k; i++)
            fout<<genes[i];
        fout<<'|';
        for(int i=k+1; i<l; i++)
            fout<<genes[i];
    }
};

int Chromosome::l;
double Chromosome::a, Chromosome::b;
double Chromosome::param_a, Chromosome::param_b, Chromosome:: param_c, Chromosome:: param_d;
double Chromosome::d;
int Chromosome::precision;
double Chromosome::crossoverProbability;
double Chromosome::mutationProbability;

void readInput(int &n, int &N){
    fin>>Chromosome::param_a>>Chromosome::param_b>>Chromosome::param_c>>Chromosome:: param_d;
    fin>>Chromosome::a>>Chromosome::b;
    fin>>n;
    fin>>Chromosome::precision;
    fin>>Chromosome::crossoverProbability;
    fin>>Chromosome::mutationProbability;
    fin>>N;
}

void showGeneration(const vector<Chromosome> &chromosomes){
    for(int i=0; i<chromosomes.size(); i++)
        fout<<setw(4)<<i+1<<": "<<chromosomes[i]<<" x= "<<setw(3+Chromosome::precision)<<fixed<<setprecision(Chromosome::precision)<<chromosomes[i].binaryToDecimal()<<" f= "<<chromosomes[i].fitness()<<'\n';

    fout<<endl;
}

vector<double> getSelectionProbabilities(const vector<Chromosome> &chromosomes){
    double total = 0;
    vector<double> selectionProbabilities;

    for(auto &c: chromosomes){
        double f = c.fitness();
        total += f;
        selectionProbabilities.emplace_back(f);
    }

    for(int i=0; i<selectionProbabilities.size(); i++)
        selectionProbabilities[i] /= total;

    return selectionProbabilities;
}

vector<double> getSelectionProbabilitiesShow(const vector<Chromosome> &chromosomes){
    double total = 0;
    vector<double> selectionProbabilities;

    for(auto &c: chromosomes){
        double f = c.fitness();
        total += f;
        selectionProbabilities.emplace_back(f);
    }

    for(int i=0; i<selectionProbabilities.size(); i++)
        selectionProbabilities[i] /= total;

    fout<<"Selection probabilities\n";
    for(int i=0; i<chromosomes.size(); i++)
        fout<<"chromosome "<<setw(4)<<i+1<<" probability "<<selectionProbabilities[i]<<'\n';

    return selectionProbabilities;
}

vector<double> getSelectionProbabilityIntervals(const vector<double> &selectionProbabilities){
    vector<double> selectionProbabilityIntervals(1);
    for(auto p: selectionProbabilities)
        selectionProbabilityIntervals.emplace_back(selectionProbabilityIntervals.back() + p);

    return selectionProbabilityIntervals;
}

Chromosome getElitist(const vector<Chromosome> &chromosomes){
    Chromosome max = chromosomes[0];
    for(auto &c: chromosomes)
        if(c.fitness() > max.fitness()) max = c;
    return max;
}

void selectChromosomes(vector<Chromosome> &chromosomes){
    vector<Chromosome> selectedChromosomes;
    selectedChromosomes.reserve(chromosomes.size());

    selectedChromosomes.emplace_back(getElitist(chromosomes));
    vector<double> selectionProbabilityIntervals = getSelectionProbabilityIntervals(getSelectionProbabilities(chromosomes));

    for(int i=1; i<chromosomes.size(); i++){
        double u = (double)rand()/(double)RAND_MAX;

        int st = 0, dr = selectionProbabilityIntervals.size()-1, mid;
        while(st + 1 < dr){
            mid = st+(dr-st)/2;
            if(u >= selectionProbabilityIntervals[mid]) st = mid;
            else dr = mid;
        }

        selectedChromosomes.emplace_back(chromosomes[st]);
    }

    chromosomes = selectedChromosomes;
}

void selectChromosomesShow(vector<Chromosome> &chromosomes){
    vector<Chromosome> selectedChromosomes;
    selectedChromosomes.reserve(chromosomes.size());

    selectedChromosomes.emplace_back(getElitist(chromosomes));
    vector<double> selectionProbabilityIntervals = getSelectionProbabilityIntervals(getSelectionProbabilitiesShow(chromosomes));
    fout<<"Selection probability intervals\n";
    for(auto i: selectionProbabilityIntervals) fout<<i<<" ";
    fout<<endl;

    for(int i=1; i<chromosomes.size(); i++){
        double u = (double)rand()/(double)RAND_MAX;

        int st = 0, dr = selectionProbabilityIntervals.size()-1, mid;
        while(st + 1 < dr){
            mid = st+(dr-st)/2;
            if(u >= selectionProbabilityIntervals[mid]) st = mid;
            else dr = mid;
        }

        selectedChromosomes.emplace_back(chromosomes[st]);

        fout<<"u="<<setw(16)<<u<<" selected chromosome "<<setw(4)<<st+1<<'\n';
    }

    chromosomes = selectedChromosomes;
}

vector<int> selectForCrossoverShow(const vector<Chromosome> &chromosomes){
    vector<int> indexes;
    fout<<"Crossover probability "<<Chromosome::crossoverProbability<<'\n';

    for(int i=0; i<chromosomes.size(); i++){
        double u = (double)rand()/(double)RAND_MAX;
        if(u < Chromosome::crossoverProbability){
            indexes.emplace_back(i);
            fout<<setw(4)<<i+1<<": "<<chromosomes[i]<<" u="<<setw(16)<<u<<"<"<<Chromosome::crossoverProbability<<" participates\n";
        }
        else fout<<setw(4)<<i+1<<": "<<chromosomes[i]<<" u="<<setw(16)<<u<<'\n';
    }

    fout<<endl;

    return indexes;
}

vector<int> selectForCrossover(const vector<Chromosome> &chromosomes){
    vector<int> indexes;

    for(int i=0; i<chromosomes.size(); i++){
        double u = (double)rand()/(double)RAND_MAX;
        if(u < Chromosome::crossoverProbability)
            indexes.emplace_back(i);
    }

    return indexes;
}

void crossoverShow(vector<Chromosome> &chromosomes, int index1, int index2, int index3=-1){
    if(index3 != -1){
        fout<<"Crossover between chromosome "<<index1+1<<", chromosome "<<index2+1<<" and chromosome "<<index3+1<<'\n';

        vector<bool> c1Genes = chromosomes[index1].genes;
        vector<bool> c2Genes = chromosomes[index2].genes;
        vector<bool> c3Genes = chromosomes[index3].genes;
        vector<bool> c1NewGenes(Chromosome::l);
        vector<bool> c2NewGenes(Chromosome::l);
        vector<bool> c3NewGenes(Chromosome::l);

        int k = rand()%Chromosome::l;

        chromosomes[index1].afisareK(k); fout<<" "; chromosomes[index2].afisareK(k); fout<<" "; chromosomes[index3].afisareK(k); fout<<" k="<<k+1<<'\n';

        for(int i=0; i<=k; i++){
            c1NewGenes[i] = c1Genes[i];
            c2NewGenes[i] = c2Genes[i];
            c3NewGenes[i] = c3Genes[i];
        }
        for(int i=k+1; i<Chromosome::l; i++){
            c1NewGenes[i] = c2Genes[i];
            c2NewGenes[i] = c3Genes[i];
            c3NewGenes[i] = c1Genes[i];
        }
        for(int i=k+1, j=Chromosome::l-1; i<=j; i++, j--){
            swap(c1NewGenes[i], c1NewGenes[j]);
            swap(c2NewGenes[i], c2NewGenes[j]);
            swap(c3NewGenes[i], c3NewGenes[j]);
        }

        chromosomes[index1].genes = c1NewGenes;
        chromosomes[index2].genes = c2NewGenes;
        chromosomes[index3].genes = c3NewGenes;

        fout<<"Result "; chromosomes[index1].afisareK(k); fout<<" "; chromosomes[index2].afisareK(k); fout<<" "; chromosomes[index3].afisareK(k); fout<<'\n';
    }
    else{
        fout<<"Crossover between chromosome "<<index1+1<<" and chromosome "<<index2+1<<'\n';

        vector<bool> c1Genes = chromosomes[index1].genes;
        vector<bool> c2Genes = chromosomes[index2].genes;
        vector<bool> c1NewGenes(Chromosome::l);
        vector<bool> c2NewGenes(Chromosome::l);

        int k = rand()%Chromosome::l;

        chromosomes[index1].afisareK(k); fout<<" "; chromosomes[index2].afisareK(k); fout<<" k="<<k+1<<'\n';

        for(int i=0; i<=k; i++){
            c1NewGenes[i] = c1Genes[i];
            c2NewGenes[i] = c2Genes[i];
        }
        for(int i=k+1; i<Chromosome::l; i++){
            c1NewGenes[i] = c2Genes[i];
            c2NewGenes[i] = c1Genes[i];
        }
        for(int i=k+1, j=Chromosome::l-1; i<=j; i++, j--){
            swap(c1NewGenes[i], c1NewGenes[j]);
            swap(c2NewGenes[i], c2NewGenes[j]);
        }

        chromosomes[index1].genes = c1NewGenes;
        chromosomes[index2].genes = c2NewGenes;

        fout<<"Result "; chromosomes[index1].afisareK(k); fout<<" "; chromosomes[index2].afisareK(k); fout<<'\n';
    }
}

void crossover(vector<Chromosome> &chromosomes, int index1, int index2, int index3=-1){
    if(index3 != -1){
        vector<bool> c1Genes = chromosomes[index1].genes;
        vector<bool> c2Genes = chromosomes[index2].genes;
        vector<bool> c3Genes = chromosomes[index3].genes;
        vector<bool> c1NewGenes(Chromosome::l);
        vector<bool> c2NewGenes(Chromosome::l);
        vector<bool> c3NewGenes(Chromosome::l);

        int k = rand()%Chromosome::l;

        for(int i=0; i<=k; i++){
            c1NewGenes[i] = c1Genes[i];
            c2NewGenes[i] = c2Genes[i];
            c3NewGenes[i] = c3Genes[i];
        }
        for(int i=k+1; i<Chromosome::l; i++){
            c1NewGenes[i] = c2Genes[i];
            c2NewGenes[i] = c3Genes[i];
            c3NewGenes[i] = c1Genes[i];
        }
        for(int i=k+1, j=Chromosome::l-1; i<=j; i++, j--){
            swap(c1NewGenes[i], c1NewGenes[j]);
            swap(c2NewGenes[i], c2NewGenes[j]);
            swap(c3NewGenes[i], c3NewGenes[j]);
        }

        chromosomes[index1].genes = c1NewGenes;
        chromosomes[index2].genes = c2NewGenes;
        chromosomes[index3].genes = c3NewGenes;
    }
    else{
        vector<bool> c1Genes = chromosomes[index1].genes;
        vector<bool> c2Genes = chromosomes[index2].genes;
        vector<bool> c1NewGenes(Chromosome::l);
        vector<bool> c2NewGenes(Chromosome::l);

        int k = rand()%Chromosome::l;

        for(int i=0; i<=k; i++){
            c1NewGenes[i] = c1Genes[i];
            c2NewGenes[i] = c2Genes[i];
        }
        for(int i=k+1; i<Chromosome::l; i++){
            c1NewGenes[i] = c2Genes[i];
            c2NewGenes[i] = c1Genes[i];
        }
        for(int i=k+1, j=Chromosome::l-1; i<=j; i++, j--){
            swap(c1NewGenes[i], c1NewGenes[j]);
            swap(c2NewGenes[i], c2NewGenes[j]);
        }

        chromosomes[index1].genes = c1NewGenes;
        chromosomes[index2].genes = c2NewGenes;
    }
}

void crossoverShow(vector<Chromosome> &chromosomes){
    vector<int> indexesCrossover = selectForCrossoverShow(chromosomes);
    if(indexesCrossover.size()==1) return;
    random_shuffle(indexesCrossover.begin(), indexesCrossover.end());

    int n = indexesCrossover.size();
    if(n%2==1){
        crossoverShow(chromosomes, indexesCrossover[n-3], indexesCrossover[n-2], indexesCrossover[n-1]);
        n -= 3;
    }

    for(int i=0; i<n-1; i+=2){
        crossoverShow(chromosomes, indexesCrossover[i], indexesCrossover[i+1]);
    }
}

void crossover(vector<Chromosome> &chromosomes){
    vector<int> indexesCrossover = selectForCrossover(chromosomes);
    if(indexesCrossover.size()==1) return;

    random_shuffle(indexesCrossover.begin(), indexesCrossover.end());

    int n = indexesCrossover.size();
    if(n%2==1){
        crossover(chromosomes, indexesCrossover[n-3], indexesCrossover[n-2], indexesCrossover[n-1]);
        n -= 3;
    }

    for(int i=0; i<n-1; i+=2){
        crossover(chromosomes, indexesCrossover[i], indexesCrossover[i+1]);
    }
}

void mutationsShow(vector<Chromosome> &chromosomes){
    fout<<"The mutation probability is "<<Chromosome::mutationProbability<<'\n';
    vector<int> indexes;

    for(int i=0; i<chromosomes.size(); i++){
        double u = (double)rand()/(double)RAND_MAX;
        if(u < Chromosome::mutationProbability){
            indexes.emplace_back(i);
            int j = rand()%Chromosome::l;
            chromosomes[i].genes[j] = !chromosomes[i].genes[j];
        }
    }

    fout<<"Mutated chromosomes: \n";
    for(auto &i: indexes) fout<<i<<'\n';
}

void mutations(vector<Chromosome> &chromosomes){
    for(int i=0; i<chromosomes.size(); i++){
        double u = (double)rand()/(double)RAND_MAX;
        if(u < Chromosome::mutationProbability){
            int j = rand()%Chromosome::l;
            chromosomes[i].genes[j] = !chromosomes[i].genes[j];
        }
    }
}

void firstGeneration(vector<Chromosome> &chromosomes){
    fout<<"Initial population\n";
    showGeneration(chromosomes);

    selectChromosomesShow(chromosomes);
    fout<<"After selection\n";
    showGeneration(chromosomes);

    crossoverShow(chromosomes);
    fout<<"After crossover\n";
    showGeneration(chromosomes);

    mutationsShow(chromosomes);
    fout<<"After mutations\n";
    showGeneration(chromosomes);

}

double getAverage(const vector<Chromosome> &chromosomes){
    double total = 0;
    for(auto &c: chromosomes)
        total += c.fitness();

    return total / chromosomes.size();
}

void generation(vector<Chromosome> &chromosomes){
    selectChromosomes(chromosomes);
    crossover(chromosomes);
    mutations(chromosomes);

    fout<<"Maximum: "<<getElitist(chromosomes).binaryToDecimal()<<" "<<setw(3+Chromosome::precision)<<getElitist(chromosomes).fitness()<<"   average: "<<setw(3+Chromosome::precision)<<getAverage(chromosomes)<<'\n';
}

int main() {
    srand (time(nullptr));

    int n, N;

    readInput(n, N);

    Chromosome::l = ceil(log2((Chromosome::b-Chromosome::a)*pow(10, Chromosome::precision)));
    Chromosome::d = (Chromosome::b-Chromosome::a)/(pow(2, Chromosome::l)-1);
    Chromosome::crossoverProbability = Chromosome::crossoverProbability / 100;
    Chromosome::mutationProbability = Chromosome::mutationProbability / 100;

    // generate initial population
    vector<Chromosome> chromosomes;
    chromosomes.reserve(n);
    for(int i=0; i<n; i++)
        chromosomes.emplace_back(Chromosome::generateGenes());


    firstGeneration(chromosomes);

    fout<<"Evolution\n";
    for(int i=2; i<=N; i++){
        generation(chromosomes);
    }

}
