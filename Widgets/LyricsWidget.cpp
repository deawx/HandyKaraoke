#include "LyricsWidget.h"

#include <QPainter>
#include <QPainterPathStroker>
#include <QDebug>

LyricsWidget::LyricsWidget(QWidget *parent) : QWidget(parent)
{
    animation = new QVariantAnimation(this);
    animation->setDuration(300);

    QFont f = font();
    f.setBold(true);
    f.setPointSize(40);

    setTextFont(f);
    setTextColor(QColor("#f3f378"));
    setTextBorderColor(QColor("#000000"));
    setTextBorderOutColor(QColor("#000000"));
    setTextBorderWidth(2);
    setTextBorderOutWidth(1);

    setCurColor(QColor("#ff0000"));
    setCurBorderColor(QColor("#ffffff"));
    setCurBorderOutColor(QColor("#000000"));
    setCurBorderWidth(2);
    setCurBorderOutWidth(1);

    setLine1Y(220);
    setLine2Y(100);

    connect(animation, SIGNAL(valueChanged(QVariant)),
            this, SLOT(onAnimationValueChanged(QVariant)));
}

LyricsWidget::~LyricsWidget()
{
    animation->stop();
    cursors.clear();
    lyrics.clear();

    delete animation;
}

void LyricsWidget::reset()
{
    animation->stop();

    linesIndex = 0;
    if (lyrics.count() > 0) {
        tLine1 = lyrics.at(0);
        setTextLine1(tLine1);
        linesIndex = 1;
    }
    if (lyrics.count() > 1) {
        tLine2 = lyrics.at(1);
        setTextLine2(tLine2);
        //linesIndex++;
    }

    isLine1 = true;
    cursor_toEnd = 0;
    cursor_width = 0;
    cursor_index = 0;
    char_index = -1;
    at_end_line = false;

    chars_width.clear();
    chars_width = getCharsWidth(tLine1);

    updateArea = calculateUpdateArea();

    update();
}

void LyricsWidget::setLyrics(const QString &lyr, const QList<long> &curs)
{
    animation->stop();

    cursors.clear();
    lyrics.clear();

    lyrics = lyr.split("\r\n");
    cursors = curs;

    reset();
}

void LyricsWidget::setPositionCursor(int tick)
{
    if (cursor_index >= cursors.count())
        return;

    if (tick < cursors[cursor_index])
        return;

    if (at_end_line) {
        at_end_line = false;
        char_index = 0;
        cursor_width = 0;
        cursor_toEnd = 0;
        isLine1 = !isLine1;
    }

    if (chars_width.count() == 0 && linesIndex < lyrics.count()) {
        if (isLine1)
            setTextLine2(lyrics.at(linesIndex));
        else
            setTextLine1(lyrics.at(linesIndex));
        linesIndex++;
        isLine1 = !isLine1;
        cursor_index++;

        chars_width.clear();
        chars_width = getCharsWidth();
        return;
    }

    if (char_index == chars_width.count()) {
        animation->stop();
        cursor_width = chars_width.last();
        at_end_line = true;
        cursor_index++;
        update();

        return;
    }

    if (char_index == 0) {
        if (linesIndex < lyrics.count()) {
            if (isLine1)
                setTextLine2(lyrics.at(linesIndex));
            else
                setTextLine1(lyrics.at(linesIndex));
            linesIndex++;
        } else {
            if (isLine1) setTextLine2("");
            else setTextLine1("");
        }

        //update();

        chars_width.clear();
        chars_width = getCharsWidth();
        updateArea = calculateUpdateArea();
    }

    if (char_index >= 0 && chars_width.count() != 0) {
        cursor_toEnd = chars_width.at(char_index);
    }

    char_index++;

    if (cursor_index == cursors.count() - 1) {
        cursor_toEnd = chars_width.count() == 0 ? 0 : chars_width.last();
    }

    cursor_index++;

    animation->stop();
    animation->setStartValue(cursor_width);
    animation->setEndValue(cursor_toEnd);
    animation->start();
}

