#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <graphics.h>
#include <random>
#include <chrono>
#include <cmath>
#include <sstream>
using namespace std;

//雷块类
class MineBlock
{
public:
    int x, y; // 雷块位置坐标
    string imageName; // 要显示的图片名称
    int content; // -1 表示雷， 0 表示空白， 1-8 表示对应的周围雷数
    bool clicked; // 标志变量，表示是否已经被点击

    MineBlock() 
    {
        6;
    }

    MineBlock(int col, int row) 
    {
        content = 0;
        clicked = false;
        imageName = "10";
        x = col * 41;
        y = row * 41 + 100;
    }

    // 在指定坐标处(x, y)显示出图片
    void PutImage(string name, map<string, IMAGE*> Image)
    {
        imageName = name;
        putimage(x, y, Image[imageName]);
    }

    // 点击函数，更新图片和点击状态
    void Click(map<string, IMAGE*> Image) 
    { 
        if (content >= 0) {
            PutImage(to_string(content), Image);
            clicked = true;
        }
        else {
            PutImage(string("9"), Image);
        }
    }
};
 
//重启方块类
class RestartBlock
{
public:
    int x, y; // 方块坐标
    string imageName; // 要显示的图片名称

    RestartBlock(){}

    RestartBlock(int cols) 
    {
        imageName = "ReStart0";
        x = cols * 41 / 2 - 20;
        y = 30;
    }

    // 在指定坐标处(x, y)显示出图片
    void PutImage(string name, map<string, IMAGE*> Image)
    {
        imageName = name;
        putimage(x, y, Image[imageName]);
    }
};

//雷区类
class MineField
{
public:
    int rows, cols, mineNum;//行列数及雷数
    vector<vector<MineBlock>> mine_blocks; // 存放所有雷块的二维数组
    bool over;//标志变量，表示游戏是否结束
    int remainingNums;//剩余雷的数量

    MineField() {}

    MineField(int width, int height, int mines) 
    {//初始化雷区
        over = false;//将标志变量over置为flase，表示游戏未结束
        cols = width; rows = height; mineNum = mines;

        mine_blocks = vector<vector<MineBlock>>(cols, vector<MineBlock>(rows));
        for (int i = 0; i < cols; i++) 
        {
            for (int j = 0; j < rows; j++) 
            {
                mine_blocks[i][j] = MineBlock(i,j);
            }
        }

        PutMines();//随机生成雷
        CalculateMines();//计算周围雷数
    }


    //随机生成雷
    void PutMines()
    {
        int n = 0, col, row;
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 gen(seed); 
        uniform_int_distribution<> dis1(0, cols - 1); 
        uniform_int_distribution<> dis2(0, rows - 1);
        do {
            col = dis1(gen); row = dis2(gen);
            if (mine_blocks[col][row].content == 0) 
            { //防止生成重复的雷
                mine_blocks[col][row].content = -1; 
                n++; 
            }
        } while (n < mineNum);
    }

    //计算周围雷数
    void CalculateMines() 
    {
        for (int i = 0; i < cols; i++) 
        {//遍历雷区
            for (int j = 0; j < rows; j++) 
            {
                MineBlock& mine_block = mine_blocks[i][j];
                if (mine_block.content != -1) 
                {//如果不是雷，就遍历该方块所在的九宫格
                    for (int p = max(0, i - 1); p <= min(cols - 1, i + 1); p++) 
                    {
                        for (int q = max(0, j - 1); q <= min(rows - 1, j + 1); q++) 
                        {
                            //每找到一个雷，该方块的值加一
                            if (mine_blocks[p][q].content == -1) 
                                mine_block.content++;
                        }
                    }
                }
            }
        }
    }

    //游戏胜利判断
    bool Win() 
    {
        int n = cols * rows;//雷块总数
        for (int i = 0; i < cols; i++) 
        {//遍历雷区
            for (int j = 0; j < rows; j++) 
            {
                n -= (mine_blocks[i][j].clicked ? 1 : 0);//如果雷块被点击，雷块总数就减一
            }
        }
        if (n <= mineNum) 
        { //如果未被点击的雷块总数不超过总雷数
            over = true; //将游戏是否结束的标志变量改为true，即游戏结束
            return true; 
        }
        else
        {
            return false;
        }
    }

