// 211RDB105 Artjoms Kučerjavijs
#include <iostream>

using namespace std;

int main() {
    int x, y, z, medium, nmedium;
    cin>>x>>y;
    medium = x > y ? x : y;
    nmedium = x > y ? y : x;
    cin>>z;
    if (z < medium) medium = nmedium > z ? nmedium : z;
    cout<<medium<<endl;
    return 0;
}