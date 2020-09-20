#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    ScribbleArea(QWidget *parent = nullptr);
    /* sets pencil color, e.g. red(#FF0000) */
    void setPenColor(const QColor &newColor);

    /* sets pencil width */
    void setPenWidth(int newWidth);

    /* open image file */
    bool openImg(const QString &fileName);

    /* save img file */
    bool saveImg(const QString &fileName, const char *fileFormat);

    /* checks if file is modified */
    bool isModified() const {return modified;}

    /* sets pencil color */
    QColor penColor() const {return myPenColor;}

    /* sets pencil width */
    int penWidth() const {return myPenWidth;}

private slots:
    /* clear image field */
    void clearImg();

    /* prints your image */
    void printImg();

protected:
    /* event checks if user clicked a mouse bttn */
    void mousePressEvent(QMouseEvent *event) override;

    /* event checks if mouse moved */
    void mouseMoveEvent(QMouseEvent *event) override;

    /* event checks if user clicked and then released mouse button */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /* event that is responsible for all drawing */
    void paintEvent(QPaintEvent *event) override;

    /* event for resizing */
    void resizeEvent(QResizeEvent *event) override;

private:
    /* draw line to your pointer aka cursor */
    void drawLineTo(const QPoint &endPoint);

    /* resize image, resize image to your chosen size */
    void resizeImg(QImage *image, const QSize &newSize);

    /* is file modified? */
    bool modified;

    /* is drawing occur?*/
    bool scribbling;

    /* pencil color  */
    QColor myPenColor;

    /* loaded/saved file */
    QImage image;

    /* last point of your cursor/brush */
    QPoint lastPoint;

    /* pencil width */
    int myPenWidth;

};
#endif // SCRIBBLEAREA_H
