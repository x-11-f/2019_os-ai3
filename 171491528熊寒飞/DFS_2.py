class Node():
    # 构建一个节点类
    def __init__(self, data=-1):
        self.data = data
        self.left = None
        self.right = None


class Tree():
    # 构建一个树类
    def __init__(self):
        self.root = Node()#定义根节点

    def add(self, data):
        # 给树加入节点
        node = Node(data)
        if self.root.data == -1:  # 如果树为空，就对根节点赋值
            self.root = node
        else:
            myQueue = []
            treeNode = self.root
            myQueue.append(treeNode)#向myqueue添加树节点元素
            while myQueue:  # 对已有的节点进行遍历
                treeNode = myQueue.pop(0)
                if not treeNode.left:#无有左子树
                    treeNode.left = node
                    return
                elif not treeNode.right:#无右子树
                    treeNode.right = node
                    return
                else:
                    myQueue.append(treeNode.left)
                    myQueue.append(treeNode.right)



    def DFS_STACK(self, root):  # 基于栈数据结构实现的深度遍历
        if root == None:
            return
        stack = []
        stack.append(root)
        while stack:
            now_node = stack.pop()
            print(now_node.data)
            if now_node.right != None:#右边没有节点了，则添加当前的这个最右节点
                stack.append(now_node.right)
            if now_node.left != None:
                stack.append(now_node.left)
                
if __name__ == '__main__':
    # 主函数
    datas = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    tree = Tree()  # 新建一个树对象
    for data in datas:
        tree.add(data)  # 逐个加入树的节点

    print('递归实现深度优先遍历：')
    tree.DFS_STACK(tree.root)