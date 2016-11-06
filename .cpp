/*
Given a sorted array keys[0.. n-1] of search keys and an array freq[0.. n-1] of frequency counts, where freq[i] is the number of searches to keys[i]. Construct a binary search tree of all keys such that the total cost of all the searches is as small as possible.
Let us first define the cost of a BST. The cost of a BST node is level of that node multiplied by its frequency. Level of root is 1.
Example 1
Input:  keys[] = {10, 12}, freq[] = {34, 50}
There can be following two possible BSTs 
        10                       12
          \                     / 
           12                 10
          I                     II
Frequency of searches of 10 and 12 are 34 and 50 respectively.
The cost of tree I is 34*1 + 50*2 = 134
The cost of tree II is 50*1 + 34*2 = 118 

Example 2
Input:  keys[] = {10, 12, 20}, freq[] = {34, 8, 50}
There can be following possible BSTs
    10                12                 20         10              20
      \             /    \              /             \            /
      12          10     20           12               20         10  
        \                            /                 /           \
         20                        10                12             12  
     I               II             III             IV             V
Among all possible BSTs, cost of the fifth BST is minimum.  
Cost of the fifth BST is 1*50 + 2*34 + 3*8 = 142
*/

//
//  main.cpp
//  Optimal Binary Search Tree-DP
//
//  Created by Zijian Xie on 2016/11/6.
//  Copyright © 2016年 Jason Xie. All rights reserved.
//
#include <iostream>
#include <vector>
using namespace std;

class OptimalBST{
private:
    vector<int> keys;
    vector<int> freq;
public:
    OptimalBST(vector<int>& key, vector<int>& freqs){
        keys = key;
        freq = freqs;
    }
    
    int DP(){
        int n = (int)keys.size();
        vector<vector<int>> dp(n, vector<int>(n,0));
        
        for(int len = 1; len <= n; ++len){
            for(int i = 0; i + len <= n; ++i){
                int j = i + len;
                int sum = 0;
                int min_res = INT_MAX;
                for(int k = i; k < j; ++k){//把key[k]作为root
                    sum += freq[k];//compute the basic cost.
                    //以k为中心，把从i到j-1的这串数从k分成两段：
                    //[i][k-1], [k+1][j-1]
                    min_res = min(min_res, (k < j - 1 ? dp[k+1][j-1] : 0) + (k == i ? 0 : dp[i][k-1]));
                }
                dp[i][j-1] = sum + min_res;
            }
        }
        return dp[0][n-1];
    }
};

int main(int argc, const char * argv[]) {
    vector<int> key = {10,12,16,21};
    vector<int> freqs ={4,2,6,3};
    OptimalBST* test = new OptimalBST(key,freqs);
    cout<< "The minized cost is "<< test->DP()<<endl;
    return 0;
}
