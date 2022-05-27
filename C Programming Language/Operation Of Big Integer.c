#include <stdio.h>
#include <stdlib.h>

int flag=1;//全局变量flag判断符号,flag=0为负
typedef struct node
{
    int digit;
    struct node*next,*prev;
}Node;

typedef struct UBigNumber
{
    int digitCount;
    Node *Head,*Tail;
}UBN;

Node*NodeCreate()
{
    Node*p;
    p=(Node*)malloc(sizeof(Node));
    if(p==NULL){
        printf("Error:out of memory\n");
        exit(-1);
    }
    return p;
}//建立结点

void BNInit(UBN*pA)//头结点初始化;
{
    Node*p=NodeCreate();
    pA->Head=pA->Tail=p;
    p->next=p->prev=NULL;
    pA->digitCount=0;//位数为0
}

void BNAppend(UBN*pA,int digit)//添加位数
{
    if(pA->digitCount==1&&pA->Tail->digit==0){//位数是1且表尾数据是0
        pA->Tail->digit=digit;
        return;
    }
    Node *p=NodeCreate();
    p->digit=digit;
    p->next=NULL;
    p->prev=pA->Tail;
    pA->Tail->next=p;
    pA->Tail=p;
    ++pA->digitCount;//位数+1
}//尾插法 插入即为输入顺序

void BNNormalize(UBN*pA)//标准化，删除首位的0
{
    if(pA->digitCount==0)
    BNAppend(pA,0);
    while(pA->digitCount>1&&pA->Head->next->digit==0)
    {
        Node*p;
        p=pA->Head->next;//待删除结点，因为是尾插法插入，所以最高位是Head->next;
        pA->Head->next=p->next;//正向链表删除
        p->next->prev=pA->Head;//反向链表删除
        free(p);
        --pA->digitCount;//位数减1
    }
}

UBN*BNInput()//插入一位数
{
    UBN*q;
    q=(UBN*)malloc(sizeof(UBN));
    BNInit(q);//建立了一个p为首地址的头结点
    char ch;
   do{
       ch=getchar();
       if(ch=='-')
        flag=0;
   }
    while(ch<'0'||ch>'9');//do-while 过滤掉非数字字符
    while(ch>='0'&&ch<='9')
    {
    BNAppend(q,ch-'0');//添加一位数
    ch=getchar();
    }
    BNNormalize(q);
    return q;
}

void BNOutput(UBN *pA)//输出大数
{
    if(pA->digitCount<1)
        return;
    Node*q;
    q=pA->Head->next;
    while(q){
        printf("%d",q->digit);
        q=q->next;
    }
}

void BNDestory(UBN*pA)//销毁大数
{
    Node *p;
    while(pA->Head!=NULL){
        p=pA->Head;
        pA->Head=p->next;
        free(p);
    }
}

void BNAppendFront(UBN*A,int n)//头插入法加在头结点
{
    Node*p=NodeCreate();
    p->digit=n;
    p->next=A->Head->next;//新节点指向头结点的下一节点
    if(p->next!=NULL)//除头结点外已有结点
        p->next->prev=p;//头结点下一节点指针指回，若头节点外无结点，则新节点指向NULL
    p->prev=A->Head;//新节点前驱节点指向头结点
    A->Head->next=p;//头结点指向新节点
    if (A->Tail==A->Head)//更改尾结点
        A->Tail=p;//若只有头节点，则尾结点也是头结点也是p，因为是头插入法，当插入一个后尾结点不变均为第一次插入的结点
    ++A->digitCount;//位数+1
}

