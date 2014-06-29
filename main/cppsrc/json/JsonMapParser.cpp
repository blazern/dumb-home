#include "JsonMapParser.h"
#include <stdexcept>
#include <QJsonArray>
#include "StaticMapLayerConstructor.h"

#include <QDebug>

// Parsed JSON-object example:
/// {
/// "player": {
///     "x": 20,
///     "y": 20,
///     "width": 10,
///     "height": 10
/// },
///
/// "staticObjectWidth": 10,
/// "staticObjectHeight": 10,
///
/// "staticLayerWidth": 4,
/// "staticLayerHeight": 4,
///
///	"rows": [ {
///		"y":0,
///		"cells:": [
///			{ "x":0 },
///			{ "x":1 },
///			{ "x":2 },
///			{ "x":3 }
///		] }, {
///		"y":1,
///		"cells:": [
///			{ "x":0 },
///			{ "x":3 }
///		] }, {
///		"y":2,
///		"cells:": [
///			{ "x":0 },
///			{ "x":3 }
///		] }, {
///		"y":3,
///		"cells:": [
///			{ "x":0 },
///			{ "x":1 },
///			{ "x":2 },
///			{ "x":3, "type": "stairs" }
///		] }	]
/// }

Map * JsonMapParser::parseJsonObject(const QJsonObject & mapAsJson) const
{
    DynamicMapLayer * dynamicMapLayer = new DynamicMapLayer(parsePlayerRect(mapAsJson));
    StaticMapLayer * staticMapLayer = parseStaticMapLayer(mapAsJson);

    if (mapAsJson.contains("staticObjectWidth")
        && mapAsJson.contains("staticObjectHeight"))
    {
        const QJsonValue staticObjectWidthValue = mapAsJson.value("staticObjectWidth");
        const QJsonValue staticObjectHeightValue = mapAsJson.value("staticObjectHeight");

        if (staticObjectWidthValue.isDouble()
            && staticObjectHeightValue.isDouble())
        {
            const double staticObjectWidth = staticObjectWidthValue.toDouble();
            const double staticObjectHeight = staticObjectHeightValue.toDouble();

            return new Map(staticMapLayer, dynamicMapLayer, staticObjectWidth, staticObjectHeight);
        }
        else
        {
            delete dynamicMapLayer;
            delete staticMapLayer;
            throw std::invalid_argument("staticObjectWidth or/and staticObjectHeight are not double");
        }
    }
    else
    {
        delete dynamicMapLayer;
        delete staticMapLayer;
        throw std::invalid_argument("the JSON-file doesn't contain staticObjectWidth or/and staticObjectHeight properties");
    }
}

QRectF JsonMapParser::parsePlayerRect(const QJsonObject & mapAsJson) const
{
    if (mapAsJson.contains("player"))
    {
        const QJsonValue playerValue = mapAsJson.value("player");

        if (playerValue.isObject())
        {
            const QJsonObject playerObject = playerValue.toObject();

            if (playerObject.contains("x")
                && playerObject.contains("y")
                && playerObject.contains("width")
                && playerObject.contains("height"))
            {
                const QJsonValue xValue = playerObject.value("x");
                const QJsonValue yValue = playerObject.value("y");
                const QJsonValue widthValue = playerObject.value("width");
                const QJsonValue heightValue = playerObject.value("height");

                if (xValue.isDouble()
                    && yValue.isDouble()
                    && widthValue.isDouble()
                    && heightValue.isDouble())
                {
                    const double x = xValue.toDouble();
                    const double y = yValue.toDouble();
                    const double width = widthValue.toDouble();
                    const double height = heightValue.toDouble();

                    return QRectF(x, y, width, height);
                }
                else
                {
                    throw std::invalid_argument("some properties of the player object are not double");
                }
            }
            else
            {
                throw std::invalid_argument(R"(the player object does not have one or more of )"
                                            R"("x", "y", "width", "height" properties)");
            }
        }
        else
        {
            throw std::invalid_argument("the player value is not an object");
        }
    }
    else
    {
        throw std::invalid_argument("the parsed JSON doesn't contain a player object");
    }
}

