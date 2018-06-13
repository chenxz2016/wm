#include "utility.h"

#include <QPainter>


namespace WMUtility
{

QPixmap pixmap_to_round(const QPixmap &src, qreal radius)
{
    if (src.isNull()) {
        return QPixmap();
    }

    QSizeF size(2*radius, 2*radius);
    QImage dst(size.toSize(),QImage::Format_ARGB32);
    QImage img(size.toSize(),QImage::Format_ARGB32);

    QPainter painter(&dst);
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(dst.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    QPainter ptr(&img);
    ptr.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    ptr.setCompositionMode(QPainter::CompositionMode_Source);
    ptr.fillRect(img.rect(), Qt::transparent);
    QPainterPath path;
    path.addEllipse(QRectF(0, 0, size.width(), size.height()));
    ptr.fillPath(path,Qt::white);
    ptr.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    ptr.end();
    painter.drawImage(dst.rect(),img);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawImage(dst.rect(),src.scaled(size.toSize()).toImage());

    return QPixmap::fromImage(dst);
}


}
