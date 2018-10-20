#include <iostream>

using namespace std;


float probability;
float bet;

float p(int x){
	if(x<1) return -1;
	if(x<10) return (1-probability)/9.0;
	else return probability;
}

float max(float x, float y){
	if(x>y) return x;
	else return y;
}


int main(){
	// cin >> probability;
	probability = 0.1;
	float E[42][42];
	float G[42][42];
	float F[42][42];
	float H1[42][42];
	float H2[42][42];
	float H3[42][42];
	float D1[42][42];
	float D2[42][42];
	float D3[42][42];
	float S[42][42];

	//////////INITIALISATION///////////////
	for(int i=0; i<42; i++){
		for(int j=0; j<42; j++){
			E[i][j] = 0;
			F[i][j] = 0;
			G[i][j] = 0;
			H1[i][j] = 0;
			H2[i][j] = 0;
			H3[i][j] = 0;
			D1[i][j] = 0;
			D2[i][j] = 0;
			D3[i][j] = 0;
			S[i][j] = 0;
		}
	}


	{	//////STAND/////////////
		{    ///////////////F//////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(j>21) F[i][j] = bet;
					else if(j>i && j>=17) F[i][j] = -bet;
					else if(j<i && j>=17) F[i][j] = bet;
					else if(i==j && j>17) F[i][j] = 0.0;
					else if(j>=11 && j<22){
						for(int k=1; k<=10; k++){
							F[i][j] += p(k)*F[i][j+k];
						}
					}
				}
			}
		}
	
	
		{	/////////////////G/////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(j>21) G[i][j] = F[i][j-10];
					else if(j>i && j>17) G[i][j] = -bet;
					else if(j<i && j>=17) G[i][j] = bet;
					else if(j>=11 && j<22){
						for(int k=1; k<=10; k++){
							G[i][j] += p(k)*G[i][j+k];
						}
					}
				}
			}
		}
	
	
		{	//////////////////E///////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(j>21) E[i][j] = bet;
					else if(j>i && j>=17) E[i][j] = -bet;
					else if(j<i && j>=17) E[i][j] = bet;
					else if(i==j && j>17) E[i][j] = 0.0;
					else if(i<17 && j<22 && j<=i){
						if(j==0){
							for(int k=2; k<=10; k++){
								E[i][j] += p(k)*E[i][j+k];
							}
							E[i][j] += p(1)*(-1.5*bet);	
						}
						else if(j==1){
							for(int k=2; k<=9; k++){
								E[i][j] += p(k)*E[i][j+k];
							}
							E[i][j] += p(1)*G[i][j+11];
							E[i][j] += p(10)*(-1.5*bet);
						}
						else{
							for(int k=2; k<=10; k++){
								E[i][j] += p(k)*E[i][j+k];
							}
							E[i][j] += p(1)*G[i][j+11];	
						}
						
					}
				}
			}
		}
	}







	{	////////////HIT///////////////////
		{	//////////////////H3/////////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(j>11) H3[i][j] = 0;
					else if(i>=21) H3[i][j] = -bet;
					else if(j<=11){
						for(int k=1; k<=10; k++){
							H3[i][j] += p(k)*max(H3[i+k][j], E[i+k][j]);
						}
					}
					// else if(j==10){
					// 	for(int k=2; k<=10; k++){
					// 		float temp = 0.0;
					// 		for(int l=2; l<=10; l++){
					// 			temp += p(l)*E[i+k][l+j];
					// 		}
					// 		temp += p(1)*(-1.5*bet);
					// 		H3[i][j] += p(k)*max(H3[i+k][j], temp);
					// 	}
					// }
					// else if(j==11){

					// }
				}
			}
		}
	
	
		{	/////////////////////H2///////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(i>21) H2[i][j] = H3[i-10][j];
					else if(j>21) H2[i][j] = bet;
					else if(j>=11 && j<22){
						for(int k=1; k<=10; k++){
							H2[i][j] += p(k)*max(H2[i+k][j], G[i+k][j]);
						}
					}
				}
			}
		}
	
	
		{	///////////////////H1///////////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(j>11) H1[i][j] = 0;
					else if(i>=21) H1[i][j] = -bet;
					else if(j>1){
						if(i==0){
							for(int k=2; k<=10; k++){
								float temp=0.0;
								for(int l=2; l<=10; l++){
									temp += p(l)*E[i+k][j+l];
								}
								temp += p(1)*G[i+k][j+11];
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							H1[i][j] += p(1)*(1.5*bet);
						}
						if(i==1){
							for(int k=2; k<=9; k++){
								float temp=0.0;
								for(int l=2; l<=10; l++){
									temp += p(l)*E[i+k][j+l];
								}
								temp += p(1)*G[i+k][j+11];
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							float temp=0.0;
							for(int l=2; l<=10; l++){
								temp += p(l)*E[i+11][j+l];
							}
							temp += p(1)*G[i+11][j+11];
							H1[i][j] += p(1)*max(H2[i+11][j], temp);
							H1[i][j] += p(10)*(1.5*bet);
						}
						else{
							for(int k=2; k<=10; k++){
								float temp=0.0;
								for(int l=2; l<=10; l++){
									temp += p(l)*E[i+k][j+l];
								}
								temp += p(1)*G[i+k][j+11];
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							float temp=0.0;
							for(int l=2; l<=10; l++){
								temp += p(l)*E[i+11][j+l];
							}
							temp += p(1)*G[i+11][j+11];
							H1[i][j] += p(1)*max(H2[i+11][j], temp);
						}
					}
					else if(j==1){
						if(i==0){
							for(int k=2; k<=10; k++){
								float temp=0.0;
								for(int l=2; l<=9; l++){
									temp += p(l)*G[i+k][11+l];
								}
								temp += p(1)*G[i+k][12];
								temp += p(10)*(-1.5*bet);
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							H1[i][j] += p(1)*(1.5*bet)*(1-p(10));
						}
						else if(i==1){
							for(int k=2; k<=9; k++){
								float temp=0.0;
								for(int l=2; l<=9; l++){
									temp += p(l)*G[i+k][11+l];
								}
								temp += p(1)*G[i+k][12];
								temp += p(10)*(-1.5*bet);
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							float temp=0.0;
							for(int l=2; l<=9; l++){
								temp += p(l)*E[i+11][11+l];
							}
							temp += p(1)*G[i+11][j+11];
							temp += p(10)*(-1.5*bet);
							H1[i][j] += p(1)*max(H2[i+11][j], temp);
							H1[i][j] += p(10)*(1.5*bet)*(1-p(10));
						}
						else{
							for(int k=2; k<=10; k++){
								float temp=0.0;
								for(int l=2; l<=9; l++){
									temp += p(l)*G[i+k][11+l];
								}
								temp += p(1)*G[i+k][12];
								temp += p(10)*(-1.5*bet);
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							float temp=0.0;
							for(int l=2; l<=9; l++){
								temp += p(l)*E[i+11][11+l];
							}
							temp += p(1)*G[i+11][j+11];
							temp += p(10)*(-1.5*bet);
							H1[i][j] += p(1)*max(H2[i+11][j], temp);
						}
					}
					else if(j==0){
						if(i==0){
							for(int k=2; k<=10; k++){
								float temp=0.0;
								for(int l=2; l<=9; l++){
									temp += p(l)*E[i+k][10+l];
								}
								temp += p(1)*(-1.5*bet);
								temp += p(10)*E[i+k][20];
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							H1[i][j] += p(1)*(1.5*bet)*(1-p(1));
						}
						else if(i==1){
							for(int k=2; k<=9; k++){
								float temp=0.0;
								for(int l=2; l<=9; l++){
									temp += p(l)*E[i+k][10+l];
								}
								temp += p(1)*(-1.5*bet);
								temp += p(10)*E[i+k][20];
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							float temp=0.0;
							for(int l=2; l<=9; l++){
								temp += p(l)*E[i+11][10+l];
							}
							temp += p(1)*(-1.5*bet);
							temp += p(10)*E[i+11][20];
							H1[i][j] += p(1)*max(H2[i+11][j], temp);
							H1[i][j] += p(10)*(1.5*bet)*(1-p(1));
						}
						else{
							for(int k=2; k<=10; k++){
								float temp=0.0;
								for(int l=2; l<=9; l++){
									temp += p(l)*E[i+k][10+l];
								}
								temp += p(1)*(-1.5*bet);
								temp += p(10)*E[i+k][20];
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							float temp=0.0;
							for(int l=2; l<=9; l++){
								temp += p(l)*E[i+11][10+l];
							}
							temp += p(1)*(-1.5*bet);
							temp += p(10)*E[i+11][20];
							H1[i][j] += p(1)*max(H2[i+11][j], temp);
						}
					}
				}
			}
		}
	}




	{	////////////DOUBLE///////////////////
		{	//////////////////D3/////////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(i>=21) D3[i][j] = -2*bet;
					else if(j>21) D3[i][j] = 2*bet;
					else if(j<22){
						for(int k=1; k<=10; k++){
							D3[i][j] += 2*p(k)*F[i+k][j];
						}
					}
				}
			}
		}
	
	
		{	/////////////////////D2///////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(i>21) D2[i][j] = D3[i-10][j];
					else if(j>21) D2[i][j] = 2*bet;
					else if(j<22){
						for(int k=1; k<=10; k++){
							D2[i][j] += 2*p(k)*G[i+k][j];
						}
					}
				}
			}
		}
	
	
		{	///////////////////D1///////////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(i>=21) D1[i][j] = -2*bet;
					else if(j>11) D1[i][j] = 0;
					else if(i>1){
						for(int k=2; k<=10; k++){
							D1[i][j] += 2*p(k)*E[i+k][j];
						}
						D1[i][j] += 2*p(1)*E[i+11][j];
					}
					else if(i==1){
						for(int k=2; k<=9; k++){
							D1[i][j] += 2*p(k)*E[i+k][j];
						}
						D1[i][j] += 2*p(1)*E[i+11][j];
						if(j>1) D1[i][j] += 3*p(10)*bet;
						else if(j==0) D1[i][j] += 3*bet*p(10)*(1-p(1));
						else if(j==1) D1[i][j] += 3*bet*p(10)*(1-p(10));
					}
					else if(i==0){
						for(int k=2; k<=10; k++){
							D1[i][j] += 2*p(k)*E[i+k][j];
						}
						// D1[i][j] += 2*p(1)*E[i+11][j];
						if(j>1) D1[i][j] += 3*p(1)*bet;
						else if(j==0) D1[i][j] += 3*bet*p(1)*(1-p(1));
						else if(j==1) D1[i][j] += 3*bet*p(1)*(1-p(10));
					}
					// else if(j>1){
					// 	for(int k=2; k<=10; k++){
					// 		D1[i][j] += 2*p(k)*E[i+k][j];
					// 	}
					// 	D1[i][j] += 2*p(1)*E[i+11][j];
					// }
				}
			}
		}
	}





	{	////////////SPLIT///////////////////
		{	//////////////////S/////////////////////////
			for(int i=4; i<22; i=i+2){
				for(int j=0; j<42; j++){
					if(j>21) S[i][j] = bet;
					else if(j<22){
						S[i][j] = 2*max(H1[i][j], E[i][j]);
					}
				}
			}
			for(int j=0; j<42; j++){
				S[2][j] = 2*max(H2[2][j], G[2][j]);	
			}
		}
	}

}