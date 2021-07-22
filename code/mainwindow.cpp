#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include <QString>
#include <vector>
#define int long long
#define double long double
using namespace std;

const double e = 2.718281828459045, Pi = M_PI;
const int digit_degree = 9;
const int max_digit_size = pow(10, digit_degree);
const int max_double_digits_cnt = 4390;
deque<string> deque_expression_components, st_variables;
stack<string> st_operators;
deque<string> str_postfix_expr, str_postfix_expr_copy;
map<string, string> variables;


class Vars_Window : public QWidget {
public:
    Vars_Window() {
        line = new QLineEdit;
        pushbutton = new QPushButton;
    };
    Vars_Window(const QString&, Ui::MainWindow*);
    ~Vars_Window() {
        delete line;
        delete pushbutton;
    } ;
public slots:
    void Pushbutton_clicked();
private:
    QLineEdit* line;
    QPushButton* pushbutton;
    Ui::MainWindow* parent;
};

Vars_Window::Vars_Window(const QString &ss, Ui::MainWindow* parent) {
    this->resize(500, 150);
    line = new QLineEdit(this);
    pushbutton = new QPushButton(this);
    //pushbutton->setParent(this);
    //line->setParent(this);
    pushbutton->setText("Enter");
    //pushbutton->show();
    //line->show();
    line->setGeometry(10, 15, 480, 40);
    pushbutton->setGeometry(10, 80, 480, 50);
    this->setWindowTitle(ss);
    this->parent = parent;
    //QMessageBox::critical(this, "", "eeee");
    QObject::connect(pushbutton, &QPushButton::clicked, this, &Vars_Window::Pushbutton_clicked);
}

bool Num(string str) {
    if (str == "e" || str == "E" || str == "Pi" || str == "PI" || str == "pI" ||str == "pi") {
        return 1;
    }
    if (str.size() == 0) {
        throw "Are you okey?\nEmpty string";
        return 0;
    }
    bool had_comma = 0, have_e = 0;
    int i = 0;
    if (str[0] == '-') {
        ++i;
        if (str.size() == i) {
            throw "Are you okey?\n \"-\" is not a number\n";
            return 0;
        }
    }
    if (str[i] == '0') {
        ++i;
        if (i < str.size()) {
            if (str[i] != '.') {
                throw "Are you okey?\n You can't start not real num with 0\n";
                return 0;
            }
            ++i;
            if (i == str.size()) {
                throw "Are you okey?\n You can't end num with comma\n";
                return 0;
            }
            if (str[i] < '0' || str[i] > '9') {
                throw "Are you okey?\n You should use digits after comma\n";
                return 0;
            }
        }
    }
    if (str[i] == 'e') {
        throw "Are you okey?\n You can't start num with \"e\"\n";
        return 0;
    }
    for (; i < str.size(); ++i) {
        char cc = str[i];
        if (cc == 'e') {
            if (have_e) {
                throw "Are you okey?\n You can't have 2 \"e\" in the num\n";
                return 0;
            }
            have_e = 1;
            if (i < str.size() - 1) {
                ++i;
                if (str[i] == '-') {
                    ++i;
                }
                if (i == str.size()) {
                    throw "Are you okey?\n You can't start integer num with 0\n";
                    return 0;
                }
                if (str[i] < '1' || str[i] > '9') {
                    throw "Are you okey?\n You should write integer number after \"e\"\n";
                    return 0;
                }
            } else {
                throw "Are you okey?\n You can't end number with \"e\"\n";
                return 0;
            }
        } else if (cc == '.') {
            if (have_e) {
                throw "Are you okey?\n You can't use comma after \"e\"\n";
                return 0;
            }
            if (had_comma) {
                throw "Are you okey?\n You can't have 2 commas in the num\n";
                return 0;
            }
            had_comma = 1;
            ++i;
            if (i == str.size()) {
                throw "Are you okey?\n You can't end num with comma\n";
                return 0;
            }
            if (str[i] < '0' || str[i] > '9') {
                throw "Are you okey?\n You should use digits after comma\n";
                return 0;
            }
        } else if (cc < '0' || cc > '9') {
            throw "Are you okey?\n You entered the wrong num\n";
            return 0;
        }
    }
    return 1;
}

bool Num_(string str) {
    if (str == "e" || str == "E" || str == "Pi" || str == "PI" || str == "pI" ||str == "pi") {
        return 1;
    }
    if (str.size() == 0) {
        return 0;
    }
    bool had_comma = 0, have_e = 0;
    int i = 0;
    if (str[0] == '-') {
        ++i;
        if (str.size() == i) {
            //throw "Are you okey?\n \"-\" is not a number\n";
            return 0;
        }
    }
    if (str[i] == '0') {
        ++i;
        if (i < str.size()) {
            if (str[i] != '.') {
                //throw "Are you okey?\n You can't start not real num with 0\n";
                return 0;
            }
            ++i;
            if (i == str.size()) {
                //throw "Are you okey?\n You can't end num with comma\n";
                return 0;
            }
            if (str[i] < '0' || str[i] > '9') {
                //throw "Are you okey?\n You should use digits after comma\n";
                return 0;
            }
        }
    }
    if (str[i] == 'e') {
        //throw "Are you okey?\n You can't start num with \"e\"\n";
        return 0;
    }
    for (; i < str.size(); ++i) {
        char cc = str[i];
        if (cc == 'e') {
            if (have_e) {
                //throw "Are you okey?\n You can't have 2 \"e\" in the num\n";
                return 0;
            }
            have_e = 1;
            if (i + 2 == str.size() && str[i + 1] == '0') return 1;
            if (i < str.size() - 1) {
                ++i;
                if (str[i] == '-') {
                    ++i;
                }
                if (i == str.size()) {
                    //throw "Are you okey?\n You can't start integer num with 0\n";
                    return 0;
                }
                if (str[i] < '1' || str[i] > '9') {
                    //throw "Are you okey?\n You should write integer number after \"e\"\n";
                    return 0;
                }
            } else {
                //throw "Are you okey?\n You can't end number with \"e\"\n";
                return 0;
            }
        } else if (cc == '.') {
            if (have_e) {
                //throw "Are you okey?\n You can't use comma after \"e\"\n";
                return 0;
            }
            if (had_comma) {
                //throw "Are you okey?\n You can't have 2 commas in the num\n";
                return 0;
            }
            had_comma = 1;
            ++i;
            if (i == str.size()) {
                //throw "Are you okey?\n You can't end num with comma\n";
                return 0;
            }
            if (str[i] < '0' || str[i] > '9') {
                //throw "Are you okey?\n You should use digits after comma\n";
                return 0;
            }
        } else if (cc < '0' || cc > '9') {
            //throw "Are you okey?\n You entered the wrong num\n";
            return 0;
        }
    }
    return 1;
}

class Long_Num {
 public:
    Long_Num() {};
    Long_Num(string str);
    Long_Num(int num);
    Long_Num(double num) {
        throw "cringe";
    }
    Long_Num(vector<int> num);
    ~Long_Num() {};
    Long_Num(const Long_Num& other): digits_(other.digits_), sign_(other.sign_) {};

    string to_string();
    double to_double();

    Long_Num& operator=(Long_Num other) { digits_ = other.digits_; sign_ = other.sign_; return  *this; };
    Long_Num operator+(Long_Num other);
    Long_Num& operator+=(Long_Num other);
    Long_Num operator-(Long_Num other);
    Long_Num operator*(Long_Num other);
    Long_Num& operator*=(Long_Num other);
    Long_Num& operator<<=(int num);
    Long_Num operator/(Long_Num other);
    Long_Num operator%(Long_Num other);
    Long_Num operator^(Long_Num other);
    Long_Num operator!();
    double operator|(Long_Num other);
    Long_Num operator-();
    bool operator<(Long_Num other);
    bool operator>(Long_Num other);
    bool operator==(Long_Num other);
    bool operator<=(Long_Num other);
    bool operator>=(Long_Num other);
    int log10(Long_Num num);

