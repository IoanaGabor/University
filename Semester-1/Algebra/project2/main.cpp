#include <bits/stdc++.h>
#define NMAX 4

using namespace std;

int n; ///n is the number of elements in the set, non zero

struct matrix{
    int mat[NMAX+1][NMAX+1];
};
vector<matrix> solutions;

bool check_associative_operation(matrix candidate_matrix){
    /// checks if a possibly incomplete operation table could be a future solution,
    /// by taking into consideration only the defined operations (which have a non-zero result)
    /// x * (y*z) = (x*y) * z, for each x,y,z, with 1<= x,y,z<=n and a defined
    /// y*z, x*y, x * (y*z), (x*y)*z 
    for(int x=1;x<=n;x++){
        for(int y=1;y<=n;y++){
            for(int z=1;z<=n;z++){
                if( candidate_matrix.mat[y][z] != 0 && candidate_matrix.mat[x][y]!= 0 && 
                candidate_matrix.mat[x][candidate_matrix.mat[y][z]] !=0 && 
                candidate_matrix.mat[candidate_matrix.mat[x][y]][z]!=0 && candidate_matrix.mat[x][candidate_matrix.mat[y][z]] != candidate_matrix.mat[candidate_matrix.mat[x][y]][z]){
                    return false;
                }
            }
        }
    }    
    return true;
}

void generate_associative_operation_tables(int n, int x, int y, matrix candidate_matrix){
    if(y == n+1){
        if(x == n){
            if(check_associative_operation(candidate_matrix)){
                solutions.push_back(candidate_matrix);///valid solution
            }
        }else{
            generate_associative_operation_tables(n, x+1, 1, candidate_matrix);
        }
        return;
    }
    if(!check_associative_operation(candidate_matrix)){ /// checking the consistency of 
                                    ///partial solutions improves the time complexity, by eliminating 
        return;                    ///sub-trees of the potential search tree
    }
    for(int i=1;i<=n;i++){
        candidate_matrix.mat[x][y] = i;
        generate_associative_operation_tables(n,x,y+1, candidate_matrix);
        candidate_matrix.mat[x][y] = 0;
    }
}

int main(){
    cin>>n;
    matrix initial_matrix;
    generate_associative_operation_tables(n,1,1,initial_matrix);
    cout<<"The number of associative operations on a set with n = "<<n<<" elements is "<<solutions.size()<<'\n';
    cout<<"The operations' tables are"<<'\n';
    for(int k=0;k<solutions.size();k++){
        cout<<"Table "<<k+1<<'\n';
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cout<<"a"<<solutions[k].mat[i][j]<<' ';               
            }
            cout<<'\n';
        }
        cout<<'\n';
    }
}