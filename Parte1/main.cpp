//
//  main.cpp
//  Parte1
//
//  Created by João Miguel on 11/02/21.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class no{
    char chave;
    int qtd;
    no *anterior, *proximo, *esq, *dir;
    string codigo;

public:

    no(char chave, no *anterior=NULL, no *proximo=NULL, no *esq=NULL, no *dir=NULL, int qtd=1):chave(chave),anterior(anterior),proximo(proximo),esq(esq),dir(dir),qtd(qtd){
    }

    ~no(){
    }

    char getChave(){ return chave; }
    int getQtd(){ return qtd; }
    no *getAnterior(){ return anterior;}
    no *getProximo(){ return proximo; }
    no *getEsq(){ return esq; }
    no *getDir(){ return dir; }
    string getCodigo(){ return codigo; }

    void setAnterior(no *novoAnterior){ anterior = novoAnterior; }
    void setProximo(no *novoProximo){ proximo = novoProximo; }
    void setEsq(no *novoEsq){ esq = novoEsq; }
    void setDir(no *novoDir){ dir = novoDir; }
    void setChave(char auxChave){ chave = auxChave; }
    void setQtd(int auxQtd){ qtd = auxQtd; }
    void setCodigo(string auxCodigo){ codigo = auxCodigo; }

    void aumQtd(){
        qtd++;
        no *pNo = this;
        while(pNo->anterior!=NULL && this->qtd > pNo->anterior->qtd){
            pNo = pNo->anterior;
        }
        this->troca(pNo);
    }

    void troca(no *no1){
        char auxChar = no1->getChave();
        int auxInt = no1->getQtd();
        no1->setChave(this->getChave());
        no1->setQtd(this->getQtd());
        this->setChave(auxChar);
        this->setQtd(auxInt);
    }

    void printPreOrdem(ofstream &arquivo){
        arquivo << chave;
        if(chave==0){
            esq->printPreOrdem(arquivo);
            dir->printPreOrdem(arquivo);
        }
    }

/*    void printOrdemSimetrica(ofstream arquivo){
        if(chave==0){
            esq->printOrdemSimetrica(arquivo);
            arquivo << chave;
            dir->printOrdemSimetrica(arquivo);
        }
        else arquivo << chave;
    }
*/
};


class lista{
    no *primeiro, *ultimo;
    int contador;

public:

    lista(){
        primeiro = NULL;
        ultimo = NULL;
    }

    ~lista(){
        no *pNo = primeiro;
        while(pNo!=NULL){
            delete pNo;
            pNo = pNo->getProximo();
        }
    }

    void setPrimeiro(no *novoPrimeiro){ primeiro = novoPrimeiro; }
    void setUltimo(no *novoUltimo){ ultimo = novoUltimo; }

    no *getPrimeiro(){ return primeiro; }
    no *getUltimo(){ return ultimo; }

    void aumContador(){
        contador++;
    }

    void addChar(char c){
        if(buscarChave(c)==NULL) inserirChave(c);
        else buscarChave(c)->aumQtd();
    }

    no *buscarChave(char c){
        no *pNo = primeiro;
        while(pNo!=NULL){
            if(pNo->getChave() == c) return pNo;
            else pNo = pNo->getProximo();
        }
        return NULL;
    }

    no *buscarCodigo(string cod){
        no *pNo = primeiro;
        while(pNo!=NULL){
            if(pNo->getCodigo().compare(cod) == 0){
                return pNo;
            }
            else pNo = pNo->getProximo();
        }
        return NULL;
    }

    void inserirChave(char c){
        no *pNo = new (nothrow) no(c, ultimo);
        if(primeiro==NULL && ultimo==NULL){
            primeiro = pNo;
            ultimo = pNo;
        }
        else{
            ultimo->setProximo(pNo);
            ultimo = pNo;
        }
    }

    void inserirCodigo(int c, string cod){
        no *pNo = new (nothrow) no(c, ultimo);
        pNo->setCodigo(cod);
        if(primeiro==NULL && ultimo==NULL){
            primeiro=pNo;
            ultimo=pNo;
        }
        else{
            ultimo->setProximo(pNo);
            ultimo=pNo;
        }
    }

    void printCodigos(){
        cout << "\n\nEis os codigos:" << endl;
        no *outroNo = primeiro;
        while(outroNo!=NULL){
            cout << outroNo->getChave() << " " << outroNo->getCodigo() << endl;
            outroNo = outroNo->getProximo();
        }
        cout << endl;
    }