    friend Long_Num long_num(int num);
    friend bool operator<(Long_Num num, int aa);
    friend bool operator>(Long_Num num, int aa);
    friend bool operator<(int aa, Long_Num num);
    friend bool operator>(int aa, Long_Num num);
    friend bool operator==(Long_Num num, int aa);
    friend bool operator==(int aa, Long_Num num);
    friend bool operator<=(Long_Num num, int aa);
    friend bool operator>=(Long_Num num, int aa);
    friend bool operator<=(int aa, Long_Num num);
    friend bool operator>=(int aa, Long_Num num);
    friend double operator+(double aa, Long_Num num);
    friend double operator-(double aa, Long_Num num);
    friend double operator*(double aa, Long_Num num);
    friend double operator^(double aa, Long_Num num);
    friend double operator|(double aa, Long_Num num);
    friend double operator+(Long_Num num, double aa);
    friend double operator-(Long_Num num, double aa);
    friend double operator*(Long_Num num, double aa);
    friend double operator^(Long_Num num, double aa);
    friend double operator|(Long_Num num, double aa);
    friend double log(double aa, Long_Num xx);
    friend double log(Long_Num aa, double xx);
    friend double log(Long_Num aa, Long_Num xx);
    friend std::ostream& operator<<(std::ostream& out, Long_Num num);

    vector<int> digits_ = vector<int>(1, 0);
    int sign_ = 1;
};

double log(double aa, double xx) {
    if (xx <= 0) {
        throw "Are you okey?\n It is negative, or null, don't try to find it's log\n";
        return INFINITY;
    }
    if (aa <= 0 || aa == 1) {
        throw "Are you okey?\n It is negative, or null, or 1, don't try to find it's log\n";
        return INFINITY;
    }
    return log(xx) / log(aa);
}

bool Integer_Num(string str) {
    if (str == "e" || str == "E" || str == "Pi" || str == "PI" || str == "pI" ||str == "pi") {
        return 0;
    }
    bool have_comma = 0, have_e = 0;
    int after_comma = 0, after_e = 0, ind_e = 0, minus_e = 1;
    for (int i = 0; i < str.size(); ++i) {
        char cc = str[i];
        if (cc == 'e') {
            have_e = 1;
            ind_e = i;
            continue;
        } else if (cc == '.') {
            have_comma = 1;
            continue;
        }
        if (have_e) {
            if (cc == '-') {
                minus_e = -1;
            } else {
                after_e *= 10;
                after_e += cc - '0';
            }
        } else if (have_comma) {
            ++after_comma;
        }
    }
    after_e *= minus_e;
    if (-after_comma + after_e >= 0) {
        return 1;
    } else if (have_comma) {
        return 0;
    }
    int nulls_cnt = 0;
    for (int i = ind_e - 1; i >= 0; --i) {
        if (str[i] != '0') {
            break;
        }
        ++nulls_cnt;
    }
    if (nulls_cnt >= -after_e) {
        return 1;
    } else {
        return 0;
    }
}

double Make_Double(string str) {
    if (str == "e" || str == "E") {
        return e;
    } else if (str == "PI" || str == "pi" || str == "Pi" || str == "pI") {
        return Pi;
    }
    bool minus = 0;
    if (str[0] == '-') {
        minus = 1;
        str.erase(str.begin());
    }
    double res = 0;
    bool have_comma = 0, have_e = 0;
    int after_comma = 0, after_e = 0, ind_e = 0, minus_e = 1, ind_comma = 0;
    for (int i = 0; i < str.size(); ++i) {
        char cc = str[i];
        if (cc == 'e') {
            have_e = 1;
            ind_e = i;
            continue;
        } else if (cc == '.') {
            have_comma = 1;
            ind_comma = i;
            continue;
        }
        if (have_e) {
            if (cc == '-') {
                minus_e = -1;
            } else {
                after_e *= 10;
                after_e += cc - '0';
            }
        } else if (have_comma) {
            ++after_comma;
        }
    }
    if (!have_e) {
        ind_e = str.size();
    }
    if (!have_comma) {
        ind_comma = ind_e;
    }
    int integ_part = 0;
    for (int i = 0; i < ind_comma; ++i) {
        integ_part *= 10;
        integ_part += str[i] - '0';
    }
    for (int i = ind_e - 1; i > ind_comma; --i) {
        res *= 0.1;
        res += str[i] - '0';
    }
    res *= 0.1;
    res += integ_part;
    double multiplier = minus_e > 0 ? 10 : 0.1;
    while (after_e) {
        if (after_e % 2) {
            res *= multiplier;
        }
        multiplier *= multiplier;
        after_e /= 2;
    }
    if (minus) {
        res *= -1;
    }
    return res;
}

double log10(Long_Num aa) {
    if (aa <= 0) {
        throw "Are you okey?\n It is negative, or null, don't try to find it's log\n";
        return INFINITY;
    }
    double res = aa.digits_.size() - 3;
    double ln = 0;
    for (int i = aa.digits_.size() - 1; i >= aa.digits_.size() - 3; --i) {
        ln *= pow(10, digit_degree);
        ln += aa.digits_[i];
    }
    res += log(ln) / log(10);
    return res;
}

class Super_Num {
 public:
    Super_Num() {} ;
    Super_Num(string str) {
        if (Integer_Num(str)) {
            long_num = Long_Num(str);
            double_num = 0;
            have_double = 0;
        } else {
            long_num = Long_Num(0ll);
            double_num = Make_Double(str);
            have_double = 1;
        }
    }

    string to_string();
    friend bool use_double_plus(Super_Num num1, Super_Num num2) {
        if (!(num1.have_double || num2.have_double)) {
            return 0;
        }
        return 1;
    }
    friend bool use_double_mult(Super_Num num1, Super_Num num2) {
        if (!(num1.have_double || num2.have_double)) {
            return 0;
        }
        return 1;
    }
    friend bool use_double_pow(Super_Num num1, Super_Num num2) {
        if (!(num1.have_double || num2.have_double)) {
            if (num2.long_num < 0) {
                /*if (num1.long_num.digits_.size() * 9 + num2.long_num.digits_.size() * 9 > max_double_digits_cnt) {
                    throw "Sorry, the result will be too small to fit double\n";
                    return INFINITY;
                }*/
                return 1;
            }
            return 0;
        }
        return 1;
    }
    friend void Normalize(Super_Num& num) {
        if (num.have_double) {

        }
    }
    Super_Num operator+(Super_Num other) {
        if (use_double_plus(*this, other)) {
            other.double_num = (have_double ? double_num : long_num.to_double()) +
                    (other.have_double ? other.double_num : other.long_num.to_double());
            other.have_double = 1;
        } else {
            other.long_num = (have_double ? Long_Num(double_num > 0 ? ceil(double_num) : floor(double_num)) : long_num) +
                    (other.have_double ? Long_Num(other.double_num > 0 ? ceil(other.double_num) : floor(other.double_num)) : other.long_num);
            other.have_double = 0;
        }
        return other;
    }
    Super_Num operator-(Super_Num other);
    Super_Num operator*(Super_Num other);
    Super_Num operator/(Super_Num other);
    Super_Num operator|(Super_Num other);
    Super_Num operator%(Super_Num other);
    Super_Num operator^(Super_Num other);
    Super_Num operator!();
    Super_Num operator-();
    friend Super_Num log(Super_Num aa, Super_Num xx) {
        if (aa.have_double) {
            if (aa.double_num <= 0 || aa.double_num == 1) {
                throw "Are you okey?\n Log's base must be positive and not 1";
            }
        } else {
            if (aa.long_num <= 0 || aa.long_num == 1) {
                throw "Are you okey?\n Log's base must be positive and not 1";
            }
        }
        if (xx.have_double) {
            if (xx.double_num <= 0) {
                throw "Are you okey?\n Log's base must be positive";
            }
        } else {
            if (xx.long_num <= 0) {
                throw "Are you okey?\n Log's base must be positive";
            }
        }
        double aa_log, xx_log;
        if (!aa.have_double && aa.long_num.digits_.size() * 9 > max_double_digits_cnt) {
            aa_log = log10(aa.long_num);
        } else if (!aa.have_double) {
            aa_log = log(aa.long_num.to_double()) / log(10);
        } else {
            aa_log = log(aa.double_num) / log(10);
        }
        if (!xx.have_double && xx.long_num.digits_.size() * 9 > max_double_digits_cnt) {
            xx_log = log10(xx.long_num);
        } else if (!xx.have_double) {
            xx_log = log(xx.long_num.to_double()) / log(10);
        } else {
            xx_log = log(xx.double_num) / log(10);
        }
        if (aa_log == 0) {
            throw "Are you okey?\n You can't use 1 as log's base\n";
        }
        aa.double_num = xx_log / aa_log;
        aa.have_double = 1;
        return aa;
    }
    friend Super_Num sin(Super_Num aa) {
        if (!aa.have_double) {
            if (aa.long_num.digits_.size() > 480) {
                throw "Sorry, this num is too big to take it's cos";
            }
            aa.double_num = aa.long_num.to_double();
        }
        aa.double_num = sin(aa.double_num);
        aa.have_double = 1;
        return aa;
    }
    friend Super_Num cos(Super_Num aa) {
        if (!aa.have_double) {
            if (aa.long_num.digits_.size() > 480) {
                throw "Sorry, this num is too big to take it's cos";
            }
            aa.double_num = aa.long_num.to_double();
        }
        aa.double_num = cos(aa.double_num);
        aa.have_double = 1;
        return aa;
    }
    friend std::ostream& operator<<(std::ostream& out, Super_Num num);

