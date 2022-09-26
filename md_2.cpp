// 211RDB105 Artjoms Kučerjavijs 8. grupa
#include <iostream>
void print(int ** array, int x, int y){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++)
            printf("%d ", array[i][j]);
        printf("\n");
    }
}
void print(int * array, int y){
    // prints result
    printf("result: ");
    for(int i = 0; i < y; i++){
        printf("%d ", array[i]);
    }
}

int * getMinCol(int ** array, int x, int y){
    // gets smallest element from each column
    int * res = new int[y];
    int * p;
    for(int i = 0; i < y; i++){
        p = &array[0][i];
        for(int j = 1; j < x; j++){
            if (array[j][i] < *p)
                p = &array[j][i];
        }
        res[i] = *p;
    }
    return res;
}

bool isAlllowed(char c, bool allowMinus){
    char digits[11] = {'-','0','1','2','3','4','5','6','7','8','9'};
    int i;
    if (allowMinus)
        i = 0;
    else
        i = 1;
    for (; i < 10; i++)
        if (c == digits[i])
            return true;
    return false;
}

int * parseInput(char * input, bool allowMinus){
    /* function checks if number was enteted correctly (isallowd) */
    /* then parses all characters-digits to numeric representation (by ASCII table) */
    /* works both for negative and positive by checking first character */
    /* return arrray of size 2, where first elem is values itself */
    /* and second value if flag -1 = found error, 1 = parsed correctly */
    int i = 0;
    int res = 0;
    int * resArr = new int[2];
    while (input[i] != '\0'){
        if (!isAlllowed(input[i], allowMinus)){
            resArr[1] = -1;
            return resArr;
        }
        i++;
    }
    if (input[0] == '-') 
        i = 1;
    else
        i = 0;
    while (input[i] != '\0'){
        res = res * 10 + (int) input[i] - 48;
        i++;
    }
    if (input[0] == '-')
        res = -res;
    resArr[0] = res;
    resArr[1] = 1;
    return resArr;
}

int ** getArray(int x, int y, int N){
    // initializes array from keyboard input
    int ** array;
    int * answ;
    char c[N];
    array = new int * [x];
    for(int i = 0; i < x; i++){
        array[i] = new int[y];
        for(int j = 0; j < y; j++){
            do{
                scanf("%s", &c);
                answ = parseInput(c, true);
            } while (answ[1] < 0);
            array[i][j] = answ[0];
        }
    }
    return array;
}

int main ()
{
    
    int **array, * res, * answ, x, y, N = 10;
    char inputX[N], inputY[N];
    // i`m using printf and scanf to look smarter
    printf("%s\n", "211RDB105 Artjoms Kučerjavijs 8. grupa");
    do {
        scanf("%s", &inputX);
        answ = parseInput(inputX, false);
    } while (answ[1] < 0);
    x = answ[0];
    do { 
        scanf("%s", &inputY);
        answ = parseInput(inputY, false);
    } while (answ[1] < 0);
    y = answ[0];
    array = getArray(x, y, N);
    print(array,x,y);
    res = getMinCol(array, x, y);
    print(res, y);
    // delete arrays
    for(int i = 0; i < x; i++){
        delete[] array[i];
    }
    delete[] res;
    delete[] array;
    delete[] answ;
    //delete[] inputX;
    //delete[] inputY;
    return 0;
}
