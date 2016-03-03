#ifndef CELL_H
#define CELL_H

#include <QString>
#include <QList>

/**
 * The lisp_exp class represents a lisp expression.
 *
 * Each valid lisp expression is either a list of lisp expressions, or a value.
 */
class lisp_exp {
public:
    /**
     * Parse the given string into a lisp expression object
     * @param str the string to parse
     * @return the resulting lisp expression
     */
    static lisp_exp parseString(QString str);

    /**
     * Construct an invalid lisp expression
     */
    lisp_exp();

    /**
     * Construct a lisp expression representing the given list of lisp expressions
     * @param cells the list of lisp expressions
     */
    lisp_exp(QList<lisp_exp> cells);

    /**
     * Construct a lisp expression representing the given value
     * @param token the value, as a string
     */
    lisp_exp(QString token);

    /**
     * @return true if this lisp expression is a value, false otherwise
     */
    bool isLeaf() const;

    /**
     * @return this lisp expression's value, assuming that it is a value
     */
    QString value() const;

    /**
     * @return the number of elements in this lisp expression, assuming that it is a list
     */
    int size() const;

    /**
     * @param i the index of the element to return
     * @return the element at the given index of this lisp expression, assuming that it is a list
     */
    lisp_exp element(int i) const;
private:
    bool m_valid;
    QList<lisp_exp> m_elements;
    QString m_value;
};

QList<QString> tokenize(const QString & str);

lisp_exp parse(QList<QString> & tokens);

#endif // CELL_H
