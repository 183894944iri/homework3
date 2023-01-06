#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>

struct Leksema {
    char type; // 0 для чисел, "+" для операции сложения и т.д.
    double value; //Значение (только для чисел). У операций значение всегда "0"
};
const double Pi = acos(-1); //Объявляем значение числа Пи

double Sin(double x) { //Функция для округления значение синуса
    return (round(sin(x) * 10000000) / 10000000);
}

double Cos(double x) { //Функция для округления значение косинуса
    return (round(cos(x) * 10000000) / 10000000);
}

double Ctg(double x) { //Функция для расчета котангенса
    double a = cos(x);
    double b = Sin(x);
    return (a / b);
}

bool Maths(std::stack<Leksema> &Stack_n, std::stack<Leksema> &Stack_o, Leksema &item) {
    double a, b, c;
    a = Stack_n.top().value;
    Stack_n.pop();
    switch (Stack_o.top().type) {
        case '+':
            b = Stack_n.top().value;
            Stack_n.pop();
            c = a + b;
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;

        case '-':
            b = Stack_n.top().value;
            Stack_n.pop();
            c = b - a;
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;

        case '^':
            b = Stack_n.top().value;
            Stack_n.pop();
            c = pow(b, a);
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;

        case '*':
            b = Stack_n.top().value;
            Stack_n.pop();
            c = a * b;
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;

        case '/':
            b = Stack_n.top().value;
            if (a == 0) {
                std::cerr << "\nError\n";
                return false;
            } else {
                Stack_n.pop();
                c = (b / a);
                item.type = '0';
                item.value = c;
                Stack_n.push(item);
                Stack_o.pop();
                break;
            }

        case 's':
            c = Sin(a);
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;

        case 'c':
            c = Cos(a);
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;

        case 't':
            if (Cos(a) == 0) {
                std::cerr << "\nError\n";
                return false;
            } else {
                c = tan(a);
                item.type = '0';
                item.value = c;
                Stack_n.push(item);
                Stack_o.pop();
                break;
            }

        case 'g':
            if (Sin(a) == 0) {
                std::cerr << "\nError\n";
                return false;
            } else {
                c = Ctg(a);
                item.type = '0';
                item.value = c;
                Stack_n.push(item);
                Stack_o.pop();
                break;
            }

        case 'e':
            c = exp(a);
            item.type = '0';
            item.value = c;
            Stack_n.push(item);
            Stack_o.pop();
            break;

        default:
            std::cerr << "\nError\n";
            return false;
    }
    return true;
}


int getRang(char Ch) {
    if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g' || Ch == 'e')return 4;
    if (Ch == '^')return 3;
    if (Ch == '+' || Ch == '-')return 1;
    if (Ch == '*' || Ch == '/')return 2;
    else return 0;
}

int main() {
    while (true) {
        std::cout << "( To use the number Pi, enter 'p', to use the number E, enter 'exp(1) )" << std::endl;
        std::cout << "Enter the expression " << std::endl;
        std::string str;
        getline(std::cin, str);
        std::stringstream sstr{str};

        char Ch;
        double value;
        bool flag = true; //Нужен для того, чтобы программа смогла отличить унарный минус (-5) от вычитания (2-5)
        std::stack<Leksema> Stack_n; //Стек с числами
        std::stack<Leksema> Stack_o; //Стек с операциями
        Leksema item;
        while (true) {
            Ch = sstr.peek();
            if (Ch == '\377')break;
            if (Ch == ' ') {
                sstr.ignore();
                continue;
            }
            if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'e') {
                char foo[3];
                for (int i = 0; i < 3; i++) {
                    Ch = sstr.peek();
                    foo[i] = Ch;
                    sstr.ignore();
                }
                if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n') { //Если прочитанная функция - синус
                    item.type = 's';
                    item.value = 0;
                    Stack_o.push(item);
                    continue;
                }
                if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's') { //Если прочитанная функция - косинус
                    item.type = 'c';
                    item.value = 0;
                    Stack_o.push(item);
                    continue;
                }
                if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n') { //Если прочитанная функция - тангенс
                    item.type = 't';
                    item.value = 0;
                    Stack_o.push(item);
                    continue;
                }
                if (foo[0] == 'c' && foo[1] == 't' && foo[2] == 'g') { //Если прочитанная функция - котангенс
                    item.type = 'g';
                    item.value = 0;
                    Stack_o.push(item);
                    continue;
                }
                if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p') { //Если прочитанная функция - экспонента
                    item.type = 'e';
                    item.value = 0;
                    Stack_o.push(item);
                    continue;
                }
            }
            if (Ch == 'p') { //Если прочитано число Пи
                item.type = '0';
                item.value = Pi;
                Stack_n.push(item);
                flag = 0;
                sstr.ignore();
                continue;
            }
            if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) { //Если прочитано число
                sstr >> value;
                item.type = '0';
                item.value = value;
                Stack_n.push(item);
                flag = 0;
                continue;
            }
            if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch == '^') { //Если прочитана операция
                if (Stack_o.size() == 0) { //Если стек с операциями пуст
                    item.type = Ch;
                    item.value = 0;
                    Stack_o.push(item);
                    sstr.ignore();
                    continue;
                }
                if (Stack_o.size() != 0 && getRang(Ch) >
                                           getRang(Stack_o.top().type)) { //Если стек с операциями НЕ пуст, но приоритет текущей операции выше верхней в стеке с операциями
                    item.type = Ch;
                    item.value = 0;
                    Stack_o.push(item);
                    sstr.ignore();
                    continue;
                }
                if (Stack_o.size() != 0 && getRang(Ch) <=
                                           getRang(Stack_o.top().type)) {//Если стек с операциями НЕ пуст, но приоритет текущей операции ниже либо равен верхней в стеке с операциями
                    if (Maths(Stack_n, Stack_o, item) == false) { //Если функция вернет "false", то прекращаем работу
                        system("pause");
                        return 0;
                    }
                    continue;
                }
            }
            if (Ch == '(') { //Если прочитана открывающаяся скобка
                item.type = Ch;
                item.value = 0;
                Stack_o.push(item);
                sstr.ignore();
                continue;
            }
            if (Ch == ')') { //Если прочитана закрывающаяся скобка
                while (Stack_o.top().type != '(') {
                    if (Maths(Stack_n, Stack_o, item) == false) {
                        system("pause");
                        return 0;
                    } else continue;
                }
                Stack_o.pop();
                sstr.ignore();
                continue;
            } else { //Если прочитан какой-то странный символ
                std::cout << "\nError\n";
                system("pause");
                return 0;
            }
        }
        while (Stack_o.size() !=
               0) { //Вызываем матем. функцию до тех пор, пока в стеке с операциями не будет 0 элементов
            if (Maths(Stack_n, Stack_o, item) == false) {
                system("pause");
                return 0;
            } else continue;
        }
        std::cout << "Answer: " << Stack_n.top().value << std::endl;
        system("pause");
    }
}