void LyricsWidget::setSeekPositionCursor(int tick)
{
    animation->stop();

    if (tick == 0) {
        reset();
        return;
    }

    if (cursors.count() == 0) {
        return;
    }

    reset();

    int round = 0;
    while (cursors[round] < tick) {
        round++;
        if (round == cursors.count())
            break;
    }

    for (int i=0; i<round; i++) {

        if (at_end_line) {
            at_end_line = false;
            char_index = 0;
            cursor_width = 0;
            cursor_toEnd = 0;
            isLine1 = !isLine1;
            //updateArea = calculateUpdateArea();
        }

        if (chars_width.count() == 0 && linesIndex < lyrics.count()) {
            if (isLine1)
                tLine2 = lyrics.at(linesIndex);
            else
                tLine1 = lyrics.at(linesIndex);
            linesIndex++;
            isLine1 = !isLine1;
            cursor_index++;

            chars_width.clear();
            chars_width = getCharsWidth();
            continue;
        }

        if (char_index == chars_width.count()) {
            cursor_width = chars_width.last();
            at_end_line = true;
            cursor_index++;

            /*if (linesIndex < lyrics.count()) {
                if (isLine1)
                    tLine1 = lyrics.at(linesIndex);
                else
                    tLine2 = lyrics.at(linesIndex);
                linesIndex++;
            } else {
                if (isLine1) tLine1 = "";
                else tLine2 = "";
            }*/

            continue;
        }

        if (char_index == 0) {
            if (linesIndex < lyrics.count()) {
                if (isLine1)
                    tLine2 = lyrics.at(linesIndex);
                else
                    tLine1 = lyrics.at(linesIndex);
                linesIndex++;
            } else {
                if (isLine1) tLine2 = "";
                else tLine1 = "";
            }
            chars_width.clear();
            chars_width = getCharsWidth();
        }

        if (char_index >= 0 && chars_width.count() != 0) {
            cursor_toEnd = chars_width.at(char_index);
        }

        char_index++;

        if (cursor_index == cursors.count() - 1) {
            cursor_toEnd = chars_width.count() == 0 ? 0 : chars_width.last();
        }

        cursor_index++;

    } // end for loop

    at_end_line = (char_index == chars_width.count()) ? true : false;
    chars_width.clear();
    chars_width = getCharsWidth();

    setTextLine1(tLine1);
    setTextLine2(tLine2);

    updateArea = calculateUpdateArea();
    cursor_width = cursor_toEnd;
    update();
}

void LyricsWidget::setTextFont(const QFont &f)
{
    setFont(f);
    setTextLine1(tLine1);
    setTextLine2(tLine2);
    updateArea = calculateUpdateArea();
}

void LyricsWidget::setTextColor(const QColor &c)
{
    tColor = c;
    setTextLine1(tLine1);
    setTextLine2(tLine2);
}

void LyricsWidget::setTextBorderColor(const QColor &c)
{
    tBorderColor = c;
    setTextLine1(tLine1);
    setTextLine2(tLine2);
}

void LyricsWidget::setTextBorderOutColor(const QColor &c)
{
    tBorderOutColor = c;
    setTextLine1(tLine1);
    setTextLine2(tLine2);
}

void LyricsWidget::setTextBorderWidth(int w)
{
    tBorderWidth = w;
    setTextLine1(tLine1);
    setTextLine2(tLine2);
    updateArea = calculateUpdateArea();
}

void LyricsWidget::setTextBorderOutWidth(int w)
{
    tBorderOutWidth = w;
    setTextLine1(tLine1);
    setTextLine2(tLine2);
    updateArea = calculateUpdateArea();
}

void LyricsWidget::setCurColor(const QColor &c)
{
    cColor = c;
    setTextLine1(tLine1);
    setTextLine2(tLine2);
}

void LyricsWidget::setCurBorderColor(const QColor &c)
{
    cBorderColor = c;
    setTextLine1(tLine1);
    setTextLine2(tLine2);
}

void LyricsWidget::setCurBorderOutColor(const QColor &c)
{
    cBorderOutColor = c;
    setTextLine1(tLine1);
    setTextLine2(tLine2);
}

void LyricsWidget::setCurBorderWidth(int w)
{
    cBorderWidth = w;
    setTextLine1(tLine1);
    setTextLine2(tLine2);
    updateArea = calculateUpdateArea();
}

void LyricsWidget::setCurBorderOutWidth(int w)
{
    cBorderOutWidth = w;
    setTextLine1(tLine1);
    setTextLine2(tLine2);
    updateArea = calculateUpdateArea();
}

void LyricsWidget::setLine1Y(int y)
{
    line1_y = y;
    update();
    updateArea = calculateUpdateArea();
}

void LyricsWidget::setLine2Y(int y)
{
    line2_y = y;
    update();
    updateArea = calculateUpdateArea();
}

void LyricsWidget::setTextLine1(const QString &text, bool andUpdate)
{
    tLine1 = text;

    pixLine1 = QPixmap(calculateLineSize(text));
    drawTextToPixmap(&pixLine1, text);

    pixCurLine1 = QPixmap(pixLine1.size());
    drawCursorTextToPixmap(&pixCurLine1, text);

    if (andUpdate)
        update();
}

void LyricsWidget::setTextLine2(const QString &text, bool andUpdate)
{
    tLine2 = text;

    pixLine2 = QPixmap(calculateLineSize(text));
    drawTextToPixmap(&pixLine2, text);

    pixCurLine2 = QPixmap(pixLine2.size());
    drawCursorTextToPixmap(&pixCurLine2, text);

    if (andUpdate)
        update();
}

