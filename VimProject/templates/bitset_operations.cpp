bitset<100> bs;

bs[2] = 1;
bs[5] = 1;
bs[10] = 1;

bs.count();
bs._Find_first(); //2
bs._Find_next(2); //5

vector<int> indexes;
for (int i = bs._Find_first(); i < bs.size(); i = bs._Find_next(i)){
    indexes.push_back(i);
}
//2, 5, 10