 private:
    Long_Num long_num = Long_Num(0ll);
    bool have_double = 0;
    double double_num = 0;
};

Super_Num Super_Num::operator-(Super_Num other) {
    if (use_double_plus(*this, other)) {
        other.double_num = (have_double ? double_num : long_num.to_double()) -
                (other.have_double ? other.double_num : other.long_num.to_double());
        other.have_double = 1;
    } else {
        other.long_num = (have_double ? Long_Num(double_num > 0 ? ceil(double_num) : floor(double_num)) : long_num) -
                (other.have_double ? Long_Num(other.double_num > 0 ? ceil(other.double_num) : floor(other.double_num)) : other.long_num);
        other.have_double = 0;
    }
    return other;
}

Super_Num Super_Num::operator*(Super_Num other) {
    if (use_double_mult(*this, other)) {
        other.double_num = (have_double ? double_num : long_num.to_double()) *
                (other.have_double ? other.double_num : other.long_num.to_double());
        other.have_double = 1;
    } else {
        other.long_num = (have_double ? Long_Num(double_num > 0 ? ceil(double_num) : floor(double_num)) : long_num) *
                (other.have_double ? Long_Num(other.double_num > 0 ? ceil(other.double_num) : floor(other.double_num)) : other.long_num);
        other.have_double = 0;
    }
    return other;
}

Super_Num Super_Num::operator|(Super_Num other) {
    if (other.have_double && other.double_num == 0 || !other.have_double && other.long_num == 0) {
        throw "Are you okey? You can't divide by null\n";
    }
    /*if (fabs(log(have_double ? double_num : long_num.to_double()) -
            log(other.have_double ? other.double_num : other.long_num.to_double())) >= max_double_digits_cnt) {
        throw "Sorry, it won't fit double\n";
    }*/
    other.double_num = 1.00 * (have_double ? double_num : long_num.to_double()) /
            (other.have_double ? other.double_num : other.long_num.to_double());
    other.have_double = 1;
    return other;
}

Super_Num Super_Num::operator/(Super_Num other) {
    if (this->have_double || other.have_double) {
        throw "Are you okey?\n You can't do integer dividing by real number\n";
    } else {
        other.long_num = (have_double ? Long_Num(double_num > 0 ? ceil(double_num) : floor(double_num)) : long_num) /
                (other.have_double ? Long_Num(other.double_num > 0 ? ceil(other.double_num) : floor(other.double_num)) : other.long_num);
        other.have_double = 0;
    }
    return other;
}

Super_Num Super_Num::operator^(Super_Num other) {
    if (use_double_pow(*this, other)) {
        other.double_num = pow((have_double ? double_num : long_num.to_double()),
                (other.have_double ? other.double_num : other.long_num.to_double()));
        other.have_double = 1;
    } else {
        other.long_num = (have_double ? Long_Num(double_num > 0 ? ceil(double_num) : floor(double_num)) : long_num) ^
                (other.have_double ? Long_Num(other.double_num > 0 ? ceil(other.double_num) : floor(other.double_num)) : other.long_num);
        other.have_double = 0;
    }
    return other;
}

Super_Num Super_Num::operator%(Super_Num other) {
    if (this->have_double || other.have_double) {
        throw "Are you okey?\n You can't do mod with real number\n";
    }
    other.long_num = this->long_num % other.long_num;
    return other;
}

Super_Num Super_Num::operator!() {
    if (this->have_double) {
        throw "Are you okey?\n You can't take factorial of real number";
    }
    Super_Num other = *this;
    other.long_num = !(other.long_num);
    return other;
}

Super_Num Super_Num::operator-() {
    Super_Num res = *this;
    if (have_double) {
        res.double_num *= -1;
    } else {
        res.long_num = -res.long_num;
    }
}

string Super_Num::to_string() {
    if (have_double) {
        return std::to_string(this->double_num);
    } else {
        return this->long_num.to_string();
    }
}

Long_Num& Long_Num::operator<<=(long long num) {
    if (*this == 0) {
        return *this;
    }
    for (int i = 0; i < num; ++i) {
        digits_.insert(digits_.begin(), 0);
    }
    return *this;
}

Long_Num::Long_Num(int num) {
    sign_ = num >= 0 ? 1 : -1;
    digits_.resize(1);
    num = abs(num);
    digits_[0] = num % max_digit_size;
    if (num >= max_digit_size) {
        digits_.push_back(num / max_digit_size);
    }
}

Long_Num::Long_Num(vector<int> num) {
    digits_ = num;
    sign_ = 1;
}

Long_Num long_num(int num) {
    Long_Num x;
    x.sign_ = num >= 0 ? 1 : -1;
    num = abs(num);
    if (num >= max_digit_size) {
        x.digits_ = vector<int>(2, num % max_digit_size);
        x.digits_[1] = num - max_digit_size;
    } else {
        x.digits_ = vector<int>(1, num);
    }
    return x;
}

double Long_Num::to_double() {
    double res = 0;
    for (int i = digits_.size() - 1; i >= 0; --i) {
        res *= max_digit_size;
        res += digits_[i];
    }
    if (sign_ < 0) {
        res *= -1;
    }
    return res;
}

int Long_Num::log10(Long_Num num) {
    return (num.digits_.size() - 1) * digit_degree + trunc(log10(digits_.back())) + 1;
}

double log(Long_Num aa, double xx) {
    if (xx <= 0) {
        throw "Are you okey?\n It is negative, or null, don't try to find it's log\n";
    }
    if (aa <= 0 || aa == 1) {
        throw "Are you okey?\n It is negative, ot null, or 1, don't try to find it's log\n";
    }
    return log(xx) / log(aa.to_double());
}

double log(double aa, Long_Num xx) {
    if (xx <= 0) {
        throw "Are you okey?\n It is negative, or null, don't try to find it's log\n";
    }
    if (aa <= 0 || aa == 1) {
        throw "Are you okey?\n It is negative, ot null, or 1, don't try to find it's log\n";
    }
    return log(xx.to_double()) / log(aa);
}

double log(Long_Num aa, Long_Num xx) {
    if (xx <= 0) {
        throw "Are you okey?\n It is negative, or null, don't try to find it's log\n";
    }
    if (aa <= 0 || aa == 1) {
        throw "Are you okey?\n It is negative, ot null, or 1, don't try to find it's log\n";
    }
    return log(xx.to_double()) / log(aa.to_double());
}

Long_Num& Long_Num::operator*=(Long_Num other) {
    *this = *this * other;
    return *this;
}

Long_Num& Long_Num::operator+=(Long_Num other) {
    *this = *this + other;
    return *this;
}

Long_Num Long_Num::operator%(Long_Num other) {
    if (other.digits_.size() > 1) {
        throw "Are you okey?\n That was a big one.\n";
    }
    if (other == 0) {
        throw "Are you okey?\n It is null, don't try to divide by it\n";
    }
    int cur_res = 0;
    for (int i = digits_.size() - 1; i >= 0; --i) {
        cur_res *= max_digit_size;
        cur_res += digits_[i];
        cur_res %= other.digits_[0];
    }
    if (sign_ * other.sign_ < 0) {
        cur_res = other.digits_[0] - cur_res;
    }
    return Long_Num(cur_res);
}

