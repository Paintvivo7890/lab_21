#include<iostream>
using namespace std;

int main(int argc, char *argv[]){
    if (argc == 1){
        cout << "Please input numbers to find average." << endl;
    }
    else if (argc > 1){
        float average = 0;
        for (int i = 1; i < argc; i++){
            average += atoi(argv[i]);
        }
        average = average / (argc - 1);
        cout << "---------------------------------"<< endl;
        cout << "Average of "<<argc -1 <<" numbers = "<< average  << endl;
        cout << "---------------------------------"<< endl;
    }
    return 0;
}
