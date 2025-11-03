    #ifndef GAMEWINDOW_H
    #define GAMEWINDOW_H

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
        void on_answerBtn1_clicked();

        void on_answerBtn2_clicked();

        void on_answerBtn_clicked();

        void proceedToNextLevel();
        void resetStylesAnswerBtn();
        void loadNextQuestion();

        void on_backToMenuBtn_clicked();

    private:
        Ui::gamewindow *ui;
        int level = 1;
        bool blockClicks = false;
    };


    #endif // GAMEWINDOW_H
