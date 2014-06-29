#include "LineDivider.h"
#include <stdexcept>

#ifdef QT_DEBUG
#include <QDebug>
#endif

QVector<int> LineDivider::getDividers(const int lineStart, const int lineWidth, const int partsCount, const int minWidth)
{
    if (partsCount * minWidth > lineWidth)
    {
        throw std::invalid_argument("received line minimum width (partsCount * minWidth) is bigger than received lineWidth");
    }

    const QVector<int> partsWidths = getPartsWidths(lineWidth, partsCount, minWidth);

    QVector<int> lineDividers;
    int nextDivider = lineStart;
    for (int widthIndex = 0; widthIndex < partsWidths.size() - 1; widthIndex++)
    {
        nextDivider += partsWidths[widthIndex];
        lineDividers.append(nextDivider);
    }

    return lineDividers;
}

QVector<int> LineDivider::getPartsWidths(const int lineWidth, const int partsCount, const int minWidth)
{
    QVector<int> partsWidths;
    for (int partIndex = 0; partIndex < partsCount; partIndex++)
    {
        partsWidths.append(minWidth);
    }

    bool lineWidthByPartsWidthsIsValid = false;
    while (!lineWidthByPartsWidthsIsValid)
    {
        int lineWidthByParts = 0;
        for (auto & partWidth : partsWidths)
        {
            lineWidthByParts += partWidth;
        }

        if (lineWidthByParts < lineWidth)
        {
            partsWidths[qrand() % partsWidths.size()] += 1;
        }
        else
        {
            lineWidthByPartsWidthsIsValid = true;
        }
    }

    return partsWidths;
}
