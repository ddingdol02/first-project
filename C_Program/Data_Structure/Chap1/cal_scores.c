#define MAX_ELEMENTS 100
int score[MAX_ELEMENTS]; //자료구조

int get_max_score(int n)
{
    int i, largest;
    largest = score[0];
    for(i=1; i<n; i++){
        if(score[i] > largest){
            largest = score[i];
        }
    }
    return largest;
}