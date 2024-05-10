#include <iostream>
using namespace std;

int main() {
    
    int score = 10;
    char buffer[10];
    int l = sprintf(buffer, "%i", score);
    cout << buffer << endl;
    cout << l << endl;


    char buffer2[50];
    int length = sprintf(buffer2, "Hello, %s!", "World");
    printf("%s\n", buffer2);
    printf("Characters written: %d\n", length);

    return 0;
}