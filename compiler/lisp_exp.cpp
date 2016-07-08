#include "lisp_exp.h"

#include <QString>
#include <QRegExp>
#include <QList>
#include <QChar>

// convert given string to list of tokens
QList<QString> tokenize(const QString & str) {
    QList<QString> tokens;
    int i = 0;
    while (i < str.size()) {
        if (str.at(i).isSpace()) {
            ++i;
        } else if (str.at(i) == '(' || str.at(i) == ')') {
            tokens.push_back(str.at(i) == '(' ? "(" : ")");
            i++;
        } else {
            int j = i;
            while (j < str.size() && !str.at(j).isSpace() && str.at(j) != '(' && str.at(j) != ')') {
                j++;
            }
            tokens.push_back(str.mid(i, j-i));
            i = j;
        }
    }
    return tokens;
}

lisp_exp parse(QList<QString> & tokens) {
    if (tokens.isEmpty()) {
        return lisp_exp(); // invalid
    }
    QString token = tokens.takeFirst();
    if (token == "(") {
        if (tokens.isEmpty()) {
            return lisp_exp(); // invalid
        }
        QList<lisp_exp> cells;
        while (tokens.front() != ")") {
            lisp_exp cell = parse(tokens);
            if (tokens.isEmpty()) {
                return lisp_exp(); // invalid
            }
            cells.push_back(cell);
        }
        tokens.pop_front();
        return lisp_exp(cells);
    } else if (token == ")") {
        return lisp_exp(); // invalid
    } else {
        return lisp_exp(token);
    }
}

lisp_exp lisp_exp::parseString(QString str) {
    QList<QString> tokens = tokenize(str);
    lisp_exp exp = parse(tokens);
    if (!tokens.isEmpty()) {
        return lisp_exp();
    }
    if (exp.isLeaf()) {
        return lisp_exp();
    }
    return exp;
}

lisp_exp::lisp_exp() {
    m_valid = false;
    m_value = "";
    m_elements = QList<lisp_exp>();
}

lisp_exp::lisp_exp(QList<lisp_exp> cells) {
    m_valid = true;
    m_value = "";
    m_elements = cells;
}

lisp_exp::lisp_exp(QString token) {
    m_valid = true;
    m_value = token;
    m_elements = QList<lisp_exp>();
}

bool lisp_exp::isValid() const {
    return m_valid;
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

QString lisp_exp::toString() const {
    if (!m_valid) {
        return QString();
    }
    if (isLeaf()) {
        return m_value;
    } else {
        QStringList tokens;
        for (lisp_exp child : m_elements) {
            tokens.append(child.toString());
        }
        return "(" + tokens.join(" ") + ")";
    }
}

bool lisp_exp::operator==(const lisp_exp& other) const {
    if (!m_valid && !other.m_valid) {
        return true;
    }
    if (isLeaf() && other.isLeaf()) {
        return (m_value == other.m_value);
    }
    if (!isLeaf() && !other.isLeaf()) {
        return (m_elements == other.m_elements);
    }
    return false;
}
