#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include "editor.h"

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(Editor *editor)
    : QWidget(editor), mCodeEditor(editor)
    {

    }

    QSize sizeHint() const override
    {
        return QSize(mCodeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        mCodeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    Editor *mCodeEditor;
};

#endif // LINENUMBERAREA_H
