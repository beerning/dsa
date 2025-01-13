
/*构造一个斐波那契数组*/
//void Fibonacci(int* F) {
//    F[0] = 0;
//    F[1] = 1;
//    for (int i = 2;i < max_size;++i)
//        F[i] = F[i - 1] + F[i - 2];
//}

/*定义斐波那契查找法*/
//int Fibonacci_Search(int* a, int n, int key) {
//    int low = 0;
//    int high = n - 1;
//
//    int F[max_size];
//    Fibonacci(F);//构造一个斐波那契数组F
//
//    int k = 0;
//    while (n > F[k] - 1)//计算n位于斐波那契数列的位置
//        ++k;
//
//    int* temp;//将数组a扩展到F[k]-1的长度
//
//    temp = (int*)malloc(sizeof(int) * (F[k] - 1));
//    memcpy(temp, a, n * sizeof(int));
//
//    for (int i = n;i < F[k] - 1;++i)
//        temp[i] = a[n - 1];
//
//    while (low <= high) {
//        int mid = low + F[k - 1] - 1;
//        if (key < temp[mid]) {
//            high = mid - 1;
//            k -= 1;
//        }
//        else if (key > temp[mid]) {
//            low = mid + 1;
//            k -= 2;
//        }
//        else {
//            if (mid < n)
//                return mid; //若相等则说明mid即为查找到的位置
//            else
//                return n - 1; //若mid>=n则说明是扩展的数值,返回n-1
//        }
//    }
//
//    free(temp);
//    return -1;
//}
// 
// 树查找
//   基本思想：二叉查找树是先对待查找的数据进行生成树，确保树的左分支的值小于右分支的值，然后在就行和每个节点的父节点比较大小，查找最适合的范围。 这个算法的查找效率很高，但是如果使用这种查找方法要首先创建树。
//
//　　二叉查找树（BinarySearch Tree，也叫二叉搜索树，或称二叉排序树Binary Sort Tree）或者是一棵空树，或者是具有下列性质的二叉树：
//
//　　1）若任意节点的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
//
//　　2）若任意节点的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
//
//　　3）任意节点的左、右子树也分别为二叉查找树。
//
//　　二叉查找树性质：对二叉查找树进行中序遍历，即可得到有序的数列。
//　　复杂度分析：它和二分查找一样，插入和查找的时间复杂度均为O(logn)，但是在最坏的情况下仍然会有O(n)的时间复杂度.原因在于插入和删除元素的时候，树没有保持平衡（比如，我们查找上图（b）中的“93”，我们需要进行n次查找操作）。我们追求的是在最坏的情况下仍然有较好的时间复杂度，这就是平衡查找树设计的初衷。

//360面试
//-(void)printViews:(UIView *)view
//{
//    //      NSArray *viewArray=[view subviews];
//    for (id childView in [view subviews]) {
//        NSLog(@"%@",childView);
//        if ([[childView subviews] count]!=0) {
//            [self printViews:childView];
//        }
//    }
//}

//#pragma mark -分离字符串
//- (void)bnSepatareString {
//    NSString* str1 = [NSString stringWithFormat : @"%@", @"hello|world"];
//    NSArray* array = [str1 componentsSeparatedByString : @"|"];
//    for (NSString* temp in array) {
//        NSLog(@"---->%@", temp);
//    }
//}
//
//#pragma mark -移除重复字符串法一
//
//- (void)bnRemoveRepeat {
//    NSMutableString* str = [[NSMutableString alloc]initWithFormat:@"aabcadabcd"];
//
//    NSMutableArray* rpArray = [[NSMutableArray alloc]init];
//    for (int i = 0; i < str.length - 1; i++) {
//        for (int j = i + 1; j < str.length; j++) {
//            if (([str characterAtIndex : i] == [str characterAtIndex : j]) && (![rpArray containsObject : @(j)]))
//                [rpArray addObject : @(j)];
//        }
//    }
//
//    NSLog(@"rpArray:%@", rpArray);
//
//    for (int i = (int)rpArray.count - 1; i >= 0;i--) {
//        NSUInteger loc = [[rpArray objectAtIndex : i]intValue];
//        [str deleteCharactersInRange : NSMakeRange(loc, 1)] ;
//        NSLog(@"unrpStr:%@---%ld--%d", str, loc, i);
//
//    }
//    NSLog(@"unrpStr:%@", str);
//
//}
//
//#pragma  mark -移除重复字符法二
//
//- (void)bnRemoveRepeat1 {
//    NSMutableString* string = [[NSMutableString alloc]initWithFormat:@"aabcadabcd"];
//    NSMutableArray* mArr = [[NSMutableArray alloc]init];
//    for (int i = 0; i < string.length; i++) {
//        [mArr addObject : [string substringWithRange : NSMakeRange(i, 1)] ] ;
//    }
//    //    NSLog(@"%@",mArr);
//    [self removeRepeatElement : mArr] ;
//    NSLog(@"%@", mArr);
//}
//
////移除数组中重复元素
//- (NSMutableArray*)removeRepeatElement:(NSMutableArray*)mArr {
//    NSLog(@"marr=%@", mArr);
//
//    int count = (int)mArr.count;
//    for (int i = 0; i < count - 1;i++) {
//
//        for (int j = i + 1;j < count;j++) {
//            NSString* a = [mArr objectAtIndex : i];
//            NSString* b = [mArr objectAtIndex : j];
//
//            if ([a isEqualToString : b]) {
//                [mArr removeObjectAtIndex : j] ;
//                count--;
//            }
//        }
//    }
//
//    return mArr;
//}

