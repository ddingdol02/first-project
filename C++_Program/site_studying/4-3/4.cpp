#include <iostream>
#include <string.h>

class string{
    char *str;
    int len;

    public:
    string(char c, int n);  // 문자 c 가 n 개 있는 문자열로 정의
    string(const char *s);
    string(const string &s);
    ~string();

    void add_string(const string &s);   // str 뒤에 s 를 붙인다.
    void copy_string(const string &s);  // str 에 s 를 붙인다. 
    int strlen();                       // 문자열 길이 리턴
    char* show_string();
};

string::string(char c, int n){
    int i;
    str = new char[n + 1];
    for(i = 0; i<n; i++)
        str[i] = c;
    str[i] = '\0';  // 끝에 \0 붙이기
    len = n;
}
string::string(const char* s){
    int i;
    for(len = 0; *s; len++) // 길이 측정
        s++;
    s -= len;
    str = new char[len + 1];
    for(i=0; *s; i++){
        str[i] = *s;
        s++;
    }
    str[i] = '\0';  // 끝에 \0 붙이기
}
string::string(const string& s){
    len = s.len;
    str = new char[len + 1];
    strcpy_s(str, len + 1, s.str);
}
string::~string(){
    if(str) delete[] str;
}
void string::add_string(const string& s){
    char* temp = new char[len + s.len + 1];
    strcpy_s(temp, len + 1, str);
    strcpy_s(&temp[len], s.len + 1, s.str); // temp에 기존 str 복사 후, \0 위치부터 s.str 덮어쓰기
    
    if(str) delete[] str;
    str = new char[len + s.len + 1];
    len += s.len;
    strcpy_s(str, len+1, temp);
    delete[] temp;
}
void string::copy_string(const string& s){
    if(str) delete[] str;
    len = s.len;
    str = new char[len + 1];
    strcpy_s(str, len + 1, s.str);
}
int string::strlen(){
    return len;
}
char* string::show_string(){
    return str;
}

int main(){
    string str1('a', 7);
    string str2("my name is Lee");
    string str3 = str2;

    std::cout << "str1 : " << str1.show_string() << ", strlen : " << str1.strlen() << std::endl;
    std::cout << "str1 : " << str2.show_string() << ", strlen : " << str2.strlen() << std::endl;
    std::cout << "str1 : " << str3.show_string() << ", strlen : " << str3.strlen() << std::endl;

    str2.add_string(str1);
    str3.copy_string(str1);

    std::cout << "str1 : " << str1.show_string() << ", strlen : " << str1.strlen() << std::endl;
    std::cout << "str1 : " << str2.show_string() << ", strlen : " << str2.strlen() << std::endl;
    std::cout << "str1 : " << str3.show_string() << ", strlen : " << str3.strlen() << std::endl;
}