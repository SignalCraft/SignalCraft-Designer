#ifndef C_EXP_H
#define C_EXP_H

#include <QString>
#include "compiler/datatype.h"
#include "compiler/lisp_exp.h"
#include <QHash>

/**
 * The c_exp class represents a C expression.
 *
 * A C expression always returns a value, and in this application is meant to
 * have no side-effects. A c_exp object stores the C code for the expression,
 * as well as the data type of its result.
 */
class c_exp {
public:
    /**
     * Compile the given lisp expression into a C expression, using the given
     * mappings of lisp symbol names to data types and C variable (wire) names.
     *
     * The root operation of the lisp expression must be one that returns a
     * value.
     *
     * @param exp the lisp expression to compile
     * @param dataTypes the mapping of lisp symbol names to data types
     * @param wireNames the mapping of lisp symbol names to C variable names
     * @return the compiled C expression
     */
    static c_exp fromLispExp(lisp_exp exp, QHash<QString, DataType> dataTypes, QHash<QString, QString> wireNames);

    /**
     * Construct an invalid C expression
     */
    c_exp();

    /**
     * Construct a C expression with the given C code and data type
     * @param code the C code
     * @param type the data type
     */
    c_exp(QString code, DataType type);

    /**
     * Create a C expression that takes the result of this C expression and
     * converts its result to a new data type
     * @param newType the data type to convert to
     * @return the new C expression
     */
    c_exp conversionTo(DataType newType) const;

    /**
     * @return true if the C expression object is valid, false if not
     */
    bool isValid() const;

    /**
     * @return the expression's C code
     */
    QString code() const;

    /**
     * @return the expression's result data type
     */
    DataType type() const;
private:
    bool m_valid;
    QString m_code;
    DataType m_type;
};

#endif // C_EXP_H
