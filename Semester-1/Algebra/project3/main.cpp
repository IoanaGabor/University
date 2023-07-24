#include <bits/stdc++.h>
#define NMAX 10

using namespace std;

int n;
int included[(1<<NMAX)+1];
int current_chosen_vectors[NMAX+5];
vector<vector<vector<int>>> solutions;

vector<int> get_vector_from_number(int nr){
    ///gets the representation of the vector, given a number that is the base 10 equivalent
    vector<int> ret;
    for(int i=0;i<n;i++){
        ret.push_back((nr>>i)&1);
    }
    return ret;
}

vector<vector<int>> get_basis(){
    vector<vector<int>> ret;
    for(int i=1;i<=n;i++){
        ret.push_back(get_vector_from_number(current_chosen_vectors[i]));
    }
    return ret;
}

void generate_basis(int k){ ///this works for n <= 4, but the output size of the file for when n=4 was too large for moodle
    /// generates all the posible basis with backtracking, k is the current vector-to-be-chosen
    /// the vectors are represented as base 10 numbers and the + operation is equivalent with the xor operation on the numbers
    if(k == n+1){
        solutions.push_back(get_basis());   
        return;     
    }
    for(int i=1;i<(1<<n);i++){ ///from the set of all strictly positive numbers, we chose the next one to be included in the current basis
        if(included[i]==0){ /// this number needs to be linearly independent with the previous chosen ones
            included[i] = k; 
            for(int j=1;j<(1<<n);j++){
                if(included[j]>0 && !included[i^j]){
                    included[i^j] = k; /// we mark the numbers that are linear combinations of the first k numbers from the basis
                }
            }
            current_chosen_vectors[k] = i;
            generate_basis(k+1); ///we proceed to the next element of the basis
            for(int j=0;j<(1<<n);j++){ /// we unmark the numbers that are linear combinations of the first k numbers from the basis, but not of the first k-1 numbers, since at the next iteration we will chose other number as the the k-th
                if(included[j]==k){
                    included[j] = 0;
                }
            }
        }
    }
}

long long number_of_basis(int n){
    long long vectors_left = (1<<n) - 1; ///initially, 2^n - 1 vectors can be candidates for being part of the basis
    long long vectors_included = 1;  ///initially, the 0 vector is the only one which can be represented as the linear combination of the already considered (0) vectors in the basis
    long long sol = vectors_left; ///the first vector of the basis can be chosen from the set of the (2^n - 1) candidates
    for(int i=2;i<=n;i++){  /// at each step, we multiply the final result with the number of ways the next vector can be chosen to be part of the basis
        vectors_included *=2;  /// the number of vectors which can be represented as a linear combination of the first i vectors from the basis is 2^i
        vectors_left = (1<<n) - vectors_included; /// the vectors that can be candidates for being part of the basis are those which are linearly independent with the set of already chosen vectors (2^n - lineary dependent vectors) = (2^n - vectors_included)
        sol = sol * vectors_left;
    }
    return sol;
}

int main(){
    cin>>n;
    cout<<number_of_basis(n)<<'\n';
    if(n>4){
        cout<<"N is too large for the 2nd subpoint";
        return 0;
    }
    generate_basis(1);
    int cnt = 1;
    for(auto basis:solutions){
        cout<< "Basis number " <<cnt<<" :";
        cnt++;
        for(auto vec: basis){
            cout<<"(";
            for(auto comp: vec){
                cout<<comp<<' ';
            }
            cout<<") ";
        }
        cout<<"\n";
    }
}