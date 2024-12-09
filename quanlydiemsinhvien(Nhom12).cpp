// chỉnh sửa lần cuối vào ngày 08/11 
// Phân hiệu Đại Học Giao Thông Vận Tải tại tp.HCM ( UTC2 )
// nhóm thực hiện nhóm 8 
// sinh viên thực hiện Lê Trường Thọ      CQ.KTĐTVT.64
//                     Bùi Quang Huy	  CQ.KTĐTVT.64
// 		       Nguyễn Phúc Thảo   CQ.KTĐTVT.64

#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdio.h>

struct SinhVien { 
    long long MaSV;
    char HoVaTenSV[50];
    char Lop[50];
    float GPA;
    int drl;
};

struct Node {
    SinhVien data; 
    Node* next;
};

class List {
private:
    Node* head; 
    Node* tail; 
    int size;  

public: 
    List(); 
    Node* createNode(SinhVien x); 
    bool Empty();
    void Themsvdauds(SinhVien x);
    void Themsvcuoids(SinhVien x);
    void Themsvbatki(SinhVien x, int pos);
    void deleteFirst(); 
    void deleteLast(); 
    void xoabatki(int pos);
    void print();
    bool check(long long MSSV);
    void SapxepMaSV();
    void SAPXEPTHEOTEN();
    void SAPXEPGPA(int tg);
    void timkiemMSV(long long key);
    void xethocbong();
    void saveToFile(const char* filename);
    void loadFromFile(const char* filename);
};

List::List() {
    head = tail = NULL;
    size = 0;
}

bool List::Empty() {
    return head == NULL; 
}

Node* List::createNode(SinhVien x) {
    Node* p = new Node();
    p->data = x;
    p->next = NULL;
    return p;
}

void List::Themsvcuoids(SinhVien x) {
    Node* p = createNode(x);
    if (head == NULL) {
        head = tail = p;
    } else {
        tail->next = p;
        tail = p;
    }
    size++;
}

void List::Themsvdauds(SinhVien x) {
    Node* p = createNode(x);
    if (head == NULL) {
        head = tail = p;
    } else {
        p->next = head;
        head = p;
    }
    size++;
}

void List::Themsvbatki(SinhVien x, int pos) {
    if (pos < 1 || pos > size + 1) {
        printf("Vi tri khong hop le\n");
        return;
    }
    
    Node* p = createNode(x);
    if (Empty()) {
        head = tail = p;
    } else if (pos == 1) {
        Themsvdauds(x);
    } else if (pos == size + 1) {
        Themsvcuoids(x);
    } else {
        Node* a = head;
        for (int i = 1; i < pos - 1; i++) {
            a = a->next;
        }
        p->next = a->next;
        a->next = p;
        size++;
    }
}

bool List::check(long long MSSV) {
    if (MSSV <= 0) {
        return false; 
    }
    for (Node* p = head; p != NULL; p = p->next) {
        if (p->data.MaSV == MSSV) {
            return true; 
        }
    }
    return false;
}

void List::deleteFirst() {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    Node* tmp = head;
    head = head->next;
    delete tmp;
    size--;
    if (head == NULL) {
        tail = NULL;
    }
}

void List::deleteLast() {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    if (head == tail) {
        deleteFirst();
        return;
    } else {
        Node* a = head;
        for (int i = 1; i < size - 1; i++) {
            a = a->next;
        }
        delete tail;
        a->next = NULL;
        tail = a;
        size--;
    }
}

void List::xoabatki(int pos) {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    if (pos < 1 || pos > size) {
        printf("Vi tri khong hop le!\n");
        return;
    }
    if (pos == 1) {
        deleteFirst();
        return;
    }
    if (pos == size) {
        deleteLast();
        return;
    }
    Node* a = head;
    for (int i = 1; i < pos - 1; i++) {
        a = a->next;
    }
    Node* temp = a->next;
    a->next = temp->next;
    delete temp;
    size--;
}