    // 标记地雷后实时更新剩余雷数
    void CalculateRemaining()
    {
        remainingNums = mineNum;//现有雷数，初值为总雷数
        for (int i = 0; i < cols; i++)
        {//遍历雷区
            for (int j = 0; j < rows; j++)
            {
                if (mine_blocks[i][j].imageName == "11") //如果雷被标记
                    remainingNums--;//雷数减一
            }
        }
    }

    // 左击
    void l_click(int col, int row, map<string, IMAGE*> Image) 
    {
        MineBlock& mine_block = mine_blocks[col][row];
        if (mine_block.content == -1) 
        {
            mine_block.Click(Image);
            over = true; 
            return;
        }
        else if (mine_block.content > 0) 
        {
            mine_block.Click(Image);
            Win(); 
            return;
        }
        else 
        {
            mine_block.Click(Image);
            for (int p = max(0, col - 1); p <= min(cols - 1, col + 1); p++) 
            {
                for (int q = max(0, row - 1); q <= min(rows - 1, row + 1); q++) 
                {
                    if (!mine_blocks[p][q].clicked)  
                        l_click(p, q, Image);
                }
            }
        }
        Win();
    }

    // 右击
    void r_click(int col, int row, map<string, IMAGE*> Image) 
    {
        if (remainingNums >= 0) 
        {
            MineBlock& mine_block = mine_blocks[col][row];
            if (mine_block.imageName == "10" && remainingNums != 0) 
            {
                mine_block.PutImage("11", Image);
                CalculateRemaining();
            }
            else if (mine_block.imageName == "11") 
            {
                mine_block.PutImage("10", Image);
                CalculateRemaining();
            }
        }
    }
};

//计时器
class Timer
{
public:
    int x, y; // 数字在屏幕上显示的坐标
    char text[30]; // 要显示的内容;
    chrono::high_resolution_clock::time_point start, end; // 开始时间和结束时间
    chrono::duration<double> duration; // 游戏时间
    int minutes, seconds;

    Timer(){}

    Timer(int cols)
    {
        x = cols * 41 / 7;
        y = 25;
        settextcolor(YELLOW);
        settextstyle(20 + cols, 0, _T("Consolas"));  // 根据雷图大小动态调整字体大小
        start = chrono::high_resolution_clock::now(); // 开始计时
    }


    // 更新时间
    void RenewTime() {
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        minutes = chrono::duration_cast<chrono::minutes>(duration).count();
        seconds = chrono::duration_cast<chrono::seconds>(duration).count() % 60;
        ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << minutes << ":";
        oss << std::setw(2) << std::setfill('0') << seconds;
        outtextxy(x, y, _T(oss.str().c_str()));
    }
};

//计数器
class Counter
{
public:
    int x, y; // 位置坐标
    char text[30]; // 要显示的内容;
    int n;//剩余雷数

    Counter(){}

    Counter(int cols) 
    {
        x = 2 * cols * 41 / 3 + 10 + cols * 2;
        y = 25;
        settextcolor(YELLOW);
        settextstyle(20 + cols, 0, _T("Consolas"));  // 根据雷图大小动态调整字体大小
    }

    // 改变剩余雷数n
    void ChangeN(int i) 
    { 
        n = i;
    }

    // 显示内容
    void Display() 
    {
        sprintf_s(text, "%d", n);
        outtextxy(x, y, _T(text));
    }
};

//地图类（包括雷区，计时器和计数器）
class Map
{
public:
    vector<string> ImageNames = { "0","1","2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "ReStartWin", "ReStartFail", "ReStart0" };
    map<string, IMAGE*> Image; // Image 是从图片名字(string)到图片指针的映射(IMAGE*)，集结了所有要显示的图片

    Map() 
    { 
        // 初始化 Image		 
        for (int i = 0; i < ImageNames.size(); i++) 
        {
            Image[ImageNames[i]] = new IMAGE;//定义图片数组
            string path = (string)"images\\" + ImageNames[i] + (string)".png"; // 使用相对路径
            loadimage(Image[ImageNames[i]], _T(path.c_str()), 40, 40);//加载图片
        }
    }

    // 画出雷区
    void displayMines(MineField& minefield)
    {
        for (int i = 0; i < minefield.cols; i++)
        {
            for (int j = 0; j < minefield.rows; j++)
            {
                minefield.mine_blocks[i][j].PutImage(minefield.mine_blocks[i][j].imageName, Image);
            }
        }

    }

    // 画出 Timer、Counter和RestartBlock
    void dispaly(MineField& minefield, Counter& count, RestartBlock& restartblock, Timer& timer) 
    {
        restartblock.PutImage(restartblock.imageName, Image);
        minefield.CalculateRemaining();
        count.ChangeN(minefield.remainingNums);
        count.Display();
        timer.RenewTime();
    }
};

class Game
{
public:
    int cols, rows, mines; //行列数和雷数
    bool over; // 游戏是否结束
    MineField mf; // 雷区
    RestartBlock rb; // 重启方块
    Timer t; // 计时器
    Counter c; // 计数器
    Map m; // 地图

