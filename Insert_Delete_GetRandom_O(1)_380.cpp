设计一个支持在平均 时间复杂度 O(1) 下，执行以下操作的数据结构。

insert(val)：当元素 val 不存在时，向集合中插入该项。
remove(val)：元素 val 存在时，从集合中移除该项。
getRandom：随机返回现有集合中的一项。每个元素应该有相同的概率被返回。
示例 :

// 初始化一个空的集合。
RandomizedSet randomSet = new RandomizedSet();

// 向集合中插入 1 。返回 true 表示 1 被成功地插入。
randomSet.insert(1);

// 返回 false ，表示集合中不存在 2 。
randomSet.remove(2);

// 向集合中插入 2 。返回 true 。集合现在包含 [1,2] 。
randomSet.insert(2);

// getRandom 应随机返回 1 或 2 。
randomSet.getRandom();

// 从集合中移除 1 ，返回 true 。集合现在包含 [2] 。
randomSet.remove(1);

// 2 已在集合中，所以返回 false 。
randomSet.insert(2);

// 由于 2 是集合中唯一的数字，getRandom 总是返回 2 。
randomSet.getRandom();

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insert-delete-getrandom-o1
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


/*
常数时间查找、插入、删除元素，应采用哈希表
随机返回一项，应采用数组，但是考虑到数组与哈希表结合后，在哈希表中删除元素后，数组也需要删除元素，
这样就无法保证删除时间复杂度O(1). 所以问题的关键在于怎样在常数时间删除数组中元素。显然数组的删除
操作通常是线性时间复杂度，但是特定情况下可以达到常数时间复杂度，那就是从尾部删除元素。但是哈希表
中插入的元素并不都是在尾部，所以要想到数组的删除可以采用覆盖法来做。将待删除元素的值用尾部元素覆盖，
然后删除尾部元素即可。
综上，我们把元素的值存储在vector中，哈希表中保存插入值在vector中的下标索引。这样就建立了二者的联系。
数据结构上，哈希表采用unordered_map即可，因为插入操作不会插入相同元素。
*/

class RandomizedSet {
private:
    unordered_map<int,int> m_table; // key: 待插入元素值 data: 元素值在vector中的下标索引
    vector<int> m_vec; 
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(m_table.find(val)==m_table.end()) {
            m_vec.push_back(val);
            m_table[val] = m_vec.size()-1;
            return true;
        }

        return false;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(m_table.find(val)!=m_table.end()) {
            int index = m_table[val];
            m_table[m_vec.back()] = index; 
            m_table.erase(val);
            m_vec[index] = m_vec.back();
            m_vec.pop_back();
            // 注意修改vector原来尾部元素在map中的值
            // 不能写在这个位置，如果删除的是最后一个元素，这里等于再次插入了该元素
            // m_table[m_vec[index]] = index;     
            return true;
        }

        return false;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        //srand(rand()); 
        //采用srand(time(0))出错。可能与time(0)有关
        
        int index = m_vec.empty() ? 0 : rand() % m_vec.size();
        return m_vec[index];
        
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
