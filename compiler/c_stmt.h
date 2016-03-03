#ifndef C_STMT_H
#define C_STMT_H

#include <QString>
#include <QHash>
#include "compiler/datatype.h"
#include "compiler/lisp_exp.h"

/**
 * The c_stmt class represents a C statement.
 *
 * C statements are one or more executable statements ending with semicolons.
 * In addition to their code, a c_stmt object also stores the names and
 * datatypes of each variable (wire) it mutates.
 */
class c_stmt {
public:
    /**
     * Compile the given lisp expression into a C statement, using the given
     * mappings of lisp symbol names to data types and C variable (wire) names.
     *
     * The root operation of the lisp expression must be one that translates
     * into a C statement, not an expression. The options are: stmt-list, set,
     * and write_dac.
     *
     * @param exp the lisp expression to compile
     * @param dataTypes the mapping of lisp symbol names to data types
     * @param wireNames the mapping of lisp symbol names to C variable names
     * @return the compiled C statement
     */
    static c_stmt fromLispExp(lisp_exp exp, QHash<QString, DataType> dataTypes, QHash<QString, QString> wireNames);

    /**
     * Construct an invalid C statement
     */
    c_stmt();

    /**
     * Construct a C statement with the given C code and mapping from output
     * variable names to data types
     * @param code the C code
     * @param outputTypes the mapping from output variable names to data types
     */
    c_stmt(QString code, QHash<QString, DataType> outputTypes);

    /**
     * @return true of the C statement object is valid, false otherwise
     */
    bool isValid() const;

    /**
     * @return the statement's C code
     */
    QString code() const;

    /**
     * @return the statement's mapping from output variable names to data types
     */
    QHash<QString, DataType> outputTypes() const;
private:
    bool m_valid;
    QString m_code;
    QHash<QString, DataType> m_outputTypes;
};

#endif // C_STMT_H
