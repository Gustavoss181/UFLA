#include <fstream>

int main(){
    std::ofstream arq("caracteres.txt");

    if(arq){
        for(int i=0; i<225; i++){
            char a = i;
            arq << "Alt + " << i << " -> " << a << std::endl;
        }
        arq.close();
    }

    return 0;
}