#include "compiler/c_stmt.h"

#include <QString>
#include <QHash>
#include "compiler/datatype.h"
#include "compiler/lisp_exp.h"
#include <QList>
#include "compiler/c_exp.h"

c_stmt c_stmt::fromLispExp(lisp_exp exp, QHash<QString, DataType> dataTypes, QHash<QString, QString> wireNames) {
    QString operand = exp.element(0).value();
    if (operand == "write_dac") {
        QString code = "write_dac(" + c_exp::fromLispExp(exp.element(1), dataTypes, wireNames).conversionTo(DATATYPE_INT).code() + ", ((" + c_exp::fromLispExp(exp.element(2), dataTypes, wireNames).conversionTo(DATATYPE_AFP(27)).code() + ") >> 16));";
        return c_stmt(code, QHash<QString, DataType>());
    } else if (operand == "set") {
        auto result = c_exp::fromLispExp(exp.element(2), dataTypes, wireNames);
        QString code = wireNames[exp.element(1).value()] + " = " + result.code() + ";";
        QHash<QString, DataType> outputTypes;
        outputTypes[wireNames[exp.element(1).value()]] = result.type();
        return c_stmt(code, outputTypes);
    } else if (operand == "stmt-list") {
        QList<c_stmt> results;
        for (int i = 1; i < exp.size(); i++) {
            c_stmt result = c_stmt::fromLispExp(exp.element(i), dataTypes, wireNames);
            results.push_back(result);
        }
        QString code;
        QHash<QString, DataType> outputTypes;
        for (auto result : results) {
            code += result.code() + "\n";
            outputTypes.unite(result.outputTypes());
        }
        return c_stmt(code, outputTypes);
    } else {
        return c_stmt(); // error condition
    }
}

c_stmt::c_stmt() {
    m_valid = false;
}

c_stmt::c_stmt(QString code, QHash<QString, DataType> outputTypes) {
    m_valid = true;
    m_code = code;
    m_outputTypes = outputTypes;
}

bool c_stmt::isValid() const {
    return m_valid;
}

QString c_stmt::code() const {
    return m_code;
}
QHash<QString, DataType> c_stmt::outputTypes() const {\
    return m_outputTypes;
}
