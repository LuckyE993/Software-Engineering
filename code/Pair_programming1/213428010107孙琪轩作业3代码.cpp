//
// Created by Lucky_E on 2023-06-21.
//

#include <iostream>
#include <string>
#include <regex>

using namespace std;

/**
 *@brief  手机号数据验证
 *
 * @param[in] phoneNumber 手机号
 *
 * @return bool
 */
bool isValidPhoneNumber(const string& phoneNumber) {
    regex pattern("^\\d{11}$");
    return regex_match(phoneNumber, pattern);
}

/**
 *@brief  邮箱数据验证
 *
 * @param[in] email 邮箱地址
 *
 * @return bool
 */
bool isValidEmail(const string& email) {
    regex pattern("^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$");
    return regex_match(email, pattern);
}


/**
 *@brief  定义通讯录节点结构
 *
 * @param[in] none
 *
 * @return none
 */
struct ContactNode {
    string name;
    string phoneNumber;
    string qqNumber;
    string email;
    ContactNode* prev;
    ContactNode* next;
};

/**
 * @brief 添加联系人
 *
 * @param[in] head 头节点指针
 * @param[in] name 联系人姓名
 * @param[in] phoneNumber 联系人手机号
 * @param[in] qqNumber 联系人QQ号
 * @param[in] email 联系人邮箱
 *
 * @return none
 */
void addContact(ContactNode*& head, const string& name, const string& phoneNumber, const string& qqNumber,
                const string& email) {
    ContactNode* newNode = new ContactNode;
    newNode->name = name;
    newNode->phoneNumber = phoneNumber;
    newNode->qqNumber = qqNumber;
    newNode->email = email;

    if (head == nullptr) {
        head = newNode;
        head->prev = newNode;
        head->next = newNode;
    }
    else {
        newNode->prev = head->prev;
        newNode->next = head;
        head->prev->next = newNode;
        head->prev = newNode;
    }
    cout << "联系人已添加：" << name << endl;
}

/**
 * @brief 插入联系人
 *
 * @param[in] head 头节点指针
 * @param[in] name 联系人姓名
 * @param[in] phoneNumber 联系人手机号
 * @param[in] qqNumber 联系人QQ号
 * @param[in] email 联系人邮箱
 * @param[in] position 插入位置
 *
 * @return none
 */
void insertContact(ContactNode*& head, const string& name, const string& phoneNumber, const string& qqNumber,
                   const string& email, int position) {
    if (position <= 0) {
        cout << "无效的插入位置" << endl;
        return;
    }

    ContactNode* newNode = new ContactNode;
    newNode->name = name;
    newNode->phoneNumber = phoneNumber;
    newNode->qqNumber = qqNumber;
    newNode->email = email;

    if (head == nullptr) {
        head = newNode;
        head->prev = newNode;
        head->next = newNode;
    }
    else {
        ContactNode* current = head;
        for (int i = 1; i < position && current->next != head; i++) {
            current = current->next;
        }
        newNode->prev = current;
        newNode->next = current->next;
        current->next->prev = newNode;
        current->next = newNode;
    }
    cout << "联系人已插入：" << name << endl;
}

/**
 * @brief 删除联系人
 *
 * @param[in] head 头节点指针
 * @param[in] name 联系人姓名
 *
 * @return none
 */
void deleteContact(ContactNode*& head, const string& name) {
    if (head == nullptr) {
        cout << "通讯录为空" << endl;
        return;
    }

    ContactNode* current = head;
    do {
        if (current->name == name) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            if (current == head) {
                head = current->next;
            }
            delete current;
            cout << "联系人已删除：" << name << endl;
            return;
        }
        current = current->next;
    } while (current != head);

    cout << "未找到联系人：" << name << endl;
}

/**
 * @brief 查询联系人
 *
 * @param[in] head 头节点指针
 * @param[in] name 联系人姓名
 *
 * @return none
 */
void searchContact(ContactNode* head, const string& searchQuery) {
    if (head == nullptr) {
        cout << "通讯录为空" << endl;
        return;
    }

    ContactNode* current = head;
    do {
        if (current->name == searchQuery ||
            current->phoneNumber == searchQuery ||
            current->qqNumber == searchQuery ||
            current->email == searchQuery) {
            cout << "姓名：" << current->name << endl;
            cout << "手机号：" << current->phoneNumber << endl;
            cout << "QQ 号：" << current->qqNumber << endl;
            cout << "邮箱：" << current->email << endl;
            return;
        }
        current = current->next;
    } while (current != head);

    cout << "未找到匹配的联系人：" << searchQuery << endl;
}


/**
 * @brief 统计联系人数量
 *
 * @param[in] head 头节点指针
 *
 * @return 联系人数量
 */
int countContacts(ContactNode* head) {
    int count = 0;
    ContactNode* current = head;
    if (current == nullptr) {
        return count;
    }

    do {
        count++;
        current = current->next;
    } while (current != head);

    return count;
}

void printMenu() {
    cout << "========================" << endl;
    cout << "通讯录管理系统" << endl;
    cout << "1. 添加联系人" << endl;
    cout << "2. 插入联系人" << endl;
    cout << "3. 删除联系人" << endl;
    cout << "4. 查询联系人" << endl;
    cout << "5. 统计联系人数量" << endl;
    cout << "0. 退出" << endl;
    cout << "========================" << endl;
    cout << "请输入操作选项：";
}

int main() {
    ContactNode* head = nullptr;
    int choice;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, phoneNumber, qqNumber, email;
                cout << "请输入联系人姓名：";
                cin >> name;

                cout << "请输入联系人手机号：";
                cin >> phoneNumber;
                while (!isValidPhoneNumber(phoneNumber)) {
                    cout << "无效的手机号格式,请重新输入。" << endl;
                    cin >> phoneNumber;
                }

                cout << "请输入联系人QQ号：";
                cin >> qqNumber;

                cout << "请输入联系人邮箱：";
                cin >> email;
                while(!isValidEmail(email)) {
                    cout << "无效的邮箱格式,请重新输入。" << endl;
                    cin >> email;
                }

                addContact(head, name, phoneNumber, qqNumber, email);
                break;
            }
            case 2: {
                string name, phoneNumber, qqNumber, email;
                int position;
                cout << "请输入联系人姓名：";
                cin >> name;
                cout << "请输入联系人手机号：";
                cin >> phoneNumber;
                cout << "请输入联系人QQ号：";
                cin >> qqNumber;
                cout << "请输入联系人邮箱：";
                cin >> email;

                if (!isValidPhoneNumber(phoneNumber)) {
                    cout << "无效的手机号格式" << endl;
                    break;
                }

                if (!isValidEmail(email)) {
                    cout << "无效的邮箱格式" << endl;
                    break;
                }

                cout << "请输入插入位置：";
                cin >> position;
                insertContact(head, name, phoneNumber, qqNumber, email, position);
                break;
            }
            case 3: {
                string name;
                cout << "请输入要删除的联系人姓名：";
                cin >> name;
                deleteContact(head, name);
                break;
            }
            case 4: {
                string name;
                cout << "请输入要查询的联系人信息（姓名、手机号、QQ号、邮箱）：";
                cin >> name;
                searchContact(head, name);
                break;
            }
            case 5: {
                cout << "联系人数量：" << countContacts(head) << endl;
                break;
            }
            case 0: {
                cout << "已退出通讯录管理系统" << endl;
                break;
            }
            default:
                cout << "无效的选项" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}