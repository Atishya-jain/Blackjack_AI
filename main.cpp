#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
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

	for(int i = 0; i< pol.size(); i++){
		for(int j = 0; j< 10; j++){
			pol[i].push_back('H');
		}
	}
}

int main(int argc, char **argv){
	if(argc!=2){
        exit(0);
    }

    int prob = stoi(argv[1]);
    vector<vector<char>> pol;
    get_policy(pol);
    output_policy(pol);
}