UBN*BNAdd(UBN*A,UBN*B)//大数相加
{
    int digit,carry=0;//carry进位
    UBN*Result;
    Result=(UBN*)malloc(sizeof(UBN));
    BNInit(Result);//初始化头结点
    Node *p1,*p2;
    p1=A->Tail;
    p2=B->Tail;
    while(p1!=A->Head&&p2!=B->Head)//相同位数处理
    {
        int digit=p1->digit+p2->digit+carry;
        carry=digit/10;
        digit=digit%10;//digit=digit%10除以十取余数为当前的数
        BNAppendFront(Result,digit);
        p1=p1->prev;
        p2=p2->prev;
    }
    while(p1!=A->Head)//第一大数剩余处理，即第一个大数位数大于第二个的情况
    {
        int digit=p1->digit+carry;
        carry=digit/10;
        digit%=10;
        BNAppendFront(Result,digit);
        p1=p1->prev;
    }
     while(p2!=B->Head)//第二大数剩余处理，即第二个大数位数大于第一个的情况
    {
        digit=p2->digit+carry;
        carry=digit/10;
        digit%=10;
        BNAppendFront(Result,digit);
        p2=p2->prev;
    }
    if(carry!=0)
        BNAppendFront(Result,carry);
    BNNormalize(Result);
    return Result;
}

UBN*BNSub(UBN*A,UBN*B)//大数相减
{
    int Carry=0;//Carry借位
    UBN*Result;
    Result=(UBN*)malloc(sizeof(UBN));
    BNInit(Result);//初始化头结点
    Node *p1,*p2;
    p1=A->Tail;
    p2=B->Tail;
    while(p1!=A->Head&&p2!=B->Head)  //两数相同位处理
    {
        int digit=p1->digit-p2->digit-Carry;
        Carry=0; //初始化
        if(digit<0)
        {
            digit+=10;
            Carry=1;  //前一位退1
        }
        BNAppendFront(Result,digit);
        p1=p1->prev;
        p2=p2->prev;
    }
    while(p1!=A->Head)  //最后退位处理
    {
        int digit=p1->digit-Carry;
        Carry=0;
        if(digit<0)
        {
            digit+=10;
            Carry=1;  //前一位退1
        }
        BNAppendFront(Result,digit);
        p1=p1->prev;
    }
    BNNormalize(Result);
    return Result;
}

int BNCompare(UBN*A,UBN*B){//比较函数，比较大数绝对值大小
    Node*p,*q;
    p=A->Head->next;
    q=B->Head->next;
    if (A->digitCount>B->digitCount)
        return 1;
    if (A->digitCount<B->digitCount)
        return 0;
    while(p){
        if(p->digit>=q->digit){
        p=p->next;
        q=q->next;
        }
        else return 0;
    }
    return 1;
}

void BNPrint(UBN*A,UBN*B,int flag1,int flag2)//输出函数 输出加法和减法
{
    if(flag1==1&&flag2==1)
    {
        BNOutput(BNAdd(A,B));//add
        putchar('\n');
        if(BNCompare(A,B))//A
        BNOutput(BNSub(A,B));
        else {
            putchar('-');
            BNOutput(BNSub(B,A));//sub
        }
    }

   if(flag1==0&&flag2==1)
    {
        if(BNCompare(A,B)){
            putchar('-');
            BNOutput(BNSub(A,B));//
            putchar('\n');
        }
        else BNOutput(BNSub(B,A));
            putchar('-');
            BNOutput(BNAdd(A,B));
    }

   if(flag1==1&&flag2==0){
         if(BNCompare(A,B)){
            BNOutput(BNSub(A,B));
            putchar('\n');
         }
         else{
              putchar('-');
            BNOutput(BNSub(B,A));
            putchar('\n');
         }
         BNOutput(BNAdd(A,B));
    }

    if(flag1==0&&flag2==0){
        putchar('-');
        BNOutput(BNAdd(A,B));
        putchar('\n');
        if(BNCompare(A,B)){
            putchar('-');
        BNOutput(BNSub(A,B));
        }
        else {
            BNOutput(BNSub(B,A));
        }
    }
}

UBN*BNMultiplyDigit(UBN*A,int digit2)//一个大数A乘一位数digit2
{
    UBN* result;
    result=(UBN*)malloc(sizeof(UBN));
    BNInit(result);//初始化头结点
    if(digit2==0){
        BNAppend(result,digit2);
        return result;
    }
    int Carry=0;//进位数初始化
    Node*p;//遍历指针p
    p=A->Tail;//从低位开始处理
    while(p!=A->Head)
    {
        int digit=p->digit*digit2+Carry;
        Carry=digit/10;
        digit %=10;
        BNAppendFront(result,digit);//头插入法，因为是从末位开始算，所以应倒序插入
        p=p->prev;//指针前移
    }
    if(Carry!=0) BNAppendFront(result,Carry);
    return result;
}