void JsonMapParser::parseStaticMapObjectSizes(const QJsonObject & mapAsJson, int * const width, int * const height) const
{
    if (mapAsJson.contains("staticLayerWidth")
        && mapAsJson.contains("staticLayerHeight"))
    {
        const QJsonValue staticLayerWidthValue = mapAsJson.value("staticLayerWidth");
        const QJsonValue staticLayerHeightValue = mapAsJson.value("staticLayerHeight");

        if (staticLayerWidthValue.isDouble()
            && staticLayerHeightValue.isDouble())
        {
            *width = staticLayerWidthValue.toDouble();
            *height = staticLayerHeightValue.toDouble();
        }
        else
        {
            throw std::invalid_argument("staticLayerWidthValue or/and staticLayerHeightValue is not double");
        }
    }
    else
    {
        throw std::invalid_argument("the JSON-file doesn't contain some of the next objects: "
                                    "staticLayerWidth, staticLayerHeight");
    }
}

// WARNING! THE BELOW CODE IS EXTREMLY UGLY!
StaticMapLayer * JsonMapParser::parseStaticMapLayer(const QJsonObject & mapAsJson) const
{
    int staticLayerWidth;
    int staticLayerHeight;
    parseStaticMapObjectSizes(mapAsJson, &staticLayerWidth, &staticLayerHeight);

    StaticMapLayerConstructor staticMapLayerConstructor(staticLayerWidth, staticLayerHeight);

    if (mapAsJson.contains("rows"))
    {
        const QJsonValue rowsValue = mapAsJson.value("rows");

        if (rowsValue.isArray())
        {
            const QJsonArray rowsArray = rowsValue.toArray();

            for (auto rowIterator = rowsArray.constBegin(); rowIterator != rowsArray.end(); rowIterator++)
            {
                const QJsonValue rowValue = *rowIterator;

                if (rowValue.isObject())
                {
                    const QJsonObject rowObject = rowValue.toObject();

                    if (rowObject.contains("y"),
                        rowObject.contains("cells"))
                    {
                        const QJsonValue yValue = rowObject.value("y");
                        int y;

                        if (yValue.isDouble())
                        {
                            y = yValue.toDouble();
                        }
                        else
                        {
                            throw std::invalid_argument("cell's 'y' in not a number");
                        }

                        const QJsonValue cellsValue = rowObject.value("cells");

                        if (cellsValue.isArray())
                        {
                            const QJsonArray cellsArray = cellsValue.toArray();

                            for (auto cellIterator = cellsArray.constBegin(); cellIterator != cellsArray.end(); cellIterator++)
                            {
                                const QJsonValue cellValue = *cellIterator;

                                if (cellValue.isObject())
                                {
                                    const QJsonObject cellObject = cellValue.toObject();

                                    if (cellObject.contains("x"))
                                    {
                                        const QJsonValue xValue = cellObject.value("x");

                                        if (xValue.isDouble())
                                        {
                                            const int x = xValue.toDouble();

                                            if (cellObject.contains("type"))
                                            {
                                                const QJsonValue typeValue = cellObject.value("type");
                                                if (typeValue.isString())
                                                {
                                                    const QString type = typeValue.toString();
                                                    if (type == "wall")
                                                    {
                                                        staticMapLayerConstructor.markCell(x, y, StaticMapObject::Type::WALL);
                                                    }
                                                    else if (type == "stairs")
                                                    {
                                                        staticMapLayerConstructor.markCell(x, y, StaticMapObject::Type::STAIRS);
                                                    }
                                                    else if (type != "air")
                                                    {
                                                        throw std::invalid_argument("only wall, stairs and air cell types are supported");
                                                    }
                                                }
                                                else
                                                {
                                                    throw std::invalid_argument("cell's 'type' is not string");
                                                }
                                            }
                                            else
                                            {
                                                staticMapLayerConstructor.markCell(x, y, StaticMapObject::Type::WALL);
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("cell's 'x' is not double");
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("cell (element of 'cells') doesn't have 'x'");
                                    }
                                }
                                else
                                {
                                    throw std::invalid_argument("cell (element of 'cells') is not an object");
                                }
                            }
                        }
                        else
                        {
                            throw std::invalid_argument("'cells' is not an array");
                        }
                    }
                    else
                    {
                        throw std::invalid_argument("a row doesn't contain 'y' or/and 'cells' properties");
                    }
                }
                else
                {
                    throw std::invalid_argument("one or more rows are not objects");
                }
            }
        }
        else
        {
            throw std::invalid_argument("'rows' object is not an array");
        }
    }
    else
    {
        throw std::invalid_argument("the JSON-file doesn't contain 'rows' object");
    }

    return staticMapLayerConstructor.construct();
}