Long_Num Long_Num::operator/(Long_Num other) {
    if (other.digits_.size() > 1) {
        if (other > *this) {
            return Long_Num(0ll);
        }
        Long_Num lhs = 0ll, rhs = *this;
        while (rhs - lhs > 1) {
            Long_Num mid = (rhs + lhs) / 2ll;
            if (mid * other > *this) {
                rhs = mid;
            } else {
                lhs = mid;
            }
        }
        return lhs;
    }
    if (other == 0) {
        throw "Are you okey?\n It is null, don't try to divide by it\n";
    }
    int other_num = (int)other.to_double();
    Long_Num res = 0ll;
    int remainder = 0;
    for (int i = digits_.size() - 1; i >= 0; --i) {
        res <<= 1;
        res += (digits_[i] + remainder * max_digit_size) / other_num;
        remainder = (digits_[i] + remainder * max_digit_size) % other_num;
    }
    res.sign_ = sign_ * other.sign_;
    return res;

}

double Long_Num::operator|(Long_Num other) {
    return this->to_double() / other.to_double();
}

double operator|(Long_Num num, double aa) {
    return num.to_double() / aa;
}

double operator|(double aa, Long_Num num) {
    return aa / num.to_double();
}

double operator+(double aa, Long_Num num) {
    return num.to_double() + aa;
}

double operator-(double aa, Long_Num num) {
    return aa - num.to_double();
}

double operator*(double aa, Long_Num num) {
    return num.to_double() * aa;
}

double operator+(Long_Num num, double aa) {
    return num.to_double() + aa;
}

double operator-(Long_Num num, double aa) {
    return num.to_double() - aa;
}

double operator*(Long_Num num, double aa) {
    return num.to_double() * aa;
}

double operator^(Long_Num num, double aa) {
    return pow(num.to_double(), aa);
}

double operator^(double aa, Long_Num num) {
    return pow(aa, num.to_double());
}

Long_Num Long_Num::operator!() {
    if (sign_ < 0) {
        throw "Are you okey?\n It is negative, don't try to find it's factorial\n";
    }
    if (digits_.size() > 1) {
        throw "Are you okey?\n That was a big one.\n";
    }
    int n = digits_[0];
    if (n > 100000) {
        throw "Are you okey?\n That was a big one.\n";
    }
    Long_Num res(1ll);
    double ans = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
        //ans *= i;
    }
    //throw "\n" << fixed << ans << "\n";
    //throw res.digits_.size() << "\n\n";
    return res;
}

bool Long_Num::operator==(Long_Num other) {
    if (this->sign_ == other.sign_ && this->digits_.size() == other.digits_.size()) {
        bool eq = 1;
        for (int i = 0; i < digits_.size(); ++i) {
            if (this->digits_[i] != other.digits_[i]) {
                eq = 0;
                break;
            }
        }
        if (eq) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

bool Long_Num::operator<(Long_Num other) {
    if (*this == other) {
        return 0;
    }
    if (this->sign_ > 0 && other.sign_ < 0) {
        return 0;
    } else if (this->sign_ < 0 && other.sign_ > 0) {
        return 1;
    } else if (this->sign_ < 0 && other.sign_ < 0) {
        if (this->digits_.size() > other.digits_.size()) {
            return 1;
        } else if (this->digits_.size() < other.digits_.size()) {
            return 0;
        } else {
            for (int i = digits_.size() - 1; i >= 0; --i) {
                if (this->digits_[i] > other.digits_[i]) {
                    return 1;
                } else if (this->digits_[i] < other.digits_[i]) {
                    return 0;
                }
            }
        }
    } else {
        if (this->digits_.size() > other.digits_.size()) {
            return 0;
        } else if (this->digits_.size() < other.digits_.size()) {
            return 1;
        } else {
            for (int i = digits_.size() - 1; i >= 0; --i) {
                if (this->digits_[i] > other.digits_[i]) {
                    return 0;
                } else if (this->digits_[i] < other.digits_[i]) {
                    return 1;
                }
            }
            return 0;
        }
    }
}

bool Long_Num::operator>(Long_Num other) {
    if (!((*this == other) || *this < other)) {
        return 1;
    } else {
        return 0;
    }
}

bool Long_Num::operator<=(Long_Num other) {
    if (*this < other || *this == other) {
        return 1;
    } else {
        return 0;
    }
}

bool Long_Num::operator>=(Long_Num other) {
    if (*this > other || *this == other) {
        return 1;
    } else {
        return 0;
    }
}

bool operator<(Long_Num num, int aa) {
    if (long_num(aa) > num) {
        return 1;
    } else {
        return 0;
    }
}

bool operator>(Long_Num num, int aa) {
    if (long_num(aa) < num) {
        return 1;
    } else {
        return 0;
    }
}

bool operator<=(Long_Num num, int aa) {
    if (long_num(aa) > num || long_num(aa) == num) {
        return 1;
    } else {
        return 0;
    }
}

bool operator>=(Long_Num num, int aa) {
    if (long_num(aa) < num || long_num(aa) == num) {
        return 1;
    } else {
        return 0;
    }
}

bool operator==(Long_Num num, int aa) {
    if (long_num(aa) == num) {
        return 1;
    } else {
        return 0;
    }
}

bool operator<(int aa, Long_Num num) {
    if (long_num(aa) < num) {
        return 1;
    } else {
        return 0;
    }
}

bool operator>(int aa, Long_Num num) {
    if (long_num(aa) > num) {
        return 1;
    } else {
        return 0;
    }
}

bool operator<=(int aa, Long_Num num) {
    if (long_num(aa) < num || long_num(aa) == num) {
        return 1;
    } else {
        return 0;
    }
}

bool operator>=(int aa, Long_Num num) {
    if (long_num(aa) > num || long_num(aa) == num) {
        return 1;
    } else {
        return 0;
    }
}

bool operator==(int aa, Long_Num num) {
    if (long_num(aa) == num) {
        return 1;
    } else {
        return 0;
    }
}

Long_Num Long_Num::operator-() {
    Long_Num other = *this;
    other.sign_ *= -1;
    return other;
}

Long_Num Long_Num::operator-(Long_Num other) {
    if (other >= 0 && *this >= 0) {
        if (*this > other) {
            return -(other - *this);
        }
        bool have_minus = 0;
        for (int i = 0; i < other.digits_.size(); ++i) {
            if (have_minus) {
                --other.digits_[i];
                have_minus = 0;
            }
            if (i < this->digits_.size()) {
                other.digits_[i] -= this->digits_[i];
            }
            if (other.digits_[i] < 0) {
                have_minus = 1;
                other.digits_[i] += max_digit_size;
            }
        }
        for (int i = other.digits_.size() - 1; i > 0; --i) {
            if (other.digits_[i] == 0) {
                other.digits_.pop_back();
            } else {
                break;
            }
        }
        if (!(other.digits_.size() == 1 && other.digits_[0] == 0)) {
            other.sign_ = -1;
        }
        return other;
    } else if (other < 0 && *this >= 0) {
        return *this + -other;
    } else if (other >= 0 && *this < 0) {
        return -(other + -*this);
    } else {
        return -*this - -other;
    }
}

Long_Num Long_Num::operator+(Long_Num other) {
    if (other >= 0 && *this >= 0) {
        if (other.digits_.size() < this->digits_.size()) {
            return other + *this;
        }
        int have_plus = 0;
        for (int i = 0; i < other.digits_.size(); ++i) {
            if (have_plus) {
                ++other.digits_[i];
                have_plus = 0;
            }
            if (this->digits_.size() == i) {
                break;
            }
            int x = this->digits_[i] + other.digits_[i];
            if (x >= max_digit_size) {
                have_plus = 1;
                x -= max_digit_size;
            }
            other.digits_[i] = x;
        }
        if (have_plus) {
            other.digits_.push_back(1);
        }
        return other;
    } else if (other < 0 && *this >= 0) {
        return *this - -other;
    } else if (other >= 0 && *this < 0) {
        return other - -*this;
    } else {
        return -(-*this + -other);
    }
}

Long_Num Long_Num::operator*(Long_Num other) {
    int sign = sign_ * other.sign_;
    if (this->digits_.size() == 1) {
        int have_plus = 0;
        for (int i = 0; i < other.digits_.size(); ++i) {
            other.digits_[i] *= 1LL * digits_[0];
            other.digits_[i] += have_plus;
            have_plus = 0;
            if (other.digits_[i] >= max_digit_size) {
                have_plus = other.digits_[i] / max_digit_size;
                other.digits_[i] %= max_digit_size;
            }
        }
        if (have_plus) {
            other.digits_.push_back(have_plus);
        }
        other.sign_ = sign;
        return other;
    } else if (other.digits_.size() == 1) {
        other = other * *this;
        other.sign_ = sign;
        return other;
    }
    int m = min(other.digits_.size() / 2, this->digits_.size() / 2);
    Long_Num a0(vector<int>(this->digits_.begin(), this->digits_.begin() + m)),
            a1(vector<int>(this->digits_.begin() + m, this->digits_.end())),
            b0(vector<int>(other.digits_.begin(), other.digits_.begin() + m)),
            b1(vector<int>(other.digits_.begin() + m, other.digits_.end()));
    Long_Num a1b1 = a1 * b1, a0b0 = a0 * b0;
    Long_Num m1 = (a0 + a1) * (b0 + b1) - a0b0 - a1b1;
    vector<int> res1(m, 0), res2(2 * m, 0);
    res1.insert(res1.end(), m1.digits_.begin(), m1.digits_.end());
    res2.insert(res2.end(), a1b1.digits_.begin(), a1b1.digits_.end());
    Long_Num term0(a0b0), term1(res1), term2(res2);
    other = term0 + term1 + term2;
    other.sign_ = sign;
    return other;
}

Long_Num Long_Num::operator^(Long_Num other) {
    if (other.sign_ < 0) {
        throw "Sorry, guy, but this programm is too shitty, so it can't raise to a negative degree\n";
    }
    if (other.digits_.size() > 1) {
        throw "Are you okey?\n That was a big one.\n";
    }
    if (other.digits_[0] * this->digits_.size() > 1e7) {
        throw "Are you okey?\n That was a big one.\n";
    }
    int degree = other.digits_[0];
    Long_Num ans(1ll);
    while (degree) {
        if (degree & 1) {
            ans = ans * *this;
        }
        *this = *this * *this;
        degree >>= 1;
    }
    return ans;
}

Long_Num::Long_Num(string str) {
    if (str == "0" || str == "-0") {
        sign_ = 1;
        digits_ = {0};
        return;
    }
    bool have_comma = 0, have_e = 0;
    int after_comma = 0, after_e = 0, ind_e = 0, minus_e = 1, ind_comma = 0;
    for (int i = 0; i < str.size(); ++i) {
        char cc = str[i];
        if (cc == 'e') {
            have_e = 1;
            ind_e = i;
            continue;
        } else if (cc == '.') {
            have_comma = 1;
            ind_comma = i;
            continue;
        }
        if (have_e) {
            if (cc == '-') {
                minus_e = -1;
            } else {
                after_e *= 10;
                after_e += cc - '0';
            }
        } else if (have_comma) {
            ++after_comma;
        }
    }
    if (have_comma) {
        str.erase(str.begin() + ind_comma);
        after_e -= after_comma;
        --ind_e;
    }
    if (have_e) {
        str = str.substr(0, ind_e);
        str += string(after_e % digit_degree, '0');
        after_e /= digit_degree;
    }
    if (after_e < 0) {
        str = str.substr(0, ind_e + after_e);
        after_e = 0;
    }

    reverse(str.begin(), str.end());
    if (str.back() == '-') {
        sign_ = -1;
        str.pop_back();
    }
    digits_.resize(0);
    for (int i = 0; i < after_e; ++i) {
        digits_.push_back(0);
    }
    for (int i = 0; i < str.size(); i += digit_degree) {
        string ss = str.substr(i, min(digit_degree, (int)str.size() - i));
        reverse(ss.begin(), ss.end());
        int x = 0;
        for (int ii = 0; ii < ss.size(); ++ii) {
            x *= 10;
            x += ss[ii] - '0';
        }
        digits_.push_back(x);
    }
}

string Long_Num::to_string() {
    string ss;
    if (digits_.size() == 1 && digits_[0] == 0) {
        return "0";
    }
    for (int i = 0; i < digits_.size(); ++i) {
        int x = digits_[i];
        for (int ii = 0; i == (int)digits_.size() - 1 ? x > 0 : ii < digit_degree; ++ii) {
            ss += x % 10 + '0';
            x /= 10;
        }
    }
    if (sign_ < 0) {
        ss.push_back('-');
    }
    reverse(ss.begin(), ss.end());
    return ss;
}

std::ostream& operator<<(std::ostream& out, Long_Num num) {
    out << num.to_string();
    return out;
}

std::ostream& operator<<(std::ostream& out, Super_Num num) {
    if (num.have_double) {
        out << num.double_num;
    } else {
        out << num.long_num;
    }
    return out;
}

void Delete_Spaces(string& str) {
    string ss;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ' && str[i] != '\n') {
            ss.push_back(str[i]);
        }
    }
    str = ss;
    return;
}

