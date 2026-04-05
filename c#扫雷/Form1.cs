using System;
using System.Drawing;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Xml.Schema;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private NumericUpDown UpDownLength;
        private NumericUpDown UpDownBombNumbers;     // 选择型按钮用来控制雷数和大小
        private Button buttonApply;                         // 用来调整大小的按钮

        int length;                     // 游戏长度
        int bomb_numbers;               // 雷数量
        private int[,] state;           // 定义当前格子的状态 0没点过 -1右键一次 -2右键点击2次 1左键一次(这个格子就没了)
        Button[,] button_array;         // 按钮数组
        private bool[,] isBomb;         // 是否当前的格子是雷
        private int[,] numbers;         // 设置每一个格子的数字
        private Random random;          // 将 Random 实例作为类的字段(也可以在类中定义不用定义一个全局的我这里是调试出错了才改的没必要)
        Button button_re;               // 重新开始按钮

        public Form1()                  //该函数就是窗口生成时候产生的操作(相当于python中的__init__)
        {
            length = 10;                            // 该参数默认为10 * 10代表我们的大小
            bomb_numbers = 10;                      // 雷的数量
            button_re = new Button();               // 设置重新开始按钮
            button_re.Text = "Restart";                   // 重新开始的笑脸
            button_re.Left = 700;                  // 该按钮位置
            button_re.Top = 20;
            button_re.Width = 100;                   // 按钮大小
            button_re.Height = 100;
            button_re.Click += Restart;             // 按钮功能 重新开始
            this.Controls.Add(button_re);           // 添加该按钮到窗口
       
            InitializeComponent();                      // 初始化
            InitializeControls();                       // 用户初始化设置可以调整雷数和大小
            GenerateButtons(length, bomb_numbers);      // 设置按钮
            SetUpBomb(length, bomb_numbers);            // 设置雷
            Setupnumbers(length, bomb_numbers);         // 设置格子中的数字
        }
        private void SetUpBomb(int length,int bomb_numbers)     // 设置雷的状态
        {
            isBomb = new bool[length,length];           // 初始化雷的状态
            random = new Random();                      // 设置随机初始化

            List<int> allPosititions = new List<int>(); // 创建一个列表
            for(int i = 0; i < length * length; i++)      // 添加所有的位置给列表
            {
                allPosititions.Add(i);                  // 给列表添加一个数值
            }
            for(int i = 0;i < allPosititions.Count; i++) // 
            {
                int temp = allPosititions[i];                               // 记录当前值
                int randomIndex = random.Next(i, allPosititions.Count);     //选择一个随机数值
                allPosititions[i] = allPosititions[randomIndex];            // 交换操作 打乱了allPositions的数组顺序
                allPosititions[randomIndex] = temp;
            }
            for (int i = 0; i < bomb_numbers; i++)                  // 放置雷
            {
                int position = allPosititions[i];                   // 当前allpositions的顺序是混乱的 所以计算出来的索引也是随机的
                int x = position / length;
                int y = position % length;                          // 计算索引
                isBomb[x, y] = true;                                // 设置为雷
            }

        }
        private void Setupnumbers(int length,int bomb_numebrs) // 设置周围雷数
        {
            // 先设置四角然后设置四边然后设置平常格子
            numbers = new int[length, length];
            for(int i = 0;i < length; i++)
            {
                for(int j = 0;j < length; j++)
                {
                    if(i == 0 && j == 0)                                       
                    {
                        if (isBomb[i+1,j]) numbers[i, j] += 1;
                        if (isBomb[i, j + 1]) numbers[i, j] += 1;
                        if (isBomb[i + 1, j + 1]) numbers[i, j] += 1;
                    }
                    else if(i == 0 && j == length -1)
                    {
                        if (isBomb[i + 1, j]) numbers[i, j] += 1;
                        if (isBomb[i, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i + 1, j - 1]) numbers[i, j] += 1;
                    }
                    else if(i == length - 1 && j == 0)
                    {
                        if (isBomb[i - 1, j]) numbers[i, j] += 1;
                        if (isBomb[i, j + 1]) numbers[i, j] += 1;
                        if (isBomb[i - 1, j + 1]) numbers[i, j] += 1;
                    }
                    else if(i == length - 1 && j == length - 1)
                    {
                        if (isBomb[i - 1, j]) numbers[i, j] += 1;
                        if (isBomb[i, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i - 1, j - 1]) numbers[i, j] += 1;
                    }
                    else if(i == 0 && j != 0 && j != length - 1)
                    {
                        if (isBomb[i, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i + 1, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i + 1, j]) numbers[i, j] += 1;
                        if (isBomb[i + 1, j + 1]) numbers[i, j] += 1;
                        if (isBomb[i, j + 1]) numbers[i, j] += 1;
                    }
                    else if(i!= 0 && i!= length-1 && j == 0)
                    {
                        if (isBomb[i - 1, j]) numbers[i, j] += 1;
                        if (isBomb[i - 1, j + 1]) numbers[i, j] += 1;
                        if (isBomb[i, j + 1]) numbers[i, j] += 1;
                        if (isBomb[i + 1, j + 1]) numbers[i, j] += 1;
                        if (isBomb[i + 1, j]) numbers[i, j] += 1;
                    }
                    else if(i == length - 1 && j != 0 && j != length - 1)
                    {
                        if (isBomb[i, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i - 1, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i - 1, j]) numbers[i, j] += 1;
                        if (isBomb[i - 1, j + 1]) numbers[i, j] += 1;
                        if (isBomb[i, j + 1]) numbers[i, j] += 1;
                    }
                    else if(i !=  length - 1 && i != 0 && j == length - 1)
                    {
                        if (isBomb[i - 1, j]) numbers[i, j] += 1;
                        if (isBomb[i - 1, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i + 1, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i + 1, j]) numbers[i, j] += 1;
                    }
                    else
                    {
                        if (isBomb[i + 1,j]) numbers[i,j]+= 1;
                        if (isBomb[i + 1, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i + 1, j + 1]) numbers[i, j] += 1;
                        if (isBomb[i, j + 1]) numbers[i, j] += 1;
                        if (isBomb[i, j - 1]) numbers[i, j] += 1;
                        if (isBomb[i - 1, j + 1]) numbers[i, j] += 1;
                        if (isBomb[i - 1, j]) numbers[i, j] += 1;
                        if (isBomb[i - 1, j - 1]) numbers[i, j] += 1;
                    }
                }
            }
        }
        private void GenerateButtons(int length,int bomb_numbers) // 当前的生成扫雷的按钮
        {
            // 初始化这个state
            state = new int[length, length];                // 全局变量state代表当前格子的状态
            button_array = new Button[length, length];      // 初始化butttons
                                                            
            int buttonWidth = 40;                           //设置按钮的位置和大小
            int buttonHeight = 40;
            int spacing = 1;                                // 按钮之间的间隔
            int startX = 250;                               // 设置起始位置
            int startY = 100;
            // 生成按钮
            for (int i = 0; i < length; i++)                // 生成length个按钮
            {
                startX += buttonWidth + spacing;            // 每一行的间隔设置
                int cur_Y = startY;                         // 当前的Y开始,方便更改用的
                for(int j = 0;j < length; j++)
                {
                    Button button = new Button();           // 生成按钮
                    button.Width = buttonWidth;             // 设置按钮的大小
                    button.Height = buttonHeight;           // 按钮宽度 
                    button.Left = startX;                   // 起始位置设置
                    button.Top = cur_Y + (buttonHeight + spacing) * j;          // 设置高度(spacing作为间隔)
                    state[i, j] = 0;                                            // 当前的状态值初始化为0 也可以没有(为了严谨)
                    button.ContextMenuStrip = new ContextMenuStrip();           // 添加一个点击的控件,用来区分点击左键右键
                    button.Tag = new Point(i, j);           // 
                    button.MouseDown += Button_Click;       // 添加点击事件将状态传递给函数
                    button_array[i, j] = button;            // 按钮添加到当前的位置
                    this.Controls.Add(button);              // 将按钮添加到窗体上
                }
            }
        }

        private void Button_Click(object sender, MouseEventArgs e) // 点击按钮触发的操作
        {
            Button button = (Button)sender;     // 记载当前按钮
            Point index = (Point)button.Tag;    // 获取按钮的索引
            int x = index.X;                    // 获取X
            int y = index.Y;                    // 获取Y

            // 处理按钮点击事件
            if (e.Button == MouseButtons.Left) // 判断左键
            {
                if (isBomb[x,y])
                {
                    button.Enabled = false;             // 不可被点击
                    button.BackColor = Color.Red;       // 颜色
                    button.Text = "雷";                 // 雷
                    MessageBox.Show("Boom!GameOver!");      // 弹窗失败
                    Restart_bomb();                     // 重新开始(因为点到雷)
                }
                else
                {
                    AutoFilp(x,y);
                    Adjustwin();
                }
            }
            if(e.Button == MouseButtons.Right)              // 判断右键
            {
                if (state[x, y] == -2) state[x, y] = 0;  
                else state[x, y] -= 1;                      // 更新当前我们的格子的状态

                if (state[x,y] == -1)                       // 判断我们的当前格子的状态
                {
                    button.BackColor = Color.White;
                    button.Text = "🚩";                      // 雷标记
                }
                else if (state[x,y] == -2)
                {
                    button.Text = "?";                       //不确定标记
                    button.BackColor = Color.AliceBlue;
                }
                else if (state[x,y] == 0)
                {
                    button.Text = " ";
                }
            }
        }
        private void AutoFilp(int x, int y)
        {
            if (state[x,y] == 0)                            //  代表当前没被翻开(不这样设置后果就是递归出错会递归到已经翻开的牌)
            {
                if (numbers[x, y] != 0)                     //  有数字的格子不会自动翻,只翻自己
                {
                    state[x, y] += 1;                       // 更新按钮状态
                    button_array[x, y].Text = numbers[x, y].ToString();     // 格子状态被转换成当前数字
                    button_array[x, y].BackColor = Color.WhiteSmoke;       // 颜色变化成翻开状态
                    button_array[x, y].Enabled = false;                     // 无法被点击
                    return;                                                 // 如果当前格子有数字，直接返回
                }
                else
                {
                    // 如果当前格子是空白格子，翻开周围的所有空白格子和数字格子
                    state[x, y] += 1;                       // 更新按钮状态
                    button_array[x, y].BackColor = Color.Gray;
                    button_array[x, y].Enabled = false;
                    // 遍历当前格子周围的8个方向
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        for (int dy = -1; dy <= 1; dy++)
                        {
                            int nx = x + dx;                        // 当前即将递归格子的x
                            int ny = y + dy;                        // 当前即将递归格子的y
                            if (nx >= 0 && nx < length && ny >= 0 && ny < length && state[nx, ny] == 0) // 没被翻开不超边界
                            {
                                AutoFilp(nx, ny);                   // 递归翻开周围的格子
                            }
                        }
                    }
                }
            }
        }
        private void Restart(object sender, EventArgs e)
        {
            foreach (Button button in button_array)
            {
                this.Controls.Remove(button);   // 从窗体上移除按钮
                button.Dispose();               // 释放按钮资源
            }

            // 重新初始化状态信息
            state = new int[length, length];
            button_array = null;  // 清空按钮数组，等待重新生成
            GenerateButtons(length, bomb_numbers);      // 设置按钮
            SetUpBomb(length, bomb_numbers);            // 设置雷
            Setupnumbers(length, bomb_numbers);         // 设置格子中的数字
        }
        private void Restart_bomb()
        {
            foreach (Button button in button_array)
            {
                this.Controls.Remove(button);           // 从窗体上移除按钮
                button.Dispose();                       // 释放按钮资源
            }

            // 重新初始化状态信息
            state = new int[length, length];
            button_array = null;                        // 清空按钮数组，等待重新生成
            GenerateButtons(length, bomb_numbers);      // 设置按钮
            SetUpBomb(length, bomb_numbers);            // 设置雷
            Setupnumbers(length, bomb_numbers);         // 设置格子中的数字
        }
        private void Adjustwin()
        {
            int sum = 0;
            for(int i = 0; i < length; i++)
            {
                for(int j = 0;j < length; j++)
                {
                    if (state[i, j] == 1) sum++;
                }
            }
            if(sum == length*length - bomb_numbers)
            {
                MessageBox.Show("You Win!");       // 弹窗成功
                Restart_bomb();                     // 重新开始
            }
        }
        private void InitializeControls()
        {
            UpDownLength = new NumericUpDown();
            UpDownLength.Minimum = 1;                       // 最小是1
            UpDownLength.Maximum = 20;                      // 设置最大长度
            UpDownLength.Value = length;                    // 设置初始长度(10)
            UpDownLength.Location = new Point(10, 10);      // 设置位置
            this.Controls.Add(UpDownLength);                // 添加到窗口

            UpDownBombNumbers = new NumericUpDown();
            UpDownBombNumbers.Minimum = 1;
            UpDownBombNumbers.Maximum = 100;                // 设置最大雷数量(不要多于位置)
            UpDownBombNumbers.Value = bomb_numbers;         // 设置初始雷数量(10)
            UpDownBombNumbers.Location = new Point(10, 40);         // 设置位置
            this.Controls.Add(UpDownBombNumbers);

            buttonApply = new Button();
            buttonApply.Text = "Apply";                     // 重置大小按钮
            buttonApply.Location = new Point(150, 30);       // 按钮位置
            buttonApply.Click += ApplySettings;
            this.Controls.Add(buttonApply);
        }

        private void ApplySettings(object sender, EventArgs e)
        {
            // 更新游戏参数
            length = (int)UpDownLength.Value;                   // 修改值
            bomb_numbers = (int)UpDownBombNumbers.Value;        // 修改值
            Restart_bomb();                                     // 重新开始游戏
        }
    }
}
