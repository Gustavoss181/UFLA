// Função criarMatrizProjeção(origem, direçãoX, direçãoY, centroProjeção):
//     // Calcula os vetores normalizados para o plano de projeção
//     direçãoX_normalizado = normalizar(direçãoX)
//     direçãoY_normalizado = normalizar(direçãoY)

//     // Calcula o vetor de visão (direção do olho) normalizado
//     visão = normalizar(centroProjeção - origem)

//     // Calcula o vetor que representa a direção Z do plano de projeção (produto vetorial de X e Y)
//     direçãoZ = produtoVetorial(direçãoX_normalizado, direçãoY_normalizado)

//     // Cria a matriz de projeção utilizando os vetores calculados
//     matrizProjeção = [
//         [direçãoX_normalizado.x, direçãoY_normalizado.x, direçãoZ.x, 0],
//         [direçãoX_normalizado.y, direçãoY_normalizado.y, direçãoZ.y, 0],
//         [direçãoX_normalizado.z, direçãoY_normalizado.z, direçãoZ.z, 0],
//         [-produtoEscalar(direçãoX_normalizado, origem), -produtoEscalar(direçãoY_normalizado, origem), -produtoEscalar(direçãoZ, origem), 1]
//     ]

//     Retornar matrizProjeção

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Matriz4x4{
    double** matriz;

    Matriz4x4(){
        matriz = new double* [4];
        for(int i=0; i<4; i++)
            matriz[i] = new double [4];
    }

    ~Matriz4x4(){
        for(int i=0; i<4; i++)  
            delete [] matriz[i];
        delete [] matriz;
    }

    void preencherLinha(int l, double c1, double c2, double c3, double c4){
        matriz[l][0] = c1;
        matriz[l][1] = c2;
        matriz[l][2] = c3;
        matriz[l][3] = c4;
    }

    void mostrar(){
        cout << fixed << setprecision(5);
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++)
                cout << "\t" << matriz[i][j] << " ";
            cout << endl;
        }
    }
};

struct Ponto4D{
    double x;
    double y;
    double z;
    double w;

    Ponto4D(double x, double y, double z, double w){
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Ponto4D(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
        w = 0;
    }

    Ponto4D operator-(Ponto4D &outroPonto){
        return Ponto4D(this->x - outroPonto.x, this->y - outroPonto.y, this->z - outroPonto.z);
    }

    void mostrar(){
        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
        cout << "z: " << z << endl;
        cout << "w: " << w << endl;
        cout << "----------------------" << endl;
    }
};

Ponto4D normalizar(Ponto4D vetor){
    double comprimento = sqrt(vetor.x*vetor.x + vetor.y*vetor.y + vetor.z*vetor.z);
    
    return Ponto4D(
        vetor.x / comprimento,
        vetor.y / comprimento,
        vetor.z / comprimento
    );
}

Ponto4D produtoVetorial(Ponto4D vetor1, Ponto4D vetor2){
    return Ponto4D(
        vetor1.y*vetor2.z - vetor1.z*vetor2.y,
        vetor1.z*vetor2.x - vetor1.x*vetor2.z,
        vetor1.x*vetor2.y - vetor1.y*vetor2.x
    );
}

double produtoEscalar(Ponto4D vetor1, Ponto4D vetor2){
    return vetor1.x*vetor2.x + vetor1.y*vetor2.y + vetor1.z*vetor2.z;
}

Matriz4x4 criarMatrizProjecao(Ponto4D origem, Ponto4D direcaoX, Ponto4D direcaoY, Ponto4D centroProjecao){
    Ponto4D direcaoX_normalizada = normalizar(direcaoX);
    direcaoX_normalizada.mostrar();
    Ponto4D direcaoY_normalizada = normalizar(direcaoY);
    direcaoY_normalizada.mostrar();

    // Ponto4D visao = normalizar(centroProjecao - origem);

    Ponto4D direcaoZ = produtoVetorial(direcaoX_normalizada, direcaoY_normalizada);
    direcaoZ.mostrar();

    Matriz4x4 ma;

    ma.preencherLinha(0, direcaoX_normalizada.x, direcaoY_normalizada.x, direcaoZ.x, 0);
    ma.preencherLinha(1, direcaoX_normalizada.y, direcaoY_normalizada.y, direcaoZ.y, 0);
    ma.preencherLinha(2, direcaoX_normalizada.z, direcaoY_normalizada.z, direcaoZ.z, 0);
    ma.preencherLinha(3, -produtoEscalar(direcaoX_normalizada, origem), -produtoEscalar(direcaoY_normalizada, origem), -produtoEscalar(direcaoZ, origem), 1);

    return ma;
}

int main(){
    Matriz4x4 projecao = criarMatrizProjecao(
        Ponto4D(0, 0, 0),
        Ponto4D(0.707106781, 0, 0.707106781),
        Ponto4D(0, 1, 0),
        Ponto4D(0.707106781, 0, -0.707106781, 0)
    );

    projecao.mostrar();

    return 0;
}