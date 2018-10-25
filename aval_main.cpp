// Blackjack lose done
// Blackjack win and draw remains
// In stand we have handled blackjack loss condition before reaching 21. If someone reaches 21 then its non blackjack
// i == 0 signifies blackjack in my iitial hand

#include <iostream>
#include <limits>
using namespace std;

int MIN_INT = numeric_limits<int>::min();
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

void solve_the_game(){
	
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
					if(j>21) F[i][j] = bet;					// Dealer busts
					else if(j>i && j>=17) F[i][j] = -bet;	// j >= 17
					else if(j<i && j>=17) F[i][j] = bet;
					else if(i==j && j>=17) F[i][j] = 0.0;	//push condition & never blackjack here
					else if(j>=11 && j<22){					// dealer hit condition
						for(int k=1; k<=10; k++){
							F[i][j] += p(k)*F[i][j+k];
						}
					}
				}
			}
		}
	
	
		{	/////////////////G/////////////////////
			for(int i=41; i>=0; i--){						// Atleast 1 ace of value 11
				for(int j=41; j>=0; j--){
					if(j>21) G[i][j] = F[i][j-10];			// if j > 21 convert 11 valued ace to 1 valued
					else if (j < 11) G[i][j] = MIN_INT;		// if j < 11 G[i][j] is highly negative		
					else if(j>i && j>=17) G[i][j] = -bet;	// if j >= 17
					else if(j<i && j>=17) G[i][j] = bet;
					else if(j==i && j>=17) G[i][j] = 0.0;		//push condition
					else if(j>=11 && j<17){					// dealer hit condition
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
					if(j>21) E[i][j] = bet;					// I win if dealer busts
					else if(i>21) E[i][j] = -bet;			// I lose if I already busted
					else if(j>i && j>=17) E[i][j] = -bet;	// I lose if I was less when dealer was above 17 with no ace
					else if(j<i && j>=17 && i!=0) E[i][j] = bet;	// I win if I was greater when dealer was above 17
					else if(j<i && j>=17 && i==0) E[i][j] = 1.5*bet;	// I win if I was blackjack
					else if(i==j && j>=17 && i!=0) E[i][j] = 0.0;	// I draw if dealer and I equal at or above 17. BlackJack condition handled earlier
					else if(/*i<17 &&*/ j<17/* && j<=i*/){	// Left case when j < 17 no matter what i is. Dealer has to hit		
						if(j==0){
							for(int k=2; k<=10; k++){
								E[i][j] += p(k)*E[i][j+k];
							}
							if(i != 0){						// if player is non-blackjack
								E[i][j] += p(1)*(-1*bet);	// He loses against blackjack
							}else{
								E[i][j] += 0;				// push
							}
						}
						else if(j==1){
							for(int k=2; k<=9; k++){
								E[i][j] += p(k)*E[i][j+k];	
							}
							E[i][j] += p(1)*G[i][j+11];
							if(i!=0){
								E[i][j] += p(10)*(-1*bet);
							}else{
								E[i][j] += 0;
							}
						}
						else{
							if(i!=0){
								for(int k=2; k<=10; k++){
									E[i][j] += p(k)*E[i][j+k];
								}
								E[i][j] += p(1)*G[i][j+11];	
							}else{
								E[i][j] += 1.5*bet;
							}
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
					if(j>11) H3[i][j] = MIN_INT;						// dealer has only 1 card so can't be > 11
					else if(i>=21) H3[i][j] = -bet;						// If I hit at >= 21 the I bust
					else if(j<=11){										// BlackJack can't occur in H3
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
					if(i>21) H2[i][j] = H3[i-10][j];					// convert 11 valued ace to 1 valued
					else if(i<11) H2[i][j] = MIN_INT;					// i < 11 not defined
					else if(j>21) H2[i][j] = bet;						
					else if(i>=11 && i<22){								
						for(int k=1; k<=10; k++){
							H2[i][j] += p(k)*max(H2[i+k][j], E[i+k][j]);
						}
					}
				}
			}
		}
	
	
		{	///////////////////H1///////////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(j>11) H1[i][j] = MIN_INT;
					else if(i>=21) H1[i][j] = -1*bet;
					// else if(j>11 && j<=21){
					// 	if(j>12){
					// 		if(i==0){
					// 			H1[i][j] += (1.5*bet);
					// 		}
					// 		if(i==1){
					// 			H1[i][j] += MIN_INT;
					// 		}
					// 		else{
					// 			if(i==0){
					// 				H1[i][j] = 1.5*bet;
					// 			}else{
					// 				for(int k=2; k<=10; k++){
					// 					float temp=0.0;
					// 					for(int l=2; l<=10; l++){
					// 						temp += p(l)*E[i+k][j+l];
					// 					}
					// 					temp += p(1)*G[i+k][j+11];
					// 					H1[i][j] += p(k)*max(H1[i+k][j], temp);
					// 				}
					// 				float temp=0.0;
					// 				for(int l=2; l<=10; l++){
					// 					temp += p(l)*E[i+11][j+l];
					// 				}
					// 				temp += p(1)*G[i+11][j+11];
					// 				H1[i][j] += p(1)*max(H2[i+11][j], temp);
					// 			}
					// 		}
					// 	}
					// 	else if(j==1){
					// 		if(i==0){
					// 			// for(int k=2; k<=10; k++){
					// 			// 	float temp=0.0;
					// 			// 	for(int l=2; l<=9; l++){
					// 			// 		temp += p(l)*G[i+k][11+l];
					// 			// 	}
					// 			// 	temp += p(1)*G[i+k][12];
					// 			// 	temp += p(10)*(-1.5*bet);
					// 			// 	H1[i][j] += p(k)*max(H1[i+k][j], temp);
					// 			// }
					// 			H1[i][j] += (1.5*bet)*(1-p(10));
					// 		}
					// 		else if(i==1){
					// 			// for(int k=2; k<=9; k++){
					// 			// 	float temp=0.0;
					// 			// 	for(int l=2; l<=9; l++){
					// 			// 		temp += p(l)*G[i+k][11+l];
					// 			// 	}
					// 			// 	temp += p(1)*G[i+k][12];
					// 			// 	temp += p(10)*(-1.5*bet);
					// 			// 	H1[i][j] += p(k)*max(H1[i+k][j], temp);
					// 			// }
					// 			// float temp=0.0;
					// 			// for(int l=2; l<=9; l++){
					// 			// 	temp += p(l)*E[i+11][11+l];
					// 			// }
					// 			// temp += p(1)*G[i+11][j+11];
					// 			// temp += p(10)*(-1.5*bet);
					// 			// H1[i][j] += p(1)*max(H2[i+11][j], temp);
					// 			// H1[i][j] += p(10)*(1.5*bet)*(1-p(10));
					// 			H1[i][j] += MIN_INT;
					// 		}
					// 		else{
					// 			for(int k=2; k<=10; k++){
					// 				float temp=0.0;
					// 				for(int l=2; l<=9; l++){
					// 					temp += p(l)*G[i+k][11+l];
					// 				}
					// 				temp += p(1)*G[i+k][12];
					// 				temp += p(10)*(-1*bet);
					// 				H1[i][j] += p(k)*max(H1[i+k][j], temp);
					// 			}
					// 			float temp=0.0;
					// 			for(int l=2; l<=9; l++){
					// 				temp += p(l)*G[i+11][11+l];
					// 			}
					// 			temp += p(1)*G[i+11][12];
					// 			temp += p(10)*(-1*bet);
					// 			H1[i][j] += p(1)*max(H2[i+11][j], temp);
					// 		}
					// 	}
					// 	else if(j==0){
					// 		if(i==0){
					// 			// for(int k=2; k<=10; k++){
					// 			// 	float temp=0.0;
					// 			// 	for(int l=2; l<=9; l++){
					// 			// 		temp += p(l)*E[i+k][10+l];
					// 			// 	}
					// 			// 	temp += p(1)*(-1.5*bet);
					// 			// 	temp += p(10)*E[i+k][20];
					// 			// 	H1[i][j] += p(k)*max(H1[i+k][j], temp);
					// 			// }
					// 			H1[i][j] += (1.5*bet)*(1-p(1));
					// 		}
					// 		else if(i==1){
					// 			// for(int k=2; k<=9; k++){
					// 			// 	float temp=0.0;
					// 			// 	for(int l=2; l<=9; l++){
					// 			// 		temp += p(l)*E[i+k][10+l];
					// 			// 	}
					// 			// 	temp += p(1)*(-1.5*bet);
					// 			// 	temp += p(10)*E[i+k][20];
					// 			// 	H1[i][j] += p(k)*max(H1[i+k][j], temp);
					// 			// }
					// 			// float temp=0.0;
					// 			// for(int l=2; l<=9; l++){
					// 			// 	temp += p(l)*E[i+11][10+l];
					// 			// }
					// 			// temp += p(1)*(-1.5*bet);
					// 			// temp += p(10)*E[i+11][20];
					// 			// H1[i][j] += p(1)*max(H2[i+11][j], temp);
					// 			// H1[i][j] += p(10)*(1.5*bet)*(1-p(1));
					// 			H1[i][j] += MIN_INT;
					// 		}
					// 		else{
					// 			for(int k=2; k<=10; k++){
					// 				float temp=0.0;
					// 				for(int l=2; l<=9; l++){
					// 					temp += p(l)*E[i+k][10+l];
					// 				}
					// 				temp += p(1)*(-1*bet);
					// 				temp += p(10)*E[i+k][20];
					// 				H1[i][j] += p(k)*max(H1[i+k][j], temp);
					// 			}
					// 			float temp=0.0;
					// 			for(int l=2; l<=9; l++){
					// 				temp += p(l)*E[i+11][10+l];
					// 			}
					// 			temp += p(1)*(-1*bet);
					// 			temp += p(10)*E[i+11][20];
					// 			H1[i][j] += p(1)*max(H2[i+11][j], temp);
					// 		}
					// 	}
					// }
					else if(j>1){
						if(i==0){
							// for(int k=2; k<=10; k++){
							// 	float temp=0.0;
							// 	for(int l=2; l<=10; l++){
							// 		temp += p(l)*E[i+k][j+l];
							// 	}
							// 	temp += p(1)*G[i+k][j+11];
							// 	H1[i][j] += p(k)*max(H1[i+k][j], temp);
							// }
							H1[i][j] += (1.5*bet);
						}
						if(i==1){
							// for(int k=2; k<=9; k++){
							// 	float temp=0.0;
							// 	for(int l=2; l<=10; l++){
							// 		temp += p(l)*E[i+k][j+l];
							// 	}
							// 	temp += p(1)*G[i+k][j+11];
							// 	H1[i][j] += p(k)*max(H1[i+k][j], temp);
							// }
							// float temp=0.0;
							// for(int l=2; l<=10; l++){
							// 	temp += p(l)*E[i+11][j+l];
							// }
							// temp += p(1)*G[i+11][j+11];
							// H1[i][j] += p(1)*max(H2[i+11][j], temp);
							H1[i][j] += MIN_INT;
						}
						else{
							if(i==0){
								H1[i][j] = 1.5*bet;
							}else{
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
					}
					else if(j==1){
						if(i==0){
							// for(int k=2; k<=10; k++){
							// 	float temp=0.0;
							// 	for(int l=2; l<=9; l++){
							// 		temp += p(l)*G[i+k][11+l];
							// 	}
							// 	temp += p(1)*G[i+k][12];
							// 	temp += p(10)*(-1.5*bet);
							// 	H1[i][j] += p(k)*max(H1[i+k][j], temp);
							// }
							H1[i][j] += (1.5*bet)*(1-p(10));
						}
						else if(i==1){
							// for(int k=2; k<=9; k++){
							// 	float temp=0.0;
							// 	for(int l=2; l<=9; l++){
							// 		temp += p(l)*G[i+k][11+l];
							// 	}
							// 	temp += p(1)*G[i+k][12];
							// 	temp += p(10)*(-1.5*bet);
							// 	H1[i][j] += p(k)*max(H1[i+k][j], temp);
							// }
							// float temp=0.0;
							// for(int l=2; l<=9; l++){
							// 	temp += p(l)*E[i+11][11+l];
							// }
							// temp += p(1)*G[i+11][j+11];
							// temp += p(10)*(-1.5*bet);
							// H1[i][j] += p(1)*max(H2[i+11][j], temp);
							// H1[i][j] += p(10)*(1.5*bet)*(1-p(10));
							H1[i][j] += MIN_INT;
						}
						else{
							for(int k=2; k<=10; k++){
								float temp=0.0;
								for(int l=2; l<=9; l++){
									temp += p(l)*G[i+k][11+l];
								}
								temp += p(1)*G[i+k][12];
								temp += p(10)*(-1*bet);
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							float temp=0.0;
							for(int l=2; l<=9; l++){
								temp += p(l)*G[i+11][11+l];
							}
							temp += p(1)*G[i+11][12];
							temp += p(10)*(-1*bet);
							H1[i][j] += p(1)*max(H2[i+11][j], temp);
						}
					}
					else if(j==0){
						if(i==0){
							// for(int k=2; k<=10; k++){
							// 	float temp=0.0;
							// 	for(int l=2; l<=9; l++){
							// 		temp += p(l)*E[i+k][10+l];
							// 	}
							// 	temp += p(1)*(-1.5*bet);
							// 	temp += p(10)*E[i+k][20];
							// 	H1[i][j] += p(k)*max(H1[i+k][j], temp);
							// }
							H1[i][j] += (1.5*bet)*(1-p(1));
						}
						else if(i==1){
							// for(int k=2; k<=9; k++){
							// 	float temp=0.0;
							// 	for(int l=2; l<=9; l++){
							// 		temp += p(l)*E[i+k][10+l];
							// 	}
							// 	temp += p(1)*(-1.5*bet);
							// 	temp += p(10)*E[i+k][20];
							// 	H1[i][j] += p(k)*max(H1[i+k][j], temp);
							// }
							// float temp=0.0;
							// for(int l=2; l<=9; l++){
							// 	temp += p(l)*E[i+11][10+l];
							// }
							// temp += p(1)*(-1.5*bet);
							// temp += p(10)*E[i+11][20];
							// H1[i][j] += p(1)*max(H2[i+11][j], temp);
							// H1[i][j] += p(10)*(1.5*bet)*(1-p(1));
							H1[i][j] += MIN_INT;
						}
						else{
							for(int k=2; k<=10; k++){
								float temp=0.0;
								for(int l=2; l<=9; l++){
									temp += p(l)*E[i+k][10+l];
								}
								temp += p(1)*(-1*bet);
								temp += p(10)*E[i+k][20];
								H1[i][j] += p(k)*max(H1[i+k][j], temp);
							}
							float temp=0.0;
							for(int l=2; l<=9; l++){
								temp += p(l)*E[i+11][10+l];
							}
							temp += p(1)*(-1*bet);
							temp += p(10)*E[i+11][20];
							H1[i][j] += p(1)*max(H2[i+11][j], temp);
						}
					}
				}
			}
		}
	}




	// {	////////////DOUBLE///////////////////
	// 	{	//////////////////D3/////////////////////////
	// 		for(int i=41; i>=0; i--){
	// 			for(int j=41; j>=0; j--){
	// 				if(i>=21) D3[i][j] = -2*bet;
	// 				else if(j>11) D3[i][j] = MIN_INT;
	// 				else if(j<=11){
	// 					for(int k=1; k<=10; k++){
	// 						D3[i][j] += 2*p(k)*E[i+k][j];
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	
	
	// 	{	/////////////////////D2///////////////////////
	// 		for(int i=41; i>=0; i--){
	// 			for(int j=41; j>=0; j--){
	// 				if(i>21) D2[i][j] = D3[i-10][j];
	// 				else if(j>11) D2[i][j] = MIN_INT;
	// 				else if(i<11) D2[i][j] = MIN_INT;
	// 				else if(j<=11){
	// 					for(int k=1; k<=10; k++){
	// 						D2[i][j] += 2*p(k)*E[i+k][j];
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	
	
		{	///////////////////D1///////////////////////////
			for(int i=41; i>=0; i--){
				for(int j=41; j>=0; j--){
					if(i>=21) D1[i][j] = -2*bet;
					else if(j>22) D1[i][j] = 0;
					else if(j>=11 && j<22){ 
						if(i>1){
							for(int k=2; k<=10; k++){
								if(11+i+k > 21){
									D1[i][j] += 2*p(k)*E[11+i+k-10][j];
								}else{
									D1[i][j] += 2*p(k)*E[11+i+k][j];
								}
							}
							D1[i][j] += 2*p(1)*E[i+12][j];
						}
						// else if(i==1){
						// 	for(int k=2; k<=10; k++){
						// 		if(11+i+k > 21){
						// 			D1[i][j] += 2*p(k)*E[11+i+k-10][j];
						// 		}else{
						// 			D1[i][j] += 2*p(k)*E[11+i+k][j];
						// 		}
						// 	}
						// 	D1[i][j] += 2*p(1)*E[13][j];
						// }
						else if(i==0){
							D1[i][j] += -2*bet;								// No double in case of blackjack
						}
					}
					else{ 
						if(i>1){
							for(int k=2; k<=10; k++){
								D1[i][j] += 2*p(k)*E[i+k][j];
							}
							D1[i][j] += 2*p(1)*E[i+11][j];
						}
						else if(i==1){
							// for(int k=2; k<=9; k++){
							// 	D1[i][j] += 2*p(k)*E[i+k][j];
							// }
							// D1[i][j] += 2*p(1)*E[i+11][j];
							// if(j>1) D1[i][j] += 3*p(10)*bet;
							// else if(j==0) D1[i][j] += 3*bet*p(10)*(1-p(1));
							// else if(j==1) D1[i][j] += 3*bet*p(10)*(1-p(10));
							D1[i][j] += MIN_INT;
						}
						else if(i==0){
							// for(int k=2; k<=10; k++){
							// 	D1[i][j] += 2*p(k)*E[i+k][j];
							// }
							// // D1[i][j] += 2*p(1)*E[i+11][j];
							// if(j>1) D1[i][j] += 3*p(1)*bet;
							// else if(j==0) D1[i][j] += 3*bet*p(1)*(1-p(1));
							// else if(j==1) D1[i][j] += 3*bet*p(1)*(1-p(10));
							D1[i][j] += -2*bet;								// No double in case of blackjack
						}
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

	solve_the_game();

}