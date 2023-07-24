/*
A basis of a k-dimensional subspace can be represented as a matrix
in reduced row echelon form with 0 empty lines.
For this project, I used the same approach as for project 5, the difference being the fact that
the matrices in reduced row echelon form must have 0 empty lines.

for a matrix, the number of lines is denoted by m (equivalent to k from the problem statement - the
dimension of the subspace) and the number of columns is denoted by n (the length of a vector)

*/
#include <bits/stdc++.h>
#define NMAX 30

using namespace std;

int n,m;

struct matrix{
    int mat[NMAX+1][NMAX+1];
};
vector<matrix> solutions;

bool check_reduced_row_echelon_form_no_empty_lines(matrix candidate_matrix, int r, int c){
    /*
    Checks if a matrix is in reduced row echelon form, with 0 empty lines. Only the first r rows and c columns are taken
    into account.
    */
    int last_leading_one = -1;
    for(int i=1;i<=r;i++){
        int current_leading_one = 0; 
        for(int j=1;j<=c;j++){
            if(candidate_matrix.mat[i][j]==1){
                current_leading_one = j; ///find the column index of the leading 1 in this row
                break;
            }
        }
        if(current_leading_one == 0){
            return false;
        }else if (current_leading_one != 0){
            if(current_leading_one<=last_leading_one){
                return false; ///if the column index of the current leading 1 is <= the column index of the last leading 1, then the matrix is not ok
            }

            for(int k=1;k<=r;k++){
                if(candidate_matrix.mat[k][current_leading_one] != 0 && k!= i){ ///if there is another 1 on the column of the current leading 1, then the matrix is not ok
                    return false;
                }
            }
        }
        last_leading_one = current_leading_one;
    }
    return true;
}

bool check_no_empty_line(matrix candidate_matrix, int line){
    for(int j=1;j<=n;j++){
        if(candidate_matrix.mat[line][j] != 0){
            return true;
        }
    }
    return false;
}

void generate_reduced_row_echelon_form_tables(int x, int y, matrix candidate_matrix){
    /*Generates all posible matrices with 1 and 0 and saves to the "solutions" vector the ones in reduced row echelon form
    */
    if(y == n+1){
        if(check_reduced_row_echelon_form_no_empty_lines(candidate_matrix, x, n)){
            if(x == m){
                solutions.push_back(candidate_matrix);///valid solution
            }else{
                generate_reduced_row_echelon_form_tables(x+1, 1, candidate_matrix);
            }
        }
        return;
    }
    candidate_matrix.mat[x][y] = 1;
    generate_reduced_row_echelon_form_tables(x,y+1, candidate_matrix);
    candidate_matrix.mat[x][y] = 0;
    generate_reduced_row_echelon_form_tables(x,y+1, candidate_matrix);
}


long long count_number_of_solutions(int m,int n){
    /*Counts the number of solutions, using a dynammic programming approach.
    m is the dimension of the base
    */
    long long dp[NMAX+5][NMAX+5];
       /*dp[i][j] = the number of ways to "fill" the positions with 1<=x<=i and 1<=y<=j such that at [i][j] there is a leading 1 and the reduced row echelon form properties are respected
    */
    long long solutions = 0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1; ///this is needed for computing the values of row 1 from dp

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=0;k<j;k++){
                dp[i][j] += dp[i-1][k] * (1<<((i-1)*(j-k-1))); /// counting all posibilities if the current leading 1 had the column-index j and the last leading 1 had the column-index k. 
                ///For each previous row, there are j-k+1 new positions that can be "filled" either with 1 or 0, so we multiply with 2^((i-1)*(j-k-1)), that is ((1<<((i-1)*(j-k-1))) using bit shifting.
            }
            if(i==m){
                solutions +=dp[i][j] * (1<<(i*(n-j))); ///when we get to the last row, we add all matrices for which the current leading 1 is j
                /// For each row, from 1 to i, there are (m-j) positions that can be "filled" either with 1 or 0, so we multiply with 2^(i*(m-j)), that is (1<<(i*(m-j))) using bit shifting.
            }
        }
    }
    return solutions;
}

int main(){
    cin>>m;
    cin>>n;
    if(n<0 || m<0){
        cout<<"k and n must be >= 2";
        return 0;
    }
    matrix initial_matrix;
    cout<<"The number of solutions is: "<<count_number_of_solutions(m,n)<<'\n';
    if(n<=6 && m<=6){
        generate_reduced_row_echelon_form_tables(1,1,initial_matrix);
        cout<<"The number of generated solutions is: "<<solutions.size()<<'\n';
        for(int k=0;k<solutions.size();k++){
            cout<<"Solution nr. "<<k+1<<'\n';
            for(int i=1;i<=m;i++){
                for(int j=1;j<=n;j++){
                    cout<<solutions[k].mat[i][j]<<' ';               
                }
                cout<<'\n';
            }
            cout<<'\n';
        }
    }else{
        cout<<"For the second part, k and n must be <= 6";
    }

}