#include <iostream>
#include <ctime>
#include <vector>
#include <chrono>

using namespace std;

struct T_List{
    int field;
    T_List* next;
    T_List* prev;
};
T_List* START(int value){
    T_List* p = new T_List;
    p->field = value;
    p->next = p;
    p->prev = p;
    return p;
}
void ADD(T_List* head, int value){
    T_List* temp, *p;
    temp = new struct T_List;
    p = head->prev;
    head->prev = temp;
    temp->field = value;
    temp->prev = p;
    temp->next = head;
    p->next = temp;
}
void SPECIAL_ADD(T_List* head, int num, int value){
    T_List* val = head;
    for(int i=0; i<num; i++){
        val = val->next;
    }

    T_List* temp, *p;
    temp = (struct T_List*)malloc(sizeof(T_List));
    p = val->next;
    val->next = temp;
    temp->field = value;
    temp->next = p;
    temp->prev = val;
    p->prev = temp;
}
void PRINT(T_List* head){
    T_List* p = head;
    do {
        std::cout << p->field << std::endl;
        p = p->next;
    } while (p != head);
}
void PRINT_R(T_List* head){
    T_List* p = head;
    do {
        p = p->prev;
        std::cout << p->field << std::endl;
    } while (p != head);
}
void DELETE(T_List* head, int value){
    T_List* p = head;
    do {
        if(p->field == value) {
            break;
        }
        p = p->next;
    } while (p != head || p->field != value);
    T_List* prev;
    T_List* next;
    prev = p->prev;
    next = p->next;
    prev->next = next;
    next->prev = prev;

    delete p;
}
void CLEAR(T_List* head){
    T_List* p = head->next;
    do {
        T_List* prev;
        T_List* next;
        prev = p->prev;
        next = p->next;
        prev->next = next;
        next->prev = prev;
        p = p->next;
    } while (p != head);
}
int main() {
    srand(time(0));

    T_List* head = START(0);
    PRINT(head);
    std::cout << "====" << std::endl;
    ADD(head, 10);
    ADD(head, 20);
    ADD(head, 30);
    ADD(head, 40);
    ADD(head, 50);
    ADD(head, 60);
    ADD(head, 5);
    SPECIAL_ADD(head,1, 3);
    PRINT(head);

    std::cout << "====" << std::endl;

    DELETE(head, 5);
    PRINT(head);

    std::cout << "====" << std::endl;

    PRINT_R(head);
    CLEAR(head);

    std::cout << "====" << std::endl;
    PRINT(head);

    delete head;
    return 0;
}

//Реализуйте двусвязный циклический список, предусмотрите в нем функции
//добавления элемента, вставки, удаления, обхода списка в обоих направлениях.
//При выполнении задачи опирайтесь на лекцию 19 про односвязный список, а также
//на справочные ресурсы, например:
//https://prog-cpp.ru/data-dcs/

//Будьте готовы объяснить вашу реализацию.