bool Bracket_Balance(string str) {
    stack<char> st;
    for (int i = 0; i < str.size(); ++i) {
        char cc = str[i];
        if (cc == '(' || cc == '[') {
            st.push(cc);
        } else if (cc == ')') {
            if (st.size() == 0) {
                throw string("Are you okey?\n Wrong bracket balance, pos. " + to_string(i + 1));
                return 0;
            }
            if (st.top() == '(') {
                st.pop();
            } else {
                throw string("Are you okey?\n Wrong bracket balance, pos. " + to_string(i + 1));
                return 0;
            }
        } else if (cc == ']') {
            if (st.size() == 0) {
                throw "Are you okey?\n Wrong bracket balance, pos. " + to_string(i + 1);
                return 0;
            }
            if (st.top() == '[') {
                st.pop();
            } else {
                throw "Are you okey?\n Wrong bracket balance, pos. " + to_string(i + 1);
                return 0;
            }
        }
    }
    if (!st.empty()) {
        throw "Are you okey?\n Wrong bracket balance at the end";
        return 0;
    }
    return 1;
}

int Find_Bracket(string str) {
    stack<char> st;
    for (int i = 0; i < str.size(); ++i) {
        char cc = str[i];
        if (cc == '(' || cc == '[') {
            st.push(cc);
        } else if (cc == ']' || cc == ')') {
            st.pop();
        }
        if (st.size() == 0) {
            return i;
        }
    }
}

int Find_Comma(string str) {
    stack<char> st;
    for (int i = 0; i < str.size(); ++i) {
        char cc = str[i];
        if (cc == '(' || cc == '[') {
            st.push(cc);
        } else if (cc == ']' || cc == ')') {
            st.pop();
        }
        if (st.size() == 1 && cc == ',') {
            return i;
        }
    }
    return 0;
}

