#ifndef SAIDA_H_INCLUDED
#define SAIDA_H_INCLUDED
#include <sstream>

// TAD do objeto sa�da, com as infos que v�o para o arquivo de sa�da
using namespace std;

class Saida{
private:

    string algoritmo;
    string tamanhos;
    int nComparacoes;
    int nTrocas;
    double tempo;


public:



    Saida (string algoritmos, int tamanho)
    {
        algoritmo = algoritmos;

        stringstream ss;

        ss << tamanho;
        tamanhos = ss.str();
        ss.str("");

        nComparacoes = 0;
        nTrocas = 0;
        tempo = 0.0;

    };

    Saida(){};

    string getAlgoritmo(){
        return algoritmo;
    }

    string getTamanho(){
        return tamanhos;
    }

    int getComparacoes(){
        return nComparacoes;
    }

    int getTrocas(){
        return nTrocas;
    }
    double getTempo(){
        return tempo;
    }

    void setnComparacoes(){
        nComparacoes++;
    }

    void setnTrocas (){
        nTrocas++;
    }

    void setTempo( float ntempo){
        tempo = ntempo;
    }

    ~Saida(){};
};


#endif // SAIDA_H_INCLUDED