void List::SapxepMaSV() {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    for (Node* i = head; i != NULL; i = i->next) {
        for (Node* j = i->next; j != NULL; j = j->next) {
            if (i->data.MaSV > j->data.MaSV) {
                SinhVien temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    printf("\n => Danh sach da duoc sap xep theo MaSV tang dan:\n");
}

char* Ten(char* HoVaTenSV) {
    char* p = strrchr(HoVaTenSV, ' ');
    return (p == NULL) ? HoVaTenSV : p + 1;
}

void List::SAPXEPTHEOTEN() {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    for (Node* p = head; p->next != NULL; p = p->next) {
        for (Node* q = p->next; q != NULL; q = q->next) {
            if (strcmp(Ten(p->data.HoVaTenSV), Ten(q->data.HoVaTenSV)) > 0) {
                SinhVien temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
    printf("\n => Danh sach da duoc sap xep theo ten:\n");
}

void List::SAPXEPGPA(int tg) {
    if (head == NULL) return;
    for (Node* p = head; p->next != NULL; p = p->next) {
        for (Node* q = p->next; q != NULL; q = q->next) {
            if ((tg == 1 && p->data.GPA > q->data.GPA) || (tg == 2 && p->data.GPA < q->data.GPA)) {
                SinhVien temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
    printf("\n => Danh sach da duoc sap xep theo GPA:\n");
}

void List::timkiemMSV(long long key) {
    Node* p = head;
    bool found = false;

    while (p != NULL) {
        if (p->data.MaSV == key) {
            printf("\n---------------------------------------------------------------");
            printf("\n| MA SINH VIEN  | HO VA TEN            | LOP         | GPA    |");
            printf("\n---------------------------------------------------------------");
            printf("\n| %-13lld | %-20s | %-11s | %-6.2f |",  
                   p->data.MaSV, 
                   p->data.HoVaTenSV, 
                   p->data.Lop, 
                   p->data.GPA);
            printf("\n---------------------------------------------------------------");
            found = true;
            break;
        }
        p = p->next;
    }
    if (!found) {
        printf(" => Khong tim thay sinh vien voi ma so: %lld\n", key);
    }
}

void List::xethocbong() {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }

    SAPXEPGPA(2); 

    printf("\n => Danh sach 5 sinh vien co GPA cao nhat: \n");
    printf("\n------------------------------------------------------------------------------------");
    printf("\n| MA SINH VIEN  | HO VA TEN            | LOP         | GPA    | DRL     | Hoc Bong |");
    printf("\n------------------------------------------------------------------------------------");

    int dem = 0;
    for (Node* i = head; i != NULL && dem < 5; i = i->next) {
        if (i->data.drl >= 70) { 
            const char* loaiHocBong;
             if ((i->data.GPA>3.59) && (i->data.drl>=90 )) {
            loaiHocBong = "Xuat sac";
            }else if ((i->data.GPA >=3.2 && i->data.GPA<3.60)&& (i->data.drl>=80 )) {
               loaiHocBong = "Gioi";
            }else if ((i->data.GPA>=3.2&& i->data.drl>=80)&& (i->data.drl<90 )) {
               loaiHocBong = "Gioi";
			}else if ((2.50 <= i->data.GPA && i->data.GPA <3.20) && (i->data.drl>=80 )) {
                loaiHocBong = "Kha";
            } else if ((i->data.GPA>=3.2)&&((i->data.drl>=70)&&(i->data.drl<80))){
            	loaiHocBong="Kha";
			}else {
                loaiHocBong = "Khong co";
            } 
            printf("\n| %-13lld | %-20s | %-11s | %-6.2f | %-7d | %-8s |", 
                   i->data.MaSV, 
                   i->data.HoVaTenSV, 
                   i->data.Lop, 
                   i->data.GPA, 
                   i->data.drl, 
                   loaiHocBong);
            dem++;
        }
    }
    printf("\n------------------------------------------------------------------------------------");
}

void List::saveToFile(const char* filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Khong the mo file de ghi!" << std::endl;
        return;
    }
    Node* p = head;
    while (p != NULL) {
        file << p->data.MaSV << "\n"
             << p->data.HoVaTenSV << "\n"
             << p->data.Lop << "\n"
             << p->data.GPA << "\n"
             << p->data.drl << "\n";
        p = p->next;
    }
    file.close();
    std::cout << "Du lieu da duoc luu vao file: " << filename << std::endl;
}

void List::loadFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Khong the mo file de doc!" << std::endl;
        return;
    }
    
    SinhVien sv;
    while (file >> sv.MaSV) {
        file.ignore(); 
        file.getline(sv.HoVaTenSV, sizeof(sv.HoVaTenSV));
        file.getline(sv.Lop, sizeof(sv.Lop));
        file >> sv.GPA >> sv.drl;
        file.ignore(); 
        Themsvcuoids(sv);
    }
    file.close();
    std::cout << "Du lieu da duoc tai ve tu file: " << filename << std::endl;
}

void List::print() {
    if (head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }
    printf("\n-------------------------------------------------------------------------");
    printf("\n| MA SINH VIEN  | HO VA TEN            | LOP         | GPA    | DRL     |");
    printf("\n-------------------------------------------------------------------------");
    for (Node* p = head; p != NULL; p = p->next) {
        printf("\n| %-13lld | %-20s | %-11s | %-6.2f | %-7d |",  
               p->data.MaSV, 
               p->data.HoVaTenSV, 
               p->data.Lop, 
               p->data.GPA, 
               p->data.drl);
    }
    printf("\n-------------------------------------------------------------------------");
}

int main() {
    List l;
    int choice;

    do {
        printf("\n*====================== MENU ======================*");
        printf("\n||1. Them sinh vien                               ||");
        printf("\n||2. Xoa sinh vien                                ||");
        printf("\n||3. Tim sinh vien                                ||");
        printf("\n||4. Sap xep sinh vien                            ||");
        printf("\n||5. Danh sach sinh vien                          ||");
        printf("\n||6. Luu danh sach vao file                       ||");
        printf("\n||7. Tai danh sach tu file                        ||");
        printf("\n||8. Xet hoc bong                                 ||");
        printf("\n||0. Thoat                                        ||");
        printf("\n*==================================================*");
        printf("\n =>  Chon chuc nang:      ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
            	int lc;
            	printf("\n1.Them sinh vien dau danh sach.");
				printf("\n2.Them sinh vien cuoi danh sach.");
				printf("\n3.Them sinh vien bat ki.");
				printf("\nChon: ");
                scanf("%d", &lc);
				switch (lc) {
                    case 1:{
                		SinhVien sv;
                		do {
                    	printf("\n- Nhap vao ma so sinh vien: ");
                    	scanf("%lld", &sv.MaSV);
                    	if (l.check(sv.MaSV)) {
                        printf("Ma so da ton tai. Vui long nhap lai.\n");
                    	}
                		} while (l.check(sv.MaSV));
                		printf("- Nhap vao ho va ten sinh vien: ");
                		getchar(); 
                		fgets(sv.HoVaTenSV, sizeof(sv.HoVaTenSV), stdin);
                		sv.HoVaTenSV[strcspn(sv.HoVaTenSV, "\n")] = 0; 
                		printf("- Nhap vao lop: ");
                		fgets(sv.Lop, sizeof(sv.Lop), stdin);
                		sv.Lop[strcspn(sv.Lop, "\n")] = 0; 
                		do {
                		printf("\n- Nhap GPA : ");
                		scanf ("%f",&sv.GPA);
                		if (sv.GPA > 4.0 || sv.GPA < 0) {
                		printf("\nGPA khong hop le vui long nhap lai");}
                		} while (sv.GPA > 4.0 || sv.GPA < 0);
                		do {
                		printf("\n- Nhap vao diem ren luyen: ");
                		scanf("%d",&sv.drl);
                		if (sv.drl>100 || sv.drl<0)
                		printf("\nDiem ren luyen khong hop le vui long nhap lai");
                		} while (sv.drl>100 || sv.drl<0);
                		l.Themsvdauds(sv);
                		printf("\n => Sinh vien da duoc them vao danh sach.\n");
                		break;
                	}
                	case 2: {
                		SinhVien sv;
                		do {
                    	printf("\n- Nhap vao ma so sinh vien: ");
                    	scanf("%lld", &sv.MaSV);
                    	if (l.check(sv.MaSV)) {
                        printf("Ma so da ton tai. Vui long nhap lai.\n");
                    	}
                		} while (l.check(sv.MaSV));
                		printf("- Nhap vao ho va ten sinh vien: ");
                		getchar(); 
                		fgets(sv.HoVaTenSV, sizeof(sv.HoVaTenSV), stdin);
                		sv.HoVaTenSV[strcspn(sv.HoVaTenSV, "\n")] = 0; 
                		printf("- Nhap vao lop: ");
                		fgets(sv.Lop, sizeof(sv.Lop), stdin);
                		sv.Lop[strcspn(sv.Lop, "\n")] = 0; 
                		do {
                		printf("\n- Nhap GPA : ");
                		scanf ("%f",&sv.GPA);
                		if (sv.GPA > 4.0 || sv.GPA < 0) {
                		printf("\nGPA khong hop le vui long nhap lai");}
                		} while (sv.GPA > 4.0 || sv.GPA < 0);
                		do {
                		printf("\n- Nhap vao diem ren luyen: ");
                		scanf("%d",&sv.drl);
                		if (sv.drl>100 || sv.drl<0)
                		printf("\nDiem ren luyen khong hop le vui long nhap lai");
                		} while (sv.drl>100 || sv.drl<0);
                		l.Themsvcuoids(sv);
                		printf("\n => Sinh vien da duoc them vao danh sach.\n");
						break;
					}
					case 3:{
						SinhVien sv;
            			int pos;
                		do {
                    	printf("\n- Nhap vao ma so sinh vien: ");
                    	scanf("%lld", &sv.MaSV);
                    	if (l.check(sv.MaSV)) {
                        printf("Ma so da ton tai. Vui long nhap lai.\n");
                    	}
                		} while (l.check(sv.MaSV) != 0);
						printf("- Nhap vao ho va ten sinh vien: ");
                		getchar(); 
                		fgets(sv.HoVaTenSV, sizeof(sv.HoVaTenSV), stdin);
                		sv.HoVaTenSV[strcspn(sv.HoVaTenSV, "\n")] = 0; 
                		printf("- Nhap vao lop: ");
                		fgets(sv.Lop, sizeof(sv.Lop), stdin);
                		sv.Lop[strcspn(sv.Lop, "\n")] = 0; 
                		do {
                		printf("\n- Nhap GPA : ");
                		scanf ("%f",&sv.GPA);
                		if (sv.GPA > 4.0 || sv.GPA < 0) {
                		printf("\nGPA khong hop le vui long nhap lai");}
                		} while (sv.GPA > 4.0 || sv.GPA < 0);
                		do {
                		printf("\n- Nhap vao diem ren luyen: ");
                		scanf("%d",&sv.drl);
                		if (sv.drl>100 || sv.drl<0)
                		printf("\nDiem ren luyen khong hop le vui long nhap lai");
                		} while (sv.drl>100 || sv.drl<0);
                		printf("\n- Nhap vi tri: ");
                		scanf("%d",&pos);
                		l.Themsvbatki(sv,pos);
                		printf("\n => Sinh vien da duoc them vao danh sach.\n");
						break;
					}
            	}
				break;
			}
            case 2: {
                int pos;
                printf("- Nhap vi tri sinh vien can xoa: ");
                scanf("%d", &pos);
                l.xoabatki(pos);
                break;
            }
            case 3: {
                long long key;
                printf("- Nhap ma so sinh vien can tim: ");
                scanf("%lld", &key);
                l.timkiemMSV(key);
                break;
            }
            case 4: {
                int subChoice;
                printf("1. Sap xep theo MaSV\n");
                printf("2. Sap xep theo Ten\n");
                printf("3. Sap xep theo GPA\n");
                printf("Chon: ");
                scanf("%d", &subChoice);
                switch (subChoice) {
                    case 1: l.SapxepMaSV(); break;
                    case 2: l.SAPXEPTHEOTEN(); break;
                    case 3: {
                        int order;
                        printf("1. Tang dan\n");
                        printf("2. Giam dan\n");
                        printf("\nChon: ");
                        scanf("%d", &order);
                        l.SAPXEPGPA(order);
                        break;
                    }
                    default: printf("Chuc nang khong hop le.\n"); break;
                }
                break;
            }
            case 5: l.print(); break;
            case 6: {
                const char* filename = "students.txt";
                l.saveToFile(filename);
                break;
            }
            case 7: {
                const char* filename = "students.txt";
                l.loadFromFile(filename);
                break;
            }
            case 8: l.xethocbong(); break;
            case 0: printf("Thoat chuong trinh.\n"); break;
            default: printf("Chuc nang khong hop le.\n"); break;
        }
    } while (choice != 0);

    return 0;
}
