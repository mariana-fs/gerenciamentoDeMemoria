#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void impimirTabelaDePaginas(bool tabelaPaginas[], int n);

int main(){
    bool tabelaPagina[2048] = {false};
    int acertoPagina = 0;
    int falhaPagina = 0;
    int acessoMemoria = 0;
    int operacaoES = 0;
    int pagina = 0;


    ifstream inFile;
    inFile.open("sequencia02.dat");

    if(inFile.fail()){
        cerr << "Erro ao abrir arquivo" << endl;
        //exit(1);
    }

    int endereco[17000] = {0};

    int value;
    int n = 0;
    while(inFile >> value)
        {
        endereco[n] = value;
        n++;
    }
    for(int i=0; i<n;i++){
        pagina = endereco[i]/32;
        acessoMemoria++;
        if(tabelaPagina[pagina] == true){
            acertoPagina++;
            acessoMemoria++;
        }else{
            falhaPagina++;
            operacaoES++;
            tabelaPagina[pagina] = true;
        }

    }

    cout<<"acertoPagina: " << acertoPagina << endl;
    cout<<"falhaPagina: " <<falhaPagina << endl;
    cout<<"acessoMemoria: " <<acessoMemoria << endl;
    cout<<"operacaoES: " <<operacaoES << endl;

    impimirTabelaDePaginas(tabelaPagina, 1024);
}

void impimirTabelaDePaginas(bool tabelaPaginas[], int n){
    for (int i=0; i<n; i++){
        cout<<tabelaPaginas[i]<<", ";
    }
}