UBN*BNCreate()
{
    UBN*A;
    A=(UBN*)malloc(sizeof(UBN));
    BNInit(A);
    return A;
}

UBN*BNFetchSub(UBN*A,int start,int end)//截取大数中从开始下标start到结束下标end的
{
    UBN*result;
    result=(UBN*)malloc(sizeof(UBN));
    BNInit(result);
    int i=0;
    Node*p;
    p=A->Head->next;
    while(i<start&&p!=NULL){
        p=p->next;
        i++;
    }
    while(i<end&&p!=NULL)
    {
        BNAppend(result,p->digit);
        p=p->next;
        i++;
    }
    BNNormalize(result);
    return result;
}

UBN*BNMultiply(UBN*A,UBN*B)//两个大数相乘
{
    if(B->digitCount==1)//递归终止条件
    return BNMultiplyDigit(A,B->Tail->digit);
    else if(A->digitCount==1)
    return BNMultiplyDigit(B,A->Tail->digit);//A或B只有一个数时，则一个大数乘一个数可用函数直接计算
    int m=A->digitCount;
    int n=B->digitCount;//统计A B大数个数
    int h=(m>n?m:n)/2;//取m n中较大的数并除以2
    UBN*A1;
    UBN*A2;
    UBN*B1;
    UBN*B2;
    A1=BNFetchSub(A,0,m-h);//取A中前m-h位数 即A=A1*10^h+A2；
    A2=BNFetchSub(A,m-h,m);//A中剩下的位数
    B1=BNFetchSub(B,0,n-h);
    B2=BNFetchSub(B,n-h,n);//B=B1*10^h+B2；
    UBN*z0=BNCreate();
    UBN*z1=BNCreate();
    UBN*z2=BNCreate();
    z2=BNMultiply(A1,B1);//z2=A1*B1,若还是大数*大数则递归，若出现一个个位数则得到结果
    z0=BNMultiply(A2,B2);
    UBN*t1=BNCreate();
    UBN*t2=BNCreate();
    UBN*t3=BNCreate();
    UBN*t4=BNCreate();
    UBN*t5=BNCreate();
    UBN*result=BNCreate();
    t1=BNAdd(A1,A2);//A1+A2
    t2=BNAdd(B1,B2);//B1+B2
    BNDestory(A1);
    BNDestory(A2);
    BNDestory(B1);
    BNDestory(B2);//销毁无用链表，有用的数据已经存入t1，t2，z0，z2
    t3=BNMultiply(t1,t2);//(A1+A2)(B1+B2)
    t4=BNAdd(z0,z2);//t4=z0+z2=b*d+a*c=A2*B2+A1*B1
    z1=BNSub(t3,t4);//z1=(A1+A2)(B1+B2)-A2*B2+A1*B1 将两次乘法转换为一次乘法
    int i;
    for(i=0;i<2*h;++i)//位数左移
    BNAppend(z2,0);//z2*=10^(2*h);
    for(i=0;i<h;++i)
    BNAppend(z1,0);//z1*=10^h;
    t5=BNAdd(z2,z1);//t5=z2*10^2h+z1*10^h
    result=BNAdd(t5,z0);//result=z2*10^2h+z1*10^h+z0=z2*10^2h+z1*10^h+b*d
    BNDestory(z0);
    BNDestory(z1);
    BNDestory(z2);
    BNDestory(t1);
    BNDestory(t2);
    BNDestory(t3);
    BNDestory(t4);
    BNDestory(t5);
    return result;
}

int main()
{
    UBN*A,*B,*multi;
    multi=BNCreate();
    int flag1=1,flag2=0;
    A=BNInput();
    flag1=flag;
    flag=1;
    B=BNInput();
    flag2=flag;
    BNPrint(A,B,flag1,flag2);
    putchar('\n');
    if(flag1!=flag2)//若符号不相同 则乘法结果为负数
    putchar('-');
    multi=BNMultiply(A,B);
    BNOutput(multi);
    putchar('\n');
    system("pause");
    return 0;
}