    Game() 
    {
        // 确定地图大小、雷数
        do {
            cout << "请分别地图的列数、行数和雷数:";
            cin >> cols >> rows >> mines;
        } while (cols * rows < mines);

        initgraph(cols * 41, rows * 41 + 100);

        Initialize();

        // 初始化地图 m
        m = Map();
    }

    void RenewOver(bool b) 
    { // 更新 over
        over = b;
    }

    // 游戏初始化
    void Initialize() 
    {
        over = false;

        // 初始化雷区及雷块
        mf = MineField(cols, rows, mines);

        // 初始化重启方块 rb
        rb = RestartBlock(cols);

        // 初始化计时器 t
        t = Timer(cols);

        // 初始化计数器 c
        c = Counter(cols);
    }

    // 鼠标点击事件
    void play() 
    {
        if (MouseHit()) {  // 检测鼠标是否有事件发生
            MOUSEMSG msg = GetMouseMsg(); // 获取鼠标事件信息
            if (msg.y >= 100) 
            {
                if (msg.uMsg == WM_LBUTTONDOWN) 
                {  // 判断是否是左键按下事件
                    MineBlock& mine_block = mf.mine_blocks[msg.x / 41][(msg.y - 100) / 41];
                    if (mine_block.imageName != "11") 
                    {
                        mf.l_click(msg.x / 41, (msg.y - 100) / 41, m.Image);
                        RenewOver(mf.over);
                    }
                }
                else if (msg.uMsg == WM_RBUTTONDOWN) 
                {  // 判断是否是右键按下事件
                    mf.r_click(msg.x / 41, (msg.y - 100) / 41, m.Image);
                }
            }
        }
    }

    // 游戏结束后显示对应内容
    void show() 
    {
        if (mf.Win()) 
        {
            for (int i = 0; i < mf.cols; i++) 
            {
                for (int j = 0; j < mf.rows; j++) 
                {
                    MineBlock& mine_block = mf.mine_blocks[i][j];
                    if (mine_block.content == -1) mine_block.PutImage((string)"11", m.Image);
                }
            }
            rb.PutImage((string)"ReStartWin", m.Image);
            MessageBox(NULL, _T("\t You win!"), _T("GameOver"), MB_OK);
        }
        else 
        {
            for (int i = 0; i < mf.cols; i++) 
            {
                for (int j = 0; j < mf.rows; j++) 
                {
                    MineBlock& mine_block = mf.mine_blocks[i][j];
                    if (mine_block.content == -1 && mine_block.imageName != "9") 
                        mine_block.PutImage((string)"12", m.Image);
                }
            }
            rb.PutImage((string)"ReStartFail", m.Image);
            MessageBox(NULL, _T("\tBomb!GameOver!"), _T("GameOver"), MB_OK);
        }
    }

    void run() {
        m.displayMines(mf);
        while (!over) {
            // 更新 Timer、Counter和RestartBlock
            m.dispaly(mf, c, rb, t);
            // 鼠标事件处理
            play();
        }
        show();
    }

    // 重启游戏
    void reset() {
        Initialize();
        start();
    }

    void start() {
        run();

        // 游戏结束后点击 RestartBlock 重启游戏
        while (over) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) 
            {
                if ((rb.x <= msg.x && msg.x <= rb.x + 41) && (rb.y <= msg.y && msg.y <= rb.y + 41)) 
                {
                    reset();
                }
            }
        }
    }
};

int main()
{
    Game game = Game();
    game.start();
    return 0;
}