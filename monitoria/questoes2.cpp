#include <iostream>
using namespace std;

void contador(string emoticons[], string linhas[], int N, int M, int& qtd){
    bool mudancas;

    for(int j=0; j<N; j++){
        for(int i=0; i<M; i++){
            for(unsigned y=0; y<linhas[i].length(); y++){
                if(linhas[i][y] == emoticons[j][0]){
                    mudancas = true;
                    for(unsigned z=1; z<emoticons[j].size(); z++){
                        if(linhas[i][y+z] != emoticons[j][z])
                            mudancas = false;
                    }
                    if(mudancas)
                        qtd += emoticons[j].size();
                }
            }
        }
    }
}

int main(){
    int N, M;

    cin >> N >> M;
    while(N != 0 and M != 0){
        int qtd=0;
        string emoticons[N];
        string linhas[M];

        cin.ignore(100, '\n');
        cin.clear();

        for(int i=0; i<N; i++){
            cout << "emote " << i << ": ";
            getline(cin, emoticons[i]);
        }
        for(int i=0; i<M; i++){
            cout << "frase " << i << ": ";
            getline(cin, linhas[i]);
        }

        contador(emoticons, linhas, N, M, qtd);

        cout<<qtd<<endl;

        cin>>N>>M;
    }
    return 0;
}