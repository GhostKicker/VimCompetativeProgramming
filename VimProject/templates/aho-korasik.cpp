
struct node{
    //vector<int> curword;
    int pch = -1; //char by which you came there
    node* par = nullptr;
    node* link = nullptr;
    map<int, node*> sons;
    map<int, node*> go;
    bool terminal = false;
    bool goes_to_terminal = false;
};
const int maxnodes = 100 * 1000 + 10;
node nodes[maxnodes];
node* nodeptr = nodes+1;

void add_word(vector<int>& w){
    node* v = nodes;
    for (auto& c : w){
        if (v->sons.count(c) == 0) v->sons[c] = nodeptr++; //if no such son, add
        v->sons[c]->pch = c; //setting parent character
        v->sons[c]->par = v; //setting parent pointer
        //v->sons[c]->curword = v->curword;
        //v->sons[c]->curword.push_back(c);
        v = v->sons[c]; //moving to son
    }
    v->terminal = true;
}

node* getSuffLink(node* v);
node* getLink(node* v, int c);
node* getSuffLink(node* v){ //suffix link
    if (v->link) return v->link; //if calced, return
    if (v == nodes || v->par == nodes) return v->link = nodes; //if root or near root, return root
    return v->link = getLink(getSuffLink(v->par), v->pch); //get suff link from parent
}
node* getLink(node* v, int c){ //transfer function
    if (v->go.count(c)) return v->go[c]; //if calced, return
    if (v->sons.count(c)) return v->go[c] = v->sons[c]; //if there is son, return
    if (v == nodes) return v->go[c] = nodes;
    return v->go[c] = getLink(getSuffLink(v), c);
}

void set_terminals(node* v){
    node* sl = getSuffLink(v);
    if (sl->terminal) v->goes_to_terminal = true;
    if (sl->goes_to_terminal) v->goes_to_terminal = true;
}

void init_corasik(vector<vector<int>>& words){

    nodeptr = nodes + 1;
    fill(nodes, nodes + maxnodes, node());
    for (auto& it : words) add_word(it);

    queue<node*> q;
    q.push(nodes);
    while(q.size()){
        node* v = q.front();
        q.pop();
        getSuffLink(v);
        set_terminals(v);
        for (auto& it : v->sons)
            q.push(it.second);
    }
}

