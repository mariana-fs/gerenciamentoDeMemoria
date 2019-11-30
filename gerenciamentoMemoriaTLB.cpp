#include <iostream>
#include <string>
#include <fstream>
#include <queue>

using namespace std;

struct tipoTLB{
    bool validade;
    int pagina;
};

void impimirTabelaDePaginas(bool tabelaPaginas[], int n);
void iniciarTLB(tipoTLB TLB[], int n);
bool verificarTLB(tipoTLB TLB[], int pagina);
void atualizarTLB(tipoTLB TLB[], int pagina, queue <int> filaTLB);


int main(){
    bool tabelaPagina[1024] = {false};
    tipoTLB TLB[128];
    queue <int> filaTLB;

    int acertoTLB = 0;
    int falhaTLB = 0;
    int acertoPagina = 0;
    int falhaPagina = 0;
    int acessoMemoria = 0;
    int operacaoES = 0;
    int pagina = 0;

    iniciarTLB(TLB,128);


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
        pagina = endereco[i]/64;
        acessoMemoria++;

        if(verificarTLB(TLB,pagina) == true){
            acertoTLB++;
            acessoMemoria++;
        }else{
            falhaTLB++;
            acessoMemoria++;
            if(tabelaPagina[pagina] == true){
                acertoPagina++;
                acessoMemoria++;
            }else{
                falhaPagina++;
                operacaoES++;
                tabelaPagina[pagina] = true;
                atualizarTLB(TLB,pagina, filaTLB);
            }
        }
    }

    cout<<"acertoPagina: " << acertoPagina << endl;
    cout<<"falhaPagina: " << falhaPagina << endl;
    cout<<"acessoMemoria: " << acessoMemoria << endl;
    cout<<"operacaoES: " << operacaoES << endl;
    cout<<"acertoTLB: " << acertoTLB << endl;
    cout<<"falhaTLB: " << falhaTLB << endl;

    //impimirTabelaDePaginas(tabelaPagina, 1024);
}

void impimirTabelaDePaginas(bool tabelaPaginas[], int n){
    for (int i=0; i<n; i++){
        cout<<tabelaPaginas[i]<<", ";
    }
}

void iniciarTLB(tipoTLB TLB[],int n){
    for(int i=0; i<n; i++){
        TLB[i].validade = false;
    }
}

bool verificarTLB(tipoTLB TLB[], int pagina){
    for(int i=0; i<sizeof(TLB); i++){
        if(TLB[i].validade == true){
            if(TLB[i].pagina == pagina){
                return true;
            }return false;
        }
    }

}

void atualizarTLB(tipoTLB TLB[], int pagina, queue <int> filaTLB){
    for(int i=0; i<sizeof(TLB);i++){
        if(TLB[i].validade == false){
            TLB[i].pagina = pagina;
            TLB[i].validade = true;
            filaTLB.push(i);
        }else{
        int posicao = filaTLB.front();
        TLB[posicao].pagina = pagina;
        TLB[posicao].validade = true;

        filaTLB.push(posicao);

        }
    }

}
