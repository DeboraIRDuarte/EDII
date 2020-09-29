#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <ratio>
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

int particionamento(int vet[], int p, int q,Saida* saida){
  int pivo = (p+q)/2;
  int i = p;
  int j = q;
  do{
       while (vet[i] < pivo){
            saida->setnComparacoes();
            i = i + 1;
       }
       while (vet[j] > pivo){
           saida->setnComparacoes();
            j = j - 1;
       }
        if (i <= j ){
            int aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
            saida->setnTrocas();
            i = i+1;
            j = j+1;
        }

  } while(i <= j);
return j;
}

void QuickSort(int vet[],int p, int r,Saida* saida){
    if (p-r > 0){
        int q = particionamento(vet,p,r,saida);
        QuickSort(vet, p, q-1,saida);
        QuickSort(vet, q+1, r,saida);
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
int main()


{
    int *vet;
    int tam;
    int c = 0;

    using namespace std::chrono;

    int nTestes;

    cout << "Informe o numero de testes: ";
    cin >> nTestes;

    Saida* saidas = new Saida[3*nTestes];

    for (int i=0; i<nTestes; i++){
        cout << "Tamanho do " << i << " teste: ";
        cin >> tam;
        vet = new int[tam];
        criaVetor(vet,tam);
        imprimeVetor(vet,tam);

        //BubbleSort
        Saida saidab = Saida("BubbleSort",tam);
        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        bubbleSort(vet,tam,&saidab);
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        saidab.setTempo(duration_cast<duration<double>>(fim-inicio).count());
        saidas[c] = saidab;
        c++;
        duration<double> time_span = duration_cast<duration<double>>(inicio-fim);
        //cout << time_span.count() << "\n";
        imprimeVetor(vet,tam);

        //QuickSort
        Saida saidaq = Saida("QuickSort", tam);
        inicio = high_resolution_clock::now();
        QuickSort(vet,0,tam,&saidaq);
        fim = high_resolution_clock::now();
        saidaq.setTempo(duration_cast<duration<double>>(fim-inicio).count());
        saidas[c] = saidaq;
        c++;
        time_span = duration_cast<duration<double>>(inicio-fim);
        imprimeVetor(vet,tam);

        //ShellSort
        Saida saidash = Saida("ShellSort",tam);
        inicio = high_resolution_clock::now();
        shellSort(vet,tam,&saidash);
        fim = high_resolution_clock::now();
        saidash.setTempo(duration_cast<duration<double>>(fim-inicio).count());
        saidas[c] = saidaq;
        c++;
        time_span = duration_cast<duration<double>>(inicio-fim);
        //cout << time_span.count() << "\n";
        imprimeVetor(vet,tam);
    }

    ofstream arquivoSaida;
    arquivoSaida.open("saida.txt");

    if (arquivoSaida.is_open()){
        for (int i=0; i<3*nTestes; i++){
            arquivoSaida << i+1 << ","
            << "Algoritmo: " << saidas[i].getAlgoritmo() << ",\t"
            << "Tamanho: " << saidas[i].getTamanho() << ",\t"
            << "Comparacoes: " << saidas[i].getnComparacoes() << ",\t"
            << "Trocas: " << saidas[i].getnTrocas() << ",\t"
            << "Tempo" << saidas[i].getTempo() << ",\t"
            << "\n";
        }
    }
    else {
        cout << "Não foi possível criar arquivo!" << endl;
    }






    delete[] saidas;
    return 0;
}
