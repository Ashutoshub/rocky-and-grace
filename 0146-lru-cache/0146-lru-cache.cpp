class LRUCache {
private:
    struct Node{
        int key;
        int val;
        Node* next;
        Node* prev;
        Node(int k, int v) : key(k),val(v),next(nullptr), prev(nullptr) {}
    };
    int capacity;
    unordered_map<int, Node*> cacheMap;
    Node* head;
    Node* tail;
    void addNode(Node* node){
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    void removeNode(Node* node){
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }
    void moveToHead(Node* node){
        removeNode(node);
        addNode(node);
    }
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if(cacheMap.find(key) != cacheMap.end()){
            Node* node = cacheMap[key];
            moveToHead(node);
            return node->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(cacheMap.find(key) != cacheMap.end()){
            Node* node = cacheMap[key];
            node->val = value;
            moveToHead(node);
        }
        else{
            Node* newNode = new Node(key, value);
            cacheMap[key] = newNode;
            addNode(newNode);
            if(cacheMap.size() > capacity){
                Node* lru = tail->prev;
                cacheMap.erase(lru->key);
                removeNode(lru);
                delete lru;
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */