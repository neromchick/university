    #ifndef GAMEWINDOW_H
    #define GAMEWINDOW_H

    #include <QPushButton>
    #include <QMainWindow>

    namespace Ui {
    class gamewindow;
    }

    class gamewindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit gamewindow(QWidget *parent = nullptr);
        ~gamewindow();

    signals:
        void sendBalance(const QString value);

    private slots:
        void on_answerBtn_clicked();
        void on_hintBtn_clicked();
        void on_backToMenuBtn_clicked();
        //void animateBlink(QPushButton* button, int times, int interval, const QString& finalStyle, std::function<void()> onFinished);
        void animateBlink(QPushButton* button, int times, int interval,
                          std::function<void()> onFinished = nullptr);

        void startCountdown();
        void resetStylesAnswerBtn();
        void applyStylesHintBtn();
        void proceedToNextLevel();
        void loadNextQuestion();
        void initPrizeList();

        void on_takeMoneyBtn_clicked();

    private:
        Ui::gamewindow *ui;
        int level = 1;
        bool blockClicks = false;
        double countdown = 15.00;
        QTimer* countdownTimer = nullptr;
        QList<QPushButton*> answerButtons;
        QList<QPushButton*> hintButtons;
    };


    #endif // GAMEWINDOW_H