    void printLista(){
        cout << "Eis a lista:" << endl;
        no *outroNo = primeiro;
        while(outroNo!=NULL){
            cout << setiosflags(ios::left) << setw(3) << setfill('.') << outroNo->getChave() << setw(10) << resetiosflags(ios::left) << setiosflags(ios::right) << outroNo->getQtd() << resetiosflags(ios::right) << endl;
            outroNo = outroNo->getProximo();
        }
        cout << endl;
    }

    no *gerarArvHuf(){

        while(primeiro!=ultimo->getAnterior()){
            no *novoNo = new (nothrow) no(0, NULL, NULL, ultimo->getAnterior(), ultimo, ultimo->getQtd() + ultimo->getAnterior()->getQtd());

            if(novoNo->getQtd() <= ultimo->getAnterior()->getAnterior()->getQtd()){
                ultimo->getAnterior()->getAnterior()->setProximo(novoNo);
                novoNo->setAnterior(ultimo->getAnterior()->getAnterior());
                ultimo = novoNo;
            }

            else if(novoNo->getQtd() >= primeiro->getQtd()){
                primeiro->setAnterior(novoNo);
                novoNo->setProximo(primeiro);
                primeiro = novoNo;
                ultimo = ultimo->getAnterior()->getAnterior();
                ultimo->setProximo(NULL);
            }

            else{
                no *pNo = primeiro;
                while(novoNo->getQtd() < pNo->getQtd()){
                    pNo = pNo->getProximo();
                }
                pNo->getAnterior()->setProximo(novoNo);
                novoNo->setAnterior(pNo->getAnterior());
                pNo->setAnterior(novoNo);
                novoNo->setProximo(pNo);
                ultimo = ultimo->getAnterior()->getAnterior();
                ultimo->setProximo(NULL);
            }
        }

        no *novoNo = new (nothrow) no(0, NULL, NULL, primeiro, ultimo, primeiro->getQtd() + ultimo->getQtd());
        primeiro = novoNo;
        ultimo = novoNo;

        this->printLista();

        return primeiro;
    }
};


void gerarCodigos(no *pNo, lista &Lista, string tempStr){
    if(pNo->getChave()==0){
        tempStr+='0';
        gerarCodigos(pNo->getEsq(), Lista, tempStr);
        tempStr.pop_back();
        tempStr+='1';
        gerarCodigos(pNo->getDir(), Lista, tempStr);
        tempStr.pop_back();
    }
    else{
        Lista.inserirCodigo(pNo->getChave(), tempStr);
    }
}

int main(){

    int i=0;
    char c;
    no *raizArv, *pNo;
    lista freqList, codigos;
    string auxStr;
    ifstream arq;
    ofstream arqSaida;

    // ABRE input.txt E CRIA A LISTA DE FREQU NCIAS

    arq.open("input.txt", ios::in);
    if(!arq.is_open()){
        cout << "Erro ao abrir arquivo\n";
        return -1;
    }
    while(arq.good() && !arq.eof()){
        arq >> noskipws >> c;
        freqList.addChar(c);
    }
    freqList.printLista();
    if(arq.bad() || !arq.eof()){
        cout << "Erro na leitura :(" << endl;
        return -1;
    }
    arq.close();

    // GERA A ¡RVORE DE HUFFMAN

    raizArv = freqList.gerarArvHuf();

    // GERA E ESCREVE arvhuf.txt

    arqSaida.open("arvhuf.txt", ios::out);
    if(!arqSaida.is_open()){
        cout << "Erro na abertura de arvhuf.txt" << endl;
        return -1;
    }
    raizArv->printPreOrdem(arqSaida);
    arqSaida.close();

    // GERA E IMPRIME OS C”DIGOS BIN¡RIOS

    gerarCodigos(raizArv, codigos, auxStr);

    codigos.printCodigos();

    cout << endl << endl;

    // CIRA BibliaCodificada.txt E ESCREVE

    arq.open("input.txt", ios::in);
    if(!arq.is_open()){
        cout << "Erro ao abrir arquivo" << endl;;
        return -1;
    }

    arqSaida.open("texto.txt", ios::out);
    if(!arqSaida.is_open()){
        cout << "Erro na abertura" << endl;
        return -1;
    }

    while(arq.good() && !arq.eof()){
        arq >> noskipws >> c;
        arqSaida << codigos.buscarChave(c)->getCodigo();
    }

    arqSaida.close();
    arq.close();




    return 0;
}
