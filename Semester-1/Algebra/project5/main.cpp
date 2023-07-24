#include <bits/stdc++.h>
#define NMAX 30

using namespace std;

int n,m;

struct matrix{
    int mat[NMAX+1][NMAX+1];
};
vector<matrix> solutions;

bool check_reduced_row_echelon_form(matrix candidate_matrix){
    /*Checks if a matrix is in reduced row echelon form.
    */
    int last_leading_one = -1;
    bool only_0_from_now_on = false;
    for(int i=1;i<=n;i++){
        int current_leading_one = 0; 
        for(int j=1;j<=m;j++){
            if(candidate_matrix.mat[i][j]==1){
                current_leading_one = j; ///find the column index of the leading 1 in this row
                break;
            }
        }
        if(current_leading_one == 0){
            only_0_from_now_on = true; ///if there are no 1's on this row, then all the remaining rows will contain only 0
        }else if (current_leading_one != 0){
            if(only_0_from_now_on){
                return false; ///if there was a 1 on this row and it should have been only 0, then the matrix is not ok
            }
            if(current_leading_one<=last_leading_one){
                return false; ///if the column index of the current leading 1 is <= the column index of the last leading 1, then the matrix is not ok
            }

            for(int k=1;k<=n;k++){
                if(candidate_matrix.mat[k][current_leading_one] != 0 && k!= i){ ///if there is another 1 on the column of the current leading 1, then the matrix is not ok
                    return false;
                }
            }
        }
        last_leading_one = current_leading_one;
    }
    return true;
}

void generate_reduced_row_echelon_form_tables(int n, int x, int y, matrix candidate_matrix){
    /*Generates all posible matrices with 1 and 0 and saves to the "solutions" vector the ones in reduced row echelon form
    */
    if(y == m+1){
        if(x == n){
            if(check_reduced_row_echelon_form(candidate_matrix)){
                solutions.push_back(candidate_matrix);///valid solution
            }
        }else{
            generate_reduced_row_echelon_form_tables(n, x+1, 1, candidate_matrix);
        }
        return;
    }
    candidate_matrix.mat[x][y] = 1;
    generate_reduced_row_echelon_form_tables(n,x,y+1, candidate_matrix);
    candidate_matrix.mat[x][y] = 0;
    generate_reduced_row_echelon_form_tables(n,x,y+1, candidate_matrix);
}


long long count_number_of_solutions(int n,int m){
    /*Counts the number of solutions, using a dynammic programming approach.
    
    */
    long long dp[NMAX+5][NMAX+5];
       /*dp[i][j] = the number of ways to "fill" the positions with 1<=x<=i and 1<=y<=j such that at [i][j] there is a leading 1 and the reduced row echelon form properties are respected
    */
    long long solutions = 1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1; ///this is needed for computing the values of row 1 from dp

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<j;k++){
                dp[i][j] += dp[i-1][k] * (1<<((i-1)*(j-k-1))); /// counting all posibilities if the current leading 1 had the column-index j and the last leading 1 had the column-index k. 
                ///For each previous row, there are j-k+1 new positions that can be "filled" either with 1 or 0, so we multiply with 2^((i-1)*(j-k-1)), that is ((1<<((i-1)*(j-k-1))) using bit shifting.
            }
            solutions +=dp[i][j] * (1<<(i*(m-j))); ///adding all matrices for which the current leading 1 is the last leading 1 in the matrix (all the following rows are 0). 
            /// For each row, from 1 to i, there are (m-j) positions that can be "filled" either with 1 or 0, so we multiply with 2^(i*(m-j)), that is (1<<(i*(m-j))) using bit shifting.
        }
    }
    return solutions;
}

int main(){
    cin>>n>>m;
    if(n<2 || m<2){
        cout<<"m and n must be >= 2";
        return 0;
    }
    matrix initial_matrix;
    cout<<"The number of solutions is: "<<count_number_of_solutions(n,m)<<'\n';
    if(n<=5 && m<=5){
        generate_reduced_row_echelon_form_tables(n,1,1,initial_matrix);
        cout<<"The number of generated solutions is: "<<solutions.size()<<'\n';
        for(int k=0;k<solutions.size();k++){
            cout<<"Solution nr. "<<k+1<<'\n';
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    cout<<solutions[k].mat[i][j]<<' ';               
                }
                cout<<'\n';
            }
            cout<<'\n';
        }
    }else{
        cout<<"For the second part, n and m must be <= 5";
    }

}