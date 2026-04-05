#include <iostream>
#include <graphics.h>
#include <chrono>
#include <iomanip>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SIZE 20
using namespace std;

//食物类
class Food 
{
public:
    int x, y;//位置坐标
    int color = GREEN;

    Food(int width, int height) 
    {
        srand((unsigned)time(NULL));
        // 计算随机的x和y坐标，确保食物定位在窗口内并且能被SIZE整除的位置
        x = rand() % (width / SIZE) * SIZE;
        y = rand() % (height / SIZE) * SIZE;

        draw();
    }

    Food() {}

    //在指定位置画出食物
    void draw() 
    {
        setfillcolor(GREEN);
        solidrectangle(x, y, x + SIZE, y + SIZE);
    }
};

//蛇类
class Snake
{
public:
    int x, y; // 蛇体节段的位置坐标
    int color = YELLOW; // 蛇默认颜色为黄色
    Snake* next; // 指向链表中下一个蛇体节段的指针

    // 绘制当前蛇体节段
    void draw()
    {
        setfillcolor(YELLOW);
        solidrectangle(x, y, x + SIZE, y + SIZE); 
    }

    // head函数用于创建一个新的蛇头，并根据方向调整其位置，新蛇头颜色为红色
    // 这是蛇移动逻辑的一部分，实际上实现了蛇的头部向前移动一格
    Snake* head(int dir)
    {
        Snake* p = new Snake; // 创建新的蛇头节点
        p->color = RED; // 新蛇头颜色设为红色
        p->next = this; // 新蛇头指向当前蛇头作为其下一个节点，实现链表结构

        // 根据给定的方向计算新蛇头的位置
        switch (dir) 
        {
        case UP:
            p->x = x;
            p->y = y - SIZE;
            break;
        case DOWN:
            p->x = x;
            p->y = y + SIZE;
            break;
        case LEFT:
            p->x = x - SIZE;
            p->y = y;
            break;
        case RIGHT:
            p->x = x + SIZE;
            p->y = y;
            break;
        }

        return p; // 返回新蛇头
    }

    // tail函数用于删除链表的尾部节点，即蛇的尾部消失
    void tail(Snake* p)
    {
        free(p->next); // 释放当前尾节点的内存
        p->next = NULL; // 将当前节点设为尾节点
    }

    // eat函数处理蛇吃食物的逻辑
    // 如果蛇头位置与食物位置重合，则重新生成食物并延长蛇身；否则，蛇身缩短
    void eat(Food& f, int width, int height)
    {
        if (x == f.x && y == f.y) 
        { // 检查蛇头是否位于食物位置
            f = Food(width, height); // 重新生成食物在随机位置
        }
        else 
        { // 如果没有吃到食物，蛇需要缩短
            Snake* p = this; // 从当前节点开始遍历
            while (p->next->next) 
            { // 找到倒数第二个节点
                p = p->next;
            }
            tail(p); // 删除最后一个节点，即蛇尾部缩短
        }
    }
};

// 游戏类，包含了游戏窗口尺寸、蛇的初始方向、蛇对象、食物对象以及指向蛇链表头部的指针
class Game
{
public:
    int width = 1600, height = 800; // 游戏窗口宽度和高度
    int dir = RIGHT; // 初始移动方向为右
    Snake s; // 蛇对象实例，虽然直接实例化但未直接使用
    Food f; // 食物对象实例
    Snake* p; // 指向蛇链表头部的指针

    // 构造函数，初始化游戏状态
    Game()
    {
        p = new Snake(); // 创建蛇的首个节点
        p->x = width / 2; p->y = height / 2; // 设置蛇的初始位置为中心
        p->next = NULL; // 初始时蛇只有一个节点，next设为NULL

        f = Food(width, height); // 在游戏区域内随机生成初始食物
    }

    // 检查游戏是否结束，即蛇是否撞墙
    bool fail(Snake* pp)
    {
        if (pp->x >= width || pp->x < 0 || pp->y >= height || pp->y < 0)
            return true; // 蛇超出边界则返回true，表示游戏结束
        return false; // 否则返回false，游戏继续
    }

    // 游戏主循环，处理所有游戏逻辑
    void run()
    {
        Snake* head = p; // 当前蛇头指针
        while (true) // 无限循环直到游戏结束
        {
            // 检测键盘输入，改变蛇的移动方向，但不反向移动
            if ((GetAsyncKeyState('W') & 0x8000) && dir != DOWN) 
                dir = UP; // W键上移
            if (GetAsyncKeyState('A') & 0x8000 && dir != RIGHT) 
                dir = LEFT; // A键左移
            if (GetAsyncKeyState('S') & 0x8000 && dir != UP) 
                dir = DOWN; // S键下移
            if (GetAsyncKeyState('D') & 0x8000 && dir != LEFT) 
                dir = RIGHT; // D键右移

            cleardevice(); // 清除屏幕，准备重新绘制
            f.draw(); // 绘制食物
            head = head->head(dir); // 根据方向移动蛇头，返回新的蛇头
            if (fail(head)) // 检查蛇头是否出界
            {
                MessageBox(NULL, _T("Game Over!"), _T("GameOver"), MB_OK); // 显示游戏结束消息框
                break; // 结束游戏循环
            }
            head->eat(f, width, height); // 检查蛇是否吃到食物并相应处理
            p = head; // 更新蛇的头指针
            // 绘制蛇的所有身体部分
            while (p)
            {
                p->draw();
                p = p->next;
            }
            Sleep(80); // 控制游戏速度，每80毫秒更新一次
            // 用于延迟，以确保按键能被正确检测
            for (int i = 0; i < 150; i++) cout << " ";
        }
    }
};


int main() {
    initgraph(1600, 800);
    Game g = Game();
    g.run();
    Sleep(5000);

    return 0;
}
