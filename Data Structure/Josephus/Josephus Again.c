/*又见约瑟夫环：有M个人围坐成一圈， 编号依次从1开始递增直到M，现从编号为1的人开始报数，报到N的人出列，
然后再从下一人开始重新报数，报到N的人出列；重复这一过程，直至所有人出列。
所有出列的人再次按出列顺序围坐成一圈，并从第1人开始报数，这次为报到K的人出队列，
然后再从下一人开始重新报数，报到K的人出列；重复这一过程，直至所有人出列。
求最后出列次序。题目输入包括M、N、K三个正整数；N、K可能为1。
题目要求按最后出队列顺序输出他们的编号，每个测试用例结果占一行，每个编号占4位。*/

#include <stdio.h>
#include<string.h>
typedef int bool;
#define true 1
#define false 0
 
typedef struct Node{
    int data;
    struct Node *next;
} Node;
 
Node* create_Yuesefu_List(int m){
    Node *head, *node,*end;//定义头节点，普通节点，尾部节点；
    head = (Node*)malloc(sizeof(Node));//分配地址
  head->data = 1;
    end = head;         //若是空链表则头尾节点一样
    for (int i = 1; i < m; i++) {
        node = (Node*)malloc(sizeof(Node));
    node->data = (i+1);
        head->next = node;
        head = head->next; 
    }
  head->next = end;
    return end;
}
Node* yuesefu_Problem(Node* head,int n){
  int counter = 1;
  bool is_First_Out = true;
  Node *node_new,*h,*node;
  node_new = (Node*)malloc(sizeof(Node));
  h=node_new;
 
  while(head!=NULL)
  {
    if(n!=1)counter++;
    else {
      if(is_First_Out==true){
        node_new->data = head->data;
        is_First_Out=false;
      }else{
        node = (Node*)malloc(sizeof(Node));
        node->data = head->next->data;//赋值操作
        node_new->next=node;
        head->next = head->next->next;
        node_new = node_new->next;
 
        if(head==head->next){
          node_new->next=h;
          return h;
        }
      }
    }
 
    if(counter==n && n!=1){
      if(is_First_Out==true){
        node_new->data = head->next->data;
        is_First_Out=false;
      }else{
        node = (Node*)malloc(sizeof(Node));
        node->data = head->next->data;
        node_new->next = node;
   //上面三句话 相当于1句话 node_new.next = new Node(head.next.value);
        node_new=node_new->next;
      }
      head->next = head->next->next;
      counter = 0;
    }else if(counter!=n&&n!=1){
      head = head->next;
      if(head == head->next){
        node = (Node*)malloc(sizeof(Node));
        node->data = head->data;
        node_new->next = node;
        node_new->next->next = h;
        break;
      }
    }
  }
    return h;
}
Node* input_LinkedList(){
  char str[1024];
  char *delim = " ";
  scanf("%[^\n]", str);
  Node* head = (Node*)malloc(sizeof(Node));
  Node * end = head;
  Node * node;
  int count=0;
  char *p = strtok(str, delim);
  head->data = atoi(p);
  // printf("%s \n", p);
  count++;
  while((p = strtok(NULL, delim))){
    node = (Node*)malloc(sizeof(Node));
    node->data = atoi(p);
    head->next = node;
    head = head->next;
    // printf("%s \n", p);
    count++;
  }
  return end;
}
void print_LinkedList(Node* head,int count){
  while(head->next != NULL && count !=0){
      printf("%4d",head->data);
      head = head->next;
      count--;
  }
  printf("\n");
}
int main(void) {
  Node* head = input_LinkedList();
  int m = head->data;
  head = head->next;
  Node* h = create_Yuesefu_List(m);
  while(head!=NULL){
      h = yuesefu_Problem(h,head->data);
      head = head->next;
    }
  print_LinkedList(h, m);
}