bool Right_Expression(string str, int prev_ind) {
    bool was_expr = 0, was_operator = 0, was_start = 1, was_1_par_func_name = 0, was_2_par_func_name = 0, was_e = 0;
    for (int i = 0; i < str.size();) {
        char cc = str[i];
        int start_ind = i;
        if (i == 1 && deque_expression_components.back() == "-") {
            deque_expression_components.pop_back();
            start_ind = 0;
        }
        if (was_expr) {
            if (cc == '!') {
                ++i;
                deque_expression_components.push_back(string(1, cc));
            } else if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%') {
                deque_expression_components.push_back(string(1, cc));
                ++i;
                was_expr = 0;
                was_operator = 1;
            } else if (cc >= '0' && cc <= '9') {
                throw "Are you okey?\n You can't write a number without an operator before, pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc == '_') {
                throw "Are you okey?\n You can't write a \"_\" not in the variable name, pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z') {
                throw "Are you okey?\n You can't write a letter not in the variable name, without an operator before it, pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc == '(' || cc == '[') {
                throw "Are you okey?\n You can't write operning brackets not after operator or function name, pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc == ')' || cc == ']') {
                ++i;
                deque_expression_components.push_back(")");
            } else {
                throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\", pos " + to_string(i + prev_ind);
                return 0;
            }
        } else if (was_operator) {
            if (cc == ']' || cc == ')') {
                throw "Are you okey?\n You can't write closing brackets after an operator, pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc == '(' || cc == '[') {
                int bracket_ind = Find_Bracket(str.substr(i, str.size() - i));
                deque_expression_components.push_back("(");
                if (Right_Expression(str.substr(i + 1, bracket_ind - 1), prev_ind + i + 1)) {
                    i += bracket_ind + 1;
                    was_operator = 0;
                    was_expr = 1;
                    deque_expression_components.push_back(")");
                } else {
                    return 0;
                }
            } else if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                throw "Are you okey?\n You can't write an operator after operator, pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z') {
                if (i + 2 < str.size()) {
                    string ss = str.substr(i, 3);
                    if (ss == "log") {
                        i += 3;
                        if (i < str.size()) {
                            cc = str[i];
                            if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc >= '0' && cc <= '9' || cc == '_') {
                                ;;
                            } else if (str[i] != '(' && str[i] != '[') {
                                throw "Are you okey?\n You should write brackets with arguments after function names, pos " + to_string(i + prev_ind);
                                return 0;
                            } else {
                                was_2_par_func_name = 1;
                                was_operator = 0;
                                deque_expression_components.push_back(ss);
                                continue;
                            }
                        } else {
                            throw "Are you okey?\n You can't name variables like function names, and after function should be brackets with parameters, pos " + to_string(i + prev_ind);
                            return 0;
                        }
                    } else if (ss == "cos" || ss == "sin") {
                        i += 3;
                        if (i < str.size()) {
                            cc = str[i];
                            if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc >= '0' && cc <= '9' || cc == '_') {
                                ;;
                            } else if (str[i] != '(' && str[i] != '[') {
                                throw "Are you okey?\n You should write brackets with arguments after function names, pos " + to_string(i + prev_ind);
                                return 0;
                            } else {
                                was_1_par_func_name = 1;
                                was_operator = 0;
                                deque_expression_components.push_back(ss);
                                continue;
                            }
                        } else {
                            throw "Are you okey?\n You can't name variables like function names, and after function should be brackets with parameters, pos " + to_string(i + prev_ind);
                            return 0;
                        }
                    }
                }
                was_operator = 0;
                was_expr = 1;
                for (++i; i < str.size(); ++i) {
                    cc = str[i];
                    if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc >= '0' && cc <= '9' || cc == '_') {
                        continue;
                    } else if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        break;
                    } else if (cc == '(' || cc == '[' || cc == ')' || cc == ']') {
                        throw "Are you okey?\n You can't write brackets after variable names, you need operator, pos " + to_string(i + prev_ind);
                        return 0;
                    } else {
                        throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\", pos " + to_string(i + prev_ind);
                        return 0;
                    }
                }
                if (i == str.size()){
                    deque_expression_components.push_back(str.substr(start_ind, str.size() - start_ind));
                }
            } else if (cc >= '1' && cc <= '9') {
                was_operator = 0;
                was_expr = 1;
                bool have_float = 0;
                for (++i; i < str.size(); ++i) {
                    cc = str[i];
                    if (cc == 'e') {
                        was_expr = 0;
                        was_e = 1;
                        ++i;
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        break;
                    } else if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        break;
                    } else if (cc >= '0' && cc <= '9') {
                        continue;
                    } else if (cc == '.') {
                        if (have_float) {
                            throw "Are you okey?\n You can't write \".\" two times in the number, pos " + to_string(i + prev_ind);
                            return 0;
                        }
                        have_float = 1;
                    } else if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc == '_') {
                        throw "Are you okey?\n You can't write letters and \"_\" into the number, pos " + to_string(i + prev_ind);
                        return 0;
                    } else if (cc == '(' || cc == '[' || cc == ')' || cc == ']') {
                        throw "Are you okey?\n You can't write brackets after number, you need operator, pos " + to_string(i + prev_ind);
                        return 0;
                    } else {
                        throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\", pos " + to_string(i + prev_ind);
                        return 0;
                    }
                }
                if (i == str.size()){
                    deque_expression_components.push_back(str.substr(start_ind, str.size() - start_ind));
                }            } else if (cc == '_') {
                throw "Are you okey?\n You can't start variable name with \"_\", pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc == '0') {
                was_operator = 0;
                was_expr = 1;
                bool have_float = 0;
                ++i;
                if (i < str.size()) {
                    cc = str[i];
                    if (cc == '.') {
                        have_float = 1;
                        ++i;
                        if (i < str.size()) {
                            cc = str[i];
                            if (!(cc >= '0' && cc <= '9')) {
                                throw "Are you okey?\n You should write digits after \".\" in float number, pos " + to_string(i + prev_ind);
                                return 0;
                            }
                        } else {
                            throw "Are you okey?\n You should write digits after \".\" in float number, pos " + to_string(i + prev_ind);
                            return 0;
                        }
                    } else if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        continue;
                    } else if (cc == 'e') {
                        ++i;
                        was_e = 1;
                        was_expr = 0;
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        continue;
                    } else {
                        throw "Are you okey, you can't start not float numbers and not 0 with 0, pos " + to_string(prev_ind + i);
                        return 0;
                    }
                }
                for (; i < str.size(); ++i) {
                    cc = str[i];
                    if (cc == 'e') {
                        ++i;
                        was_expr = 0;
                        was_e = 1;
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        break;
                    }
                    if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        break;
                    } else if (cc >= '0' && cc <= '9') {
                        continue;
                    } else if (cc == '.') {
                        if (have_float) {
                            throw "Are you okey?\n You can't write \".\" two times in the number, pos " + to_string(i + prev_ind);
                            return 0;
                        }
                        have_float = 1;
                    } else if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc == '_') {
                        throw "Are you okey?\n You can't write letters and \"_\" into the number, pos " + to_string(i + prev_ind);
                        return 0;
                    } else if (cc == '(' || cc == '[' || cc == ')' || cc == ']') {
                        throw "Are you okey?\n You can't write brackets after number, you need operator, pos " + to_string(i + prev_ind);
                        return 0;
                    } else {
                        throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\", pos " + to_string(i + prev_ind);
                        return 0;
                    }
                }
                if (i == str.size()){
                    deque_expression_components.push_back(str.substr(start_ind, str.size() - start_ind));
                }            } else {
                throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\", pos " + to_string(i + prev_ind);
                return 0;
            }
        } else if (was_start) {
            if (cc == ']' || cc == ')') {
                throw "Are you okey?\n You can't write closing brackets in the expression start, pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc == '(' || cc == '[') {
                int bracket_ind = Find_Bracket(str.substr(i, str.size() - i));
                deque_expression_components.push_back("(");
                if (Right_Expression(str.substr(i + 1, bracket_ind - 1), prev_ind + i + 1)) {
                    i += bracket_ind + 1;
                    was_start = 0;
                    was_expr = 1;
                    deque_expression_components.push_back(")");
                } else {
                    return 0;
                }
            } else if (cc == '-') {
                ++i;
                was_start = 0;
                was_operator = 1;
                deque_expression_components.push_back("-");
            } else if (cc == '+' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                throw "Are you okey?\n You can't write operators in the expression start, pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc >= '1' && cc <= '9') {
                was_start = 0;
                was_expr = 1;
                bool have_float = 0;
                for (++i; i < str.size(); ++i) {
                    cc = str[i];
                    if (cc == 'e') {
                        was_expr = 0;
                        was_e = 1;
                        ++i;
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        break;
                    } else if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        break;
                    } else if (cc >= '0' && cc <= '9') {
                        continue;
                    } else if (cc == '.') {
                        if (have_float) {
                            throw "Are you okey?\n You can't write \".\" two times in the number, pos " + to_string(i + prev_ind);
                            return 0;
                        }
                        have_float = 1;
                    } else if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc == '_') {
                        throw "Are you okey?\n You can't write letters and \"_\" into the number, pos " + to_string(i + prev_ind);
                        return 0;
                    } else if (cc == '(' || cc == '[' || cc == ')' || cc == ']') {
                        throw "Are you okey?\n You can't write brackets after number, you need operator, pos " + to_string(i + prev_ind);
                        return 0;
                    } else {
                        throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\", pos " + to_string(i + prev_ind);
                        return 0;
                    }
                }
                if (i == str.size()){
                    deque_expression_components.push_back(str.substr(start_ind, str.size() - start_ind));
                }
            } else if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z') {
                if (i + 2 < str.size()) {
                    string ss = str.substr(i, 3);
                    if (ss == "log") {
                        i += 3;
                        if (i < str.size()) {
                            cc = str[i];
                            if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc >= '0' && cc <= '9' || cc == '_') {
                                ;;
                            } else if (str[i] != '(' && str[i] != '[') {
                                throw "Are you okey?\n You should write brackets with arguments after function names, pos " + to_string(i + prev_ind);
                                return 0;
                            } else {
                                was_2_par_func_name = 1;
                                was_start = 0;
                                deque_expression_components.push_back(ss);
                                continue;
                            }
                        } else {
                            throw "Are you okey?\n You can't name variables like function names, and after function should be brackets with parameters, pos " + to_string(i + prev_ind);
                            return 0;
                        }
                    } else if (ss == "cos" || ss == "sin") {
                        i += 3;
                        if (i < str.size()) {
                            cc = str[i];
                            if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc >= '0' && cc <= '9' || cc == '_') {
                                ;;
                            } else if (str[i] != '(' && str[i] != '[') {
                                throw "Are you okey?\n You should write brackets with arguments after function names, pos " + to_string(i + prev_ind);
                                return 0;
                            } else {
                                was_1_par_func_name = 1;
                                was_start = 0;
                                deque_expression_components.push_back(ss);
                                continue;
                            }
                        } else {
                            throw "Are you okey?\n You can't name variables like function names, and after function should be brackets with parameters, pos " + to_string(i + prev_ind);
                            return 0;
                        }
                    }
                }
                was_start = 0;
                was_expr = 1;
                for (++i; i < str.size(); ++i) {
                    cc = str[i];
                    if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc >= '0' && cc <= '9' || cc == '_') {
                        continue;
                    } else if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        break;
                    } else if (cc == '(' || cc == '[' || cc == ')' || cc == ']') {
                        throw "Are you okey?\n You can't write brackets after variable names, you need operator, pos " + to_string(i + prev_ind);
                        return 0;
                    } else {
                        throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\", pos " + to_string(i + prev_ind);
                        return 0;
                    }
                }
                if (i == str.size()){
                    deque_expression_components.push_back(str.substr(start_ind, str.size() - start_ind));
                }
            } else if (cc == '_') {
                throw "Are you okey?\n You can't start variable name with \"_\", pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc == '0') {
                was_start = 0;
                was_expr = 1;
                bool have_float = 0;
                ++i;
                if (i < str.size()) {
                    cc = str[i];
                    if (cc == '.') {
                        have_float = 1;
                        ++i;
                        if (i < str.size()) {
                            cc = str[i];
                            if (!(cc >= '0' && cc <= '9')) {
                                throw "Are you okey?\n You should write digits after \".\" in float number, pos " + to_string(i + prev_ind);
                                return 0;
                            }
                        } else {
                            throw "Are you okey?\n You should write digits after \".\" in float number, pos " + to_string(i + prev_ind);
                            return 0;
                        }
                    } else if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        continue;
                    } else if (cc == 'e') {
                        ++i;
                        was_e = 1;
                        was_expr = 0;
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        continue;
                    } else {
                        throw "Are you okey, you can't start not float numbers and not 0 with 0, pos " + to_string(prev_ind + i);
                        return 0;
                    }
                }
                for (; i < str.size(); ++i) {
                    cc = str[i];
                    if (cc == 'e') {
                        ++i;
                        was_expr = 0;
                        was_e = 1;
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        break;
                    }
                    if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                        deque_expression_components.push_back(str.substr(start_ind, i - start_ind));
                        break;
                    } else if (cc >= '0' && cc <= '9') {
                        continue;
                    } else if (cc == '.') {
                        if (have_float) {
                            throw "Are you okey?\n You can't write \".\" two times in the number, pos " + to_string(i + prev_ind);
                            return 0;
                        }
                        have_float = 1;
                    } else if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc == '_') {
                        throw "Are you okey?\n You can't write letters and \"_\" into the number, pos " + to_string(i + prev_ind);
                        return 0;
                    } else if (cc == '(' || cc == '[' || cc == ')' || cc == ']') {
                        throw "Are you okey?\n You can't write brackets after number, you need operator, pos " + to_string(i + prev_ind);
                        return 0;
                    } else {
                        throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\", pos " + to_string(i + prev_ind);
                        return 0;
                    }
                }
                if (i == str.size()){
                    deque_expression_components.push_back(str.substr(start_ind, str.size() - start_ind));
                }
            } else {
                throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\", pos " + to_string(i + prev_ind);
                return 0;
            }
        } else if (was_2_par_func_name) {
            int bracket_ind = Find_Bracket(str.substr(i, str.size() - i));
            int comma_ind = Find_Comma(str.substr(i, bracket_ind));
            if (comma_ind <= 1) {
                throw "Are you okey?\n This function supposes two arguments, divided by comma, pos " + to_string(i + prev_ind);
                return 0;
            }
            deque_expression_components.push_back("(");
            if (Right_Expression(str.substr(i + 1, comma_ind - 1), prev_ind + i + 1) &&
                    (deque_expression_components.push_back(","), Right_Expression(str.substr(i + comma_ind + 1, bracket_ind - comma_ind - 1), prev_ind + i + comma_ind + 1))) {
                i += bracket_ind + 1;
                was_2_par_func_name = 0;
                was_expr = 1;
            } else {
                return 0;
            }
            deque_expression_components.push_back(")");
        } else if (was_1_par_func_name) {
            int bracket_ind = Find_Bracket(str.substr(i, str.size() - i));
            deque_expression_components.push_back("(");
            if (Right_Expression(str.substr(i + 1, bracket_ind - 1), prev_ind + i + 1)) {
                i += bracket_ind + 1;
                was_1_par_func_name = 0;
                was_expr = 1;
            } else {
                return 0;
            }
            deque_expression_components.push_back(")");
        } else {
            if (cc == '-') {
                ++i;
                if (i < str.size()) {
                    cc = str[i];
                } else {
                    throw "Are you okey?\n You should write degree (number)4 after \"e\", pos " + to_string(i + prev_ind);
                    return 0;
                }
            }
            if (cc >= '0' && cc <= '9') {
                was_e = 0;
                was_expr = 1;
                for (++i; i < str.size(); ++i) {
                    cc = str[i];
                    if (cc == 'e') {
                        throw "Are you okey?\n You can't write \"e\" in the number after \"e\", pos " + to_string(i + prev_ind);
                        return 0;
                    } else if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                        deque_expression_components.back() += str.substr(start_ind, i - start_ind);
                        break;
                    } else if (cc >= '0' && cc <= '9') {
                        continue;
                    } else if (cc == '.') {
                        throw "Are you okey?\n Number after \"e\" must be integer, pos " + to_string(i + prev_ind);
                        return 0;
                    } else if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc == '_') {
                        throw "Are you okey?\n You can't write letters and \"_\" into the number, pos " + to_string(i + prev_ind);
                        return 0;
                    } else if (cc == '(' || cc == '[' || cc == ')' || cc == ']') {
                        throw "Are you okey?\n You can't write brackets after number, you need operator, pos " + to_string(i + prev_ind);
                        return 0;
                    } else {
                        throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\" into the number, pos " + to_string(i + prev_ind);
                        return 0;
                    }
                }
                if (i == str.size()) {
                    deque_expression_components.back() += str.substr(start_ind, str.size() - start_ind);
                }
            } else if (cc == '+' || cc == '-' || cc == '*' || cc == '/' || cc == '|' || cc == '^' || cc == '%' || cc == '!') {
                throw "Are you okey?\n You can't write an operator, should write degree (number) after\"e\", pos " + to_string(i + prev_ind);
                return 0;
            } else if (cc >= 'a' && cc <= 'z' || cc >= 'A' && cc <= 'Z' || cc == '_') {
                throw "Are you okey?\n You should write an operator between number and variable name, pos " + to_string(i + prev_ind) - 2;
                return 0;
            } else if (cc == '[' || cc == ']' || cc == ')' || cc == '(') {
                throw "Are you okey?\n You can't write brackets, you should write degree (number) after\"e\", pos " + to_string(i + prev_ind);
                return 0;
            } else {
                throw "Are you okey?\n You can't write this \"" + string(1, cc) + "\", pos " + to_string(i + prev_ind);
                return 0;
            }
        }
    }
    if (was_expr) {
        return 1;
    } else {
        throw "Are you okey?\n You expression can't end like this";
        return 0;
    }
}

