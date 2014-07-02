#ifndef LINEDIVIDER_H
#define LINEDIVIDER_H

#include <QVector>

class LineDivider
{
    LineDivider() = delete;

public:
    // throws std::invalid_argument if partsCount * minWidth > lineWidth
    static QVector<int> getDividers(const int lineStart, const int lineWidth, const int partsCount, const int minWidth);

private:
    static QVector<int> getPartsWidths(const int lineWidth, const int partsCount, const int minWidth);
};

#endif // LINEDIVIDER_H
