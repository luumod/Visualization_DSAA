#ifndef SLIDE_PAGE
#define SLIDE_PAGE

#include <QWidget>


class QLabel;
class customIcon;
class QParallelAnimationGroup;
class QGraphicsOpacityEffect;
class ScrollAreaCustom;
class SheildLayer : public QWidget{
    Q_OBJECT

private:
    bool pressed = false;
    bool enabled = true;
    QWidget *bg;
    void mousePressEvent(QMouseEvent *event){if(enabled)pressed = true;}
    void mouseReleaseEvent(QMouseEvent *event){if(enabled && pressed)emit clicked();pressed = false;}
    void resizeEvent(QResizeEvent *event){bg->resize(this->parentWidget()->size());}
public:
    SheildLayer(QWidget *parent = nullptr) : QWidget(parent){
        bg = new QWidget(this);
        bg->resize(parent->size());
        bg->setStyleSheet("background-color:#5a000000");
        bg->setAttribute(Qt::WA_TransparentForMouseEvents);
        bg->show();
    }
    void setEnabled(bool e){enabled = e;}
signals:
    void clicked();
};

class SlidePage : public QWidget
{
    Q_OBJECT
private:
    int cornerRadius;
    QString pageName;
    ScrollAreaCustom *pageContentContainer;
    QLabel *nameLabel;
    customIcon *backIcon;
    SheildLayer *sheildLayer;
    QWidget *bgWidget;
    QFont textFont = QFont("Corbel Light", 24);

    bool onShown = false;
    QParallelAnimationGroup *curAni = nullptr;
    QGraphicsOpacityEffect *opacity;

    void resizeEvent(QResizeEvent *event);

public:
    const int preferWidth = 350;
    int parentWidgetWidth{};
    int parentWidgetHeight{};
    explicit SlidePage(int radius, QString name, QWidget *parent = nullptr);
    void SetRadius(int radius);
    void SetName(QString name);
    void AddContent(QWidget* widget);
    void AddContents(QVector<QWidget*> widgets);
    void RemoveContents(QVector<QWidget*> widgets);
    void UpdateContents();
    void ScrollToTop();

signals:
    void sizeChange();

public slots:
    void slideIn();
    void slideOut();
    void autoResize();

};

#endif // SLIDEPAGE_H
