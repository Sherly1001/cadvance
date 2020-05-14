#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_SIZE 3

/*một phần tử trong danh bạ điện thoại*/
typedef struct {
	char name[80];
	long number;
} PhoneEntry;

/*lưu trữ danh bạ điện thoại
entries: mảng cấp phát động chứa danh bạ
kích thước ban đầu là INITIAL_SIZE
total là kích thước tối đa của danh bạn hiện tại
size là số lượng phần tử thực sự hiện đang lưu trữ
nếu size == total nghĩa là mảng động đang đầy và ta cần nhân đôi mảng
trước khi thêm một phần tử mới
*/
typedef struct {
	PhoneEntry * entries;
	int total;
	int size;
} PhoneBook;

// khởi tạo danh bạ ban đầu với kích thước INITIAL_SIZE
PhoneBook*  createPhoneBook()
{
    PhoneBook* aContactList = NULL;
    aContactList = malloc(sizeof(PhoneBook));
    
    // danh bạ ban đầu rỗng và total size là INITIAL_SIZE
    aContactList->total = INITIAL_SIZE;
    aContactList->size = 0;
    
    // cấp phát mảng động ban đầu để lưu trữ các contact
    aContactList->entries = malloc(sizeof(PhoneEntry) * INITIAL_SIZE);
    
    return aContactList;
}

// giải phóng bộ nhớ động cấp phát cho danh bạ ở trên 
void  dropPhoneBook(PhoneBook** aContactList)
{
    PhoneBook* tmp = *aContactList;
    
    free(tmp->entries);
    tmp = NULL;
    
    free(*aContactList);
    *aContactList = NULL;
}

int checkExist(char *name, PhoneBook* aContactList)
{
    for(int i=0;i<aContactList->size; i++)
        if(!strcmp(aContactList->entries[i].name, name))
            return 1;
    return 0;
}

// thêm một phần tử mới vào danh bạ
// chú ý nhân đôi nếu mảng đang đầy
void addPhoneNumber(char *name, long number, PhoneBook** aContactList)
{
    PhoneBook* clist = *aContactList;
    if(checkExist(name,clist)) return ;
    if(clist->size < clist->total)//chua day --> them vao cuoi
    {
        int last = clist->size;
        (clist->entries[last]).number = number;
        strcpy((clist->entries[last]).name,name);
        clist->size++;
    }
    else // nhan doi mang cu
    {
        PhoneEntry *newList = malloc(sizeof(PhoneEntry) * clist->total * 2);
        memcpy(newList, clist->entries, sizeof(PhoneEntry) * clist->total);
        free(clist->entries);

        clist->entries = newList;

        clist->total *= 2;
        int last = clist->size;
        (clist->entries[last]).number = number;
        strcpy((clist->entries[last]).name,name);
        clist->size++;
    }
}

// tra cứu sdt theo họ tên
// tìm theo hàm strstr
// co dang phan biet HOA va thuong
PhoneEntry *lookupPhoneBook(char *name, PhoneBook* book)
{
    PhoneEntry* aEntry = NULL;
    
    // tim tuan tu, moi phan tu thi so sanh name voi gia tri trong danh ba
    for(int i=0;i<book->size; i++)
        if(NULL!=strstr(book->entries[i].name, name))
        {
            aEntry = &(book->entries[i]);
            break;
        }
    return aEntry;
}

void addPhoneNumbers(PhoneBook** book) {
    char name[50] = "";
    long phone = 0;
    while (1) {
        printf("Nhap ten: ");
        scanf("%[^\n]s\n", name);
        printf("Nhap so dien thoai: ");
        scanf("%ld\n", &phone);
        addPhoneNumber(name, phone, book);
        int c = 0;
        do {
            printf("\nBan co muon nhap tiep khong?\n0. khong\n1. co\n");
            scanf("%d\n", &c);
        } while (c < 0 || c > 1);
        if (!c) break;
    }
}

void saveContactToFile(PhoneBook *list) {
    FILE *f = fopen("contacts.txt", "w");
    fprintf(f, "%ld\n", list->size);
    for (int i = 0; i < list->size; ++i) {
        fprintf(f, "%s|%ld\n", list->entries[i].name, list->entries[i].number);
    }
    fclose(f);
}

void loadContactFromFile(char *fn, PhoneBook **list) {
    FILE *f = fopen(fn, "r");
    if (!f) {
        printf("Khong thay file %s\n", fn);
        return;
    }
    char line[100];
    char name[80] = "";
    long phone = 0, size = 0;
    fscanf(f, "%ld\n", &size);
    while (size) {
        fgets(line, 99, f);
        int i = 0;
        while (i < 99 & line[i] != '|') ++i;
        line[i] = 0;
        sscanf(line + i + 1, "%ld", &phone);
        addPhoneNumber(line, phone, list);
        --size;
    }
    fclose(f);
}

PhoneEntry *lookupPhoneBookIgnoreCase(const char *name, PhoneBook* book) {
    char iName1[80] = "", iName2[80] = "";

    for(int i = 0; i < book->size; i++) {
        int j = 0;
        for (; book->entries[i].name[j]; ++j) iName1[j] = tolower(book->entries[i].name[j]);
        iName1[j] = '\0';
        j = 0;
        for (; name[j]; ++j) iName2[j] = tolower(name[j]);
        iName2[j] = '\0';
        char *found = NULL;
        if (found = strstr(iName1, iName2)) return book->entries + i;
    }
    return NULL;
}

void prt(PhoneBook *list) {
    for (int i = 0; i < list->size; ++i) {
        printf("%s|%ld\n", list->entries[i].name, list->entries[i].number);
    }
    printf("\n");
}

int main()
{
    PhoneBook* myContactList;
    myContactList = createPhoneBook();

    //test ham them
    // addPhoneNumber("Nguyen Van A",12233423,&myContactList);
    // addPhoneNumber("Le Van An",2322423,&myContactList);
    // addPhoneNumber("Van Ngoc Anh",32233423,&myContactList);
    // addPhoneNumber("Nguyen Tien Dung",44233423,&myContactList);
    // addPhoneNumber("Nguyen Tien Du",54233423,&myContactList);
    // addPhoneNumber("Huynh Tien Dung",64233423,&myContactList)
    // test ham tim kiem
    // char lookupname[] = "Huynh";

    // PhoneEntry *anEntry = lookupPhoneBook(lookupname,myContactList);
    // if(NULL==anEntry)
    //     printf("%s Khong co trong danh ba!\n",lookupname);
    // else
    //     printf("%s co SDT la %ld!\n",lookupname,anEntry->number);

    loadContactFromFile("contacts.txt", &myContactList);

    prt(myContactList);

    char lookupname[] = "tien dung";
    PhoneEntry *found = lookupPhoneBookIgnoreCase(lookupname, myContactList);
    if(found)
        printf("%s co SDT la %ld!\n",lookupname, found->number);
    else
        printf("%s Khong co trong danh ba!\n", lookupname);
    // saveContactToFile(myContactList);
    dropPhoneBook(&myContactList);
    return 0;
}
