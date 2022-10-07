// 211RDB105 Artjoms Kučerjavijs
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void inputSequence(vector<int>& array){
    int input = 1;
    bool flag = false;
    while (input != 0){
        scanf("%d", &input);
        array.push_back(input);
    }
}

int main() {
    vector<int> first, second;
    inputSequence(first);
    inputSequence(second);
    for(int i = 0; i < first.size(); i++){
        if (count(begin(second), end(second), first[i]) < 1 ){
            cout<<first[i]<<endl;
        }
    }
    return 0;
}