def find_min(ps, sum):
    # 在节点数组中找到两个权重最小的节点
    min_weight = float('inf')
    result_l = 0
    result_r = 0
    l_subscript = 0
    r_subscript = 0

    # 查找最小权重节点
    for c in range(sum):
        if ps[c][1] < min_weight and ps[c][0] == 0:
            min_weight = ps[c][1]
            l_subscript = c

    ps[l_subscript][0] = 1
    result_l = min_weight

    min_weight = float('inf')
    # 查找次小权重节点
    for c in range(sum):
        if ps[c][1] < min_weight and ps[c][0] == 0:
            min_weight = ps[c][1]
            r_subscript = c

    ps[r_subscript][0] = 1
    result_r = min_weight

    return result_l, result_r, l_subscript, r_subscript


def main():
    num = int(input("请输入用来构建哈夫曼树的带权重的节点的个数：\n"))
    print("请输入%d个整数来表示权重(输入的数以空格分开)" % num)

    # 输入节点的权重
    weights = list(map(int, input().split()))
    ps = [[0, weight] for weight in weights]  # 初始化节点数组，每个节点包括[父节点标志, 权重]

    # 构建哈夫曼树的节点数组
    for c in range(num, 2 * num - 1):
        result_min = find_min(ps, c)
        ps.append([0, result_min[0] + result_min[1]])  # 新节点的权重为两个最小权重的和
        ps[c].extend(result_min[2:])  # 将两个最小权重节点作为新节点的子节点
        ps[result_min[2]][0] = c  # 更新两个最小权重节点的父节点标志
        ps[result_min[3]][0] = c

    # 输出每个节点的信息
    for c in range(num * 2 - 1):
        if c >= num:
            if ps[c][0] + 1 == 1:
                print("第%-2d个节点  权重为%-5d  左子节点为第%-2d个  右子节点为第%-2d个 (无父节点)" %
                      (c + 1, ps[c][1], ps[c][2] + 1, ps[c][3] + 1))
            else:
                print("第%-2d个节点  权重为%-5d  父节点为第%-2d个  左子节点为第%-2d个  右子节点为第%-2d个" %
                      (c + 1, ps[c][1], ps[c][0] + 1, ps[c][2] + 1, ps[c][3] + 1))
        else:
            print("第%-2d个节点  权重为%-5d  父节点为第%-2d个 (无左右子节点)" % (c + 1, ps[c][1], ps[c][0] + 1))


if __name__ == "__main__":
    main()