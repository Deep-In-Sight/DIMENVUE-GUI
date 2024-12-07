#ifndef DIMENVUE_H
#define DIMENVUE_H

#include <QGuiApplication>

class DimenvuePrivate;

class Dimenvue : public QGuiApplication
{
    Q_OBJECT

    Q_PROPERTY(float globalScale READ globalScale)

public:
    Dimenvue(int& argc, char** argv);
    virtual ~Dimenvue();

    bool initialize();

    Q_INVOKABLE void showKeyboard();
    Q_INVOKABLE void hideKeyboard();

    Q_INVOKABLE void inputHangulKey(QString c);
    Q_INVOKABLE void inputNoHangulKey(QString c);
    Q_INVOKABLE void inputBackspace();
    Q_INVOKABLE void inputInit(const QString& s);

    Q_INVOKABLE void changeLanguage(int lang);  //0: kor
                                                //1: eng

    Q_INVOKABLE void setSortRole(int role, int order);  //0: accending

    Q_INVOKABLE void removeChecked();

    Q_INVOKABLE void loadScanComplete();

    Q_INVOKABLE void openMap(int index);

    float globalScale() const;

Q_SIGNALS:
    void keyboardTextUpdated(QString value);

private:
    QScopedPointer<DimenvuePrivate> d;
};

#endif // DIMENVUE_H
