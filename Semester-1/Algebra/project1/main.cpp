#include <bits/stdc++.h>
#define NMAX 10

using namespace std;

int n; ///n is the number of the elements in the set, non zero
int current_state[NMAX+5]; ///used in the generate partitions function
int partition_index; ///used to output the partition's index

int number_of_partitions(){ 
    ///The number of partitions is generated with the Bell Triangle.
    int bell_triangle[NMAX+5][NMAX+5];
    bell_triangle[1][1] = 1;
    for(int i=2;i<=n;i++){
        bell_triangle[i][1] = bell_triangle[i-1][i-1];  /// on a new row, the first element is the last of the previous row
        for(int j=2;j<=i;j++){
            bell_triangle[i][j] = bell_triangle[i][j-1] + bell_triangle[i-1][j-1];
        }
    }
    return bell_triangle[n][n]; ///the solution for a set with n elements
}

void output_partition(int nr_sets){  
    ///function that outputs a partition and it's corresponding equivalene relation
    partition_index++;
    cout<<"Partition "<<partition_index<<"\n";
    cout<<"{";
    bool flag_first_printed = false;
    bool flag_first_printed_subset = true;
    for(int i=1;i<=nr_sets;i++){
        if(flag_first_printed_subset){
            flag_first_printed_subset = false;
        }else{
            cout<<",";
        }
        cout<<"{";
        flag_first_printed = true;
        for(int j=1;j<=n;j++){
            if(current_state[j] == i){
                if(flag_first_printed){
                    cout<<"a"<<j;
                    flag_first_printed = false;
                }else{
                    cout<<" ,a"<<j;
                }
                
            }
        }    
        cout<<"}";
    }
    cout<<"}\n";
    cout<<"Equivalence relations for partition "<<partition_index<<":\n";
    for(int i=1;i<=nr_sets;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                if(current_state[j] == i && current_state[k] == i){
                    cout<<"(a"<<j<<", a"<<k<<"),";
                }
            }
        }
    }
    cout<<'\n';
}

void fill_current_state(int mask, int current_subset){ 
    /// marks the current subset with values represented in the bitmask
    int index = 0;
    for(int i=1;i<=n;i++){
        if(current_state[i] == 0){
            index++;
            if((1<<(index-1))&mask){ /// if the index-1 bit is set, the element appears in the subset
                current_state[i] = current_subset;
            }
        }
    }
}

int size_of_current_subset(int current_subset){
    int cnt=0;
    for(int i=1;i<=n;i++){
        cnt+= (current_state[i] == current_subset);
    }
    return cnt;
}

void clear_subset_without_first_element(int current_subset, int first){
    for(int i=1;i<=n;i++){
        if(current_state[i] == current_subset && i!=first){
            current_state[i] = 0;
        }
    }
}

int find_next_first_element_of_a_subset(){
    for(int i=1;i<=n;i++){
        if(current_state[i] == 0){
            return i;
        }
    }
    return n+1;
}

void generate_paritions(int current_element, int current_subset, int remaining_elements){
    /// generates partitions of a set of n elements recursively
    /// current_element is the minimum representative of its subset (the current_subset)
    /// current_subset is the index of the current subset that will be constructed 
    if(n+1 == current_element){
        output_partition(current_subset - 1);
    }
    current_state[current_element] = current_subset;
    int new_remaining_elements;
    /// the current subset is built by taking all the possible subsets with elements
    /// that are not yet part of a subset
    /// all the possible subsets are generated with bitmasks
    for(int bitmask=0;bitmask<(1<<(remaining_elements-1));bitmask++){
        fill_current_state(bitmask, current_subset); 
        new_remaining_elements = remaining_elements - size_of_current_subset(current_subset);
        /// once the current subset is marked, the other subsets are built recursively, now
        /// starting from the next element that is not part of a subset
        generate_paritions(find_next_first_element_of_a_subset(), current_subset+1, new_remaining_elements);
        clear_subset_without_first_element(current_subset, current_element);
    }
    current_state[current_element] = 0;
}

int main(){
    cin>>n;
    cout<<"Number of partitions with n = "<<n<<'\n';
    cout<<number_of_partitions()<<'\n';
    generate_paritions(1,1,n);
}