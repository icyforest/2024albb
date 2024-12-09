#include"skipList.h"
int main() {
    skipList<int,int> skip_list(0x7fffffff);

    int length = 10;
    for(int i = 1;i <= length;i++) {
        skip_list.insert(i,i * 10);
    }
    cout << skip_list.getNodeSize() << endl;

    //search
    Node<int,int>* a = skip_list.search(2);
    printf("%d\n",(a == nullptr));

    //delete

    printf("%d ",skip_list.remove(6));
    printf("%d",skip_list.getNodeSize());
}