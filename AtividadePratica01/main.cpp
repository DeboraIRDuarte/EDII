#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include "saida.h"

using namespace std;

void criaVetor(int vet[],int tam){

    for (int i=0; i<tam; i++){
        vet[i] = rand() % 100;
    }
}

void imprimeVetor(int vet[], int tam){
    for (int i=0; i<tam; i++){
        cout << vet[i] << "\t";
    }
    cout << endl;
}

void bubbleSort(int vet[], int tam, Saida* saida){
    for (int i=tam-1; i>0; i--){
        for (int j=0; j<=i; j++){
            saida->setnComparacoes();
            if (vet[j] > vet[j+1]){
                int aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
                saida->setnTrocas();
            }
        }
    }
}

void MaxHeapfy(int vet[],int tam, int i,Saida* saida){
    int maior =i;
    int esq = 2*i+1;
    int dir = 2*i+2;

    //se filho a esquerda é maior que a raiz
    saida->setnComparacoes();
    if(esq<tam && vet[esq]>vet[maior]){
        maior = esq;
    }

    //se filho a direita é maior que "maior"
    saida->setnComparacoes();
    if (dir<tam && vet[dir]>vet[maior]){
        maior=dir;
    }

    //se maior não é a raiz
    if (maior!=i){
        saida->setnTrocas();
        int aux = vet[i];//troca maior e raiz
        vet[i] = vet[maior];
        vet[maior] = aux;

        MaxHeapfy(vet,tam,maior,saida);//maxheapfy a sub-arvore afetada
    }
}

void HeapSort(int vet[],int tam,Saida* saida){

    //constroi a heap e ordena o vetor
    for(int i=tam/2-1; i>=0; i--){
        MaxHeapfy(vet,tam,i,saida);

    }

    //extrai elementos um a um da heap
    for (int i=tam-1; i>=0;i--){

        int aux = vet[0];//move a raiz para o final
        vet[0] = vet[i];
        vet[i] = aux;
        saida->setnTrocas();

        //max heapfy a heap reduzida
        MaxHeapfy(vet,i,0,saida);

    }
}

void shellSort(int *V, int tam,Saida* saida){
  int i, j, incremento, t;
  incremento = 3;
  while (incremento > 0){
    for (i = 0; i < tam; i++){
      j = i;
      t = V[i];
      while ((j >= incremento) && (V[j - incremento] > t)){
        saida->setnComparacoes();
        V[j] = V[j - incremento];
        saida->setnTrocas();
        j = j - incremento;
      }
      V[j] = t;
    }
    if (incremento / 2 != 0)
      incremento = incremento / 2;
    else if (incremento == 1)
      incremento = 0;
    else
      incremento = 1;
  }
}
int main(){

    clock_t t;

    int *vet;
    int tam;
    int c = 0;


    int nTestes;

    cout << "Informe o numero de testes: ";
    cin >> nTestes;

    Saida* saidas = new Saida[3*nTestes];

    for (int i=0; i<nTestes; i++){
        cout << "Tamanho do " << i << " teste: ";
        cin >> tam;
        vet = new int[tam];


        //BubbleSort
        criaVetor(vet,tam); //cria um vetor com valores aleatórios
        Saida saidab = Saida("BubbleSort",tam);
        t = clock();
        bubbleSort(vet,tam,&saidab);
        t = clock() - t;
        saidab.setTempo(((float)t)/CLOCKS_PER_SEC);
        saidas[c] = saidab;
        c++;

        //imprimeVetor(vet,tam);

        //HeapSort
        criaVetor(vet,tam); //cria um vetor com valores aleatórios
        Saida saidaq = Saida("HeapSort  ", tam);
        t = clock();
        HeapSort(vet,tam,&saidaq);
        t = clock() - t;
        saidaq.setTempo(((float)t)/CLOCKS_PER_SEC);
        saidas[c] = saidaq;
        c++;

        //imprimeVetor(vet,tam);

        //ShellSort
        criaVetor(vet,tam); //cria um vetor com valores aleatórios
        Saida saidash = Saida("ShellSort ",tam);
        t = clock();
        shellSort(vet,tam,&saidash);
        t = clock() - t;
        saidash.setTempo(((float)t)/CLOCKS_PER_SEC);
        saidas[c] = saidash;
        c++;

        //imprimeVetor(vet,tam);
    }

    //gravando no arquivo de saida
    ofstream arquivoSaida;
    arquivoSaida.open("saida.txt");

    if (arquivoSaida.is_open()){
        for (int i=0; i<3*nTestes; i++){
            string nome;
            nome = saidas[i].getAlgoritmo();
            arquivoSaida << i+1 << ","
            << "Algoritmo: " << nome << ",  "
            << "Tamanho: " << saidas[i].getTamanho() << ",  "
            << "Comparacoes: " << saidas[i].getComparacoes() << ",  "
            << "Trocas: " << saidas[i].getTrocas() << ",  "
            << "Tempo: " << saidas[i].getTempo() << ",  "
            << "\n\n";
        }
        cout << "Arquivo criado!" << endl;
    }
    else {
        cout << "Não foi possível criar arquivo!" << endl;
    }






    delete[] saidas;
    return 0;
}
