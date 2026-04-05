#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <chrono>
using namespace std;//可以简化代码，不必在每个标识符前面写上 std::

class Mine 
{
public:
    int row, col; // 雷块的行号和列号
    int content = 0; // -1:有雷  0:空白  >= 1:周围雷数
    string appearance = "■"; // 雷在雷图上呈现的样子，未被点击前都为■；被点击后若为雷则变为●，周围无雷则变为□，其余的则是对应的数字(1,2,3,4.....)
    bool clicked = false; // 用于连片点开空白块(□)时避免无限递归

    Mine() {} // 默认构造函数
};

class MineMap 
{
public:
    int size, mine_num; // size：边长，mine_num：雷数
    Mine** mines; // mines是所有方块构成的二维数组，元素是对象
    bool over = false;//游戏结束标志
    int remaining;  // 剩余未被点击的方块数，用于判断是否游戏胜利

    MineMap() 
    {
        setSizeAndMines();////用户输入地图大小和雷数
        cout << "\n雷图大小：" << size << "x" << size << "  雷个数：" << mine_num << endl << endl;

        // 初始化 mines 数组
        mines = new Mine * [size];
        for (int i = 0; i < size; i++) 
        {
            mines[i] = new Mine[size];
        }
    }

    //用户输入地图大小和雷数
    void setSizeAndMines() 
    {
        int N, M;
        do {
            cout << "请输入雷图的大小（边长）和雷的数量：" << endl; cin >> N >> M;
            if (N <= 0 || M <= 0) cout << "输入数据不合理，请重新输入：\n\n";
            else if (N * N < M) cout << "雷数过大，请重新输入：\n\n";
            else { size = N; mine_num = M; }
        } while (N <= 0 || M <= 0 || N * N < M);//确保用户输入的数据合理
    }

    //初始化雷图
    void GenerateMines()
    {
        int n = 0;  // 表示已经生成的雷数，初值为0
        // 使用当前时间作为随机数生成器的种子
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        // 均匀分布的随机数生成器，范围是 [0, size - 1]
        std::uniform_int_distribution<> dis(0, size - 1);
        const int MINE = -1; // 定义雷的标记常量

        // 生成雷直到达到指定数量
        while (n < mine_num) {
            // 生成随机位置
            int row = dis(gen), col = dis(gen);
            // 获取当前位置的内容
            int& content = mines[row][col].content;
            // 如果当前位置不是雷，则标记为雷并增加雷数计数
            if (content != MINE) {
                content = MINE;
                n++;
            }
        }
    }

    // 计算每个雷块周围的雷数
    void CalculateCont()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                // 获取当前雷块
                Mine& mine = mines[i][j];
                if (mine.content == 0) // 如果当前雷块不是雷
                {
                    // 遍历当前雷块周围的8个位置
                    for (int m = max(0, i - 1); m <= min(size - 1, i + 1); m++)
                    {
                        for (int n = max(0, j - 1); n <= min(size - 1, j + 1); n++)
                        {
                            // 如果周围位置是雷，则增加当前雷块的雷数计数
                            if (mines[m][n].content == -1) mine.content++;
                        }
                    }
                }
            }
        }
    }

    //绘制地图
    void DrawMap()
    {
        // 遍历雷图的每个位置
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                // 输出雷块的外观
                cout << mines[i][j].appearance << " ";
            }
            // 换行，以便每行结束后输出
            cout << endl;
        }
    }

    // 挖雷
    void Click(int row, int col)
    {
        Mine& mine = mines[row][col]; // 获取当前点击的雷块
        string s = (mine.content >= 0 ? to_string(mine.content) : "●"); // 根据雷块内容决定显示的字符（非雷：将雷数由整型转为字符型；雷：●）
        mine.appearance = (s == "0" ? "□" : s); // 如果内容为0，则显示□，否则显示内容数字或●

        if (mine.content == -1)
        {
            over = true; // 如果点到了雷，游戏结束
            mine.clicked = true; // 设置雷块为点击状态
            return; 
        }
        else if (mine.content > 0)
        {
            mine.clicked = true; // 设置雷块为点击状态
            return;
        }
        else
        {
            // 当雷块内容为0时，展开周围的区域
            //使用两个嵌套的循环遍历当前雷块周围的区域。
            // 这个区域由以当前雷块为中心的3x3的方块组成
            //（如果当前雷块位于边缘，则会有部分方块超出边界，这里使用 max 和 min 函数确保不会越界）
            for (int i = max(row - 1, 0); i <= min(size - 1, row + 1); i++)
            {
                for (int j = max(0, col - 1); j <= min(size - 1, col + 1); j++)
                {
                    if (mines[i][j].content == 0 && !mines[i][j].clicked)
                    {//如果其内容为0并且尚未被点击过
                        mines[i][j].clicked = true; // 先置为true，再递归调用 Click
                        Click(i, j); // 递归展开该区域
                    }
                    else if (mines[i][j].content != 0)
                    {//如果周围的雷块内容不为0
                        Click(i, j); // 递归展开非0内容的雷块
                        mines[i][j].clicked = true; // 设置雷块为点击状态
                    }
                }
            }
        }
    }

    //计算剩余雷块数量，用判断是否游戏胜利
    int CalculateRemaining()
    {
        // 初始化剩余雷块数量为雷区总格数
        remaining = size * size;
        // 遍历雷区中的每个雷块
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                // 如果当前雷块已被点击，则剩余雷块数量减1
                remaining -= (mines[i][j].clicked ? 1 : 0);
            }
        }
        // 返回剩余雷块数量
        return remaining;
    }

    void Start()
    {
        // 初始化雷区
        GenerateMines();    // 生成雷区
        CalculateCont();    // 计算每个方块周围的雷数
        DrawMap();          // 绘制游戏地图

        // 主循环，直到游戏结束
        while (!over)
        {
            int row, col;
            // 循环提示用户输入合法的行号和列号，用于点击雷块
            do {
                cout << "分别输入一组正确的行号和列号以点击对应的方块（如:2 5）:";
                cin >> row >> col;
            } while (!(0 <= row && row < size && 0 <= col && col < size)); // 输入必须在雷区范围内

            // 点击雷块
            Click(row, col);

            // 检查剩余雷块数量是否等于雷数，判断游戏是否结束
            if (CalculateRemaining() == mine_num)
                over = true;

            // 如果游戏未结束，绘制更新后的游戏地图
            if (!over)
                DrawMap();
        }

        // 游戏结束，显示所有雷的位置
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (mines[i][j].content == -1)
                    mines[i][j].appearance = "●"; // 标记为雷的外观
            }
        }
        DrawMap();  // 最终绘制游戏地图

        // 判断游戏结果并输出相应信息
        if (CalculateRemaining() == mine_num)
        {
            cout << "\n\nCongratulation!You Win！\n";
        }
        else
        {
            cout << "\n\nBomb!Game over!\n";
        }
    }

};

class Game 
{
public:
    Game() 
    {
        MineMap map = MineMap();
        map.Start();
    }
};

int main() 
{
    Game game = Game();
}