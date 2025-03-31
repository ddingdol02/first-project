#define WHITE 0
#define BLACK 1
#define YELLOW 2
// 좌표 최대값 100*100
int screen[100][100]; 
// 해당 좌표 색 알아내기
char read_pixel(int x, int y){
    return screen[x][y];
}
// 좌표에 색 입히기
void write_pixel(int x, int y, int color){
    screen[x][y] = color;
}
// 영역 채우기 알고리즘
void flood_fill(int x, int y){
    if(read_pixel(x, y) == WHITE){
        write_pixel(x, y, BLACK);
        // 동서남북으로 움직인다.
        flood_fill(x+1, y);
        flood_fill(x-1, y);
        flood_fill(x, y+1);
        flood_fill(x, y-1);
    }
}