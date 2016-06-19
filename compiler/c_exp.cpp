#include "c_exp.h"

#include <QString>
#include "datatype.h"
#include "lisp_exp.h"
#include <QHash>
#include <QList>

// helper functions

DataType moreGeneralType(DataType a, DataType b) {
    if (a.isFloat() || b.isFloat()) {
        return DATATYPE_FLOAT;
    } else if (a.isAFP() && b.isAFP()) {
        return DATATYPE_AFP(qMin(a.afpPrecision(), b.afpPrecision()));
    } else if (a.isAFP()) {
        return DATATYPE_AFP(a.afpPrecision());
    } else if (b.isAFP()) {
        return DATATYPE_AFP(b.afpPrecision());
    } else {
        return DATATYPE_INT;
    }
}

unsigned int intLog2(unsigned int x) {
    unsigned int result = 0;
    unsigned int bits = x;
    while (bits > 1) {
        bits = bits >> 1;
        result++;
    }
    // round up
    if (x > ((unsigned int)1 << result)) {
        result++;
    }
    return result;
}

DataType getMostGeneralType(QList<c_exp> results) {
    DataType mostGeneralType = DATATYPE_INT;
    for (auto result : results) {
        mostGeneralType = moreGeneralType(mostGeneralType, result.type());
    }
    return mostGeneralType;
}

QList<QString> getConversionCodes(QList<c_exp> results, DataType resultType) {
    QList<QString> conversionCodes;
    for (c_exp result : results) {
        QString conversion = result.conversionTo(resultType).code();
        conversionCodes.push_back("(" + conversion + ")");
    }
    return conversionCodes;
}

QList<QString> getCodes(QList<c_exp> results) {
    QList<QString> codes;
    for (c_exp result : results) {
        codes.push_back("(" + result.code() + ")");
    }
    return codes;
}

QList<c_exp> evaluateArguments(lisp_exp cell, QHash<QString, DataType> dataTypes, QHash<QString, QString> wireNames) {
    QList<c_exp> results;
    for (int i = 1; i < cell.size(); i++) {
        c_exp result = c_exp::fromLispExp(cell.element(i), dataTypes, wireNames);
        results.push_back(result);
    }
    return results;
}

c_exp c_exp::fromLispExp(lisp_exp exp, QHash<QString, DataType> dataTypes, QHash<QString, QString> wireNames) {
    if (exp.isLeaf()) {
        if (wireNames.contains(exp.value())) {
            DataType dt = dataTypes.value(exp.value());
            QString wireName = wireNames.value(exp.value());
            return c_exp(wireName, dt);
        } else {
            bool success;
            exp.value().toInt(&success);
            if (success) {
                return c_exp(exp.value(), DATATYPE_INT);
            } else {
                exp.value().toFloat(&success);
                if (success) {
                    return c_exp(exp.value(), DATATYPE_FLOAT);
                } else {
                    return c_exp(); // error condition
                }
            }
        }
    } else {
        QString theOperator = exp.element(0).value();
        if (theOperator == "+" || theOperator == "-") {
            QList<c_exp> results = evaluateArguments(exp, dataTypes, wireNames);
            DataType mostGeneralType = getMostGeneralType(results);
            DataType resultType;
            if (mostGeneralType.isAFP()) {
                resultType = DATATYPE_AFP(mostGeneralType.afpPrecision() - intLog2(results.size()));
            } else {
                resultType = mostGeneralType;
            }
            QList<QString> conversionCodes = getConversionCodes(results, resultType);
            QString code = conversionCodes.join(" " + theOperator + " ");
            return c_exp(code, resultType);
        } else if (theOperator == "*") {
            QList<c_exp > results = evaluateArguments(exp, dataTypes, wireNames);
            DataType mostGeneralType = getMostGeneralType(results);
            if (mostGeneralType.isAFP()) {
                QString lastCode = "(int64_t)(" + results[0].code() + ")";
                DataType lastType = results[0].type();
                for (int i = 1; i < results.size(); i++) {
                    c_exp result = results[i];
                    if (! result.isValid()) {
                        lastType = DataType();
                    }
                    lastCode = "(" + lastCode + ") * (" + result.code() + ")";
                    lastCode = "(" + lastCode + ") >> 32";
                    int lastAFPPrecision = lastType.isAFP() ? lastType.afpPrecision() : 0;
                    int resultAFPPrecision = result.type().isAFP() ? result.type().afpPrecision() : 0;
                    if (lastType.isValid()) {
                        lastType = DATATYPE_AFP(32 - ((32 - lastAFPPrecision) + (32 - resultAFPPrecision)));
                    }
                }
                lastCode = "(int)(" + lastCode + ")";
                return c_exp(lastCode, lastType);
            } else {
                DataType resultType = mostGeneralType;
                QList<QString> codes = getCodes(results);
                QString code = codes.join(" * ");
                return c_exp(code, resultType);
            }
        } else if (theOperator == "/") {
            return c_exp();
        } else if (theOperator == "//") {
            return c_exp();
        } else if (theOperator == "%") {
            return c_exp();
        } else if (theOperator == "mod") {
            return c_exp();
        } else if (theOperator == "if") {
            c_exp condResult = c_exp::fromLispExp(exp.element(1), dataTypes, wireNames);
            c_exp ifTrueResult = c_exp::fromLispExp(exp.element(2), dataTypes, wireNames);
            c_exp ifFalseResult = c_exp::fromLispExp(exp.element(3), dataTypes, wireNames);
            DataType resultType = moreGeneralType(ifTrueResult.type(), ifFalseResult.type());
            QString code = "(" + condResult.code() + ") ? (" + ifTrueResult.conversionTo(resultType).code() + ") : (" + ifFalseResult.conversionTo(resultType).code() + ")";
            return c_exp(code, resultType);
        } else if (theOperator == ">" || theOperator == "<" || theOperator == ">=" || theOperator == "<=" || theOperator == "==" || theOperator == "!=") {
            c_exp leftOperand = c_exp::fromLispExp(exp.element(1), dataTypes, wireNames);
            c_exp rightOperand = c_exp::fromLispExp(exp.element(2), dataTypes, wireNames);
            DataType resultType = moreGeneralType(leftOperand.type(), rightOperand.type());
            QString code = "(" + leftOperand.conversionTo(resultType).code() + ") " + theOperator + " (" + rightOperand.conversionTo(resultType).code() + ")";
            return c_exp(code, resultType);
        } else if (theOperator == "sqrt") {
            c_exp operand = c_exp::fromLispExp(exp.element(1), dataTypes, wireNames);
            QString code = "sqrt(" + operand.code() + ")";
            return c_exp(code, DATATYPE_FLOAT);
        } else if (theOperator == "read_adc") {
            QString code = "((int)read_adc(" + c_exp::fromLispExp(exp.element(1), dataTypes, wireNames).conversionTo(DATATYPE_INT).code() + ") << 16)";
            return c_exp(code, DATATYPE_AFP(27));
        } else {
            return c_exp(); // error condition
        }
    }
}

