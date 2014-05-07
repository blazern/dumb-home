#ifndef JSONOBJECTPARSER_H
#define JSONOBJECTPARSER_H

#include <QUrl>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <stdexcept>
#include <QFile>

#ifdef QT_DEBUG
#include <QDebug>
#endif

template<typename ObjectType>
class JsonObjectParser
{
public:
    // throws std::invalid_argument
    ObjectType * parse(const QUrl & url) const
    {
        return parseJsonObject(parseJsonFile(url));
    }

    // throws std::invalid_argument
    ObjectType * parse(const QString & json) const
    {
        return parseJsonObject(jsonToObject(json.toUtf8()));
    }

protected:
    // throws std::invalid_argument
    virtual ObjectType * parseJsonObject(const QJsonObject & mapAsJson) const = 0;

private:
    // throws std::invalid_argument
    QJsonObject parseJsonFile(const QUrl & url) const
    {
        const QString path = url.toLocalFile();
        QFile file(path);

        if (file.exists())
        {
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            const QByteArray json = file.readAll();
            file.close();

            return jsonToObject(json);
        }
        else
        {
            throw std::invalid_argument(QString(
                                            "Parsing of file with URL: "
                                            + url.toString()
                                            + " is impossible because file doesn't exist").toStdString());
        }
    }

    // throws std::invalid_argument
    QJsonObject jsonToObject(const QByteArray & json) const
    {
        QJsonParseError jsonParseError;

        QJsonDocument document = QJsonDocument::fromJson(json, &jsonParseError);

        if (jsonParseError.error == QJsonParseError::NoError)
        {
            return document.object();
        }
        else
        {
            throw std::invalid_argument(QString(
                                            "Parsing of JSON failed with error: "
                                            + jsonParseError.errorString()
                                            + " at position: "
                                            + QString::number(jsonParseError.offset)).toStdString());
        }
    }
};

#endif // JSONOBJECTPARSER_H
