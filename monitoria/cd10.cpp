#include <iostream>
using namespace std;
int main(){
	int A, B;
	bool ha = false;
	cin>>A>>B;
	
	int vetor1[A], vetor2[B];
	 
	 for(int i=0; i<A; i++){
		 cin>>vetor1[i];
	 }
	 for(int i=0; i<B; i++){
		 cin>>vetor2[i];
	 }
	 for(int z=0; z<A; z++){ 
		for(int i=0; i<B; i++){
			if(vetor1[z]==vetor2[i]){
				cout<<vetor1[z]<<" ";
				ha = true;
			}
		}
	}
	if(ha==false){
		 cout<<"-1";
	 }
	
	
	return 0;
}
