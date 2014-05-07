#ifndef JSONMAPPARSER_H
#define JSONMAPPARSER_H

#include "JsonObjectParser.h"
#include "../map/Map.h"


class JsonMapParser : public JsonObjectParser<Map>
{
    Q_DISABLE_COPY(JsonMapParser)
public:
    JsonMapParser() = default;
    // never returns nullptr
    // throws std::invalid_argument
    virtual Map * parseJsonObject(const QJsonObject & mapAsJson) const final override;

private:
    QRectF parsePlayerRect(const QJsonObject & mapAsJson) const;
    void parseStaticMapObjectSizes(const QJsonObject & mapAsJson, int * width, int * height) const;
    StaticMapLayer * parseStaticMapLayer(const QJsonObject & mapAsJson) const;
};

#endif // JSONMAPPARSER_H
