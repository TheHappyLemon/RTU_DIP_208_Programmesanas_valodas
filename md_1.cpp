// 211RDB105 Artjoms Kučerjavijs
#include <iostream>
#include <cmath>

using namespace std;

double a(double x){
    return 3 * x + 3;
}

double b(double x){
    return sqrt(2 * (x*x*x));
}

void posY(double &x){
    x = a(x) + b(x) + 2 * a(x) * b (x);
}

void negY(double &x){
    x = sqrt( a(x) * (b(x) - 1) );
}

int main() {
    double x;
    char sym = 'y';
    while (sym == 'y' || sym == 'Y')
    {
        cin>>x;
        if (b(x) != b(x)) {    
            // check for NaN
            cout<<"error";
        } 
        else {
            if (a(x) < b(x)) {
                posY(x);
                printf("%.2f\n", x);
            }
            else{
                negY(x);
                if (x != x){
                    cout<<"error";
                }
                else{
                    printf("%.2f\n", x);
                }
            }
        }
        cin>>sym;
    }
    return 0;
}