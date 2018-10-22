#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int MIN_INT = numeric_limits<int>::min();
double probability;
double bet;

double E[42][42];
double G[42][42];
double F[42][42];
double H1[42][42];
double H2[42][42];
double H3[42][42];
double D1[42][42];
double D2[42][42];
double D3[42][42];
double S[42][42];

double p(int x){
    if(x<1) return -1;
    if(x<10) return (1-probability)/9.0;
    else return probability;
}

double max(double x, double y){
    if(x>y) return x;
    else return y;
}

double get_split(int x, int y){
    if(x == 1){
        return D2[11][y];
    }else if(x == 10){
        double temp = 0;
        for(int i = 2;i < 10; i++){
            temp += p(i)*max(H1[x+i][y], max(E[x+i][y], D1[x+i][y]));
        }
        temp += 1.5*bet*p(1);
        temp = (temp*2)/(1-2*p(x));
        return temp;
    }

    double temp = 0;
    for(int i = 2;i <= 10; i++){
        if(i==x){
            continue;
        }else{
            temp += p(i)*max(H1[x+i][y], max(E[x+i][y], D1[x+i][y]));
        }
    }
    temp += p(1)*max(H2[x+11][y], max(E[x+11][y], D2[x+11][y]));
    temp = (temp*2)/(1-2*p(x));
    return temp;
}   

