#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int state; // 0��ʾ��ϸ����1��ʾ��ϸ��

public:
    // Ĭ�Ϲ��캯��
    Cell();

    // ���캯��
    Cell(int initState);

    // ��ȡϸ��״̬
    int getState() const;

    // ����ϸ��״̬
    void setState(int newState);

    // ��ӡϸ��״̬
    void printCell() const;
};

#endif
