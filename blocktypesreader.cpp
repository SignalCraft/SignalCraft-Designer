#include "blocktypesreader.h"

#include <QVector>
#include <flowchart/blocktype.h>
#include <QIODevice>
#include <QXmlStreamReader>
#include <QString>

BlockTypesReader::BlockTypesReader() {}

QVector<BlockType> BlockTypesReader::blockTypes() {
    return m_blockTypes;
}

void BlockTypesReader::read(QIODevice *device) {
    xml.setDevice(device);
    while (xml.readNextStartElement()) {
        if (xml.name() == "BlockTypes") {
            readBlockTypes();
        }
    }
}

void BlockTypesReader::readBlockTypes() {
    while (xml.readNextStartElement()) {
        if (xml.name() == "BlockType") {
            m_blockTypes.push_back(readBlockType());
        }
    }
}

BlockType BlockTypesReader::readBlockType() {
    BlockType bt;
    bool hasName = false;
    bool hasInputs = false;
    bool hasOutputs = false;
    while (xml.readNextStartElement()) {
        if (xml.name() == "name") {
            if (hasName) {
                xml.raiseError(QObject::tr("XML parsing error: BlockType has multiple names"));
            }
            hasName = true;
            bt.name = readString();
        } else if (xml.name() == "inputs") {
            if (hasInputs) {
                xml.raiseError(QObject::tr("XML parsing error: BlockType has multiple input lists"));
            }
            hasInputs = true;
            bt.inputs = readVectorString();
        } else if (xml.name() == "outputs") {
            if (hasOutputs) {
                xml.raiseError(QObject::tr("XML parsing error: BlockType has multiple output lists"));
            }
            hasOutputs = true;
            bt.outputs = readVectorString();
        } else {
            xml.skipCurrentElement();
        }
    }
    if (!hasName) {
        xml.raiseError(QObject::tr("XML parsing error: BlockType has no name"));
    }
    if (!hasInputs) {
        xml.raiseError(QObject::tr("XML parsing error: BlockType has no input list"));
    }
    if (!hasOutputs) {
        xml.raiseError(QObject::tr("XML parsing error: BlockType has no output list"));
    }
    return bt;
}

QVector<QString> BlockTypesReader::readVectorString() {
    QVector<QString> v;
    while (xml.readNextStartElement()) {
        if (xml.name() == "item") {
            v.push_back(readString());
        } else {
            xml.skipCurrentElement();
        }
    }
    return v;
}

QString BlockTypesReader::readString() {
    return xml.readElementText();
}

