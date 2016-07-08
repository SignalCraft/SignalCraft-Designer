#ifndef LISP_EXP_H
#define LISP_EXP_H

#include <QString>
#include <QList>

/**
 * The lisp_exp class represents a lisp expression.
 *
 * Each valid lisp expression contains either a list of lisp expressions, or a
 * string value. If a lisp expression is a leaf, its value is a non-empty
 * string. If a lisp expression is not a leaf, it contains 0 or more elements,
 * each of which is a lisp expression.
 *
 * The identify of a lisp expression is determined by its validity, status as a
 * leaf, and contents. So two expressions are equal if they are both invalid,
 * or if they are both valid leafs with the same value, or if they are both
 * valid non-leafs with equal elements.
 */
class lisp_exp {
public:
    /**
     * Parse the given string into a non-leaf lisp expression object.
     *
     * In order to be successfully parsed, the string must be a valid
     * representation of a single non-leaf lisp expression. This means the
     * first non-whitespace character must be an open paren, the last
     * non-whitespace character must be a close paren, the depth of the
     * parenthetical must always be greater than 0 inside those outer
     * parentheses, and the parentheses must be balanced. Any continuous run
     * of non-whitespace and non-parenthese characters is interpreted as a
     * single leaf token.
     *
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
     * @return true if this lisp expression is valid, false otherwise
     */
    bool isValid() const;

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

    /**
     * For the definition of lisp_exp identity, see the class definition.
     *
     * @param other the lisp expression to compare to this one
     * @return true if the two lisp expressions are equal, false otherwise
     */
    bool operator==(const lisp_exp& other) const;

private:
    bool m_valid;
    QList<lisp_exp> m_elements;
    QString m_value;
};

QList<QString> tokenize(const QString & str);

lisp_exp parse(QList<QString> & tokens);

#endif // LISP_EXP_H
