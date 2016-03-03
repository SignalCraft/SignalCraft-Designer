#include "compiler/lisp_exp.h"

#include <QString>
#include <QRegExp>
#include <QList>
#include <QChar>

// convert given string to list of tokens
QList<QString> tokenize(const QString & str) {
    QList<QString> tokens;
    int i = 0;
    while (i < str.size()) {
        while (str.at(i) == ' ') {
            ++i;
        }
        if (str.at(i) == '(' || str.at(i) == ')') {
            tokens.push_back(str.at(i) == '(' ? "(" : ")");
            i++;
        } else {
            int j = i;
            while (j < str.size() && str.at(j) != ' ' && str.at(j) != '(' && str.at(j) != ')') {
                j++;
            }
            tokens.push_back(str.mid(i, j-i));
            i = j;
        }
    }
    return tokens;
}

lisp_exp parse(QList<QString> & tokens) {
    QString token = tokens.front();
    tokens.pop_front();
    if (token == "(") {
        QList<lisp_exp> cells;
        while (tokens.front() != ")") {
            cells.push_back(parse(tokens));
        }
        tokens.pop_front();
        return lisp_exp(cells);
    }
    else
        return lisp_exp(token);
}

lisp_exp lisp_exp::parseString(QString str) {
    QList<QString> tokens = tokenize(str);
    lisp_exp exp = parse(tokens);
    return exp;
}

lisp_exp::lisp_exp(QList<lisp_exp> cells) {
    m_elements = cells;
}

lisp_exp::lisp_exp(QString token) {
    m_value = token;
}

bool lisp_exp::isLeaf() const {
    return !m_value.isEmpty();
}

QString lisp_exp::value() const {
    return m_value;
}

int lisp_exp::size() const {
    return m_elements.size();
}

lisp_exp lisp_exp::element(int i) const {
    return m_elements[i];
}