void output_policy(vector<vector<char>>& pol){
	string outputfile = "Policy.txt";
    ofstream outfile(outputfile.c_str());
    
    if(!(outfile).is_open()){
        cout << "There is no such output file" << "\n";
        exit(2);
    }
    vector<string> mapp = {"5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "22", "33", "44", "55", "66", "77", "88", "99", "1010", "AA"};
    
    for(int i = 0; i<mapp.size(); i++){
    	outfile << mapp[i] << "\t";
    	for(int j = 0; j<pol[i].size(); j++){
    		outfile << pol[i][j] << " ";
    	}
    	if(i < mapp.size() - 1){
	    	outfile << "\n";
    	}
    }

    outfile.close();
}

void get_policy(vector<vector<char>>& pol){
	for(int i = 0; i< 33; i++){
		vector<char> v;
		pol.push_back(v);
	}

    int run = 2;
	for(int i = 0; i< pol.size(); i++){
		if(i < 15){
            for(int j = 2; j<11; j++){
                if(H1[i+5][j] > E[i+5][j]){
                    if(H1[i+5][j] >= D1[i+5][j]){
                        pol[i].push_back('H');
                    }else{
                        pol[i].push_back('D');
                    }
                }else if(E[i+5][j] >= D1[i+5][j]){
                        pol[i].push_back('S');
                }else{
                        pol[i].push_back('D');
                }
            }
            if(H1[i+5][1] >= E[i+5][1]){
                if(H1[i+5][1] >= D1[i+5][1]){
                    pol[i].push_back('H');
                }else{
                    pol[i].push_back('D');
                }
            }else if(E[i+5][1] >= D1[i+5][1]){
                    pol[i].push_back('S');
            }else{
                    pol[i].push_back('D');
            }
        }else if(i < 23){
            for(int j = 2; j<11; j++){
                if(H2[i-2][j] >= E[i-2][j]){
                    if(H2[i-2][j] >= D2[i-2][j]){
                        pol[i].push_back('H');
                    }else{
                        pol[i].push_back('D');
                    }
                }else if(E[i-2][j] >= D2[i-2][j]){
                        pol[i].push_back('S');
                }else{
                        pol[i].push_back('D');
                }
            }
            if(H2[i-2][1] >= E[i-2][1]){
                if(H2[i-2][1] >= D2[i-2][1]){
                    pol[i].push_back('H');
                }else{
                    pol[i].push_back('D');
                }
            }else if(E[i-2][1] >= D2[i-2][1]){
                    pol[i].push_back('S');
            }else{
                    pol[i].push_back('D');
            }
        }else if(i < 32){
            for(int j = 2; j<11; j++){
                double S = get_split(run,j);
                if((H1[2*run][j]>=E[2*run][j]) && (H1[2*run][j]>=D1[2*run][j]) && (H1[2*run][j]>=S)){
                    pol[i].push_back('H');
                }else if((D1[2*run][j]>=E[2*run][j]) && (D1[2*run][j]>=H1[2*run][j]) && (D1[2*run][j]>=S)){
                    pol[i].push_back('D');
                }else if((S>=E[2*run][j]) && (S>=H1[2*run][j]) && (D1[2*run][j]<=S)){
                    pol[i].push_back('P');
                }else{
                    pol[i].push_back('S');
                }
            }
            double S = get_split(run,1);
            if((H1[2*run][1]>=E[2*run][1]) && (H1[2*run][1]>=D1[2*run][1]) && (H1[2*run][1]>=S)){
                pol[i].push_back('H');
            }else if((D1[2*run][1]>=E[2*run][1]) && (D1[2*run][1]>=H1[2*run][1]) && (D1[2*run][1]>=S)){
                pol[i].push_back('D');
            }else if((S>=E[2*run][1]) && (S>=H1[2*run][1]) && (D1[2*run][1]<=S)){
                pol[i].push_back('P');
            }else{
                pol[i].push_back('S');
            }
            run++;
        }else{
            for(int j = 2; j<11; j++){
                double S = get_split(1,j);
                if((H2[12][j]>=E[12][j]) && (H2[12][j]>=D2[12][j]) && (H2[12][j]>=S)){
                    pol[i].push_back('H');
                }else if((D2[12][j]>=E[12][j]) && (D2[12][j]>=H2[12][j]) && (D2[12][j]>=S)){
                    pol[i].push_back('D');
                }else if((S>=E[12][j]) && (S>=H2[12][j]) && (D2[12][j]<=S)){
                    pol[i].push_back('P');
                }else{
                    pol[i].push_back('S');
                }
            }
            double S = get_split(1,1);
            if((H2[12][1]>=E[12][1]) && (H2[12][1]>=D2[12][1]) && (H2[12][1]>=S)){
                pol[i].push_back('H');
            }else if((D2[12][1]>=E[12][1]) && (D2[12][1]>=H2[12][1]) && (D2[12][1]>=S)){
                pol[i].push_back('D');
            }else if((S>=E[12][1]) && (S>=H2[12][1]) && (D2[12][1]<=S)){
                pol[i].push_back('P');
            }else{
                pol[i].push_back('S');
            }
        }
	}
}

int main(int argc, char **argv){
    if(argc!=2){
        exit(0);
    }

    probability = stof(argv[1]);
    bet = 1;
    vector<vector<char>> pol;

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


    {   //////STAND/////////////
        {    ///////////////F//////////////////////
            for(int i=41; i>=0; i--){
                for(int j=41; j>=0; j--){
                    if(i>21) F[i][j] = -bet;
                    else if(j>21) F[i][j] = bet;                 // Dealer busts
                    else if(j>i && j>=17) F[i][j] = -bet;   // j >= 17
                    else if(j<i && j>=17) F[i][j] = bet;
                    else if(i==j && j>=17) F[i][j] = 0.0;   //push condition & never blackjack here
                    else if(j>=11 && j<17){                 // dealer hit condition
                        for(int k=1; k<=10; k++){
                            F[i][j] += p(k)*F[i][j+k];
                        }
                    }
                }
            }
        }
    
    
        {   /////////////////G/////////////////////
            for(int i=41; i>=0; i--){                       // Atleast 1 ace of value 11
                for(int j=41; j>=0; j--){
                    
                    if(j>21) G[i][j] = F[i][j-10];          // if j > 21 convert 11 valued ace to 1 valued
                    else if(i>21) G[i][j] = -bet;         
                    else if (j < 11) G[i][j] = MIN_INT;     // if j < 11 G[i][j] is highly negative     
                    else if(j>i && j>=17) G[i][j] = -bet;   // if j >= 17
                    else if(j<i && j>=17) G[i][j] = bet;
                    else if(j==i && j>=17) G[i][j] = 0.0;       //push condition
                    else if(j>=11 && j<17){                 // dealer hit condition
                        for(int k=1; k<=10; k++){
                            G[i][j] += p(k)*G[i][j+k];
                        }
                    }
                }
            }
        }
    
    
        {   //////////////////E///////////////////////
            for(int i=41; i>=0; i--){
                for(int j=41; j>=0; j--){
                    if(i>21) E[i][j] = -bet;                 // I win if dealer busts
                    else if(j>21) E[i][j] = bet;           // I lose if I already busted
                    else if(j>i && j>=17) E[i][j] = -bet;   // I lose if I was less when dealer was above 17 with no ace
                    else if(j<i && j>=17 && i!=0) E[i][j] = bet;    // I win if I was greater when dealer was above 17
                    else if(j<i && j>=17 && i==0) E[i][j] = 1.5*bet;    // I win if I was blackjack
                    else if(i==j && j>=17 && i!=0) E[i][j] = 0.0;   // I draw if dealer and I equal at or above 17. BlackJack condition handled earlier
                    else if(/*i<17 &&*/ j<17/* && j<=i*/){  // Left case when j < 17 no matter what i is. Dealer has to hit     
                        if(j==0){
                            for(int k=2; k<=10; k++){
                                E[i][j] += p(k)*E[i][10+k];
                            }
                            if(i != 0){                     // if player is non-blackjack
                                E[i][j] += p(1)*(-1*bet);   // He loses against blackjack
                            }else{
                                E[i][j] += 0;               // push
                            }
                        }
                        else if(j==1){
                            for(int k=1; k<=9; k++){
                                E[i][j] += p(k)*G[i][11+k];  
                            }
                            // E[i][j] += p(1)*G[i][j+11];
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


    {   ////////////HIT///////////////////
        {   //////////////////H3/////////////////////////
            for(int i=41; i>=0; i--){
                for(int j=41; j>=0; j--){
                    if(j>11) H3[i][j] = MIN_INT;                        // dealer has only 1 card so can't be > 11
                    else if(i>=21) H3[i][j] = -bet;                     // If I hit at >= 21 the I bust
                    else if(j<=11){                                     // BlackJack can't occur in H3
                        for(int k=1; k<=10; k++){
                            H3[i][j] += p(k)*max(H3[i+k][j], E[i+k][j]);
                        }
                    }
                }
            }
        }
    
    
        {   /////////////////////H2///////////////////////
            for(int i=41; i>=0; i--){
                for(int j=41; j>=0; j--){
                    if(i>21) H2[i][j] = H3[i-10][j];                    // convert 11 valued ace to 1 valued
                    else if(i<11) H2[i][j] = MIN_INT;                   // i < 11 not defined
                    else if(j>11) H2[i][j] = MIN_INT;                       
                    else if(i>=11 && i<22){                             
                        for(int k=1; k<=10; k++){
                            if(i+k <= 21){
                                H2[i][j] += p(k)*max(H2[i+k][j], E[i+k][j]);
                            }else{
                                H2[i][j] += p(k)*max(H3[i+k-10][j], E[i+k-10][j]);
                            }
                        }
                    }
                }
            }
        }
    
    
        {   ///////////////////H1///////////////////////////
            for(int i=41; i>=0; i--){
                for(int j=41; j>=0; j--){
                    if(j>11) H1[i][j] = MIN_INT;
                    else if(i>=21) H1[i][j] = -1*bet;
                   
                    else if(j>1){
                        if(i==0){
                            H1[i][j] += (1.5*bet);
                        }
                        if(i==1){
                            H1[i][j] += MIN_INT;
                        }else{
                            for(int k=2; k<=10; k++){
                                double temp=0.0;
                                for(int l=2; l<=10; l++){
                                    temp += p(l)*E[i+k][j+l];
                                }
                                temp += p(1)*G[i+k][j+11];
                                H1[i][j] += p(k)*max(H1[i+k][j], E[i+k][j]);
                            }
                            double temp=0.0;
                            for(int l=2; l<=10; l++){
                                if(i+11 <=21){
                                    temp += p(l)*E[i+11][j+l];
                                }else{
                                    temp += p(l)*E[i+1][j+l];
                                }
                            }
                            if(i+11 <= 21){
                                temp += p(1)*G[i+11][j+11];                                
                            }else{
                                temp += p(1)*G[i+1][j+11];                                
                            }
                            H1[i][j] += p(1)*max(H2[i+11][j], temp);
                        }
                    }
                    else if(j==1){
                        if(i==0){
                            H1[i][j] += (1.5*bet)*(1-p(10));
                        }
                        else if(i==1){
                            H1[i][j] += MIN_INT;
                        }
                        else{
                            for(int k=2; k<=10; k++){
                                double temp=0.0;
                                for(int l=2; l<=9; l++){
                                    temp += p(l)*G[i+k][11+l];
                                }
                                temp += p(1)*G[i+k][12];
                                temp += p(10)*(-1*bet);
                                H1[i][j] += p(k)*max(H1[i+k][j], temp);
                            }
                            double temp=0.0;
                            for(int l=2; l<=9; l++){
                                if(i+11 <= 21){
                                    temp += p(l)*G[i+11][11+l];                                    
                                }else{
                                    temp += p(l)*G[i+1][11+l];
                                }
                            }
                            if(i+11 <= 21){
                                temp += p(1)*G[i+11][12];
                            }else{
                                temp += p(1)*G[i+1][12];
                            }
                            temp += p(10)*(-1*bet);
                            H1[i][j] += p(1)*max(H2[i+11][j], temp);
                        }
                    }
                    else if(j==0){
                        if(i==0){
                            H1[i][j] += (1.5*bet)*(1-p(1));
                        }
                        else if(i==1){
                            H1[i][j] += MIN_INT;
                        }else{
                            for(int k=2; k<=10; k++){
                                double temp=0.0;
                                for(int l=2; l<=9; l++){
                                    temp += p(l)*E[i+k][10+l];
                                }
                                temp += p(1)*(-1*bet);
                                temp += p(10)*E[i+k][20];
                                H1[i][j] += p(k)*max(H1[i+k][j], temp);
                            }
                            double temp=0.0;
                            for(int l=2; l<=9; l++){
                                if(i+11 <= 21){
                                    temp += p(l)*E[i+11][10+l];
                                }else{
                                    temp += p(l)*E[i+1][10+l];
                                }
                            }
                            temp += p(1)*(-1*bet);
                            if(i+11 <= 21){
                                temp += p(10)*E[i+11][20];
                            }else{
                                temp += p(10)*E[i+1][20];
                            }
                            H1[i][j] += p(1)*max(H2[i+11][j], temp);
                        }
                    }
                }
            }
        }
    }




    {    ////////////DOUBLE///////////////////
     {   //////////////////D3/////////////////////////
         for(int i=41; i>=0; i--){
             for(int j=41; j>=0; j--){
                 if(i>=21) D3[i][j] = -2*bet;
                 else if(j>11) D3[i][j] = MIN_INT;
                 else if(i<11) D3[i][j] = MIN_INT;
                 else if(j<=11){
                     for(int k=1; k<=10; k++){
                         D3[i][j] += 2*p(k)*E[i+k][j];
                     }
                 }
             }
         }
     }
    
    
     {   /////////////////////D2///////////////////////
         for(int i=41; i>=0; i--){
             for(int j=41; j>=0; j--){
                 if(i>21) D2[i][j] = D3[i-10][j];
                 else if(j>11) D2[i][j] = MIN_INT;
                 else if(i<11) D2[i][j] = MIN_INT;
                 else if(j<=11){
                    for(int k=1; k<=10; k++){
                        if(i+k <= 21){
                            D2[i][j] += 2*p(k)*E[i+k][j];
                        }else{
                            D2[i][j] += 2*p(k)*E[i+k-10][j];
                        }
                    }
                 }
             }
         }
     }
    
    
        {   ///////////////////D1///////////////////////////
            for(int i=41; i>=0; i--){
                for(int j=41; j>=0; j--){
                    if(i>=21) D1[i][j] = -2*bet;
                    else if(j>11) D1[i][j] = MIN_INT;
                    else{ 
                        if(i>1){
                            for(int k=2; k<=10; k++){
                                D1[i][j] += 2*p(k)*E[i+k][j];
                            }
                            if(i+11 <= 21) D1[i][j] += 2*p(1)*E[i+11][j];
                            else D1[i][j] += 2*p(1)*E[i+1][j];
                        }
                    }
                }
            }
        }
    }

   
    get_policy(pol);
    output_policy(pol);
    // cout << get_split(4,5) << endl << H1[8][5] << endl << D1[8][5] << endl << E[8][5] << endl;
    cout << H2[15][4] << endl << D2[15][4] << endl << E[15][4] << endl;
    // for(int i=2; i<=21; i++){
        cout << G[14][16] << endl;
    // }
    return 0;
}