c_exp::c_exp() {
    m_valid = false;
}

c_exp::c_exp(QString code, DataType type) {
    m_valid = true;
    m_code = code;
    m_type = type;
}

c_exp c_exp::conversionTo(DataType outType) const {
    QString inCode = code();
    DataType inType = type();
    QString outCode;
    if (outType.isFloat()) {
        if (inType.isFloat()) {
            outCode = inCode;
        } else if (inType.isAFP()) {
            if (inType.afpPrecision() >= 0) {
                outCode = "(float)(" + inCode + ") / " + QString::number(1 << inType.afpPrecision());
            } else {
                outCode = "(float)(" + inCode + ") * " + QString::number(1 << (-inType.afpPrecision()));
            }
        } else if (inType.isInt()) {
            outCode = "(float)(" + inCode + ")";
        } else {
            outCode = inCode; // error condition
        }
    } else if (outType.isAFP()) {
        if (inType.isFloat()) {
            if (outType.afpPrecision() >= 0) {
                outCode = "(int)(" + inCode + " * 1.6 * (1 << " + QString::number(outType.afpPrecision()) + "))";
            } else {
                outCode = "(int)(" + inCode + " * 1.6 / (1 << " + QString::number(-outType.afpPrecision()) + "))";
            }
        } else if (inType.isAFP()) {
            int numLeftShifts = outType.afpPrecision() - inType.afpPrecision();
            if (numLeftShifts > 0) {
                outCode = "(" + inCode + ") << " + QString::number(numLeftShifts);
            } else {
                outCode = "(" + inCode + ") >> " + QString::number(-numLeftShifts);
            }
        } else if (inType.isInt()) {
            if (outType.afpPrecision() >= 0) {
                outCode = "(" + inCode + ") << " + QString::number(outType.afpPrecision());
            } else {
                outCode = "(" + inCode + ") >> " + QString::number(-(outType.afpPrecision()));
            }
        } else {
            outCode = inCode; // error condition
        }
    } else if (outType.isInt()) {
        if (inType.isFloat()) {
            return c_exp(); // error condition
        } else if (inType.isAFP()) {
            return c_exp(); // error condition
        } else if (inType.isInt()) {
            outCode = inCode;
        } else {
            outCode = inCode; // error condition
        }
    }
    return c_exp(outCode, outType);
}

bool c_exp::isValid() const {
    return m_valid;
}

QString c_exp::code() const {
    return m_code;
}
DataType c_exp::type() const {
    return m_type;
}
