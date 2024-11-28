#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

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
        w = 1;
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

// vetores base
const Ponto4D vetorX(1,0,0,0);
const Ponto4D vetorY(0,1,0,0);
const Ponto4D vetorZ(0,0,1,0);

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

double calculaNorma(Ponto4D vetor){
    return sqrt(vetor.x*vetor.x + vetor.y*vetor.y + vetor.z*vetor.z);
}

double acharAngulo(Ponto4D v1, Ponto4D v2){
    double normaV1 = calculaNorma(v1);
    double normaV2 = calculaNorma(v2);
    if(normaV1 == 0 or normaV2 == 0)
        return 0;
    return acos(produtoEscalar(v1, v2)/(normaV1*normaV2));
}

struct Matriz4x4{
    double matriz[4][4];

    Matriz4x4(){
        fazIdentidade();
    }

    void preencherLinha(int l, double c1, double c2, double c3, double c4){
        matriz[l][0] = c1;
        matriz[l][1] = c2;
        matriz[l][2] = c3;
        matriz[l][3] = c4;
    }

    void fazIdentidade(){
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++){
                if(i == j)
                    matriz[i][j] = 1;
                else
                    matriz[i][j] = 0;
            }
    }

    void fazerTranslacao(Ponto4D origemPlano){
        matriz[0][3] = origemPlano.x*(-1);
        matriz[1][3] = origemPlano.y*(-1);
        matriz[2][3] = origemPlano.z*(-1);
    }

    void fazerRotacaoY(Ponto4D vetor){
        Ponto4D vetorProjetadoXZ(vetor.x, 0, vetor.z);
        double angulo = acharAngulo(vetorProjetadoXZ, vetorX);
        Ponto4D prodV = produtoVetorial(vetorProjetadoXZ, vetorX);
        if(prodV.y < 0)
            angulo*=-1;
        
        matriz[0][0] =  cos(angulo);
        matriz[0][2] =  sin(angulo);
        matriz[2][0] = -sin(angulo);
        matriz[2][2] =  cos(angulo);
    }

    void fazerRotacaoZ(Ponto4D vetor){
        Ponto4D vetorProjetadoXY(vetor.x, vetor.y, 0);
        double angulo = acharAngulo(vetorProjetadoXY, vetorX);
        Ponto4D prodV = produtoVetorial(vetorProjetadoXY, vetorX);
        if(prodV.z < 0)
            angulo*=-1;
        
        matriz[0][0] =  cos(angulo);
        matriz[0][1] = -sin(angulo);
        matriz[1][0] =  sin(angulo);
        matriz[1][1] =  cos(angulo);
    }

    void fazerRotacaoX(Ponto4D vetor){
        Ponto4D vetorProjetadoYZ(0, vetor.y, vetor.z);
        double angulo = acharAngulo(vetorProjetadoYZ, vetorY);
        Ponto4D prodV = produtoVetorial(vetorProjetadoYZ, vetorY);
        if(prodV.x < 0)
            angulo*=-1;
        
        matriz[1][1] =  cos(angulo);
        matriz[1][2] = -sin(angulo);
        matriz[2][1] =  sin(angulo);
        matriz[2][2] =  cos(angulo);
    }

    void fazerCisalhamento(Ponto4D ponto){
        if(ponto.z != 0){
            double shx = (-ponto.x) / ponto.z;
            double shy = (-ponto.y) / ponto.z;

            matriz[0][2] = shx;
            matriz[1][2] = shy;
        }
    }

    void fazerEspecial(Ponto4D origem_alterado){
        if(origem_alterado.z != 0 ){
            matriz[3][2] = 1/origem_alterado.z;
            matriz[3][3] = 0;
        }
    }

    Matriz4x4 operator*(Matriz4x4 outraMatriz){
        Matriz4x4 result;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                double soma = 0;
                for(int k=0; k<4; k++){
                    soma += matriz[i][k] * outraMatriz.matriz[k][j];
                }
                result.matriz[i][j] = soma;
            }
        }
        return result;
    }

    Ponto4D operator*(Ponto4D vetor){
        Ponto4D result(0,0,0,0);
        result.x = matriz[0][0]*vetor.x + matriz[0][1]*vetor.y + matriz[0][2]*vetor.z + matriz[0][3]*vetor.w;
        result.y = matriz[1][0]*vetor.x + matriz[1][1]*vetor.y + matriz[1][2]*vetor.z + matriz[1][3]*vetor.w;
        result.z = matriz[2][0]*vetor.x + matriz[2][1]*vetor.y + matriz[2][2]*vetor.z + matriz[2][3]*vetor.w;
        result.w = matriz[3][0]*vetor.x + matriz[3][1]*vetor.y + matriz[3][2]*vetor.z + matriz[3][3]*vetor.w;
        return result;
    }

    void mostrar(){
        cout << fixed << setprecision(5);
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(matriz[i][j] == 0)
                    matriz[i][j] = 0;
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }
    }
};

void criarMatrizProjecao(Ponto4D origem, Ponto4D direcaoX, Ponto4D direcaoY, Ponto4D centroDireProj){
    // Ponto4D dirX_normalizado = normalizar(direcaoX);
    // Ponto4D dirY_normalizado = normalizar(direcaoY);

    Matriz4x4 MtzTrans;
    MtzTrans.fazerTranslacao(origem);

    Matriz4x4 MtzRot1;
    MtzRot1.fazerRotacaoY(direcaoX);

    Ponto4D dirX_alterado = MtzRot1*direcaoX;
    Ponto4D dirY_alterado = MtzRot1*direcaoY;
    Matriz4x4 MtzRot2;
    MtzRot2.fazerRotacaoZ(dirX_alterado);

    dirX_alterado = MtzRot2*dirX_alterado;
    dirY_alterado = MtzRot2*dirY_alterado;
    Matriz4x4 MtzRot3;
    MtzRot3.fazerRotacaoX(dirY_alterado);

    Matriz4x4 MtzAux = MtzRot3*MtzRot2*MtzRot1*MtzTrans;
    Ponto4D centroDireProj_alterado = MtzAux*centroDireProj;

    Matriz4x4 MtzResult;
    if(centroDireProj.w == 0){
        Matriz4x4 MtzCisa;
        MtzCisa.fazerCisalhamento(centroDireProj_alterado);

        MtzResult = MtzCisa*MtzAux;
    }
    else{
        Matriz4x4 MtzTransCentro;
        MtzTransCentro.fazerTranslacao(centroDireProj_alterado);

        Ponto4D origem_alterado = MtzAux * origem;
        origem_alterado = MtzTransCentro * origem_alterado;

        Matriz4x4 MtzCisa;
        MtzCisa.fazerCisalhamento(origem_alterado);
        origem_alterado = MtzCisa * origem_alterado;

        Matriz4x4 MtzEspecial;
        MtzEspecial.fazerEspecial(origem_alterado);

        MtzResult = MtzEspecial*MtzCisa*MtzTransCentro*MtzAux;
    }
    
    MtzResult.mostrar();
}

int main(){
    double x, y, z, w;

    cin >> x >> y >> z;
    Ponto4D origem(x, y, z);

    cin >> x >> y >> z;
    Ponto4D direcaoX(x, y, z, 0);

    cin >> x >> y >> z;
    Ponto4D direcaoY(x, y, z, 0);

    cin >> x >> y >> z >> w;
    Ponto4D centroDireProj(x, y, z, w);

    criarMatrizProjecao(
        origem,
        direcaoX,
        direcaoY,
        centroDireProj
    );

    return 0;
}