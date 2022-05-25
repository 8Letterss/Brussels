//�ݹ��½��ӳ������
//Ϊ�˷���д���룬ʹ�á�E_����ʾ��E������ʹ�á�@�������š����ش�������


#include <bits/stdc++.h>
using namespace std;

struct info_node //��������������Ϣ
{
    //int steps_number;//���������
    string grammer; //�õ����﷨
    string hv_ana;  //�Ѿ����������ַ���
    char bi_ana;    //���ڷ������ַ�
    string rem_str; //ʣ����ַ���
    info_node(/*int steps_number,*/ string grammer, string hv_ana, char bi_ana, string rem_str)
    {
        //this->steps_number = steps_number;
        this->grammer = grammer;
        this->hv_ana = hv_ana;
        this->bi_ana = bi_ana;
        this->rem_str = rem_str;
    }
};

string expression; //����ı��ʽ
int lookahead;     //��ǰ��ƥ���ַ����±�
//set<int> error_id; //ƥ��ʱ������ַ����±�
stack<info_node *> steps; //�����Ϣ�ڵ㣬������ӡ
bool is_valid = true;     //����ı��ʽ�Ƿ�Ϸ�
int steps_number = 0;     //��ǰ����ı��

/****************function declaration********/
void E();

void match(char a)
{
    if (lookahead >= expression.size())//˵���Ѿ�������ɺ�������ֻ�����һ�仰���ã��������ࡣ
    {
        is_valid = false;
        return;
    }
    if (expression[lookahead] != a)
    {
        //error_id.insert(lookahead);
        is_valid = false;
    }
    else
        lookahead++;
}

void M()
{
    if (lookahead >= expression.size())//˵���Ѿ��������
    {
        is_valid = false;
        return;
    }
    if (expression[lookahead] == '*') //����Ͳ��û����ˣ���if�жϼ��ɣ����ݵ�ȻҲ����д
    {
        steps.push(new info_node(/*steps_number++,*/ "M->*", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
        match('*');
    }
    else if(expression[lookahead] == '/')
    {
        steps.push(new info_node(/*steps_number++,*/ "M->/", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
        match('/');
    }
    else
        is_valid = false;
}

void A()
{
    if (lookahead >= expression.size())//˵���Ѿ��������
    {
        is_valid = false;
        return;
    }
    if (expression[lookahead] == '+') //����Ͳ��û����ˣ���if�жϼ��ɣ����ݵ�ȻҲ����д
    {
        steps.push(new info_node(/*steps_number++,*/ "A->+", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
        match('+');
    }
    else if(expression[lookahead] == '-')
    {
        steps.push(new info_node(/*steps_number++,*/ "A->-", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
        match('-');
    }
    else
        is_valid = false;
}

void F()
{
    if (lookahead >= expression.size())//˵���Ѿ��������
    {
        is_valid = false;
        return;
    }
    if (expression[lookahead] == '(') //����Ͳ��û����ˣ���if�жϼ��ɣ����ݵ�ȻҲ����д
    {
        steps.push(new info_node(/*steps_number++,*/ "F->(E)", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
        match('(');
        E();
        match(')');
    }
    else if(expression[lookahead] == 'i')
    {
        steps.push(new info_node(/*steps_number++,*/ "F->i", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
        match('i');
    }
    else
        is_valid = false;
}

void T_()
{
    if(!is_valid)
        return;

    int cu_lookahead = lookahead;//��¼�µ�ǰƥ���ֵ������仰��Ϊ�˷��������ڡ�i*����������ȷ��
    steps.push(new info_node(/*steps_number++,*/ "T'->MFT'", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
    M();
    F();
    T_();
    if (!is_valid) //���ݵ�����һ�����
    {
        if(cu_lookahead != lookahead)//˵�����ַ�ƥ����,���Ǽ�Ȼ���ݣ���ôƥ����ַ��Ͳ��㡣
            lookahead--;
        is_valid = true;
        steps.pop();
        steps.push(new info_node(/*steps_number++,*/ "T'->��", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
    }
}
void T()
{
    if(!is_valid)
        return;
    steps.push(new info_node(/*steps_number++,*/ "T->FT'", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
    F();
    T_();
}

void E_() //������
{
    if(!is_valid)
        return;

    int cu_lookahead = lookahead;//��¼�µ�ǰƥ���ֵ������仰��Ϊ�˷��������ڡ�i*����������ȷ��
    //cout<<lookahead;
    steps.push(new info_node(/*steps_number++,*/ "E'->ATE'", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
    A();
    T();
    E_();
    if (!is_valid) //���ݵ�����һ����䣺E->��
    {
        if(cu_lookahead != lookahead)//˵�����ַ�ƥ����,���Ǽ�Ȼ���ݣ���ôƥ����ַ��Ͳ��㡣
            lookahead--;
        is_valid = true;
        steps.pop();
        steps.push(new info_node(/*steps_number++,*/ "E'->��", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
    }
}

void E()
{
    if(!is_valid)
        return;
    steps.push(new info_node(/*steps_number++,*/ "E->TE'", expression.substr(0, lookahead), expression[lookahead], expression.substr(lookahead)));
    T();
    E_();

}

void print_table()
{
    while(!steps.empty())
    {
        cout<<setiosflags(ios::left)<<setw(15)<<steps.top()->grammer<<setw(15)<<steps.top()->hv_ana<<setw(15)<<steps.top()->bi_ana<<setw(15)<<steps.top()->rem_str<<'\n';
        /*printf("%*s",20,steps.top()->grammer);
        printf("%*s",20,steps.top()->hv_ana);
        printf("%*s",20,steps.top()->bi_ana);
        printf("%*s",20,steps.top()->rem_str);*/
        steps.pop();
    }
}

int main()
{
    //cout<<lookahead;
    cin >> expression;
    E();
    if(lookahead == expression.size())
        is_valid = true;
    else
        is_valid = false;
    if(is_valid)
        cout<<"���ʽ�Ϸ���"<<'\n';
    else
        cout<<"���ʽ���Ϸ���"<<'\n';
    cout<<setiosflags(ios::left)<<setw(15)<<"�ķ�"<<setw(15)<<"�ѷ���"<<setw(15)<<"������"<<setw(15)<<"δ����"<<'\n';
    if(is_valid)
        print_table();
    system("pause");
}
