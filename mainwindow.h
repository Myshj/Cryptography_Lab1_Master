#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <matrix.h>
#include "QTableWidget"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void on_generateTableOfFunctionButton_Square_clicked();
    void on_generateAprioriMessageProbabilities_Square_clicked();
    void on_generateAprioriKeyProbabilities_Square_clicked();
    void on_generateTableOfAposterioriMessageProbabilityButton_Square_clicked();
    void on_tableOfFunction_Square_cellChanged(int row, int column);
    void on_tableOfAprioriMessageProbability_Square_cellChanged(int row, int column);
    void on_tableOfAprioriKeyProbability_Square_cellChanged(int row, int column);
    void on_generateTableOfDifferenceBetweenAprAndApostMessageProbabilitiesButton_Square_clicked();
    void on_generateTableOfRatiosBetweenApostKeyProbAndAprMesProbButton_Square_clicked();

    void on_generateTableOfFunctionButton_Rect_clicked();
    void on_generateAprioriMessageProbabilities_Rect_clicked();
    void on_generateAprioriKeyProbabilities_Rect_clicked();
    void on_generateTableOfAposterioriMessageProbabilityButton_Rect_clicked();
    void on_tableOfFunction_Rect_cellChanged(int row, int column);
    void on_tableOfAprioriMessageProbability_Rect_cellChanged(int row, int column);
    void on_tableOfAprioriKeyProbability_Rect_cellChanged(int row, int column);
    void on_generateTableOfDifferenceBetweenAprAndApostMessageProbabilitiesButton_Rect_clicked();
    void on_generateTableOfRatiosBetweenApostKeyProbAndAprMesProbButton_Rect_clicked();

    void on_generateTableOfFunctionButton_Rect_2_clicked();
    void on_generateAprioriMessageProbabilities_Rect_2_clicked();
    void on_generateAprioriKeyProbabilities_Rect_2_clicked();
    void on_generateTableOfAposterioriMessageProbabilityButton_Rect_2_clicked();
    void on_tableOfFunction_Rect_2_cellChanged(int row, int column);
    void on_tableOfAprioriMessageProbability_Rect_2_cellChanged(int row, int column);
    void on_tableOfAprioriKeyProbability_Rect_2_cellChanged(int row, int column);
    void on_generateTableOfDifferenceBetweenAprAndApostMessageProbabilitiesButton_Rect_2_clicked();
    void on_generateTableOfRatiosBetweenApostKeyProbAndAprMesProbButton_Rect_2_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;

private:

    void switchToSquare();
    void switchToRectangle();
    void switchToRectangle_2();

    void generateTableOfFunction(
            const unsigned int constRow1,
            const unsigned int constColumn1,
            const unsigned int constValue1,
            const unsigned int constRow2,
            const unsigned int constColumn2,
            const unsigned int constValue2
            );

    void generateAprioriMessageProbabilities();
    void generateAprioriKeyProbabilities();

    void generateAposterioriMessageProbabilities();
    void generateDifferenceBetweenAprAndApostMessageProbabilities();
    void generateRatiosBetweenApostKeyProbAndAprMesProb();

    void writeVectorToTable(const QVector<double>& vector, const QTableWidget* table);

    template<typename T>
    void writeMatrixToTable(const Matrix<T>& matrix, const QTableWidget* table);

private:
    Matrix<unsigned int> tableOfFunction;
    QVector<double> aprioriMessageProbabilities;// = QVector<double>(ui->tableOfAprioriMessageProbability->columnCount());
    QVector<double> aprioriKeyProbabilities;

    Matrix<double> aposterioriMessageProbabilities;
    Matrix<double> differenceBetweenAprAndApostMessageProbabilities;
    Matrix<double> ratiosBetweenApostKeyProbAndAprMesrob;
};

#endif // MAINWINDOW_H
