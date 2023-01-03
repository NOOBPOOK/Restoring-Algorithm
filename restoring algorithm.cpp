#include <iostream>
#include <iomanip>
using namespace std;

int de[2];
int b[2][40];
int sub[40];
int ac[40] = {0};
int carry_n = 0;
int cycles = 0;

void con_bin(int y);
void head();
void body();
void left_shift();
void print(int y);
void add(int y[40]);
void comp2();
void extend();
void compare();

int main()
{
    cout << "Enter Number One:\t";
    cin >> de[0];
    cout << "Enter Number Two:\t";
    cin >> de[1];
    cout << "Binary for " << de[0] << " : ";
    con_bin(0);
    for(int i=0;i<8;i++){
        cout << b[0][i];
    }
    cout << endl;
    cout << "Binary for " << de[1] << " : ";
    con_bin(1);
    for(int i=0;i<8;i++){
        cout << b[1][i];
    }
    extend();
    cout << endl;
    for(int i=0;i<=8;i++){
        cout << b[1][i];
    }
    cout << endl << endl;
    cout << "9 indicates a null value which is to be determined by next operation." << endl << endl;
    comp2();
    cout << "-M in Binary : ";
    for(int i=0;i<=8;i++){
        cout << sub[i];
    }
    cout << endl << endl;
    head();
    while(cycles<8){
        body();
        cycles++;
    }
    cout << " " << string(45,'-') << endl;
    cout << endl << "The Quotient is : ";
    for(int i=0;i<8;i++){
        cout << b[0][i];
    }
    cout << endl << "The Remainder is : ";
    for(int i=0;i<8;i++){
        cout << ac[i];
    }
}

void con_bin(int y)
{
    int i = 0;
    int gh[2][10];
    while (i<8){
        if(de[y] != 0){
            gh[y][i] = de[y]%2;
            de[y] = de[y]/2;
        }
        else if(de[y]==0){
            gh[y][i] = 0;
        }
        else if(i==7 && de[y]!=0){
            cout << "Number too big to hnadle\nPlease Enter a Valid Number:";
            main();
            abort();
        }
        i++;
    }
    i--;
    for(int j=0;i>=0;i--,j++){
        b[y][j] = gh[y][i];
    }
}
void head()
{
    cout << " " << string(45,'-') << endl;
    cout << "| C |    AC    |     Q    |        init       |" << endl;
    cout << " " << string(45,'-') << endl;
    print(0);
}
void body()
{
    left_shift();
    add(sub);
    print(2);
    compare();
}
void left_shift()
{
    carry_n = ac[0];
    for(int i=1,j=0;i<=8;i++,j++){
        ac[j] = ac[i];
    }
    ac[7] = b[0][0];
    for(int i=1,j=0;i<=8;i++,j++){
        b[0][j] = b[0][i];
    }
    b[0][7] = 9;
    print(1); 
}
void print(int y)
{
    cout << "| " << carry_n  << " | ";
    for(int i=0;i<8;i++){
        cout << ac[i];
    }
    cout << " | ";
    for(int i=0;i<8;i++){
        cout << b[0][i];
    }
    cout << " | ";
    if (y==0)
        cout << setw(18) << " Start" << "|" << endl;
    else if (y==1)
        cout << setw(18) << " Left Shift" << "|" << endl;
    else if(y==2)
        cout << setw(18) << " AC = AC - M" << "|" << endl;
    else if(y==3)
        cout << setw(18) << " AC = AC + M" << "|" << endl;
    else if(y==4)
        cout << setw(18) << " Q[7] = 1" << "|" << endl;
    cout << "|   |          |          |                   |" << endl;
}
void comp2()
{
    int detect = 0;
    for(int i=8;i>=0;i--){
        if(detect==0){
            if(b[1][i]==0)
                sub[i] = 0;
            else{
                sub[i] = 1;
                detect = 1;
            }
        }
        else{
            if(b[1][i]==0)
                sub[i] = 1;
            else{
                sub[i] = 0;
            }
        }   
    }
}
void add(int y[40])
{
    int carry = 0;
    int g;
    for(int i=7;i>=0;i--){
        if(carry==0){
            if(ac[i]==0 && y[i+1]==0){
                ac[i] = 0;
            }
            else if(ac[i]==1 && y[i+1]==0){
                ac[i] = 1;
            }
            else if(ac[i]==0 && y[i+1]==1){
                ac[i] = 1;
            }
            else{
                ac[i] = 0;
                carry = 1;
            }
        }
        else{
            if(ac[i]==0 && y[i+1]==0){
                ac[i] = 1;
                carry = 0;
            }
            else if(ac[i]==1 && y[i+1]==0){
                ac[i] = 0;
            }
            else if(ac[i]==0 && y[i+1]==1){
                ac[i] = 0;
            }
            else{
                ac[i] = 1;
                carry = 1;
            }
        }
    }
    if(carry==0){
        carry_n = carry_n+y[0];
        if(carry_n==2){
            carry_n = 0;
        }
    }
    else{
        carry_n = carry_n+y[0]+1;
        if(carry_n>=2){
            carry_n = 0;
        }
    }
}
void compare()
{
    if(carry_n==1){
        b[0][7] = 0;
        add(b[1]);
        print(3);
    }
    else{
        b[0][7] = 1;
        print(4);
    }
}
void extend()
{
    for(int i=8;i>=1;i--){
        b[1][i] = b[1][i-1];
    }
    b[1][0] = 0;
}
