#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Term {
    int coefficient;
    int exponent;
};

struct Polynomial {
    Term* terms; // 动态数组用于存储多项式的项
    int numTerms; // 项的数量
};

// 比较函数，用于指数的降序排序
bool compareTerms(const Term& a, const Term& b) {
    return a.exponent > b.exponent;
}

// 从键盘输入多项式
void readPolynomial(Polynomial& poly) {
    cout << "请输入多项式的项数: ";
    cin >> poly.numTerms;

    poly.terms = new Term[poly.numTerms];

    for (int i = 0; i < poly.numTerms; i++) {
        cout << "请输入第" << i + 1 << "项的系数: ";
        cin >> poly.terms[i].coefficient;
        cout << "请输入第" << i + 1 << "项的指数: ";
        cin >> poly.terms[i].exponent;
    }

    // 根据指数对多项式进行排序，以便后续操作
    sort(poly.terms, poly.terms + poly.numTerms, compareTerms);
}

// 保存多项式到文件
void savePolynomialToFile(const Polynomial& poly, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (int i = 0; i < poly.numTerms; i++) {
            file << poly.terms[i].coefficient << "x^" << poly.terms[i].exponent << " ";
        }

        file.close();
        cout << "多项式已保存到文件: " << filename << endl;
    } else {
        cout << "无法打开文件: " << filename << endl;
    }
}

// 输出多项式
void printPolynomial(const Polynomial& poly) {
    for (int i = 0; i < poly.numTerms; i++) {
        cout << poly.terms[i].coefficient << "x^" << poly.terms[i].exponent << " ";
    }

    cout << endl;
}

// 多项式相加
Polynomial addPolynomials(const Polynomial& poly1, const Polynomial& poly2) {
    Polynomial result;
    int maxSize = max(poly1.numTerms, poly2.numTerms);
    result.terms = new Term[maxSize];

    int i = 0, j = 0, k = 0;
    while (i < poly1.numTerms && j < poly2.numTerms)
    {
        if (poly1.terms[i].exponent > poly2.terms[j].exponent)
        {
            result.terms[k] = poly1.terms[i];
            i++;
        } else if (poly1.terms[i].exponent < poly2.terms[j].exponent) {
            result.terms[k] = poly2.terms[j];
            j++;
        } else {
            result.terms[k].coefficient = poly1.terms[i].coefficient + poly2.terms[j].coefficient;
            result.terms[k].exponent = poly1.terms[i].exponent;
            i++;
            j++;
        }
        k++;
    }

    // 处理剩余的项
    while (i < poly1.numTerms) {
        result.terms[k] = poly1.terms[i];
        i++;
        k++;
    }

    while (j < poly2.numTerms) {
        result.terms[k] = poly2.terms[j];
        j++;
        k++;
    }

    result.numTerms = k;

    cout << "多项式相加结果: ";
    printPolynomial(result);

    return result;
}

// 多项式相减
Polynomial subtractPolynomials(const Polynomial& poly1, const Polynomial& poly2) {
    Polynomial result;
    int maxSize = max(poly1.numTerms, poly2.numTerms);
    result.terms = new Term[maxSize];

    int i = 0, j = 0, k = 0;
    while (i < poly1.numTerms && j < poly2.numTerms) {
        if (poly1.terms[i].exponent > poly2.terms[j].exponent) {
            result.terms[k] = poly1.terms[i];
            i++;
        } else if (poly1.terms[i].exponent < poly2.terms[j].exponent) {
            result.terms[k] = poly2.terms[j];
            j++;
        } else {
            result.terms[k].coefficient = poly1.terms[i].coefficient - poly2.terms[j].coefficient;
            result.terms[k].exponent = poly1.terms[i].exponent;
            i++;
            j++;
        }
        k++;
    }

    // 处理剩余的项
    while (i < poly1.numTerms) {
        result.terms[k] = poly1.terms[i];
        i++;
        k++;
    }

    while (j < poly2.numTerms) {
        result.terms[k] = poly2.terms[j];
        j++;
        k++;
    }

    result.numTerms = k;

    cout << "多项式相减结果: ";
    printPolynomial(result);

    return result;
}

int main() {
    Polynomial poly1;
    Polynomial poly2;
    Polynomial sum;
    Polynomial diff;

    cout << "输入第一个多项式：" << endl;
    readPolynomial(poly1);

    cout << "输入第二个多项式：" << endl;
    readPolynomial(poly2);

    sum = addPolynomials(poly1, poly2);
    diff = subtractPolynomials(poly1, poly2);

    cout << "第一个多项式: ";
    printPolynomial(poly1);

    cout << "第二个多项式: ";
    printPolynomial(poly2);

    savePolynomialToFile(sum, "sum.txt");
    savePolynomialToFile(diff, "diff.txt");

    delete[] poly1.terms;
    delete[] poly2.terms;
    delete[] sum.terms;
    delete[] diff.terms;

    return 0;
}
