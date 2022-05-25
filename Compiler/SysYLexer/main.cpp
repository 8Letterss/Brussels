#include<bits/stdc++.h>
using namespace std;

bool isdigit(char ch);
bool isletter(char ch);
int char_type(char ch);//�����ַ�ch������
void Handle_annotation(char *src);//��src�г���ע�͵����ݶ��ŵ�dele_annotation����
void Handle_tab(char *src); //ȥ��tab

//������
string reserved_keywords[] = {"const", "int", "void", "if", "while", "break", "return", "continue", "main"};
set<string> reserved_keywords_set(reserved_keywords, reserved_keywords + 9);
//�����
string operational_characters[] = {"+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "!", "&&", "||", "[", "]", "++", "--", "=", "><"};
set<string> operational_characters_set(operational_characters, operational_characters + 20);
//�ָ���
string separators[] = {";", "{", "}", "(", ")"};
set<string> separators_set(separators, separators +5);
//�Զ����ʶ��
set<string> identifiers_set;
char dele_annotation[255];//���洦���ע�͵�һ���ַ���
char dele_tab[255];//���洦����˸�����ַ���


int main(){
    char one_row_char[255] = {};//���һ���Զ�ȡ���ļ���һ�е��ַ�
    bool is_annotation = false;//��ǰ���Ƿ���ע����
    char *str = NULL;//�������еĿո�ָ��У���ŷָ�����ַ���
    char delims[] = " ";//�ո���Ϊ�ָ��еı�־
    char temp[255];//�����ݴ�ͬһ��str�������ģ��ַ������֣��»��ߣ�����������������ָ�����
    int row_number = 0;//��¼�к�
    freopen("source.txt", "r", stdin);
    freopen("result.txt", "w", stdout);

    while(gets(one_row_char) != NULL){
        row_number++;
        Handle_tab(one_row_char);//����tab
        Handle_annotation(dele_tab);//����ע��
        str=strtok(dele_annotation, delims);//���ݿո�ָ�dele_annotation���õ��ַ�����
        while(str != NULL){
            //cout<<str<<'\n';
            for(int i = 0; i < strlen(str); i++){
                memset(temp, 0, 255);
                if(str[i] == '/' && str[i+1] == '*'){ //����ע��
                    is_annotation = true;
                }
                if(str[i] == '*' && str[i+1] == '/') //ȡ��ע��
                {
                    is_annotation = false;
                    i++;
                    i++;
                    if(i>=strlen(str))
                        break;
                }

                if(char_type(str[i]) == 5 && !is_annotation){ //�ָ���
                    printf("<�ֽ����%c>\n", str[i]);
                }else if(char_type(str[i]) == 4 && !is_annotation){ //�����
                    if(char_type(str[i+1]) == 4) //���������������
                    {
                        temp[0] = str[i];
                        temp[1] = str[i+1];
                        i++;
                        printf("<�������%s>\n", temp);
                    }
                    else //�������һ������
                    {
                        printf("<�������%c>\n", str[i]);
                    }
                }else if(char_type(str[i])==6){
                    printf("ERROR IN LINE %d, ERROR TYPE: ���ִʷ���δ�����ַ���\n", row_number);
                }else if(!is_annotation){ //�ؼ��֡���ʶ�������������֣��ַ���
                    int j = 0;
                    temp[j++] = str[i++];
                    while((char_type(str[i]) == 1 || char_type(str[i]) == 2 || char_type(str[i]) == 3)&&i<strlen(str)){
                        temp[j++] = str[i++];
                    }
                    if(isdigit(temp[0])) //�����һ���ַ������֣���ô�������������ˡ�ʮ��ʮ�����ƣ����߷Ƿ���ʶ��
                    {
                        if(temp[0] == '0')
                        {
                            if(strlen(temp) == 1)
                                printf("<��ֵ�ͳ�����ʮ���ƣ���%s>\n", temp);
                            else
                            {
                                if(temp[1] == 'x' || temp[1] == 'X') //ʮ������
                                {
                                    printf("<��ֵ�ͳ�����ʮ�����ƣ���%s>\n", temp);
                                }
                                else //�˽���
                                {
                                    printf("<��ֵ�ͳ������˽��ƣ���%s>\n", temp);
                                }
                            }
                        }
                        else
                        {
                            int flag = 0;
                            for(int j = 0; j < strlen(temp); j++)
                            {
                                if(!isdigit(temp[j]))
                                {
                                    printf("ERROR IN LINE %d, ERROR TYPE: ��ʶ�������ֿ�ͷ��\n", row_number);
                                    flag = 1;
                                    break;
                                }
                            }
                            if(!flag)
                            printf("<��ֵ�ͳ�����ʮ���ƣ���%s>\n", temp);
                        }
                    }
                    else
                    {
                        if(reserved_keywords_set.find(temp) != reserved_keywords_set.end()) //�Ǳ�����
                        {
                            printf("<�����֣�%s>\n", temp);
                        }else
                        {
                            printf("<��ʶ����%s>\n", temp);
                        }
                    }
                    i--;//�����˳��󣬻ص�forѭ����Ҫ++������������--;�����
                }
            }
            str = strtok(NULL, delims);
        }
    }

    if(is_annotation==true) printf("ERROR, ERROR TYPE: ע�Ͳ����������顣\n");
    freopen("CON", "w", stdout);//Ϊ�˺������������̨������򿪡�����̨���ļ���
    cout<<"����ɴʷ�����:"<<endl<<endl;
    freopen("result.txt", "r", stdin);//���ļ������������Ϊ���룬���������̨��
    while ((gets(one_row_char)) != NULL)
        cout<<one_row_char<<endl;
    while (getchar() != '\n') //�����������������뻺�������ݣ���ͬ��fflush(stdin);
        continue;
    getchar();
    system("pause");
    return 0;
}

bool isdigit(char ch){
    if (ch >= '0'&&ch <= '9')
        return true;
    return false;
}

bool isletter(char ch){
    if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
        return true;
    return false;
}

//�����ַ�ch������
int char_type(char ch){
    if(isdigit(ch))
        return 1;
    if(isletter(ch))
        return 2;
    if(ch == '_')
        return 3;
    string ch1(1, ch);//��charתΪΪstring
    if(operational_characters_set.find(ch1) != operational_characters_set.end())
        return 4;
    if(separators_set.find(ch1) != separators_set.end())
        return 5;
    return 6;
}

void Handle_annotation(char *src){ //��src�г���ע�͵����ݶ��ŵ�dele_annotation����
    int j = 0;
    memset(dele_annotation, 0, 255);
    for(int i = 0; i < strlen(src); i++)
    {
        if(src[i] == '/')//����һԭ��for��д����i < strlen(src)-1
            if(src[i+1] == '/')
                return;
        dele_annotation[j++] = src[i];
    }
}

void Handle_tab(char *src){ //ȥ��tab
    int j = 0;
    memset(dele_tab, 0, 255);
    for(int i = 0; i < strlen(src); i++)
    {
        if(src[i] == '\t')
            continue;
        dele_tab[j++] = src[i];
    }
}
