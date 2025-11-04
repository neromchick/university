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

    private slots:
        void on_answerBtn_clicked();
        void on_backToMenuBtn_clicked();
        void animateBlink(QPushButton* button, int times, int interval, std::function<void()> onFinished);
        void showAnswerResult(QPushButton* clickedButton);
        void startCountdown();
        void resetStylesAnswerBtn();
        void proceedToNextLevel();
        void loadNextQuestion();
        void initPrizeList();

    private:
        Ui::gamewindow *ui;
        int level = 1;
        bool blockClicks = false;
        double countdown = 15.00;
        QTimer* countdownTimer = nullptr;
        QList<QPushButton*> answerButtons;
    };


    #endif // GAMEWINDOW_H