void Dijkstra() {
    while (!deque_expression_components.empty()) {
        string ss = deque_expression_components.front();
        deque_expression_components.pop_front();
        if (ss == "*" || ss == "/" || ss == "|" || ss == "%") {
            while (!st_operators.empty()) {
                string str = st_operators.top();
                if (str == "(" || str == "-" || str == "+") {
                    break;
                }
                str_postfix_expr.push_back(str);
                st_operators.pop();
            }
            st_operators.push(ss);
        } else if (ss == "-" || ss == "+") {
            while (!st_operators.empty()) {
                string str = st_operators.top();
                if (str == "(") {
                    break;
                }
                str_postfix_expr.push_back(str);
                st_operators.pop();
            }
            st_operators.push(ss);
        } else if (ss == "^") {
            while (!st_operators.empty()) {
                string str = st_operators.top();
                if (str == "(" || str == "-" || str == "+" || str == "*" || str == "/" || str == "|" || str == "%" || str == "^") {
                    break;
                }
                str_postfix_expr.push_back(str);
                st_operators.pop();
            }
            st_operators.push(ss);
        } else if (ss == "!") {
            while (!st_operators.empty()) {
                string str = st_operators.top();
                if (str == "(" || str == "-" || str == "+" || str == "*" || str == "/" || str == "|" || str == "%" || str == "^") {
                    break;
                }
                str_postfix_expr.push_back(str);
                st_operators.pop();
            }
            st_operators.push(ss);
        } else if (ss == "(") {
            st_operators.push(ss);
        } else if (ss == ")") {
            while (!st_operators.empty()) {
                string str = st_operators.top();
                if (str == "(") {
                    break;
                }
                str_postfix_expr.push_back(str);
                st_operators.pop();
            }
            st_operators.pop();
            if (st_operators.empty()) {
                continue;
            }
            ss = st_operators.top();
            if (ss == "log" || ss == "cos" || ss == "sin") {
                str_postfix_expr.push_back(ss);
                st_operators.pop();
            }
        } else if (ss == "log" || ss == "cos" || ss == "sin") {
            st_operators.push(ss);
        } else if (ss == ",") {
            while (!st_operators.empty()) {
                string str = st_operators.top();
                if (str == "(") {
                    break;
                }
                str_postfix_expr.push_back(str);
                st_operators.pop();
            }
        } else if (ss == "e" || ss == "E" || ss == "Pi" || ss == "PI" || ss == "pI" || ss == "pi") {
            str_postfix_expr.push_back(ss);
        } else {
            if (ss[0] >= 'a' && ss[0] <= 'z' || ss[0] >= 'A' && ss[0] <= 'Z') {
                if (variables.find(ss) == variables.end()) {
                    st_variables.push_back(ss);
                    variables[ss] = "";
                }
            }
            str_postfix_expr.push_back(ss);
        }
    }
    while (!st_operators.empty()) {
        str_postfix_expr.push_back(st_operators.top());
        st_operators.pop();
    }
    str_postfix_expr_copy = str_postfix_expr;
}