void LyricsWidget::resizeEvent(QResizeEvent *event)
{
    update();
    updateArea = calculateUpdateArea();
}

void LyricsWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap( (width() - pixLine1.width()) / 2, height() - line1_y, pixLine1 );
    p.drawPixmap( (width() - pixLine2.width()) / 2 , height() - line2_y, pixLine2 );

    if (isLine1) {
        int x = (width() - pixLine1.width()) / 2;
        int y = height() - line1_y;
        QRect rect(x, y, pixLine1.width(), pixLine1.height());
        QRect inRect(rect.x(), rect.y(), cursor_width, rect.height());
        //QRegion r(rect);
        //r = r.intersected(inRect);

        //p.setClipRegion(r);
        p.setClipRect(inRect);
        p.drawPixmap(x, y, pixCurLine1);
    }
    else {
        int x = (width() - pixLine2.width()) / 2;
        int y = height() - line2_y;
        QRect rect(x, y, pixLine2.width(), pixLine2.height());
        QRect inRect(rect.x(), rect.y(), cursor_width, rect.height());
        //QRegion r(rect);
        //r = r.intersected(inRect);

        //p.setClipRegion(r);
        p.setClipRect(inRect);
        p.drawPixmap(x, y, pixCurLine2);
    }

    p.end();
}

void LyricsWidget::onAnimationValueChanged(const QVariant &v)
{
    cursor_width = v.toInt();
    update(updateArea);
}

QList<int> LyricsWidget::getCharsWidth()
{
    if (isLine1)
        return getCharsWidth(tLine1);
    else
        return getCharsWidth(tLine2);
}

QList<int> LyricsWidget::getCharsWidth(const QString &text)
{
    QList<int> cl;
    for (int i=0; i<text.length(); i++) {
        int w = fontMetrics().width(text.left(i+1)) + qMax(tBorderWidth, cBorderWidth);
        cl.append(w);
    }

    if (cl.count() > 0)
        cl.last() += qMax(tBorderWidth, cBorderWidth);

    return cl;
}

QRect LyricsWidget::calculateUpdateArea()
{
    QRect r;
    if (isLine1) {
        r.setX((width() - pixLine1.width()) / 2);
        r.setY(height() - line1_y);
        r.setWidth(pixLine1.width());
        r.setHeight(pixLine1.height());
    }
    else {
        r.setX((width() - pixLine2.width()) / 2);
        r.setY(height() - line2_y);
        r.setWidth(pixLine2.width());
        r.setHeight(pixLine2.height());
    }
    return r;
}

QSize LyricsWidget::calculateLineSize(const QString &text)
{
    QSize s;
    s.setWidth( fontMetrics().width(text)
                + (qMax(tBorderWidth, cBorderWidth)*2) );
    s.setHeight( font().pointSize() * 2.5 );
    return s;
}

void LyricsWidget::drawTextToPixmap(QPixmap *pix, const QString &text)
{
    pix->fill(Qt::transparent);
    QPainter p(pix);
    p.setRenderHints(QPainter::Antialiasing);

    QPainterPath path;
    path.addText(qMax(tBorderWidth, cBorderWidth), font().pointSize() * 2, font(), text);

    p.setBrush(tColor);
    p.setPen(Qt::NoPen);
    p.drawPath(path);

    if (tBorderWidth > 0) {
        QPen pen(Qt::red, tBorderWidth * 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
        QPainterPathStroker stroker(pen);
        QPainterPath strokedPath = stroker.createStroke(path);

        if (tBorderOutWidth > 0)
            p.setPen(QPen(tBorderOutColor, tBorderOutWidth));
        p.setBrush(tBorderColor);
        p.drawPath(strokedPath.subtracted(path));
    }

    p.end();
}

void LyricsWidget::drawCursorTextToPixmap(QPixmap *pix, const QString &text)
{
    pix->fill(Qt::transparent);
    QPainter p(pix);
    p.setRenderHints(QPainter::Antialiasing);

    QPainterPath path;
    path.addText(qMax(tBorderWidth, cBorderWidth), font().pointSize() * 2, font(), text);

    p.setBrush(cColor);
    p.setPen(Qt::NoPen);
    p.drawPath(path);

    if (cBorderWidth > 0) {
        QPen pen(Qt::red, cBorderWidth * 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
        QPainterPathStroker stroker(pen);
        QPainterPath strokedPath = stroker.createStroke(path);

        if (cBorderOutWidth > 0)
            p.setPen(QPen(cBorderOutColor, cBorderOutWidth));
        p.setBrush(cBorderColor);
        p.drawPath(strokedPath.subtracted(path));
    }

    p.end();
}