void Count(Ui::MainWindow* ui) {
    Super_Num op1("0"), op2("0");
    string ss;
    stack<Super_Num> st_operands;
    try {
        while (!str_postfix_expr.empty()) {
            ss = str_postfix_expr.front();
            str_postfix_expr.pop_front();
            if (ss == "!" || ss == "cos" || ss == "sin") {
                op1 = st_operands.top();
                st_operands.pop();
                if (ss == "!") {
                    op1 = !op1;
                } else if (ss == "sin") {
                    op1 = sin(op1);
                } else {
                    op1 = cos(op1);
                }
                Normalize(op1);
                st_operands.push(op1);
            } else if (ss == "*" || ss == "/" || ss == "|" || ss == "%" ||
                    ss == "+" || ss == "-" || ss == "^" || ss == "log") {
                op2 = st_operands.top();
                st_operands.pop();
                op1 = st_operands.top();
                st_operands.pop();
                if (ss == "*") {
                    op1 = op1 * op2;
                } else if (ss == "|") {
                    op1 = op1 / op2;
                } else if (ss == "%") {
                    op1 = op1 % op2;
                } else if (ss == "/") {
                    op1 = op1 | op2;
                } else if (ss == "+") {
                    op1 = op1 + op2;
                } else if (ss == "-") {
                    op1 = op1 - op2;
                } else if (ss == "^") {
                    op1 = op1 ^ op2;
                } else if (ss == "log") {
                    op1 = log(op1, op2);
                }
                Normalize(op1);
                st_operands.push(op1);
            } else {
                if (Num_(ss)) {
                    st_operands.push(Super_Num(ss));
                } else {
                    st_operands.push(Super_Num(variables[ss]));
                }
            }
        }
    } catch (const char * ss) {
        QMessageBox::critical(nullptr, "", QString::fromStdString(ss));
        return;
    } catch (string ss) {
        QMessageBox::critical(nullptr, "", QString::fromStdString(ss));
        return;
    }

    ui->lineEdit->setText(QString::fromStdString(st_operands.top().to_string()));
    st_operands.pop();
    return;
}

void Vars_Window::Pushbutton_clicked() {
    string res_string = this->line->text().toStdString();
    try {
        if (Num(res_string)) {
            variables[this->windowTitle().toStdString()] = res_string;
        }
    } catch (const char * ss) {
        QMessageBox::critical(this, "", QString::fromStdString(ss));
        this->deleteLater();
        return;
    } catch (string ss) {
        QMessageBox::critical(this, "", QString::fromStdString(ss));
        this->deleteLater();
        return;
    }
    variables[this->windowTitle().toStdString()] = res_string;
    if (st_variables.size()) {
        this->deleteLater();
        QString str(QString::fromStdString(st_variables.back()));
        st_variables.pop_back();
        Vars_Window* p = new Vars_Window(str, parent);
        p->show();
        return;
    }
    Count(this->parent);
    this->deleteLater();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void Make_Var_Windows(Ui::MainWindow* parent) {
    QString str(QString::fromStdString(st_variables.back()));
    st_variables.pop_back();
    Vars_Window* p = new Vars_Window(str, parent);
    p->show();
}

QString Concatenate() {
    QString ss;
    while (!str_postfix_expr_copy.empty()) {
        QString str = QString::fromStdString(str_postfix_expr_copy.front());
        ss += str + " ";
        str_postfix_expr_copy.pop_front();
    }
    return ss;
}

void MainWindow::on_pushButton_clicked()
{
    try {
        //cout << pow(0, -1) << "\n";
        variables.clear();
        str_postfix_expr.clear();
        str_postfix_expr_copy.clear();
        deque_expression_components.clear();
        while (!st_operators.empty()) {
            st_operators.pop();
        }
        string ss = ui->textEdit->toPlainText().toStdString();
        //QMessageBox::critical(this, "", QString::fromStdString(ss));
        Delete_Spaces(ss);
        Bracket_Balance(ss);
        Right_Expression(ss, 0);
        Dijkstra();
        QString sss = Concatenate();
        ui->textEdit_2->setText(sss);
        cout << st_variables.size();
        if (st_variables.empty()) {
            Count(ui);
            return;
        }
        //QMessageBox::critical(nullptr, "", QString::fromStdString(st_variables.back()));
        Make_Var_Windows(ui);
    } catch (char const* str) {
        QMessageBox::critical(this, "", QString::fromStdString(str));
    } catch (string str) {
        QMessageBox::critical(this, "", QString::fromStdString(str));
    }

}
